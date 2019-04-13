#include"symbol_table.hpp"
#include"leaves.hpp"
#include"expressions.hpp"
#include"statements.hpp"

#include<iostream>



bool SymbolTable::addStringLiteral(std::string name, std::string string)
{
  literal_table.insert(std::pair<std::string, std::string>(name,string));
  return true;
}

bool SymbolTable::addVariable(std::string name, std::string type)
{
  if(variable_symbol_table.size() > 2)
  {
    current_local_offset -= retrieveTypeSymbol(type)->getSize();
    Variable variable(false, type, current_local_offset, 0);
    variable_symbol_table[variable_symbol_table.size()-1][name] = variable;
  }
  else
  {
    Variable variable(false, type, current_global_offset, 0);
    current_global_offset += retrieveTypeSymbol(type)->getSize();
    variable_symbol_table[variable_symbol_table.size()-1][name] = variable;
  }
  return true;
}

bool SymbolTable::addVariableConstant(std::string name, std::string type, ConstValue value)
{
  Variable variable;
  if(variable_symbol_table.size() > 2)
  {
    variable = Variable(true, type, current_local_offset, value);
    current_local_offset -= retrieveTypeSymbol(type)->getSize();
  }
  else
  {
    variable = Variable(true, type, current_global_offset, value);
    current_global_offset += retrieveTypeSymbol(type)->getSize();
  }
  variable_symbol_table[variable_symbol_table.size()-1][name] = variable;

  Register* reg = RegisterPool::getInstance().getRegister();
  std::string address = getVariableAddress(name);
  std::cout << "li " << reg->getAsm() << ", " << value   << "      #Put constant value: " << value << " into register\n";
  std::cout << "sw " << reg->getAsm() << ", " << address << "      #Store value at address of constant: " << name <<"\n\n";
  delete(reg);
  return true;
}

Variable SymbolTable::retrieveVariableSymbol(std::string id)
{
  return retrieveVariableSymbolAndScope(id).second;
}

bool SymbolTable::addType(std::string name, Type* type)
{
  //std::cerr << "adding type: " << name << std::endl;
  type_symbol_table[type_symbol_table.size()-1][name] = type;
}

Type* SymbolTable::retrieveTypeSymbol(std::string id)
{
  for(auto iter = type_symbol_table.rbegin(); iter != type_symbol_table.rend(); ++iter)
  {
    auto found = iter->find(id);
    if(found != iter->end()) 
    {
      return found->second;
    }
  }
  std::cerr << "Error: Undefined Type ID: " << id << std::endl;
  exit(0);
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
  type_symbol_table.push_back(std::map<std::string, Type*>());
  variable_symbol_table.push_back(std::map<std::string, Variable>());
  current_local_offset = 0;//TODO: Make this a stack that can push and pop.
  return variable_symbol_table.size();
}

int SymbolTable::leaveScope()
{
  type_symbol_table.pop_back();
  variable_symbol_table.pop_back();
  current_local_offset = 0;//TODO: Make this a stack that can be pushed and popped. 
  return variable_symbol_table.size();
}

std::string SymbolTable::getVariableAddress(std::string name)
{
  auto variableAndScope = retrieveVariableSymbolAndScope(name);
  if(variableAndScope.first < 2) //That means it's global scope.
  {
    return std::to_string(variableAndScope.second.getOffset()) + "($gp)";
  }
  else //Else it's local scope. 
  {
    return std::to_string(variableAndScope.second.getOffset()) + "($fp)";
  }
}

std::pair<int, std::string> SymbolTable::getVariableOffsetAndBase(std::string name)
{
  auto variableAndScope = retrieveVariableSymbolAndScope(name);
  if(variableAndScope.first < 2) //That means it's global scope.
  {
    return std::pair<int, std::string>(variableAndScope.second.getOffset(), "$gp");
  }
  else //Else it's local scope. 
  {
    return std::pair<int, std::string>(variableAndScope.second.getOffset(), "$fp");
  }
}


std::string SymbolTable::getVariableAddressWithOffset(std::string name, int offset)
{
  auto variableAndScope = retrieveVariableSymbolAndScope(name);
  if(variableAndScope.first < 2) //That means it's global scope.
  {
    return std::to_string(variableAndScope.second.getOffset() + offset) + "($gp)";
  }
  else //Else it's local scope. 
  {
    return std::to_string(variableAndScope.second.getOffset() + offset) + "($fp)";
  }
}

bool SymbolTable::addStringConstant(std::string id, std::string type, std::string string_value)
{
  Variable variable;
  if(variable_symbol_table.size() > 2)
  {
    variable = Variable(true, type, current_local_offset, 0);
    current_local_offset -= retrieveTypeSymbol(type)->getSize();
  }
  else
  {
    variable = Variable(true, type, current_global_offset, 0);
    current_global_offset += retrieveTypeSymbol(type)->getSize();
  }
  std::string label = getNewStringLabel();
  addStringLiteral(label, string_value);

  variable.setStringLabel(label);
  variable_symbol_table[variable_symbol_table.size()-1][id] = variable;

  return true;
}

bool SymbolTable::doesVariableExist(std::string id)
{
  int scope = variable_symbol_table.size() - 1;
  for(auto iter = variable_symbol_table.rbegin(); iter != variable_symbol_table.rend(); ++iter)
  {
    auto found = iter->find(id);
    if(found != iter->end()) 
    {
      return true;
    }
    scope--;
  }
  return false;
}

std::string SymbolTable::retrieveFunctionType(std::string id)
{
  //TODO: make this do soemthing real
  return "integer";
}

void SymbolTable::addFunction(std::string function)
{
  //function_map[function] = 
}

void SymbolTable::addParamIsRefToFunction(std::string function, bool isRef, int param_position)
{
  function_map[function][param_position] = isRef;
}

bool SymbolTable::getParamIsRefOfFunction(std::string function, int param_position)
{
  return function_map[function][param_position];
}

bool SymbolTable::addVariableWithOffset(std::string name, std::string type, int fp_offset)
{
  Variable variable(false, type, fp_offset, 0);
  variable_symbol_table[variable_symbol_table.size()-1][name] = variable;
  return true;
}


std::pair<int,Variable> SymbolTable::retrieveVariableSymbolAndScope(std::string id)
{
  int scope = variable_symbol_table.size() - 1;
  for(auto iter = variable_symbol_table.rbegin(); iter != variable_symbol_table.rend(); ++iter)
  {
    auto found = iter->find(id);
    if(found != iter->end()) 
    {
      return std::pair<int, Variable>(scope,found->second);
    }
    scope--;
  }
  std::cerr << "Error: Undefined Variable ID: " << id << std::endl;
  //throw "undefined id";
  exit(0);
}
