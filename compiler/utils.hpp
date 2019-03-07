
#ifndef UTILS_HPP
#define UTILS_HPP


#include<vector>
#include<string>
#include<iostream>
#include<error> 


class Register
{
public:
	Register(bool* inUse, int name) : inUse(inUse), name(name) {*inUse = true;}
	~Register() {*inUse = false;}
	std::string getAsm() {return "$t" + std::to_string(name);}
	void printAsm() {std::cout << "$t" << name;}
private:
	bool* inUse;
	const int name;
}

class RegisterPool
{
public:
	RegisterPool();
	RegisterPool(int size);
	~RegisterPool() {}
	Register getRegister();
private:
	std::vector<bool> register_pool;
	const int pool_size;
}



	
class LabelMaker
{
public:
	LabelMaker() : while_begin_next_label(0), while_end_next_label(0) {}
	~LabelMaker() {}
	std::string getNewWhileBeginLabel() {return "whileBegin" + std::to_string(while_begin_next_label++);}
	std::string getNewWhileEndLabel() {return "whileEnd" + std::to_string(while_end_next_label++);}
private:
	static int while_begin_next_label; 
	static int while_end_next_label; 
}


#endif
