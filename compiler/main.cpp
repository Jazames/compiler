#include <iostream>
#include "symbol_table.hpp"

extern int yyparse();

int main()
{
  //Setup Symbol Table. 
  SymbolTable& sym_tab = SymbolTable::getInstance();
  sym_tab.enterScope();
  //Add predefined stuff. 
  //sym_tab.addType();

  //sym_tab.addVariable();

  //Get scope ready for next 
  sym_tab.enterScope();

  //Output header information.
  std::cout << "#Header\n";
  std::cout << ".globl main\n" << ".text\n" << "main:\n";
  std::cout << "la $gp, GlobalArea\n"; //Perhaps this needs to be removed? 

  yyparse();

  std::cout << "#terminate program\n";
  std::cout << "li $v0, 10\nsyscall\n";
  std::cout << ".data\n";
  sym_tab.emitLiterals();
  std::cout << "GlobalArea:\n";
};
