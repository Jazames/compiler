#include <iostream>
#include <string>
#include "symbol_table.hpp"
#include "utils.hpp"
#include "types.hpp"

extern int yyparse();

int main()
{

  //Output header information.
  std::cout << "#Header\n";
  std::cout << ".globl main\n" << ".text\n" << "main:\n";
  std::cout << "la $gp, GlobalArea\n\n"; //Perhaps this needs to be removed? 

  //Setup Symbol Table. 
  SymbolTable& sym_tab = SymbolTable::getInstance();
  //Get scope ready for predefined things
  sym_tab.enterScope();
  SimpleType* intType    = new SimpleType("integer");
  SimpleType* charType   = new SimpleType("char");   
  SimpleType* boolType   = new SimpleType("boolean");
  SimpleType* stringType = new SimpleType("string"); 

  sym_tab.addType("integer", intType);
  sym_tab.addType("INTEGER", intType);

  sym_tab.addType("char", charType);
  sym_tab.addType("CHAR", charType);


  sym_tab.addType("boolean", boolType);
  sym_tab.addType("BOOLEAN", boolType);


  sym_tab.addType("string", stringType);
  sym_tab.addType("STRING", stringType);

  sym_tab.addVariableConstant("true", boolType->getTypeID(), 1);
  sym_tab.addVariableConstant("TRUE", boolType->getTypeID(), 1);

  sym_tab.addVariableConstant("false", boolType->getTypeID(), 0);
  sym_tab.addVariableConstant("FALSE", boolType->getTypeID(), 0);

  //Get scope ready for global things
  sym_tab.enterScope();


  yyparse();

  std::cout << "#terminate program\n";
  std::cout << "li $v0, 10\nsyscall\n\n";
  std::cout << ".data\n.align 4\n\n";
  sym_tab.emitLiterals();
  std::cout << ".align 4\nGlobalArea:\n\n";

  delete(intType);
  delete(charType);
  delete(boolType);
  delete(stringType);

  exit(0);
};
