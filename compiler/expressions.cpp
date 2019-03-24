#include "expressions.hpp"


//Expression Member Functions

AddExpr::AddExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) 
{
  if(!typeIsArithmetic(l->getType()) || !typeIsArithmetic(r->getType()))
  {
    std::cerr << "Syntax Error: Attempting to perform arithmetic on non-arithmetic types: "
    << l->getType() << " and " << r->getType() << " at line number: "
      << SymbolTable::getInstance().getLineNumber() << std::endl;
  }
}

Register AddExpr::emit()
{
  if(isConst())
  {
    Register reg = RegisterPool::getInstance().getRegister();
    Value val = l->getValue() + r->getValue();
    std::cout << "li " << reg.getAsm() << ", " << val << "      # Put Literal " << val << " into register.\n";
    return reg;
  }
  else
  {
    Register lreg = l->emit();
    Register rreg = r->emit();
    Register sumReg = RegisterPool::getInstance().getRegister();
    std::cout << "add " << sumReg.getAsm() << ", " << lreg.getAsm() << ", " << rreg.getAsm() << "      #Add two registers.\n";
    return sumReg;
  }
}

Value AddExpr::getValue() 
{
  if(isConst())
  {
    return l->getValue() + r->getValue();
  }
} 

std::string AddExpr::getType()
{
  if(r->getType() == l->getType())
  {
    return r->getType();
  }
}

Register LValueExpr::emit() 
{
  Register reg = RegisterPool::getInstance().getRegister();
  std::cout << "lw " << reg.getAsm() << ", ";
  std::cout << SymbolTable::getInstance().getVariableAddress(lval->getID());
  std::cout << "    #Load LVal: " << lval->getID() << " into register.\n";
  return reg;
}

Value LValueExpr::getValue() 
{
  if(isConst())
  {

  }
  else
  {
    std::cerr << "Syntax Error: Attempting to get constant value of non-constant LValue." << std::endl;
    exit(0);
  }
}

std::string LValueExpr::getType()
{
  return SymbolTable::getInstance().retrieveVariableSymbol(lval->getID()).getType();
}

LiteralExpr::LiteralExpr(Value val, std::string type) : Expression(), val(val), type(type) 
{
}


LiteralExpr::LiteralExpr(std::string value, std::string type) : Expression(), val(charStringToChar(value)), s_val(value), type(type) 
{
  //
  if(typeIsChar(type))
  {
    //std::cerr << "DEBUG: Character Literal found: " << s_val << std::endl;
    //val = charStringToChar(s_val);
    //std::cout << "DEBUG: Character is: " << (char)val << std::endl;
  }
  if(typeIsString(type))
  {
    //std::cerr << "DEBUG: String literal found: " << s_val << std::endl;
  }
}



Register LiteralExpr::emit()
{
  if (typeIsString(type)) 
  {
    Register reg = RegisterPool::getInstance().getRegister();
    //Create a non-colliding name, and add it to the list of strings, and put them in the .data field. 
    std::string label = getNewStringLabel();
    SymbolTable::getInstance().addStringLiteral(label, s_val);
    std::cout << "la " << reg.getAsm() << ", " << label << "      # Put Address of String Literal: "<< s_val << " into register.\n";
    return reg;
  }
  else //Should be good for integers, chars, and booleans. Maybe?
  {
    Register reg = RegisterPool::getInstance().getRegister();
    std::cout << "li " << reg.getAsm() << ", " << val << "      # Put Literal " << val << " into register.\n";
    return reg;
  }
}

Value LiteralExpr::getValue()
{
  return val;
}

std::string LiteralExpr::getType() 
{
  return type;
}



//Functions