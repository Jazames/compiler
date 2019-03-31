
#include "types.hpp"




int getConstValue(Expression* e)
{
  if(e == nullptr)
  {
    std::cerr << "Error: Given null expression at line number ";
    std::cerr << SymbolTable::getInstance().getLineNumber() << std::endl;
    exit(0);
  }
  if(e->isConst())
  {
    return e->getValue();
  }
  else
  {
    std::cerr << "Syntax Error: Given non-constant expression at line number ";
    std::cerr << SymbolTable::getInstance().getLineNumber() << std::endl;
    exit(0);
  }
}

//Array type

//member variables
  //std::string typeID;
  //int lb;
  //int ub;
  //Type* baseType;

ArrayType::ArrayType(Expression* lb, Expression* ub, Type* baseType) 
  : Type(), baseType(baseType), lb(getConstValue(lb)), ub(getConstValue(ub))
{

}

int ArrayType::getSize()
{
  return (ub - lb) * SymbolTable::getInstance().retrieveTypeSymbol(baseType->getTypeID())->getSize();
}


int ArrayType::getAddressOffsetOfElement(int position)
{
  return (position - lb) * SymbolTable::getInstance().retrieveTypeSymbol(baseType->getTypeID())->getSize();
}