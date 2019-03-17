
#ifndef UTILS_HPP
#define UTILS_HPP


#include<vector>
#include<string>
#include<iostream>


class Register
{
public:
	Register(char* inUse, int name) : inUse(inUse), name(name) {*inUse = 1;}
	~Register() {*inUse = 0;}
	std::string getAsm() {return "$t" + std::to_string(name);}
	void printAsm() {std::cout << "$t" << name;}
private:
	char* inUse;
	const int name;
};

class RegisterPool
{
public:
	Register getRegister();
	static RegisterPool& getInstance() {static RegisterPool instance; return instance;}
private:
	RegisterPool();
	RegisterPool(int size);
	~RegisterPool() {}
	std::vector<char> register_pool;
	const int pool_size;
};



extern int while_begin_next_label; 
extern int while_end_next_label; 
extern int string_next_label;

std::string getNewWhileBeginLabel();// {return "whileBegin" + std::to_string(while_begin_next_label++);}
std::string getNewWhileEndLabel();// {return "whileEnd" + std::to_string(while_end_next_label++);}
std::string getNewStringLabel();// {return "nonCollidingStringLabel" + std::to_string(string_next_label++);}

/*
class LabelMaker
{
public:
	//LabelMaker() {}
	//~LabelMaker() {}
	static std::string getNewWhileBeginLabel() {return "whileBegin" + std::to_string(while_begin_next_label++);}
	static std::string getNewWhileEndLabel() {return "whileEnd" + std::to_string(while_end_next_label++);}
	static std::string getNewStringLabel() {return "nonCollidingStringLabel" + std::to_string(string_next_label++);}
private:
	static int while_begin_next_label; 
	static int while_end_next_label; 
	static int string_next_label;
};
*/

#endif
