#include "statements.hpp"
#include "types.hpp"



//Statement Helper Member Functions

void StatementSequence::emit() 
{
  //Need to emit in reverse order, because statements are added last to first. 
  //std::cerr << "Emitting statements in block. Size = " << list.size() << std::endl;
  for(int i = list.size() - 1; i >= 0; i--)
  {
    if(list[i] != nullptr)
    {
      list[i]->emit();
    }
    else
    {
      std::cerr << "Statement is null. i=" << i << " listSize=" << list.size() << std::endl;
    }
  }
}

ElseSequence::ElseSequence() : ss(new StatementSequence(new Null()))  //Put a statement in there that doesn't do anything. It's safe to put these everywhere. 
{

}



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

/*
  Expression* e;
  StatementSequence* list;
  ElseIfSequence* eifs;
  ElseSequence* els;
*/
void If::emit() 
{
  std::cout << "#If Statement\n";
  std::string end_label = getNewIfEndLabel();
  
  //Check condition.
  Register* reg = e->emit();
  std::string else_if_label = getNewElseIfLabel();
  std::cout << "beq " << reg->getAsm() << ", $zero, "  << else_if_label << "   #     \n";
  delete(reg);

  //Now output commands in if block. 
  list->emit();
  std::cout << "j " << end_label << " #Go to end of if statement\n\n";


  std::cout << else_if_label << ": # Start of next condition\n";
  //Need to get these backwards because of how the thingaling works. 
  for(int i = eifs->getSize() - 1; i >= 0; i--)
  {
    Expression* eif_e = eifs->getExpr(i);
    StatementSequence* eif_ss = eifs->getSS(i);
    
    //Check condition
    Register* ereg = eif_e->emit();
    else_if_label = getNewElseIfLabel();
    std::cout << "beq " << ereg->getAsm() << ", $zero, " << else_if_label << "   #   \n";
    delete(ereg);

    //Now throw out statements. 
    eif_ss->emit();
    std::cout << "j " << end_label << " #Go to end of if statement\n\n";

    //Setup for next condition
    std::cout << else_if_label << ": # Start of next condition\n";
  }

  //Now take care of else. 
  //Label is already output. 
  els->emitSS();

  //Throw down end label. 
  std::cout << end_label << ": #   End of If Statement\n\n";
}

/* Members
Expression* e
StatementSequence* ss
*/
void While::emit()
{
  std::cout << "#While Statment\n";
  std::string begin_label = getNewWhileBeginLabel();
  std::string end_label = getNewWhileEndLabel();

  //Place begin label
  std::cout << begin_label << ":    #Start of while loop\n";

  //Place expression
  Register* reg = e->emit();

  //Check condition, end if unmet.
  std::cout << "beq " << reg->getAsm() << ", $zero, " << end_label << "   #Exit loop.\n";
  delete(reg);

  //Place statement sequence. 
  ss->emit();

  //Jump back to beginning. 
  std::cout << "j " << begin_label << "    # Repeat the loop\n";
  //Place end label. 
  std::cout << end_label << ":     #End of while loop\n";
}
/* Members
Expression* e
StatementSequence* ss
*/

void Repeat::emit()
{
  std::cout << "#Repeat Statment\n";
  std::string repeat_label = getNewRepeatLabel();

  //Place begin label
  std::cout << repeat_label << ":    #Start of repeat loop\n";

  //Place statement sequence. 
  ss->emit();

  //Place expression
  Register* reg = e->emit();

  //Check condition, end if unmet.
  std::cout << "beq " << reg->getAsm() << ", $zero, " << repeat_label << "   #Exit loop if condition is met.\n\n";
  delete(reg);
}

