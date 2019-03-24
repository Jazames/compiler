
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

//Helper Functions
char charStringToChar(std::string s_val)
{
	if(s_val[1] == '\\')
	{
		switch(s_val[2])
		{
			case 'n':
			return '\n';
			case 'r':
			return '\r';
			case 'b':
			return '\b';
			case 't':
			return '\t';
			case 'f':
			return '\f';
			default:
			return s_val[2];
		}
	}
	else
	{
		return s_val[1];
	}
}

bool typeIsInt(std::string type)
{
	return type.compare("integer") == 0 || type.compare("INTEGER") == 0;
}
bool typeIsString(std::string type)
{
	return type.compare("string") == 0 || type.compare("STRING") == 0;
}
bool typeIsChar(std::string type)
{
	return type.compare("char") == 0 || type.compare("CHAR") == 0;
}
bool typeIsBool(std::string type)
{
	return type.compare("boolean") == 0 || type.compare("BOOLEAN") == 0;
}
bool typeIsArithmetic(std::string type)
{
	return typeIsInt(type) || typeIsChar(type) || typeIsBool(type);
}