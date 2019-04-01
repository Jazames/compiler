#include "expressions.hpp"

#include "types.hpp"

//Expression Member Functions


//Logical Operators

OrExpr::OrExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) 
{
  if(!typeIsBool(l->getType()) || !typeIsBool(r->getType()))
  {
    std::cerr << "Syntax Error: Attempting to perform arithmetic on non-arithmetic types: "
    << l->getType() << " and " << r->getType() << " at line number: "
      << SymbolTable::getInstance().getLineNumber() << std::endl;
  }
}

Register* OrExpr::emit()
{
  if(isConst())
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    Value val = l->getValue() | r->getValue();
    std::cout << "li " << reg->getAsm() << ", " << val << "      # Put Literal " << val << " into register.\n";
    return reg;
  }
  else
  {
    Register* lreg = l->emit();
    Register* rreg = r->emit();
    Register* reg = RegisterPool::getInstance().getRegister();
    std::cout << "or " << reg->getAsm() << ", " << lreg->getAsm() << ", " << rreg->getAsm() << "      #Or two registers.\n";
    delete(rreg);
    delete(lreg);
    return reg;
  }
}

Value OrExpr::getValue() 
{
  if(isConst())
  {
    return l->getValue() | r->getValue();
  }
} 

std::string OrExpr::getType()
{
  if(r->getType() == l->getType())
  {
    return r->getType();
  }
  else
  {
    std::cout << "Syntax Error: Attempting mathematical operation between different types." << std::endl;
    exit(0);
  }
}

AndExpr::AndExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) 
{
  if(!typeIsBool(l->getType()) || !typeIsBool(r->getType()))
  {
    std::cerr << "Syntax Error: Attempting to perform arithmetic on non-arithmetic types: "
    << l->getType() << " and " << r->getType() << " at line number: "
      << SymbolTable::getInstance().getLineNumber() << std::endl;
  }
}

Register* AndExpr::emit()
{
  if(isConst())
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    Value val = l->getValue() & r->getValue();
    std::cout << "li " << reg->getAsm() << ", " << val << "      # Put Literal " << val << " into register.\n";
    return reg;
  }
  else
  {
    Register* lreg = l->emit();
    Register* rreg = r->emit();
    Register* reg = RegisterPool::getInstance().getRegister();
    std::cout << "and " << reg->getAsm() << ", " << lreg->getAsm() << ", " << rreg->getAsm() << "      #Or two registers.\n";
    delete(rreg);
    delete(lreg);
    return reg;
  }
}

Value AndExpr::getValue() 
{
  if(isConst())
  {
    return l->getValue() | r->getValue();
  }
} 

std::string AndExpr::getType()
{
  if(r->getType() == l->getType())
  {
    return r->getType();
  }
  else
  {
    std::cout << "Syntax Error: Attempting mathematical operation between different types." << std::endl;
    exit(0);
  }
}

//Comparison operators

EqualToExpr::EqualToExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) 
{
  if(!typeIsArithmetic(l->getType()) || !typeIsArithmetic(r->getType()))
  {
    std::cerr << "Syntax Error: Attempting to perform arithmetic on non-arithmetic types: "
    << l->getType() << " and " << r->getType() << " at line number: "
      << SymbolTable::getInstance().getLineNumber() << std::endl;
  }
}

Register* EqualToExpr::emit()
{
  if(isConst())
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    Value val = l->getValue() == r->getValue();
    std::cout << "li " << reg->getAsm() << ", " << val << "       # Put Literal " << val << " into register.\n";
    return reg;
  }
  else
  {
    Register* lreg = l->emit();
    Register* rreg = r->emit();
    Register* reg = RegisterPool::getInstance().getRegister();
    std::cout << "subu " << reg->getAsm() << ", " << lreg->getAsm() << ", " << rreg->getAsm() << "      #Subtract two registers.\n";
    std::cout << "sltu " << reg->getAsm() << ", $zero, " << reg->getAsm() << "      #See if result is zero.\n";
    std::cout << "xori " << reg->getAsm() << ", " << reg->getAsm() << ", 1        #Flip the lsb to get what we want.\n";
    delete(rreg);
    delete(lreg);
    return reg;
  }
}

