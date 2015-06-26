#ifndef ALLOC_H
#define ALLOC_H

#include <cstdlib>

namespace TinySTL{
	class alloc{
	private:
		enum EAlign{ALIGN = 8};                                              //小型区块的上调边界
		enum EMaxBytes{MAXBYTES = 128};                                      //小型区块的上限，超过区块由malloc分配
		enum ENFreeLists{NFREELISTS = (EMaxBytes::MAXBYTES / EAlign::ALIGN)};//free-lists的个数
		enum ENObjs{NOBJS = 20};                                             //每次增加的区块数
	private:
		//free-list节点
		union obj{
			union obj* next;
			char clien[1];
		};
		static obj* free_list[ENFreeLists::NFREELISTS];
	private:
		static char* start_free;//内存池起始位置
		static char* end_free;  //内存池结束位置
		static size_t heap_size;//堆大小
	private:
		//将bytes上调至8的倍数
		static size_t ROUND_UP(size_t bytes){
			return ((bytes + EAlign::ALIGN - 1) & ~(EAlign::ALIGN - 1));
		}
		//根据需求大小，决定使用第n个free-list，n从0开始计算
		static size_t FREELIST_INDEX(size_t bytes){
			return ((bytes + EAlign::ALIGN - 1) / (EAlign::ALIGN - 1));
		}
		//free-list没有可用区块时，将从内存池申请获得新的区块（由chunk_alloc完成）
		//返回一个区块给调用者，并可能在此free-list中新增一定数量新的区块
		static void *refill(size_t n);
		//从内存池取一大块空间，可容纳nobjs个大小为size的区块
		//如果配置nobjs个区块有所不便，则nobjs会减少
		static char* chunk_alloc(size_t size, size_t& nobjs);
	public:
		static void *allocate(size_t bytes);
		static void deallocate(void *ptr, size_t bytes);
		static void *reallocate(void *ptr, size_t old_size, size_t new_size);
	};

	char *alloc::start_free = 0;
	char *alloc::end_free = 0;
	size_t alloc::heap_size = 0;
	alloc::obj *alloc::free_list[alloc::ENFreeLists::NFREELISTS] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};//end of class alloc
	
	void *alloc::allocate(size_t bytes){
		if(bytes > EMaxBytes::MAXBYTES){
			//调用第一级配置器
			return malloc(bytes);
		}
		size_t index = FREELIST_INDEX(bytes);
		obj *list = free_list[index];
		if(list){
			//此list还有空间
			//申请一个区块，即从list中删除一个区块
			free_list[index] = list->next;
			return list;
		} else {
			//此list没有足够空间，则从内存池中取空间
			return refill(ROUND_UP(bytes));
		}
	}
	void alloc::deallocate(void *ptr, size_t bytes){
		if(bytes > EMaxBytes::MAXBYTES){
			//调用第一级配置器
			free(ptr);
		} else {
			//回收一个区块，即往list中新增一个区块
			size_t index = FREELIST_INDEX(bytes);
			obj *node = static_cast<obj*>(ptr);
			node->next = free_list[index];
			free_list[index] = node;
		}
	}
	void *alloc::reallocate(void *ptr, size_t old_size, size_t new_size){
		deallocate(ptr, old_size);
		ptr = allocate(new_size);
		return ptr;
	}
	//返回一个大小为bytes的区块，并且可能会为list新增区块
	//bytes已经上调至8的倍数
	void *alloc::refill(size_t bytes){
		size_t nobjs = ENObjs::NOBJS;
		
		char* chunk = chunk_alloc(bytes, nobjs);//内存池中取
		obj *result = 0;
		obj *current_obj = 0, *next_obj = 0;
		obj **my_free_list = 0;
		
		if(nobjs == 1){
			//取出的空间只有一个区块大小
			return chunk;
		} else {
			//将多余的区块加入到list中
			my_free_list = free_list + FREELIST_INDEX(bytes);
			result = (obj*)chunk;
			*my_free_list = next_obj = (obj*)(chunk + bytes);
			for(int i = 1; ; i++){
				current_obj = next_obj;
				next_obj = (obj*)((char*)next_obj + bytes);
				if(nobjs - 1 == i){
					current_obj->next = 0;
					break;
				} else {
					current_obj->next = next_obj;
				}
			}
			return result;
		}
	}
	//从内存池中去空间给free-list使用
	//bytes已经上调至8的倍数
	char *alloc::chunk_alloc(size_t bytes, size_t &nobjs){
		char* result = 0;
		size_t total_bytes = bytes * nobjs;
		size_t bytes_left = end_free - start_free;

		if(bytes_left >= total_bytes){
			//内存池剩余空间可以满足需求
			result = start_free;
			start_free = start_free + total_bytes;
			return result;
		} else if(bytes_left >= bytes){
			//内存池空间不能完全满足需求，但可以满足一个或以上的区块
			nobjs = bytes_left / bytes;
			total_bytes = nobjs * bytes;
			result = start_free;
			start_free = start_free + total_bytes;
			return result;
		} else {
			//内存池连一个区块大小都无法满足
			size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
			if(bytes_left > 0){
				//让内存池的残余零头，先配给适当的list
				obj **my_free_list = free_list + FREELIST_INDEX(bytes_left);
				((obj*)start_free)->next = *my_free_list;
				*my_free_list = (obj*)start_free;
			}
			//配置heap空间，用于补充内存池
			start_free = (char*)malloc(bytes_to_get);
			if(!start_free){
				//heap空间不足，malloc失败
				//遍历free-list，寻找可用区块，进行回收
				obj **my_free_list = 0;
				obj *p = 0;
				for(int i = 0; i < EMaxBytes::MAXBYTES; i += EAlign::ALIGN){
					my_free_list = free_list + FREELIST_INDEX(i);
					p = *my_free_list;
					if(p){
						//释放出未用区块
						*my_free_list = p->next;
						start_free = (char*)p;
						end_free = start_free + i;
						//递归调用自己，为了修正nobjs
						return chunk_alloc(bytes, nobjs);
					}
				}
				//到处都没有内存可用
				end_free = 0;
			}
			heap_size += bytes_to_get;
			end_free = start_free + bytes_to_get;
			//递归调用自己，为了修正nobjs
			return chunk_alloc(bytes, nobjs);
		}
	}
}
#endif