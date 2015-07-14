#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <cstdlib>

namespace TinySTL{
	class alloc{
	private:
		enum EAlign{ALIGN = 8};                                              //小型区块的上调边界
		enum EMaxBytes{MAXBYTES = 128};                                      //小型区块的上限，超过区块由malloc分配
		enum ENFreeLists{NFREELISTS = (alloc::MAXBYTES / alloc::ALIGN)};     //free-lists的个数
		enum ENObjs{NOBJS = 20};                                             //每次增加的区块数
	private:
		//free-list节点
		union obj{
			union obj* next;
			char clien[1];
		};
		static obj* free_list[alloc::NFREELISTS];
	private:
		static char* start_free;//内存池起始位置
		static char* end_free;  //内存池结束位置
		static size_t heap_size;//堆大小
	private:
		//将bytes上调至8的倍数
		static size_t ROUND_UP(size_t bytes){
			return ((bytes + alloc::ALIGN - 1) & ~(alloc::ALIGN - 1));
		}
		//根据需求大小，决定使用第n个free-list，n从0开始计算
		static size_t FREELIST_INDEX(size_t bytes){
			return ((bytes + alloc::ALIGN - 1) / (alloc::ALIGN - 1));
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
}
#endif