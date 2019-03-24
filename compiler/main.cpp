#include <iostream>
#include <string>
#include "symbol_table.hpp"
#include "utils.hpp"

extern int yyparse();

int main()
{

  //Output header information.
  std::cout << "#Header\n";
  std::cout << ".globl main\n" << ".text\n" << "main:\n\n";
  //std::cout << "la $gp, GlobalArea\n"; //Perhaps this needs to be removed? 

  //Setup Symbol Table. 
  SymbolTable& sym_tab = SymbolTable::getInstance();
  //Get scope ready for predefined things
  sym_tab.enterScope();
  Type intType(4);
  Type charType(4);
  Type boolType(4);
  Type stringType(4);//Todo wut? 

  sym_tab.addType("integer", intType);
  sym_tab.addType("INTEGER", intType);

  sym_tab.addType("char", charType);
  sym_tab.addType("CHAR", charType);


  sym_tab.addType("boolean", boolType);
  sym_tab.addType("BOOLEAN", boolType);


  sym_tab.addType("string", stringType);
  sym_tab.addType("STRING", stringType);

  sym_tab.addVariableConstant("true", "boolean", 1);
  sym_tab.addVariableConstant("TRUE", "boolean", 1);

  sym_tab.addVariableConstant("false", "boolean", 0);
  sym_tab.addVariableConstant("FALSE", "boolean", 0);

  //Get scope ready for global things
  sym_tab.enterScope();


  yyparse();

  std::cout << "#terminate program\n";
  std::cout << "li $v0, 10\nsyscall\n\n";
  std::cout << ".data\n\n";
  sym_tab.emitLiterals();
  std::cout << "GlobalArea:\n\n";
};
