
#include "utils.hpp"


static int fake_name;
static int while_begin_next_label; 
static int while_end_next_label; 
static int string_next_label;
static int if_end_next_label;
static int else_if_next_label;
static int repeat_next_lablel;
static int for_next_label;

std::string getNameForAnon() {return "_fakeName" + std::to_string(fake_name++);}
std::string getNewWhileBeginLabel() {return "_whileBegin" + std::to_string(while_begin_next_label++);}
std::string getNewWhileEndLabel() {return "_whileEnd" + std::to_string(while_end_next_label++);}
std::string getNewStringLabel() {return "_nonCollidingStringLabel" + std::to_string(string_next_label++);}
std::string getNewIfEndLabel() {return "_IfEndLabel" + std::to_string(if_end_next_label++);}
std::string getNewElseIfLabel() {return "_ElseIfLabel" + std::to_string(else_if_next_label++);}
std::string getNewRepeatLabel() {return "_RepeatLabel" + std::to_string(repeat_next_lablel++);}
std::string getNewForLabel() {return "_ForLabel" + std::to_string(for_next_label++);}



std::string Register::getAsm() 
{
	if(isSaved)
	{
		return "$s" + std::to_string(name);
	}
	else
	{
		return "$t" + std::to_string(name);
	}
}
void Register::printAsm() 
{
	if(isSaved)
	{
		std::cout << "$s" << name;
	}
	else
	{
		std::cout << "$t" << name;
	}
}


RegisterPool::RegisterPool() : pool_size(10), saved_pool_size(8), register_pool(), saved_register_pool()
{
	register_pool.reserve(pool_size);
	for(int i = 0; i < pool_size; i++)
	{
		register_pool[i] = 0;
	}
	saved_register_pool.reserve(saved_pool_size);
	for(int i = 0; i < saved_pool_size; i++)
	{
		saved_register_pool[i] = 0;
	}
}
RegisterPool::RegisterPool(int size) : pool_size(size), saved_pool_size(8), register_pool(), saved_register_pool()
{
	register_pool.reserve(pool_size);
	for(int i = 0; i < pool_size; i++)
	{
		register_pool[i] = 0;
	}
}

Register* RegisterPool::getRegister()
{
	for(int i = 0; i < pool_size; i++)
	{
		if(register_pool[i] == 0)
		{
			char* ptr = register_pool.data() + (i);
			return new Register(ptr, i, false); //Better not leak this!
		}
	}
	for(int i = 0; i < saved_pool_size; i++)
	{
		if(saved_register_pool[i] == 0)
		{
			char* ptr = saved_register_pool.data() + (i);
			return new Register(ptr, i, true); //Better not leak this!
		}
	}

	std::cerr << "ERROR: Ran out of Registers." << std::endl;
	exit(0);
}


std::vector<std::string> RegisterPool::getUsedRegisters()
{
	std::vector<std::string> used_regs;
	for(int i = 0; i < pool_size; i++)
	{
		if(register_pool[i] != 0)
		{
			used_regs.push_back("$t" + std::to_string(i));
		}
	}
	for(int i = 0; i < saved_pool_size; i++)
	{
		if(saved_register_pool[i] != 0)
		{
			used_regs.push_back("$s" + std::to_string(i));
		}
	}
	return used_regs;
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




void pushRegs(std::vector<std::string> regs, int stackAdjustment)
{
  for(int i = 0; i < regs.size(); i++)
  {
    std::cout << "sw " << regs[i] << ", " << stackAdjustment - 12 - (i * 4) << "($sp)    #Save register\n";
  }
}

void popRegs(std::vector<std::string> regs, int stackAdjustment)
{
  for(int i = 0; i < regs.size(); i++)
  {
    std::cout << "lw " << regs[i] << ", " << stackAdjustment - 12 - (i * 4) << "($sp)    #Load register\n";
  }
}