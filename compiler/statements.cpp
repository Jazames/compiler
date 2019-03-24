#include "statements.hpp"




//Statements Member Functions

void Assignment::emit()
{
  std::cout << "#Assignment Statement: \n"; //TODO: put what assignment this is. 
  if(e->isConst())
  {
    int value = e->getValue();
    Register reg = RegisterPool::getInstance().getRegister();
    auto address = SymbolTable::getInstance().getVariableAddress(lval->getID());
    std::cout << "li " << reg.getAsm() << ", " << value   << "      #Put constant expression into register\n";
    std::cout << "sw " << reg.getAsm() << ", " << address << "      #Store value at address\n\n";
  }
  else 
  {
    Register exprReg = e->emit();
    auto address = SymbolTable::getInstance().getVariableAddress(lval->getID());
    std::cout << "sw " << exprReg.getAsm() << ", " << address << "      #Store value at address\n\n";
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
      Register reg = expression_list[i]->emit();
      std::cout << "ori $a0, " << reg.getAsm() << ", 0\n";
      std::cout << "li $v0, 1\nsyscall\n";
    }
    else if(typeIsChar(expression_list[i]->getType()))
    {
      Register reg = expression_list[i]->emit();
      std::cout << "ori $a0, " << reg.getAsm() << ", 0\n";
      std::cout << "li $v0, 11\nsyscall\n";
    }
    else if(typeIsString(expression_list[i]->getType()))
    {
      Register reg = expression_list[i]->emit();
      std::cout << "ori $a0, " << reg.getAsm() << ", 0\n";
      std::cout << "li $v0, 4\nsyscall\n";
    }
    else
    {
      std::cerr << "Syntax Error, trying to print out a user-defined type." << std::endl;
    }
  }
  std::cout << "\n";
  

  //Once it's all cleaned up, deallocate the memory. 
}

