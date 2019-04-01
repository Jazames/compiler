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
  SimpleType* intType    = new SimpleType("integer", 4);
  SimpleType* charType   = new SimpleType("char", 4);   
  SimpleType* boolType   = new SimpleType("boolean", 4);
  SimpleType* stringType = new SimpleType("string", 4); 

  sym_tab.addType("integer", intType);
  sym_tab.addType("INTEGER", intType);

  sym_tab.addType("char", charType);
  sym_tab.addType("CHAR", charType);

  sym_tab.addType("boolean", boolType);
  sym_tab.addType("BOOLEAN", boolType);

  sym_tab.addType("string", stringType);
  sym_tab.addType("STRING", stringType);


  //std::cerr << "About to add constants. " << std::endl;

  sym_tab.addVariableConstant("true", "boolean", 1);
  sym_tab.addVariableConstant("TRUE", "boolean", 1);

  sym_tab.addVariableConstant("false", "boolean", 0);
  sym_tab.addVariableConstant("FALSE", "boolean", 0);

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
