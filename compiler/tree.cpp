

#include <iostream>
#include <string>
#include "tree.hpp"
#include "utils.hpp"



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

//Class Functions


AddExpr::AddExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) 
{
	if(!typeIsArithmetic(l->getType()) || !typeIsArithmetic(r->getType()))
	{
		std::cerr << "Syntax Error: Attempting to perform arithmetic on non-arithmetic types: "
		<< l->getType() << " and " << r->getType() << " at line number: "
			<< SymbolTable::getInstance().getLineNumber() << std::endl;
	}
}

Reg AddExpr::emit()
{
	if(isConst())
	{
		Reg regName = RegisterPool::getInstance().getRegister().getAsm();
		Value val = l->getValue() + r->getValue();
		std::cout << "li " << regName << ", " << val << "      # Put Literal " << val << " into register.\n";
		return regName;
	}
	else
	{
		Reg lreg = l->emit();
		Reg rreg = r->emit();
		Reg sumReg = RegisterPool::getInstance().getRegister().getAsm();
		std::cout << "addi " << sumReg << ", " << lreg << ", " << rreg << "      #Add two registers.\n";
		return sumReg;
	}
}

Value AddExpr::getValue() 
{
	if(isConst())
	{
		return l->getValue() + r->getValue();
	}
}	

std::string AddExpr::getType()
{
	if(r->getType() == l->getType())
	{
		return r->getType();
	}
}


LiteralExpr::LiteralExpr(Value val, std::string type) : Expression(), val(val), type(type) 
{
	
}


LiteralExpr::LiteralExpr(std::string value, std::string type) : Expression(), val(charStringToChar(value)), s_val(value), type(type) 
{
	//
	if(typeIsChar(type))
	{
		//std::cerr << "DEBUG: Character Literal found: " << s_val << std::endl;
		//val = charStringToChar(s_val);
		//std::cout << "DEBUG: Character is: " << (char)val << std::endl;
	}
	if(typeIsString(type))
	{
		//std::cerr << "DEBUG: String literal found: " << s_val << std::endl;
	}
}



Reg LiteralExpr::emit()
{
	if (typeIsString(type)) //Rearrange this. 
	{
		Reg regName = RegisterPool::getInstance().getRegister().getAsm();
		//Create a non-colliding name, and add it to the list of strings, and put them in the .data field. 
		std::string label = getNewStringLabel();
		SymbolTable::getInstance().addStringLiteral(label, s_val);
		std::cout << "la " << regName << ", " << label << "      # Put Address of String Literal into register.\n";
		return regName;
	}
	else //Should be good for integers, chars, and booleans. Maybe?
	{
		Reg regName = RegisterPool::getInstance().getRegister().getAsm();
		std::cout << "li " << regName << ", " << val << "      # Put Literal " << val << " into register.\n";
		return regName;
	}
}

Value LiteralExpr::getValue()
{
	return val;
}

std::string LiteralExpr::getType() 
{
	return type;
}

Write::Write(ExpressionList* el)
{
	for(int i = 0; i < el->size(); i++)
	{
		expression_list.push_back(el->get(i));
	}
}

void Write::emit()
{
	//TODO: put checks to see if expression methods are null, and if so, fail or something. 	
	std::cout << "#Write Statement\n";
	for(int i = 0; i < expression_list.size(); i++)
	{
		if(typeIsInt(expression_list[i]->getType()) || typeIsBool(expression_list[i]->getType())) 
		{	
			Reg regName = expression_list[i]->emit();
			std::cout << "ori $a0, " << regName << " 0\n";
			std::cout << "li $v0, 1\nsyscall\n";
		}
		else if(typeIsChar(expression_list[i]->getType()))
		{
			Reg regName = expression_list[i]->emit();
			std::cout << "ori $a0, " << regName << " 0\n";
			std::cout << "li $v0, 11\nsyscall\n";
		}
		else if(typeIsString(expression_list[i]->getType()))
		{
			Reg regName = expression_list[i]->emit();
			std::cout << "ori $a0, " << regName << " 0\n";
			std::cout << "li $v0, 4\nsyscall\n";
		}
		else
		{
			std::cerr << "Syntax Error, trying to print out a user-defined type." << std::endl;
		}
	}
	std::cout << "\n";
	

	//Once it's all cleaned up, deallocate the memory. 
}
