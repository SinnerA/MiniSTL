#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <cstdlib>

namespace TinySTL{
	class alloc{
	private:
		enum EAlign{ALIGN = 8};                                              //С��������ϵ��߽�
		enum EMaxBytes{MAXBYTES = 128};                                      //С����������ޣ�����������malloc����
		enum ENFreeLists{NFREELISTS = (alloc::MAXBYTES / alloc::ALIGN)};     //free-lists�ĸ���
		enum ENObjs{NOBJS = 20};                                             //ÿ�����ӵ�������
	private:
		//free-list�ڵ�
		union obj{
			union obj* next;
			char clien[1];
		};
		static obj* free_list[alloc::NFREELISTS];
	private:
		static char* start_free;//�ڴ����ʼλ��
		static char* end_free;  //�ڴ�ؽ���λ��
		static size_t heap_size;//�Ѵ�С
	private:
		//��bytes�ϵ���8�ı���
		static size_t ROUND_UP(size_t bytes){
			return ((bytes + alloc::ALIGN - 1) & ~(alloc::ALIGN - 1));
		}
		//���������С������ʹ�õ�n��free-list��n��0��ʼ����
		static size_t FREELIST_INDEX(size_t bytes){
			return ((bytes + alloc::ALIGN - 1) / (alloc::ALIGN - 1));
		}
		//free-listû�п�������ʱ�������ڴ���������µ����飨��chunk_alloc��ɣ�
		//����һ������������ߣ��������ڴ�free-list������һ�������µ�����
		static void *refill(size_t n);
		//���ڴ��ȡһ���ռ䣬������nobjs����СΪsize������
		//�������nobjs�������������㣬��nobjs�����
		static char* chunk_alloc(size_t size, size_t& nobjs);
	public:
		static void *allocate(size_t bytes);
		static void deallocate(void *ptr, size_t bytes);
		static void *reallocate(void *ptr, size_t old_size, size_t new_size);
	};
}
#endif