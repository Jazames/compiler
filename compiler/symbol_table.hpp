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

struct StringLiteral
{
  std::string name;
  std::string literal;
};

class SymbolTable
{
public:
  static SymbolTable& getInstance() {static SymbolTable instance; return instance;}
	void incrementLineNumber() {line_number++;}
	int getLineNumber() {return line_number;}
  void emitLiterals();
  bool addVariableSymbol(std::string name);
  VariableSymbol retrieveVariableSymbol(std::string name);
private:
	int line_number;
  std::vector<TypeSymbol> type_symbol_table;
  std::vector<VariableSymbol> variable_symbol_table;
  std::vector<StringLiteral> literal_table;
  SymbolTable() : line_number(1) {}
  ~SymbolTable() {}

};


#endif
