#include "LinearAllocator.h"
#include "Game.h"
#include <iostream>

LinearAllocator::LinearAllocator(void* ptr, const size_t size)
{
	// TODO ここを適切に実装してください
	p = ptr;
	s = size;
	r_s = s; //使用していないメモリサイズ
	Info* allocator_Info = reinterpret_cast<Info*>(p);
	allocator_Info->head_ptr = p;
	allocator_Info->size = r_s - s;
	allocator_Info->use = false;
	allocator_Info->next = nullptr;
}

void* LinearAllocator::Alloc(const size_t size)
{
	// TODO ここを適切に実装してください
	if (size + sizeof(struct Info) > this->s)
	{
		return nullptr;
	}
	Info* p_Info = reinterpret_cast<Info*>(p);
	Info* p_next=nullptr;
	while (true)
	{
		p_next = reinterpret_cast<Info*>(p_Info->next);
		if (p_Info->use == false)
		{
			if (p_Info->size > sizeof(struct Info) + size)
			{
				if (r_s - (size + sizeof(struct Info)) < 0)
				{
					return nullptr;
				}
				p_Info->head_ptr = (void*)(reinterpret_cast<std::uintptr_t>(p_Info) + sizeof(Info));
				p_Info->size = size + sizeof(struct Info);
				p_Info->use = true;
				p_Info->next = reinterpret_cast<Info*>(reinterpret_cast<std::uintptr_t>(p_Info->head_ptr) + size);
				r_s = r_s - p_Info->size;
				p_next->head_ptr = (void*)(reinterpret_cast<std::uintptr_t>(p_next) + sizeof(Info));
				p_next->size = r_s;
				p_next->use = false;
				p_next->next = nullptr;
				return p_Info->head_ptr;
			}
		}
		p_Info = p_next;
		if (p_Info == nullptr)
		{
			return nullptr;
		}

	}
}

void LinearAllocator::Free(void* ptr)
{
	// TODO ここを適切に実装してください
	if (ptr == nullptr) return;
	Info* p_Info = reinterpret_cast<Info*>(p);
	Info* p_next=nullptr;
	Info* p_prev=nullptr;
	while (true)
	{
		p_next = reinterpret_cast<Info*>(p_Info->next);

		if (p_Info->use == true)
		{
			if (p_Info->head_ptr == ptr)
			{
				p_Info->use = false;
				break;
			}
		}
		if ((p_Info == nullptr))
		{
			return;
		}
		p_prev = reinterpret_cast<Info*>(p_Info);
		p_Info = p_next;
	}
	if (p_prev && (p_prev->use == false))
	{
		p_prev->size += p_Info->size + sizeof(Info);
		p_prev->next = p_Info->next;
		p_Info = p_prev;
	}
	if (p_next && (p_next->use == false))
	{
		p_Info->size += p_next->size + sizeof(Info);
		p_Info->next = p_next->next;
	}
}