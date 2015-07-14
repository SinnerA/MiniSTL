#include "../Alloc.h"

namespace TinySTL{
	char *alloc::start_free = 0;
	char *alloc::end_free = 0;
	size_t alloc::heap_size = 0;
	alloc::obj *alloc::free_list[alloc::NFREELISTS] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};//end of class alloc
	
	void *alloc::allocate(size_t bytes){
		if(bytes > alloc::MAXBYTES){
			//���õ�һ��������
			return malloc(bytes);
		}
		size_t index = FREELIST_INDEX(bytes);
		obj *list = free_list[index];
		if(list){
			//��list���пռ�
			//����һ�����飬����list��ɾ��һ������
			free_list[index] = list->next;
			return list;
		} else {
			//��listû���㹻�ռ䣬����ڴ����ȡ�ռ�
			return refill(ROUND_UP(bytes));
		}
	}
	void alloc::deallocate(void *ptr, size_t bytes){
		if(bytes > alloc::MAXBYTES){
			//���õ�һ��������
			free(ptr);
		} else {
			//����һ�����飬����list������һ������
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
	//����һ����СΪbytes�����飬���ҿ��ܻ�Ϊlist��������
	//bytes�Ѿ��ϵ���8�ı���
	void *alloc::refill(size_t bytes){
		size_t nobjs = alloc::NOBJS;
		
		char* chunk = chunk_alloc(bytes, nobjs);//�ڴ����ȡ
		obj *result = 0;
		obj *current_obj = 0, *next_obj = 0;
		obj **my_free_list = 0;
		
		if(nobjs == 1){
			//ȡ���Ŀռ�ֻ��һ�������С
			return chunk;
		} else {
			//�������������뵽list��
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
	//���ڴ����ȥ�ռ��free-listʹ��
	//bytes�Ѿ��ϵ���8�ı���
	char *alloc::chunk_alloc(size_t bytes, size_t &nobjs){
		char* result = 0;
		size_t total_bytes = bytes * nobjs;
		size_t bytes_left = end_free - start_free;

		if(bytes_left >= total_bytes){
			//�ڴ��ʣ��ռ������������
			result = start_free;
			start_free = start_free + total_bytes;
			return result;
		} else if(bytes_left >= bytes){
			//�ڴ�ؿռ䲻����ȫ�������󣬵���������һ�������ϵ�����
			nobjs = bytes_left / bytes;
			total_bytes = nobjs * bytes;
			result = start_free;
			start_free = start_free + total_bytes;
			return result;
		} else {
			//�ڴ����һ�������С���޷�����
			size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
			if(bytes_left > 0){
				//���ڴ�صĲ�����ͷ��������ʵ���list
				obj **my_free_list = free_list + FREELIST_INDEX(bytes_left);
				((obj*)start_free)->next = *my_free_list;
				*my_free_list = (obj*)start_free;
			}
			//����heap�ռ䣬���ڲ����ڴ��
			start_free = (char*)malloc(bytes_to_get);
			if(!start_free){
				//heap�ռ䲻�㣬mallocʧ��
				//����free-list��Ѱ�ҿ������飬���л���
				obj **my_free_list = 0;
				obj *p = 0;
				for(int i = 0; i < alloc::MAXBYTES; i += alloc::ALIGN){
					my_free_list = free_list + FREELIST_INDEX(i);
					p = *my_free_list;
					if(p){
						//�ͷų�δ������
						*my_free_list = p->next;
						start_free = (char*)p;
						end_free = start_free + i;
						//�ݹ�����Լ���Ϊ������nobjs
						return chunk_alloc(bytes, nobjs);
					}
				}
				//������û���ڴ����
				end_free = 0;
			}
			heap_size += bytes_to_get;
			end_free = start_free + bytes_to_get;
			//�ݹ�����Լ���Ϊ������nobjs
			return chunk_alloc(bytes, nobjs);
		}
	}
}