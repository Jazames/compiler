

#include <iostream>
#include <string>
#include "tree.hpp"
#include "utils.hpp"





//Class Functions


//Header file functions

void addVarsToSymbolTable(IdentList* identList, Type* type)
{
	SymbolTable& sym_tab = SymbolTable::getInstance();
	std::string typeID = type->getTypeID();
	for(int i = 0; i < identList->getSize(); i++)
	{
		sym_tab.addVariable(identList->get(i), typeID);
	}
}



void addConstantToSymbolTable(std::string id, Expression* e)
{
  if(e->isConst())
  {
    if(typeIsString(e->getType()))
    {
      LiteralExpr* le = dynamic_cast<LiteralExpr*>(e);
      SymbolTable::getInstance().addStringConstant(id, "string", le->getStringValue());

    }
    else
    {
      SymbolTable::getInstance().addVariableConstant(id, e->getType(), e->getValue());
    }
  }
  else
  {
    std::cerr << "Syntax Error: Cannot declare a constant with a non-constant expression." << std::endl;
    exit(0);
  }
}
