
#include "utils.hpp"


std::string getNewWhileBeginLabel() {return "whileBegin" + std::to_string(while_begin_next_label++);}
std::string getNewWhileEndLabel() {return "whileEnd" + std::to_string(while_end_next_label++);}
std::string getNewStringLabel() {return "nonCollidingStringLabel" + std::to_string(string_next_label++);}

int while_begin_next_label; 
int while_end_next_label; 
int string_next_label;


RegisterPool::RegisterPool() : pool_size(10), register_pool()
{
	register_pool.reserve(pool_size);
	for(int i = 0; i < pool_size; i++)
	{
		register_pool[i] = 0;
	}
}
RegisterPool::RegisterPool(int size) : pool_size(size), register_pool()
{
	register_pool.reserve(pool_size);
	for(int i = 0; i < pool_size; i++)
	{
		register_pool[i] = 0;
	}
}

Register RegisterPool::getRegister()
{
	for(int i = 0; i < pool_size; i++)
	{
		if(register_pool[i] == 0)
		{
			char* ptr = register_pool.data() + (i);
			return Register(ptr, i);
		}
	}
	std::cerr << "ERROR: Ran out of Registers." << std::endl;
}
