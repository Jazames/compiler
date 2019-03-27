#ifndef LEAVES_HPP
#define LEAVES_HPP

#include <vector>
#include <string>
#include <iostream>


class LValue //LValues are used by read statements, assignment statements, and can be an expression. May want to 
{
public:
  LValue(std::string id) : id(id) {}
  virtual ~LValue() = default;
  //virtual Reg emit() = 0;
  //virtual bool isConst() {return false;}
  //virtual std::string getType() = 0;
  virtual std::string getID() {return id;}
private:
  std::string id;
};

class IdentLValue : public LValue
{
public:
  IdentLValue(std::string id) : LValue(id) {} 
  //Reg Emit();
  //bool isConst() override {return isDeclConst;}
  //std::string getType() override {return type;}
  //std::string getID() override {return id;}
private:
  //Identifier* ident;
  //std::string id;
  //Expression* expr;
  //std::string type;
  //const bool isDeclConst;
};

class ArrayLValue : public LValue
{
public:
  
private:
  
};

class RecordLValue : public LValue
{
public:
  
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

class SimpleType : public Type
{
public:
  SimpleType(std::string id) : Type(), id(id), size(4) {}
  std::string getTypeID() {return id;}
  int getSize() {return size;}
private:
  std::string id;
  int size;
};

class ArrayType : public Type
{
public:

private:

};

class RecordType : public Type
{
public:

private:

};

#endif