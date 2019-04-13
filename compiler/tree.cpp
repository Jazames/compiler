

#include <iostream>
#include <string>
#include "tree.hpp"
#include "utils.hpp"





//Class Functions



//Header file functions

void addDeclarations(ConstantDeclList* constant_decl_list, TypeDeclList* type_decl_list, VarDeclList* var_decl_list)
{
  std::cerr << "Adding Declarations" << std::endl;
  
  if(constant_decl_list != nullptr)
  {
    std::cerr << "Adding Constant Declarations" << std::endl;
    for(int i = 0; i < constant_decl_list->constant_decls.size(); i++)
    {
      std::string id = constant_decl_list->constant_decls[i]->id;
      Expression* e = constant_decl_list->constant_decls[i]->e;
      addConstantToSymbolTable(id, e);
    }
  } 

  if(type_decl_list != nullptr)
  {
    std::cerr << "Adding Type Declarations" << std::endl;
    for(int i = 0; i < type_decl_list->type_decls.size(); i++)
    {
      std::string id = type_decl_list->type_decls[i]->id;
      Type* type = type_decl_list->type_decls[i]->type;
      SymbolTable::getInstance().addType(id, type);
    }
  }

  if(var_decl_list != NULL)
  {
    std::cerr << "Adding Variable Declarations" << std::endl;
    for(int i = 0; i < var_decl_list->variable_decls.size(); i++)
    {
      IdentList* ident = var_decl_list->variable_decls[i]->ident_list;
      Type* type = var_decl_list->variable_decls[i]->type;
      addVarsToSymbolTable(ident, type);
    }
  }
  else
  {
    std::cerr << "VarDeclList is null" << std::endl;
  }
  std::cerr << "Finished adding declarations" << std::endl;
}


void addVarsToSymbolTable(IdentList* identList, Type* type)
{
	SymbolTable& sym_tab = SymbolTable::getInstance();
	std::string typeID = type->getTypeID(); //sym_tab.retrieveTypeSymbol(type->getTypeID())->getTypeID();//type->getTypeID();
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



void createProcedure(std::string id, FormalParameters* params, Block* body)
{
  std::cout << id << ":    #start of function\n";

  SymbolTable& sym_tab = SymbolTable::getInstance();
  int size = 0;
  int variable_number = 0;
  for(int i = params->params.size() -1; i >= 0; i--)
  {
    //addVarsToSymbolTable(params->params[i]->ident_list, params->params[i]->type);

    //Add parameters to the symbol table. 
    std::string typeID = params->params[i]->type->getTypeID(); //sym_tab.retrieveTypeSymbol(type->getTypeID())->getTypeID();//type->getTypeID();
    for(int j = params->params[i]->ident_list->getSize() - 1; j >= 0; j--)
    {
      sym_tab.addVariableWithOffset(params->params[i]->ident_list->get(j), typeID, (size)); //This is probably sufficient. Hopefully. 
      size += params->params[i]->type->getSize();//Get the size first so that we're properly far from the frame pointer. 
      //TODO: put information about parameters into some table about the function, because it's needed whenever there's a function call with a ref type. 
      sym_tab.addParamIsRefToFunction(id, params->params[i]->isRef, variable_number++);
    }
  }

  body->emit();

  //Todo Copy return value into right place? 

  std::cout << "jr $ra      # Return control\n";
}