Value EqualToExpr::getValue() 
{
  if(isConst())
  {
    return l->getValue() == r->getValue();
  }
} 

std::string EqualToExpr::getType()
{
  if(r->getType() == l->getType())
  {
    return "boolean";
  }
  else
  {
    std::cout << "Syntax Error: Attempting mathematical operation between different types." << std::endl;
    exit(0);
  }
}


NotEqualToExpr::NotEqualToExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) 
{
  if(!typeIsArithmetic(l->getType()) || !typeIsArithmetic(r->getType()))
  {
    std::cerr << "Syntax Error: Attempting to perform arithmetic on non-arithmetic types: "
    << l->getType() << " and " << r->getType() << " at line number: "
      << SymbolTable::getInstance().getLineNumber() << std::endl;
  }
}

Register* NotEqualToExpr::emit()
{
  if(isConst())
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    Value val = l->getValue() != r->getValue();
    std::cout << "li " << reg->getAsm() << ", " << val << "       # Put Literal " << val << " into register.\n";
    return reg;
  }
  else
  {
    Register* lreg = l->emit();
    Register* rreg = r->emit();
    Register* reg = RegisterPool::getInstance().getRegister();
    std::cout << "subu " << reg->getAsm() << ", " << lreg->getAsm() << ", " << rreg->getAsm() << "      #Subtract two registers.\n";
    std::cout << "sltu " << reg->getAsm() << ", $zero, " << reg->getAsm() << "      #See if result is zero.\n";
    //std::cout << "xori " << reg->getAsm() << ", " << reg->getAsm() << ", 1        #Flip the lsb to get what we want.\n";
    delete(rreg);
    delete(lreg);
    return reg;
  }
}

Value NotEqualToExpr::getValue() 
{
  if(isConst())
  {
    return l->getValue() != r->getValue();
  }
} 

std::string NotEqualToExpr::getType()
{
  if(r->getType() == l->getType())
  {
    return "boolean";
  }
  else
  {
    std::cout << "Syntax Error: Attempting mathematical operation between different types." << std::endl;
    exit(0);
  }
}

LessThanEqualToExpr::LessThanEqualToExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) 
{
  if(!typeIsArithmetic(l->getType()) || !typeIsArithmetic(r->getType()))
  {
    std::cerr << "Syntax Error: Attempting to perform arithmetic on non-arithmetic types: "
    << l->getType() << " and " << r->getType() << " at line number: "
      << SymbolTable::getInstance().getLineNumber() << std::endl;
  }
}

Register* LessThanEqualToExpr::emit()
{
  if(isConst())
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    Value val = l->getValue() <= r->getValue();
    std::cout << "li " << reg->getAsm() << ", " << val << "      # Put Literal " << val << " into register.\n";
    return reg;
  }
  else
  {
    Register* lreg = l->emit();
    Register* rreg = r->emit();
    Register* reg = RegisterPool::getInstance().getRegister();
    std::cout << "sle " << reg->getAsm() << ", " << lreg->getAsm() << ", " << rreg->getAsm() << "      #Opp two registers.\n";
    delete(rreg);
    delete(lreg);
    return reg;
  }
}

Value LessThanEqualToExpr::getValue() 
{
  if(isConst())
  {
    return l->getValue() <= r->getValue();
  }
} 

std::string LessThanEqualToExpr::getType()
{
  if(r->getType() == l->getType())
  {
    return "boolean";
  }
  else
  {
    std::cout << "Syntax Error: Attempting mathematical operation between different types." << std::endl;
    exit(0);
  }
}



