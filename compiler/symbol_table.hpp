#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <string>
#include <vector>
#include <map>



//TODO: make this a proper class. 
class Type
{
public:
  int getSize();
private:
  int size; 
};

//TODO: turn this into a proper class. 
class Variable
{
public:
  std::string getType() {return type;}
  bool isConst() {return is_const;}
private:
  std::string name;
  int gp_offset;
  bool is_const;
  std::string type; 
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
  bool addType(std::string name);
  bool addVariable(std::string name);
  Variable retrieveVariableSymbol(std::string name);
  Type retrieveTypeSymbol(std::string name);
  int enterScope();
  bool addStringLiteral(std::string name, std::string string);
private:
	int line_number;
  int current_scope;
  std::vector<std::map<std::string, Type> > type_symbol_table;
  std::vector<std::map<std::string, Variable> > variable_symbol_table;
  std::map<std::string, std::string> literal_table;
  SymbolTable() : line_number(1), current_scope(0) {}
  ~SymbolTable() {}

};


#endif
