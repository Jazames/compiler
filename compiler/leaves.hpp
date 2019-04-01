#ifndef LEAVES_HPP
#define LEAVES_HPP

#include <vector>
#include <string>
#include <iostream>
#include "utils.hpp"
//#include "expressions.hpp"

class LValue //LValues are used by read statements, assignment statements, and can be an expression. 
{
public:
  LValue()  {}
  virtual ~LValue() = default;
  virtual Register* emit() = 0;
  virtual Register* emitAddress() = 0;
  //virtual bool isConst() {return false;}
  virtual std::string getType() = 0;
  virtual std::string getID() = 0;
private:
  //std::string id;
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