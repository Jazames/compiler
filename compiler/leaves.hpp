#ifndef LEAVES_HPP
#define LEAVES_HPP

#include <vector>
#include <string>
#include <iostream>


class LValue //LValues are used by read statements, assignment statements, and can be an expression. May want to 
{
public:
  LValue()  {}
  virtual ~LValue() = default;
  //virtual Reg emit() = 0;
  //virtual bool isConst() {return false;}
  virtual std::string getType() = 0;
  virtual std::string getID() = 0;
private:
  //std::string id;
};

class IdentLValue : public LValue
{
public:
  IdentLValue(std::string id) : LValue(), id(id) {} 
  //Reg Emit();
  //bool isConst() override {return isDeclConst;}
  std::string getType() override; //{return SymbolTable::getInstance().retrieveVariableSymbol(id).getType();}
  std::string getID() override {return id;}
private:
  //Identifier* ident;
  std::string id;
  //Expression* expr;
  //std::string type;
  //const bool isDeclConst;
};

class ArrayLValue : public LValue
{
public:
  ArrayLValue(LValue* lval, std::string type) : LValue(), lval(lval), type(type) {}
  std::string getID() override {return lval->getID();}
  std::string getType() override {return type;}
private:
  LValue* lval;
  std::string type;
};

class RecordLValue : public LValue
{
public:
  //Get type should return the type of the identifier. 
private:
  
};



/*
class Type
{
public:
  Type() : size(0) {}
  Type(int size) : size(size) {}
  int getSize() {return size;}
private:
  int size; 
};
*/

class Type
{
public:
  Type() = default;
  virtual ~Type() = default;
  virtual int getSize() = 0;
  virtual std::string getTypeID() = 0;
private:
  
};



#endif