#include <iostream>
#include "symbol_table.hpp"

extern int yyparse();

int main()
{
  //Output header information.
  std::cout << "#Header\n";
  std::cout << ".globl main\n" << ".text\n" << "main:\n";
  std::cout << "la $gp, GlobalArea\n"; //Perhaps this needs to be removed? 

  yyparse();

  std::cout << "#terminate program\n";
  std::cout << "li $v0, 10\nsyscall\n";
  std::cout << ".data\n";
  SymbolTable::getInstance().emitLiterals();
  std::cout << "GlobalArea:\n";
};