/* Members
  bool downto;
  StatementSequence* ss;
  Expression* startE;
  Expression* endE;
  std::string id;

//Function: 
Id = startE

startForLabel
| statements

increment/decrement Id
| endE
if Id <=/>= endE branch startForLabel
*/
void For::emit()
{
  bool added_to_stack = false;
  std::cout << "# For Statement\n";
  //Add variable. 
  SymbolTable& sym_tab = SymbolTable::getInstance();

  if(!sym_tab.doesVariableExist(id))
  {
    sym_tab.addVariable(id, startE->getType());
    //Need to make room on the stack if this is a local variable.
    //TODO: only add to stack if local. 
    std::cout << "addi $sp, $sp, -4    #Increase stack for For Loop variable\n";
    added_to_stack = true;
  }
  LValue* lval = new IdentLValue(id);
  Expression* expr = new LValueExpr(lval);

  Assignment ass(lval, startE);
  ass.emit();


//Need to do initial check just in case it should never run. 
  std::string end_label = getNewForLabel();
  //Check if should never run for loop. 
  if(downto)
  {
    //if regID < regEnd, then be done. 
    LessThanExpr lesso(expr, endE);
    Register* reg = lesso.emit();
    std::cout << "bne " << reg->getAsm() << ", $zero, " << end_label << "     # skip for loop if finished check is true.\n\n";
    delete(reg);
    //std::cout << "bne " << regEnd->getAsm() << ", " << regId->getAsm() << ", " << for_label << "   # repeat for loop if not equal yet\n\n";
  }
  else
  {
    //if regID > regEnd, then be done. 
    GreaterThanExpr greato(expr, endE);
    Register* reg = greato.emit();
    std::cout << "bne " << reg->getAsm() << ", $zero, " << end_label << "     # skip for loop if finished check is true.\n\n";
    delete(reg);
    //std::cout << "bne " << regEnd->getAsm() << ", " << regId->getAsm() << ", " << for_label << "   # repeat for loop if not equal yet\n\n";
  }
  


  //Throw out label. 
  std::string for_label = getNewForLabel();
  std::cout << for_label << ":      # Start of For Loop\n";






  //Throw out statements;
  ss->emit();

  //Increment/decrement Id
  if(downto)
  { //decrement case
    PredExpr Predy(expr);
    Assignment new_ass(lval, &Predy);
    new_ass.emit();
  }
  else
  { //increment case
    SuccExpr Succy(expr);
    Assignment new_ass(lval, &Succy);
    new_ass.emit();
  }

  //Throw out End Expression
  //Register* regEnd = endE->emit();
  //Register* regId  = expr->emit();

  //Check if should repeat. 
  if(downto)
  {
    //if regID < regEnd, then be done. 
    LessThanExpr lesso(expr, endE);
    Register* reg = lesso.emit();
    std::cout << "beq " << reg->getAsm() << ", $zero, " << for_label << "     # repeat for loop if finished check isn't true.\n\n";
    delete(reg);
    //std::cout << "bne " << regEnd->getAsm() << ", " << regId->getAsm() << ", " << for_label << "   # repeat for loop if not equal yet\n\n";
  }
  else
  {
    //if regID > regEnd, then be done. 
    GreaterThanExpr greato(expr, endE);
    Register* reg = greato.emit();
    std::cout << "beq " << reg->getAsm() << ", $zero, " << for_label << "     # repeat for loop if finished check isn't true.\n\n";
    delete(reg);
    //std::cout << "bne " << regEnd->getAsm() << ", " << regId->getAsm() << ", " << for_label << "   # repeat for loop if not equal yet\n\n";
  }
  
  std::cout << end_label << ":       #End of the for loop\n";
  //Clean up. 
  if(added_to_stack)
  {
    //Need to remove room on the stack if this is a local variable.
    //TODO: only add to stack if local. 
    std::cout << "addi $sp, $sp, 4    #Increase stack for For Loop variable\n";
  }
  //delete(regEnd);
  //delete(regId);
  delete(expr);
  delete(lval);
}


