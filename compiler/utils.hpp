
#ifndef UTILS_HPP
#define UTILS_HPP


#include<vector>
#include<string>
#include<iostream>


class Register
{
public:
	Register(char* inUse, int name, bool isSaved) : inUse(inUse), name(name), isSaved(isSaved) {*inUse = 1;}
	~Register() {*inUse = 0;}
	std::string getAsm();
	void printAsm();
private:
	char* inUse;
	const int name;
	bool isSaved;
};

class RegisterPool
{
public:
	Register* getRegister();
	static RegisterPool& getInstance() {static RegisterPool instance; return instance;}
	void print() {for(int i=0;i<register_pool.size();i++){std::cout << i << ":" << register_pool[i] << "\n";}}
	std::vector<std::string> getUsedRegisters();
private:
	RegisterPool();
	RegisterPool(int size);
	~RegisterPool() {}
	std::vector<char> register_pool;
	std::vector<char> saved_register_pool;
	const int pool_size;
	const int saved_pool_size;
};



//Useful Functions
//extern int while_begin_next_label; 
//extern int while_end_next_label; 
//extern int string_next_label;

std::string getNameForAnon();
std::string getNewWhileBeginLabel();// {return "whileBegin" + std::to_string(while_begin_next_label++);}
std::string getNewWhileEndLabel();// {return "whileEnd" + std::to_string(while_end_next_label++);}
std::string getNewStringLabel();// {return "nonCollidingStringLabel" + std::to_string(string_next_label++);}
std::string getNewIfEndLabel();
std::string getNewElseIfLabel();
std::string getNewRepeatLabel();
std::string getNewForLabel();

//Helper Functions
char charStringToChar(std::string s_val);

bool typeIsInt(std::string type);
bool typeIsString(std::string type);
bool typeIsChar(std::string type);
bool typeIsBool(std::string type);
bool typeIsArithmetic(std::string type);

void pushRegs(std::vector<std::string> regs, int stackAdjustment);
void popRegs(std::vector<std::string> regs, int stackAdjustment);
#endif
