

#include <iostream>
#include <string>
#include "tree.hpp"
#include "utils.hpp"





//Class Functions





//Header file functions

void addVarsToSymbolTable(IdentList* identList, Parse_Type* type)
{
	SymbolTable& sym_tab = SymbolTable::getInstance();
	std::string typeID = type->getTypeID();
	for(int i = 0; i < identList->getSize(); i++)
	{
		sym_tab.addVariable(identList->get(i), typeID);
	}
}


