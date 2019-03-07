
#include "utils.hpp"



RegisterPool::RegisterPool() : pool_size(10), register_pool()
{
	register_pool.reserve(pool_size);
	for(int i = 0; i < pool_size; i++)
	{
		register_pool[i] = false;
	}
}
RegisterPool::RegisterPool(int size) : pool_size(size), register_pool()
{
	register_pool.reserve(pool_size);
	for(int i = 0; i < pool_size; i++)
	{
		register_pool[i] = false;
	}
}

Register RegisterPool::getRegister()
{
	for(int i = 0; i < pool_size; i++)
	{
		if(!register_pool[i])
		{
			return Register(&(register_pool[i]), i);
		}
	}
	std::cerr << "ERROR: Ran out of Registers." 
}
