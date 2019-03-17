#include"symbol_table.hpp"

#include<iostream>



bool SymbolTable::addStringLiteral(std::string name, std::string string)
{
  literal_table.insert(std::pair<std::string, std::string>(name,string));

  return true;
}


void SymbolTable::emitLiterals()
{
  std::cout << "#String Literals\n";
  //Example: 
  //    str: .asciiz "the answer = "
  for (auto it=literal_table.begin(); it!=literal_table.end(); ++it)
  {
    //std::cout << it->first << " => " << it->second << '\n';
    std::cout << it->first << ": .asciiz " << it->second << "\n";
  }
}

int SymbolTable::enterScope()
{
  type_symbol_table.push_back(std::map<std::string, Type>());
  variable_symbol_table.push_back(std::map<std::string, Variable>());

  return variable_symbol_table.size();
}