void Return::emit() 
{
  if(e==nullptr)
  {
    //Transfer control. 
    std::cout << "jr $ra      # Return control\n";
  }
  int fp_offset = SymbolTable::getInstance().getFunctionReturnOffset();
  Register* reg = e->emit();
  std::cout << "sw " << reg->getAsm() << ", " << fp_offset << "($fp)      #Store return value at correct place on stack.\n\n";
  std::cout << "j _" << SymbolTable::getInstance().getFunction() << "       # Go to end of function fo rcleanup.\n";
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

void ProcedureCall::emit()
{
  //Todo before transferring control. 
    //Save used registers
    //Save Frame Pointer
    //Save return address
    //Put parameters on the stack
    //Create place for return value. 
    //Create place for local variables. 

  auto regs = RegisterPool::getInstance().getUsedRegisters();
  int adjust_stack_size = 8; //Need room for return address, frame pointer, and return value, even though return value isn't used. 
  adjust_stack_size += regs.size() * 4;


  if(el == nullptr)
  {
    //No parameters
    std::cout << "addi $sp, $sp, " << -adjust_stack_size << "# Increase the stack\n";
    pushRegs(regs, adjust_stack_size);

    std::cout << "sw $ra, " << adjust_stack_size - 4 << "($sp)   # Save frame pointer\n";
    std::cout << "sw $fp, " << adjust_stack_size - 8 << "($sp)   # Save return address\n";

    std::cout << "ori $fp, $sp, 0    #set the frame pointer for the call\n";
    std::cout << "jal " << id << " # Jump to function\n"; 

    std::cout << "lw $ra, " << adjust_stack_size - 4 << "($sp)   # Retrieve return address\n";
    std::cout << "lw $fp, " << adjust_stack_size - 8 << "($sp)   # Retrieve frame pointer\n";
  }
  else
  {
    //But there actually are parameters now. :'(

    for(int i = 0; i < el->size(); i++)
    {
      std::string type = el->get(i)->getType();
      int e_size = SymbolTable::getInstance().retrieveTypeSymbol(type)->getSize();
      adjust_stack_size += e_size;

      //Probably do more stuff here... like make instructions to copy values? 
    }

    //TODO: Make space for return value. 

    std::cout << "addi $sp, $sp, " << -adjust_stack_size << "# Increase the stack\n";
    pushRegs(regs, adjust_stack_size);

    int parameter_offset_from_stack = 0;
    for(int i = 0; i < el->size(); i++)
    {

      std::string type = el->get(i)->getType();
      int e_size = SymbolTable::getInstance().retrieveTypeSymbol(type)->getSize();
      Expression* e = el->get(i);

      LValueExpr* rval = dynamic_cast<LValueExpr*>(e);

      if(rval == nullptr)
      { //Case that the expression isn't an lValue. 
        Register* reg = e->emit();
        std::cout << "sw " << reg->getAsm() << ", " << parameter_offset_from_stack << "($sp)      # Put value in stack offset.\n";
        parameter_offset_from_stack += 4;
        delete(reg);
      }
      else //But if the expression is an LValue, need to copy it all over. 
      {
        int temp = 0;
        Register* reg = RegisterPool::getInstance().getRegister();
        Register* rreg = rval->getLValue()->emitAddress();  
        for(int i = 0; i < e_size; i+=4)
        {
          std::cout << "lw " << reg->getAsm() << ", " << i << "(" << rreg->getAsm() << ")     # obtain word at address\n";
          std::cout << "sw " << reg->getAsm() << ", " << i + parameter_offset_from_stack << "($sp)     # put word in stack offset\n";   
          temp += 4;
        }
        parameter_offset_from_stack += temp;
        delete(reg);
        delete(rreg);
      }
    }

    std::cout << "sw $ra, " << adjust_stack_size - 4 << "($sp)   # Save frame pointer\n";
    std::cout << "sw $fp, " << adjust_stack_size - 8 << "($sp)   # Save return address\n";

    std::cout << "ori $fp, $sp, 0    #set the frame pointer for the call\n";
    std::cout << "jal " << id << " # Jump to function\n"; 

    std::cout << "lw $ra, " << adjust_stack_size - 4 << "($sp)   # Retrieve return address\n";
    std::cout << "lw $fp, " << adjust_stack_size - 8 << "($sp)   # Retrieve frame pointer\n";


    parameter_offset_from_stack = 0;
    for(int i = 0; i < el->size(); i++)
    {
      std::string type = el->get(i)->getType();
      int e_size = SymbolTable::getInstance().retrieveTypeSymbol(type)->getSize();
      Expression* e = el->get(i);

      LValueExpr* rval = dynamic_cast<LValueExpr*>(e);

      bool isRef = SymbolTable::getInstance().getParamIsRefOfFunction(id, i);
      if(rval != nullptr && isRef)
      { //Need to copy things back if they're passed by ref. 
        int temp = 0;
        Register* reg = RegisterPool::getInstance().getRegister();
        Register* rreg = rval->getLValue()->emitAddress();  
        for(int i = 0; i < e_size; i+=4)
        {
          std::cout << "lw " << reg->getAsm() << ", " << i + parameter_offset_from_stack << "($sp)     # get word in stack offset\n";   
          std::cout << "sw " << reg->getAsm() << ", " << i << "(" << rreg->getAsm() << ")     # store word at address of variable\n";
          temp += 4;
        }
        parameter_offset_from_stack += temp;
        delete(reg);
        delete(rreg);
      }
    }



  }
  popRegs(regs, adjust_stack_size);
  std::cout << "addi $sp, $sp, " << adjust_stack_size << "# Decrease the stack\n";
  std::cout << "\n";
}