GreaterThanEqualToExpr::GreaterThanEqualToExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) 
{
  if(!typeIsArithmetic(l->getType()) || !typeIsArithmetic(r->getType()))
  {
    std::cerr << "Syntax Error: Attempting to perform arithmetic on non-arithmetic types: "
    << l->getType() << " and " << r->getType() << " at line number: "
      << SymbolTable::getInstance().getLineNumber() << std::endl;
  }
}

Register* GreaterThanEqualToExpr::emit()
{
  if(isConst())
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    Value val = l->getValue() >= r->getValue();
    std::cout << "li " << reg->getAsm() << ", " << val << "      # Put Literal " << val << " into register.\n";
    return reg;
  }
  else
  {
    Register* lreg = l->emit();
    Register* rreg = r->emit();
    Register* reg = RegisterPool::getInstance().getRegister();
    std::cout << "sge " << reg->getAsm() << ", " << lreg->getAsm() << ", " << rreg->getAsm() << "      #Opp two registers.\n";
    delete(rreg);
    delete(lreg);
    return reg;
  }
}

Value GreaterThanEqualToExpr::getValue() 
{
  if(isConst())
  {
    return l->getValue() >= r->getValue();
  }
} 

std::string GreaterThanEqualToExpr::getType()
{
  if(r->getType() == l->getType())
  {
    return "boolean";
  }
  else
  {
    std::cout << "Syntax Error: Attempting mathematical operation between different types." << std::endl;
    exit(0);
  }
}

LessThanExpr::LessThanExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) 
{
  if(!typeIsArithmetic(l->getType()) || !typeIsArithmetic(r->getType()))
  {
    std::cerr << "Syntax Error: Attempting to perform arithmetic on non-arithmetic types: "
    << l->getType() << " and " << r->getType() << " at line number: "
      << SymbolTable::getInstance().getLineNumber() << std::endl;
  }
}

Register* LessThanExpr::emit()
{
  if(isConst())
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    Value val = l->getValue() < r->getValue();
    std::cout << "li " << reg->getAsm() << ", " << val << "      # Put Literal " << val << " into register.\n";
    return reg;
  }
  else
  {
    Register* lreg = l->emit();
    Register* rreg = r->emit();
    Register* reg = RegisterPool::getInstance().getRegister();
    std::cout << "slt " << reg->getAsm() << ", " << lreg->getAsm() << ", " << rreg->getAsm() << "      #Opp two registers.\n";
    delete(rreg);
    delete(lreg);
    return reg;
  }
}

Value LessThanExpr::getValue() 
{
  if(isConst())
  {
    return l->getValue() < r->getValue();
  }
} 

std::string LessThanExpr::getType()
{
  if(r->getType() == l->getType())
  {
    return "boolean";
  }
  else
  {
    std::cout << "Syntax Error: Attempting mathematical operation between different types." << std::endl;
    exit(0);
  }
}

GreaterThanExpr::GreaterThanExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) 
{
  if(!typeIsArithmetic(l->getType()) || !typeIsArithmetic(r->getType()))
  {
    std::cerr << "Syntax Error: Attempting to perform arithmetic on non-arithmetic types: "
    << l->getType() << " and " << r->getType() << " at line number: "
      << SymbolTable::getInstance().getLineNumber() << std::endl;
  }
}

Register* GreaterThanExpr::emit()
{
  if(isConst())
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    Value val = l->getValue() > r->getValue();
    std::cout << "li " << reg->getAsm() << ", " << val << "      # Put Literal " << val << " into register.\n";
    return reg;
  }
  else
  {
    Register* lreg = l->emit();
    Register* rreg = r->emit();
    Register* reg = RegisterPool::getInstance().getRegister();
    std::cout << "sgt " << reg->getAsm() << ", " << lreg->getAsm() << ", " << rreg->getAsm() << "      #Opp two registers.\n";
    delete(rreg);
    delete(lreg);
    return reg;
  }
}

