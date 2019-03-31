#include "leaves.hpp"

#include "symbol_table.hpp"

std::string IdentLValue::getType()
{
  return SymbolTable::getInstance().retrieveVariableSymbol(id).getType();
}