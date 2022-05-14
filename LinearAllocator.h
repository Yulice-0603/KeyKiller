#pragma once

#include <cstdint>
#include "iMemoryAllocator.h"
#include "Actor.h"
#include "EnemyL.h"
#include "EnemyR.h"
#include "Boss.h"
#include "Player.h"
struct Info
{
	void* head_ptr;
	size_t size;
	bool use;
	Info* next;
	
};

class LinearAllocator : public iMemoryAllocator
{
public:
	LinearAllocator(void* ptr, const size_t size);
	virtual ~LinearAllocator() {};

	void* Alloc(const size_t size); 
	void Free(void* ptr);

private:
	// TODO Ç±Ç±ÇìKêÿÇ…é¿ëïÇµÇƒÇ≠ÇæÇ≥Ç¢
	void* p; 
	size_t s;
	size_t r_s;
};