Value GreaterThanExpr::getValue() 
{
  if(isConst())
  {
    return l->getValue() > r->getValue();
  }
} 

std::string GreaterThanExpr::getType()
{
  if(r->getType() == l->getType())
  {
    return "boolean";
  }
  else
  {
    std::cout << "Syntax Error: Attempting mathematical operation between different types." << std::endl;
    exit(0);
  }
}

//Arithmatic operators

AddExpr::AddExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) 
{
  if(!typeIsArithmetic(l->getType()) || !typeIsArithmetic(r->getType()))
  {
    std::cerr << "Syntax Error: Attempting to perform arithmetic on non-arithmetic types: "
    << l->getType() << " and " << r->getType() << " at line number: "
      << SymbolTable::getInstance().getLineNumber() << std::endl;
  }
}

Register* AddExpr::emit()
{
  if(isConst())
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    Value val = l->getValue() + r->getValue();
    std::cout << "li " << reg->getAsm() << ", " << val << "      # Put Literal " << val << " into register.\n";
    return reg;
  }
  else
  {
    Register* rreg = r->emit();
    Register* lreg = l->emit();
    Register* reg = RegisterPool::getInstance().getRegister();
    std::cout << "add " << reg->getAsm() << ", " << lreg->getAsm() << ", " << rreg->getAsm() << "      #Add two registers.\n";
    delete(rreg);
    delete(lreg);
    return reg;
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
  else
  {
    std::cout << "Syntax Error: Attempting mathematical operation between different types." << std::endl;
    exit(0);
  }
}

SubExpr::SubExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) 
{
  if(!typeIsArithmetic(l->getType()) || !typeIsArithmetic(r->getType()))
  {
    std::cerr << "Syntax Error: Attempting to perform arithmetic on non-arithmetic types: "
    << l->getType() << " and " << r->getType() << " at line number: "
      << SymbolTable::getInstance().getLineNumber() << std::endl;
  }
}

Register* SubExpr::emit()
{
  if(isConst())
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    Value val = l->getValue() - r->getValue();
    std::cout << "li " << reg->getAsm() << ", " << val << "      # Put Literal " << val << " into register.\n";
    return reg;
  }
  else
  {
    Register* rreg = r->emit();
    Register* lreg = l->emit();
    Register* reg = RegisterPool::getInstance().getRegister();
    std::cout << "sub " << reg->getAsm() << ", " << lreg->getAsm() << ", " << rreg->getAsm() << "      #Subtract two registers.\n";
    delete(rreg);
    delete(lreg);
    return reg;
  }
}

Value SubExpr::getValue() 
{
  if(isConst())
  {
    return l->getValue() - r->getValue();
  }
  else
  {
    return 0;
  }
} 

std::string SubExpr::getType()
{
  if(r->getType() == l->getType())
  {
    return r->getType();
  }
  else
  {
    std::cout << "Syntax Error: Attempting mathematical operation between different types." << std::endl;
    exit(0);
  }
}

MultExpr::MultExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) 
{
  if(!typeIsArithmetic(l->getType()) || !typeIsArithmetic(r->getType()))
  {
    std::cerr << "Syntax Error: Attempting to perform arithmetic on non-arithmetic types: "
    << l->getType() << " and " << r->getType() << " at line number: "
      << SymbolTable::getInstance().getLineNumber() << std::endl;
  }
}

Register* MultExpr::emit()
{
  if(isConst())
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    Value val = l->getValue() * r->getValue();
    std::cout << "li " << reg->getAsm() << ", " << val << "      # Put Literal " << val << " into register.\n";
    return reg;
  }
  else
  {
    Register* lreg = l->emit();
    Register* rreg = r->emit();
    std::cout << "mult " << lreg->getAsm() << ", " << rreg->getAsm() << "      #Multiply two registers.\n";

    delete(rreg);
    delete(lreg);
    Register* reg = RegisterPool::getInstance().getRegister();

    std::cout << "mflo " << reg->getAsm() << "      #move the result into the correct register\n";
    return reg;
  }
}

