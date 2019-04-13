#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <string>
#include <vector>
#include <map>
#include "leaves.hpp"


using ConstValue = int;

class Variable
{
public:
  Variable() : is_const(false), type(""), gp_offset(0) {}
  Variable(bool is_const, std::string type, int gp_offset, int value) : is_const(is_const), type(type), gp_offset(gp_offset), value(value) {}
  std::string getType() {return type;}
  bool isConst() {return is_const;}
  int getOffset() {return gp_offset;}
  std::string getStringLabel() {return string_label;}
  void setStringLabel(std::string s) {string_label = s;}
  int getValue() {return value;}
private:
  //std::string name;
  int gp_offset;
  int value; //Only to be used if constant. 
  bool is_const;
  std::string type; 
  std::string string_label;
};

class SymbolTable//Will also store local variables in here, but those will be offset from the frame pointer. 
{
public:
  static SymbolTable& getInstance() {static SymbolTable instance; return instance;}
	void incrementLineNumber() {line_number++;}
	int getLineNumber() {return line_number;}
  void emitLiterals();
  bool addType(std::string name, Type* type);
  //bool addPredefinedType(std::string name, )
  bool addVariable(std::string name, std::string type);
  bool addVariableConstant(std::string name, std::string type, ConstValue value);
  Variable retrieveVariableSymbol(std::string name);
  Type* retrieveTypeSymbol(std::string name);
  int enterScope();
  int leaveScope();
  bool addStringLiteral(std::string name, std::string string);
  std::string getVariableAddress(std::string name);
  std::string getVariableAddressWithOffset(std::string name, int offset);
  bool addStringConstant(std::string id, std::string type, std::string string_value);
  std::pair<int, std::string> getVariableOffsetAndBase(std::string name);
  bool doesVariableExist(std::string id);
  std::string retrieveFunctionType(std::string id);
  void addFunction(std::string function);
  void addParamIsRefToFunction(std::string function, bool isRef, int param_position);
  bool getParamIsRefOfFunction(std::string function, int param_position);
  bool addVariableWithOffset(std::string name, std::string type, int fp_offset);
  void setFunctionReturnOffset(int offset);
  int getFunctionReturnOffset();
  void setFunctionType(std::string function, std::string type);
  std::string getFunctionType(std::string function);
  void setFunction(std::string id) {current_function_id = id;}
  std::string getFunction() {return current_function_id;}
private:
	int line_number;
  //int current_scope;
  int current_global_offset;
  int current_local_offset;
  int function_return_offset;
  std::string current_function_id;
  std::pair<int,Variable> retrieveVariableSymbolAndScope(std::string name);
  std::vector<std::map<std::string, Type*> > type_symbol_table;
  std::vector<std::map<std::string, Variable> > variable_symbol_table;
  std::map<std::string, std::string> literal_table;

  std::map<std::string, std::map<int, bool> > function_map;
  std::map<std::string, std::string> function_type_map;

  SymbolTable() : line_number(1), current_global_offset(0), current_local_offset(0), function_return_offset(0) {}
  ~SymbolTable() {}
};


#endif
