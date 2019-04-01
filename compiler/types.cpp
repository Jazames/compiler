
#include "types.hpp"
#include "utils.hpp"


//Helper functions

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

////////////////////////////
//Types
////////////////////////////


SimpleType::SimpleType(std::string id)
  : Type(), id(id), size(SymbolTable::getInstance().retrieveTypeSymbol(id)->getSize()) 
{

}

//Array type

//member variables
  //std::string typeID;
  //int lb;
  //int ub;
  //Type* baseType;

ArrayType::ArrayType(Expression* lb, Expression* ub, Type* baseType) 
  : Type(), baseType(baseType), lb(getConstValue(lb)), ub(getConstValue(ub)), type(getNameForAnon())
{
  SymbolTable::getInstance().addType(type, this);
}

int ArrayType::getSize()
{
  return (ub - lb + 1) * SymbolTable::getInstance().retrieveTypeSymbol(baseType->getTypeID())->getSize();
}

int ArrayType::getLowerBound()
{
  return lb;
}

int ArrayType::getAddressOffsetOfElement(int position)
{
  return (position - lb) * SymbolTable::getInstance().retrieveTypeSymbol(baseType->getTypeID())->getSize();
}

////////////////////////////
//LValues
////////////////////////////

std::string IdentLValue::getType()
{
  //std::cerr << "Type: " << SymbolTable::getInstance().retrieveVariableSymbol(id).getType() << std::endl;
  std::string type = SymbolTable::getInstance().retrieveVariableSymbol(id).getType();
  //Check if this type has an alias. 
  type = SymbolTable::getInstance().retrieveTypeSymbol(type)->getTypeID();
  //while(SymbolTable::getInstance().retrieveTypeSymbol(type))

  return type;//SymbolTable::getInstance().retrieveVariableSymbol(id).getType();
}


Register* IdentLValue::emit()
{
  if(typeIsString(getType()))
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    std::cout << "la " << reg->getAsm() << ", ";
    std::cout << SymbolTable::getInstance().retrieveVariableSymbol(id).getStringLabel();
    std::cout << "     # Load address of String literal into LVal\n";
    return reg;
  }
  else if(typeIsArithmetic(getType()))
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    std::cout << "lw " << reg->getAsm() << ", ";
    std::cout << SymbolTable::getInstance().getVariableAddress(id);
    std::cout << "     #Load value of LVal: " << id << " into register.\n";
    return reg;
  }
}


Register* IdentLValue::emitAddress()
{
  if(typeIsString(getType()))
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    std::cout << "la " << reg->getAsm() << ", ";
    std::cout << SymbolTable::getInstance().retrieveVariableSymbol(id).getStringLabel();
    std::cout << "     # Load address of String literal into LVal\n";
    return reg;
  }
  else if(typeIsArithmetic(getType()))
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    auto address = SymbolTable::getInstance().getVariableOffsetAndBase(id);
    std::cout << "addi " << reg->getAsm() << ", " << address.second << ", " <<  address.first;
    std::cout << "     # Get address of variable: " << id << "\n";
    return reg;
  }
  else
  {
    Register* reg = RegisterPool::getInstance().getRegister();
    auto address = SymbolTable::getInstance().getVariableOffsetAndBase(id);
    std::cout << "addi " << reg->getAsm() << ", " << address.second << ", " <<  address.first;
    std::cout << "     # Get address of variable: " << id << "\n";
    return reg;
    //Register* reg
    //std::cerr << "Did the thing, type be wrong. Type is: " << getType() << std::endl;
  }
}