Value MultExpr::getValue() 
{
  if(isConst())
  {
    return l->getValue() * r->getValue();
  }
  else
  {
    return 0;
  }
} 

std::string MultExpr::getType()
{
  if(r->getType() == l->getType())
  {
    return r->getType();
  }
  else
  {
    std::cout << "Syntax Error: Attempting mathematical operation between different types." << std::endl;
    exit(0);
  }
}

DivExpr::DivExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) 
{
  if(!typeIsArithmetic(l->getType()) || !typeIsArithmetic(r->getType()))
  {
    std::cerr << "Syntax Error: Attempting to perform arithmetic on non-arithmetic types: "
    << l->getType() << " and " << r->getType() << " at line number: "
      << SymbolTable::getInstance().getLineNumber() << std::endl;
  }
}

Register* DivExpr::emit()
{
  if(isConst())
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    Value val = l->getValue() / r->getValue();
    std::cout << "li " << reg->getAsm() << ", " << val << "      # Put Literal " << val << " into register.\n";
    return reg;
  }
  else
  {
    Register* lreg = l->emit();
    Register* rreg = r->emit();
    std::cout << "div "  << lreg->getAsm() << ", " << rreg->getAsm() << "      #Divide two registers.\n";
    
    delete(rreg);
    delete(lreg);
    Register* reg = RegisterPool::getInstance().getRegister();
    
    std::cout << "mflo " << reg->getAsm() << "      #move the result into the correct register\n";
    return reg;
  }
}

Value DivExpr::getValue() 
{
  if(isConst())
  {
    return l->getValue() / r->getValue();
  }
  else
  {
    return 0;
  }
} 

std::string DivExpr::getType()
{
  if(r->getType() == l->getType())
  {
    return r->getType();
  }
  else
  {
    std::cout << "Syntax Error: Attempting mathematical operation between different types." << std::endl;
    exit(0);
  }
}

ModExpr::ModExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) 
{
  if(!typeIsArithmetic(l->getType()) || !typeIsArithmetic(r->getType()))
  {
    std::cerr << "Syntax Error: Attempting to perform arithmetic on non-arithmetic types: "
    << l->getType() << " and " << r->getType() << " at line number: "
      << SymbolTable::getInstance().getLineNumber() << std::endl;
  }
}

Register* ModExpr::emit()
{
  if(isConst())
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    Value val = l->getValue() % r->getValue();
    std::cout << "li " << reg->getAsm() << ", " << val << "      # Put Literal " << val << " into register.\n";
    return reg;
  }
  else
  {
    Register* rreg = r->emit();
    Register* lreg = l->emit();
    std::cout << "div "  << lreg->getAsm() << ", " << rreg->getAsm() << "      #Divide two registers.\n";    

    delete(rreg);
    delete(lreg);
    Register* reg = RegisterPool::getInstance().getRegister();

    std::cout << "mfhi " << reg->getAsm() << "      #move the result into the correct register\n";
    return reg;
  }
}

Value ModExpr::getValue() 
{
  if(isConst())
  {
    return l->getValue() % r->getValue();
  }
  else
  {
    return 0;
  }
} 

std::string ModExpr::getType()
{
  if(r->getType() == l->getType())
  {
    return r->getType();
  }
  else
  {
    std::cout << "Syntax Error: Attempting mathematical operation between different types." << std::endl;
    exit(0);
  }
}


//Unary Expressions

NotExpr::NotExpr(Expression* e) : Expression(), e(e) 
{
  if(!typeIsBool(e->getType()))
  {
    std::cerr << "Syntax Error: Attempting to perform logical not on non-bool type: "
    << e->getType() << " at line number: "
      << SymbolTable::getInstance().getLineNumber() << std::endl;
  }
}

