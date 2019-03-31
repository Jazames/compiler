#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>
#include <string>
#include <iostream>

#include "leaves.hpp"
#include "expressions.hpp"


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
  ArrayType(Expression* lb, Expression* ub, Type* baseType);
  int getSize();
  int getAddressOffsetOfElement(int position);//This is probably a useless function. 
  std::string getTypeID() {return baseType->getTypeID();}
private:
  //std::string typeID;
  int lb;
  int ub;
  Type* baseType;
};

class RecordType : public Type
{
public:

  //std::string getTypeID() {std::cerr << "TYPE ERROR"; exit(0); return "";}
private:

};


#endif