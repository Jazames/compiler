

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



void createProcedure(std::string id, FormalParameters* params, Body* body)
{
  std::cout << id << ":    #start of function\n";



  SymbolTable& sym_tab = SymbolTable::getInstance();
  int size = 0;
  int variable_number = 0;

  if(params != nullptr)
  {
    //Put vars in symbol table. But do it backwards, so that the positions match the expression list. 
    for(int i = params->params.size() -1; i >= 0; i--)
    {
      //addVarsToSymbolTable(params->params[i]->ident_list, params->params[i]->type); 

      //Add parameters to the symbol table. 
      std::string typeID = params->params[i]->type->getTypeID(); //sym_tab.retrieveTypeSymbol(type->getTypeID())->getTypeID();//type->getTypeID();
      for(int j = params->params[i]->ident_list->getSize() - 1; j >= 0; j--)
      {
        sym_tab.addVariableWithOffset(params->params[i]->ident_list->get(j), typeID, (size));
        size += params->params[i]->type->getSize();

        //put information about parameters into some table about the function, because it's needed whenever there's a function call with a ref type. 
        sym_tab.addParamIsRefToFunction(id, params->params[i]->isRef, variable_number++);
      }
    }
  }

  //Increase stack pointer the size of local variables. 

  body->emit();

  //Decrease stack pointer the size of local variables. 


  std::cout << "jr $ra      # Return control\n";
}


void createFunction(std::string id, FormalParameters* params, Type* type, Body* body)
{
  std::cout << id << ":    #start of function\n";



  SymbolTable& sym_tab = SymbolTable::getInstance();
  int size = 0;
  int variable_number = 0;
  if(params != nullptr)
  {
    //Put vars in symbol table. But do it backwards, so that the positions match the expression list. 
    for(int i = params->params.size() -1; i >= 0; i--)
    {
      //addVarsToSymbolTable(params->params[i]->ident_list, params->params[i]->type); 

      //Add parameters to the symbol table. 
      std::string typeID = params->params[i]->type->getTypeID(); //sym_tab.retrieveTypeSymbol(type->getTypeID())->getTypeID();//type->getTypeID();
      for(int j = params->params[i]->ident_list->getSize() - 1; j >= 0; j--)
      {
        sym_tab.addVariableWithOffset(params->params[i]->ident_list->get(j), typeID, (size));
        size += params->params[i]->type->getSize();

        //put information about parameters into some table about the function, because it's needed whenever there's a function call with a ref type. 
        sym_tab.addParamIsRefToFunction(id, params->params[i]->isRef, variable_number++);
      }
    }
  }

  //Set address offset of return value for function. 
  sym_tab.setFunctionReturnOffset(size); //TODO: Possibly need to be able to return things that are not 4 bytes. 
  sym_tab.setFunction(id);
  sym_tab.setFunctionType(id, type->getTypeID());//Possibly need to look this up in the symbol table? 

  //Increase stack pointer the size of local variables. 
  int local_var_size = 0;
  VarDeclList* var_list = body->getVarList();
  if(var_list != nullptr)
  {
    for(int i = 0; i < var_list->variable_decls.size(); i++)
    {
      int type_size = var_list->variable_decls[i]->ident_list->getSize();
      local_var_size += type_size * var_list->variable_decls[i]->type->getSize();
    }
  }

  std::cout << "addi $sp, $sp, " << -local_var_size << "      #Increase stack for local variables\n";

  body->emit();

  std::cout << "_" << id << ":       #End of function " << id << "\n";
  //Decrease stack pointer the size of local variables. 
  std::cout << "addi $sp, $sp, " << local_var_size << "      #Decrease stack used for local variables\n";

  std::cout << "jr $ra      # Return control\n";
}