Register* NotExpr::emit()
{
  if(isConst())
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    Value val = e->getValue() ^ 0x1; //The hex makes it look more like a logical not. 
    std::cout << "li " << reg->getAsm() << ", " << val << "      # Put Literal " << val << " into register.\n";
    return reg;
  }
  else
  {
    Register* ereg = e->emit();
    Register* reg = RegisterPool::getInstance().getRegister();
    std::cout << "xor " << reg->getAsm() << ", " << ereg->getAsm() << ", 1      #flip the lsb.\n";
    delete(ereg);
    return reg;
  }
}

Value NotExpr::getValue() 
{
  if(isConst())
  {
    return e->getValue() ^ 0x1;
  }
} 

std::string NotExpr::getType()
{
  return e->getType();
}



NegationExpr::NegationExpr(Expression* e) : Expression(), e(e) 
{
  if(!typeIsArithmetic(e->getType()))
  {
    std::cerr << "Syntax Error: Attempting to perform negation on non-arithmetic type: "
    << e->getType() << " at line number: "
      << SymbolTable::getInstance().getLineNumber() << std::endl;
  }
}

Register* NegationExpr::emit()
{
  if(isConst())
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    Value val = e->getValue() * -1; 
    std::cout << "li " << reg->getAsm() << ", " << val << "      # Put Literal " << val << " into register.\n";
    return reg;
  }
  else
  {
    Register* ereg = e->emit();
    Register* reg = RegisterPool::getInstance().getRegister();
    std::cout << "sub " << reg->getAsm() << ", $zero, " << ereg->getAsm() << "      #change the sign.\n";
    delete(ereg);
    return reg;
  }
}

Value NegationExpr::getValue() 
{
  if(isConst())
  {
    return e->getValue() * -1;
  }
} 

std::string NegationExpr::getType()
{
  return e->getType();
}



ParenthesisExpr::ParenthesisExpr(Expression* e) : Expression(), e(e) 
{
  //No type checks necessary. 
}

Register* ParenthesisExpr::emit()
{
  if(isConst())
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    Value val = e->getValue(); //The hex makes it look more like a logical not. 
    std::cout << "li " << reg->getAsm() << ", " << val << "      # Put Literal " << val << " into register.\n";
    return reg;
  }
  else
  {
    Register* ereg = e->emit(); //Don't actually have to do anything, just put it in a register. 
    //Register* reg = RegisterPool::getInstance().getRegister();
    //std::cout << "xor " << reg->getAsm() << ", " << ereg->getAsm() << ", 1      #flip the lsb.\n";
    return ereg;
  }
}

Value ParenthesisExpr::getValue() 
{
  if(isConst())
  {
    return e->getValue();
  }
} 

std::string ParenthesisExpr::getType()
{
  return e->getType();
}

//Function call expression


//Modifying expressions

ChrExpr::ChrExpr(Expression* e) : Expression(), e(e) 
{
  //No type checks necessary. 
}

Register* ChrExpr::emit()
{
  return e->emit();
}

Value ChrExpr::getValue() 
{
  return e->getValue();
} 

std::string ChrExpr::getType()
{
  return "char";
}

OrdExpr::OrdExpr(Expression* e) : Expression(), e(e) 
{
  //No type checks necessary. 
}

Register* OrdExpr::emit()
{
  return e->emit();
}

Value OrdExpr::getValue() 
{
  return e->getValue();
} 

std::string OrdExpr::getType()
{
  return "integer";
}



Register* PredExpr::emit()
{
  Register* reg = e->emit();
  if(typeIsBool(e->getType()))
  {
    std::cout << "xori " << reg->getAsm() << ", " << reg->getAsm() << ", 1     #Flip bit if boolean\n"; 
    return reg;
  }
  else if(typeIsArithmetic(e->getType()))
  {
    std::cout << "addi " << reg->getAsm() << ", " << reg->getAsm() << ", -1     #Decrement the expression\n"; 
    return reg;
  }
  else
  {
    std::cerr << "Error: Attempting to get the predecessor of a non-arithmetic expression." << std::endl;
    exit(0);
  }
}

