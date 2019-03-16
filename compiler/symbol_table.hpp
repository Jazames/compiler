#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <string>
#include <vector>
#include <map>



struct VariableSymbol
{
  std::string name;
  int gp_offset;
};

struct TypeSymbol
{
  std::string name;
};

class SymbolTable
{
public:
  static SymbolTable& getInstance() {static SymbolTable instance; return instance;}
	void incrementLineNumber() {line_number++;}
	int getLineNumber() {return line_number;}
private:
	int line_number;
  std::vector<TypeSymbol> type_symbol_table;
  std::vector<VariableSymbol> variable_symbol_table;


};


#endif