Register* ArrayLValue::emit()
{
  //members: lval* e*
  SymbolTable& sym_tab = SymbolTable::getInstance();
  if(!typeIsArithmetic(e->getType()))
  {
    std::cerr << "Attempting to index an array with a non-arithmatic type at line number ";
    std::cerr << sym_tab.getLineNumber() << std::endl;
    exit(0);
  }
  Register* reg = e->emit();//Get expression value into register. 

  //Subtract lowerbound. 
  std::string type = sym_tab.retrieveVariableSymbol(lval->getID()).getType();
  ArrayType* arr = dynamic_cast<ArrayType*>(sym_tab.retrieveTypeSymbol(type));
  if(arr == nullptr)
  {
    std::cerr << "Bigole error, trying to make an array type out of something that isn't an array.\n";
    std::cerr << "Type: " << type << "\n";
    std::cerr << "Lval ID: " << lval->getID() << "\n";
    exit(0);
  }

  Register* temp = RegisterPool::getInstance().getRegister();
  std::cout << "li " << temp->getAsm() << ", " << arr->getLowerBound() << "     # Load lowerbound into register\n";
  std::cout << "sub " << reg->getAsm() << ", " << reg->getAsm() << ", " << temp->getAsm() << "      # Subtract lowerbound.\n";


  //multiply by type size. 
  int size = sym_tab.retrieveTypeSymbol(getType())->getSize();
  std::cout << "li "   << temp->getAsm() << ", " << size << "  # Load size of array elements into register\n";
  std::cout << "mult " << reg->getAsm()  << ", " << temp->getAsm() << "      # Multiply by the size of array elements\n";
  std::cout << "mflo " << reg->getAsm()  << "     # Get the result.\n";

  //Now have number of bytes offset from variable base. 

  //Add the offset (in reg) to base address of variable
  //std::pair<int, std::string> address = sym_tab.getVariableOffsetAndBase(lval->getID());
  //std::cout << "add " << reg->getAsm() << ", " << reg->getAsm() << ", " << address.second << "    # Sum the base address and offset\n";
  //std::cout << "lw " << reg->getAsm() << ", " << address.first << "(" << reg->getAsm() << ")       # Load the word at the address into a register.\n";


  delete(temp);
  Register* addrReg = lval->emitAddress();
  std::cout << "add "  << reg->getAsm() << ", " << reg->getAsm() << ", " << addrReg->getAsm() << "    #Sum the offset and the base address\n"; 
  std::cout << "lw " << reg->getAsm() << ", (" << reg->getAsm() << ")      #Load value from address into register.\n";
  delete(addrReg);
  return reg;//or something. 
}

Register* ArrayLValue::emitAddress()
{
  //members: lval* e*
  SymbolTable& sym_tab = SymbolTable::getInstance();
  if(!typeIsArithmetic(e->getType()))
  {
    std::cerr << "Attempting to index an array with a non-arithmatic type at line number ";
    std::cerr << sym_tab.getLineNumber() << std::endl;
    exit(0);
  }
  Register* reg = e->emit();//Get expression value into register. 

  //Subtract lowerbound. 
  std::string type = sym_tab.retrieveVariableSymbol(lval->getID()).getType();
  ArrayType* arr = dynamic_cast<ArrayType*>(sym_tab.retrieveTypeSymbol(type));
  if(arr == nullptr)
  {
    std::cerr << "Bigole error, trying to make an array type out of something that isn't an array.\n";
    std::cerr << "Type: " << type << "\n";
    std::cerr << "Lval ID: " << lval->getID() << "\n";
    exit(0);
  }

  Register* temp = RegisterPool::getInstance().getRegister();
  std::cout << "li " << temp->getAsm() << ", " << arr->getLowerBound() << "     # Load lowerbound into register\n";
  std::cout << "sub " << reg->getAsm() << ", " << reg->getAsm() << ", " << temp->getAsm() << "      # Subtract lowerbound.\n";


  //multiply by type size. 
  int size = sym_tab.retrieveTypeSymbol(getType())->getSize();
  std::cout << "li "   << temp->getAsm() << ", " << size << "  # Load size of array elements into register\n";
  std::cout << "mult " << reg->getAsm()  << ", " << temp->getAsm() << "      # Multiply by the size of array elements\n";
  std::cout << "mflo " << reg->getAsm()  << "     # Get the result, it is now the offset from the base\n";


  //Now have number of bytes offset from variable base. 

  //Add the offset (in reg) to base address of variable
  //std::pair<int, std::string> address = lval->//sym_tab.getVariableOffsetAndBase(lval->getID());
  delete(temp);
  Register* addrReg = lval->emitAddress();
  std::cout << "add "  << reg->getAsm() << ", " << reg->getAsm() << ", " << addrReg->getAsm() << "    #Sum the offset and the base address\n"; 
  //std::cout << "add "  << reg->getAsm() << ", " << reg->getAsm() << ", " << address.second << "    # Sum the base pointer and array offset\n";
  //std::cout << "addi " << reg->getAsm() << ", " << reg->getAsm() << ", " << address.first  << "     #Add the variable base offset\n";
  delete(addrReg);
  //Load word from address 
  return reg;//or something. 
}


std::string ArrayLValue::getType()
{
  std::string type_str = lval->getType();
  Type* type_ptr = SymbolTable::getInstance().retrieveTypeSymbol(type_str);
  ArrayType* arr = dynamic_cast<ArrayType*>(type_ptr);
  return arr->getBaseType()->getTypeID();
}