#include "statements.hpp"




//Statements Member Functions

void Assignment::emit()
{
  std::cout << "#Assignment Statement: \n"; //TODO: put what assignment this is. 
  //Check if trying to assign to constant l-value
  if(SymbolTable::getInstance().retrieveVariableSymbol(lval->getID()).isConst())
  {
    std::cerr << "Syntax Error: Attempting to assign to constant L-Value." << std::endl;
    return;
  }

  //potential todo: check if types match. 
  //If the lval size is greater than 4, then the expression is an lval. Or else there's a type mismatch. 
  int size = SymbolTable::getInstance().retrieveTypeSymbol(lval->getType())->getSize();

  //If the expression is constant, just load a literal. 
  if(e->isConst() && size == 4)
  {
    int value = e->getValue();
    Register* reg = RegisterPool::getInstance().getRegister();
    //auto address = SymbolTable::getInstance().getVariableAddress(lval->getID());
    Register* addressReg = lval->emitAddress();
    std::cout << "li " << reg->getAsm() << ", " << value   << "      #Put constant expression into register\n";
    std::cout << "sw " << reg->getAsm() << ", (" << addressReg->getAsm() << ")      #Store value at address\n\n";
    delete(reg);
    delete(addressReg);
  }
  else if (size > 4)
  {
    //std::cerr << "Size is " << size << std::endl;
    LValueExpr* rval = dynamic_cast<LValueExpr*>(e);
    if(rval == nullptr)
    {
      std::cerr << "Error, assignment between types of different sizes at line number ";
      std::cerr << SymbolTable::getInstance().getLineNumber() << std::endl;
      std::cerr << "Left hand side type: " << lval->getType() << " size: " << size << std::endl;;
      std::cerr << "Right hand side type: " << e->getType() << " size: ";
      std::cerr << SymbolTable::getInstance().retrieveTypeSymbol(e->getType())->getSize() << std::endl;
      exit(0);
    }

    Register* reg = RegisterPool::getInstance().getRegister();
    Register* lreg = lval->emitAddress();
    Register* rreg = rval->getLValue()->emitAddress();
    for(int i = 0; i < size; i+=4)
    {
      //std::string laddress = SymbolTable::getInstance().getVariableAddressWithOffset(lval->getID(), i);
      //std::string raddress = SymbolTable::getInstance().getVariableAddressWithOffset(rval->getID(), i);

      //std::cout << "lw " << reg->getAsm() << ", " << raddress << "     # obtain word at address\n";
      //std::cout << "sw " << reg->getAsm() << ", " << laddress << "     # store word at address\n";

      std::cout << "lw " << reg->getAsm() << ", " << i << "(" << rreg->getAsm() << ")     # obtain word at address\n";
      std::cout << "sw " << reg->getAsm() << ", " << i << "(" << lreg->getAsm() << ")     # store word at address\n";

    }
    delete(reg);
    delete(lreg);
    delete(rreg);
    std::cout << std::endl;
  }
  else 
  {
    std::cout << "# Doing an other type of assignment.\n";
    Register* reg = e->emit();
    //auto address = SymbolTable::getInstance().getVariableAddress(lval->getID());
    Register* addressReg = lval->emitAddress();
    std::cout << "sw " << reg->getAsm() << ", (" << addressReg->getAsm() << ")      #Store value at address\n\n";
    delete(reg);
    delete(addressReg);
  }
}

Read::Read(LValueList* lvl)
{
  for(int i = 0; i < lvl->size(); i++)
  {
    lvalue_list.push_back(lvl->get(i));
  }
}

void Read::emit()
{
  // li $v0, 5 #read integer command. 
  // syscall 
  // or $t0, $v0, $zero 
  SymbolTable& sym_tab = SymbolTable::getInstance();
  std::cout << "#Read Statement\n";
  for(int i = 0; i < lvalue_list.size(); i++)
  {
    if(typeIsInt(sym_tab.retrieveVariableSymbol(lvalue_list[i]->getID()).getType()))
    {
      //TODO: read into the address of the lvalue. 
      std::cout << "li $v0, 5\n      # syscall for reading an integer\nsyscall\n";
      //Value is now in $v0;
      std::cout << "sw $v0, " << sym_tab.getVariableAddress(lvalue_list[i]->getID());
      std::cout << "     # Store value into variable location.\n";

    }
    else if (typeIsChar(sym_tab.retrieveVariableSymbol(lvalue_list[i]->getID()).getType()))
    {
      std::cout << "li $v0, 12\n      # syscall for reading a character\nsyscall\n";
      //Value is now in $v0;
      std::cout << "sw $v0, " << sym_tab.getVariableAddress(lvalue_list[i]->getID());
      std::cout << "     # Store value into variable location.\n";

    }
    else
    {
      std::cerr << "Syntax Error: Attempting to read into non-character or non-integer L-Value." << std::endl;
      exit(0);
    }
  }
  std::cout << "\n";//space after the statement. 
  //TODO: Deallocate LValues. 
}

Write::Write(ExpressionList* el)
{
  for(int i = 0; i < el->size(); i++)
  {
    expression_list.push_back(el->get(i));
  }
}

void Write::emit()
{
  //TODO: put checks to see if expression methods are null, and if so, fail or something.   
  std::cout << "#Write Statement\n";
  for(int i = 0; i < expression_list.size(); i++)
  {
    if(typeIsInt(expression_list[i]->getType()) || typeIsBool(expression_list[i]->getType())) 
    { 
      Register* reg = expression_list[i]->emit();
      std::cout << "ori $a0, " << reg->getAsm() << ", 0\n";
      std::cout << "li $v0, 1\nsyscall\n";
      delete(reg);
    }
    else if(typeIsChar(expression_list[i]->getType()))
    {
      Register* reg = expression_list[i]->emit();
      std::cout << "ori $a0, " << reg->getAsm() << ", 0\n";
      std::cout << "li $v0, 11\nsyscall\n";
      delete(reg);
    }
    else if(typeIsString(expression_list[i]->getType()))
    {
      Register* reg = expression_list[i]->emit();
      std::cout << "ori $a0, " << reg->getAsm() << ", 0\n";
      std::cout << "li $v0, 4\nsyscall\n";
      delete(reg);
    }
    else
    {
      std::cerr << "Syntax Error, trying to print out a user-defined type: " << expression_list[i]->getType() << std::endl;
    }
  }
  std::cout << "\n";
  

  //Once it's all cleaned up, deallocate the memory. 
}