Value PredExpr::getValue() 
{
  if(typeIsBool(e->getType()))
  {
    return e->getValue() ^ 0x01;
  }
  else
  {
    return e->getValue() - 1;
  }
} 

std::string PredExpr::getType()
{
  return e->getType();
}



Register* SuccExpr::emit()
{
  Register* reg = e->emit();
  if(typeIsBool(e->getType()))
  {
    std::cout << "xori " << reg->getAsm() << ", " << reg->getAsm() << ", 1     #Flip bit if boolean\n"; 
    return reg;
  }
  else if(typeIsArithmetic(e->getType()))
  {
    std::cout << "addi " << reg->getAsm() << ", " << reg->getAsm() << ", 1     #Increment the expression\n"; 
    return reg;
  }
  else
  {
    std::cerr << "Error: Attempting to get the successor of a non-arithmetic expression." << std::endl;
    exit(0);
  }
}

Value SuccExpr::getValue() 
{
  if(typeIsBool(e->getType()))
  {
    return e->getValue() ^ 0x01;
  }
  else
  {
    return e->getValue() + 1;
  }
} 

std::string SuccExpr::getType()
{
  return e->getType();
}


//Expressions with single value

Register* LValueExpr::emit()//TODO: Change emit scheme based on lvalue type. 
{
  Register* reg = lval->emit();
  return reg;

  /*
  //Possibly useless stuff. 
  ArrayLValue*  arr = dynamic_cast<ArrayLValue* >(lval);
  RecordLValue* rec = dynamic_cast<RecordLValue*>(lval);

  if(arr != nullptr) //Check if lval is of Array type.
  {
    //arr->
  }

  if(typeIsString(getType()))
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    std::cout << "la " << reg->getAsm() << ", ";
    std::cout << SymbolTable::getInstance().retrieveVariableSymbol(lval->getID()).getStringLabel();
    std::cout << "     # Load address of String literal into LVal\n";
    return reg;
  }
  else if(typeIsArithmetic(getType()))
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    std::cout << "lw " << reg->getAsm() << ", ";
    std::cout << SymbolTable::getInstance().getVariableAddress(lval->getID());
    std::cout << "     #Load LVal: " << lval->getID() << " into register.\n";
    return reg;
  }
  */
}

Value LValueExpr::getValue() 
{
  if(isConst())
  {
    return SymbolTable::getInstance().retrieveVariableSymbol(lval->getID()).getValue();
  }
  else
  {
    std::cerr << "Syntax Error: Attempting to get constant value of non-constant LValue." << std::endl;
    exit(0);
  }
}

std::string LValueExpr::getType()
{
  ArrayLValue*  arr = dynamic_cast<ArrayLValue* >(lval);
  RecordLValue* rec = dynamic_cast<RecordLValue*>(lval);
  if(arr != nullptr)
  {
    return arr->getType();
  }
  else if(rec != nullptr)
  {
    return rec->getType();
  }
  else
  {
    std::string type = SymbolTable::getInstance().retrieveVariableSymbol(lval->getID()).getType();
    auto ptr = SymbolTable::getInstance().retrieveTypeSymbol(type);
    return ptr->getTypeID();
  }
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



Register* LiteralExpr::emit()
{
  if (typeIsString(type)) 
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    //Create a non-colliding name, and add it to the list of strings, and put them in the .data field. 
    std::string label = getNewStringLabel();
    SymbolTable::getInstance().addStringLiteral(label, s_val);
    std::cout << "la " << reg->getAsm() << ", " << label << "      # Put Address of String Literal: "<< s_val << " into register.\n";
    return reg;
  }
  else  //Should be good for integers, chars, and booleans. Maybe?
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    std::cout << "li " << reg->getAsm() << ", " << val << "      # Put Literal " << val << " into register.\n";
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