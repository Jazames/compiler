#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>
#include <string>
#include <iostream>

#include "leaves.hpp"
#include "expressions.hpp"
#include "tree.hpp"


class SimpleType : public Type
{
public:
  SimpleType(std::string id);// : Type(), id(id), size(4) {}
  SimpleType(std::string id, int size) : Type(), id(id), size(size) {}
  std::string getTypeID() override {return id;}// SymbolTable::getInstance().retrieveTypeSymbol(id)->getTypeID();}
  int getSize() override;// {return size;}
private:
  std::string id;
  int size;
};


class ArrayType : public Type
{
public:
  ArrayType(Expression* lb, Expression* ub, Type* baseType);
  int getSize() override;
  int getAddressOffsetOfElement(int position);//This is probably a useless function. 
  std::string getTypeID() override {return type;}
  int getLowerBound();
  Type* getBaseType() {return baseType;}
private:
  std::string type;
  int lb;
  int ub;
  Type* baseType;
};

class RecordType : public Type
{
public:
  RecordType(RecordList* recordList);
  int getSize() override;
  std::string getTypeID() override;
  Type* getTypeOfMember(std::string id);
  int getOffsetOfMember(std::string id);
private:
  std::string type;
  std::map<std::string, std::pair<int, Type*> > memberList;
  int size;
};

class IdentLValue : public LValue
{
public:
  IdentLValue(std::string id) : LValue(), id(id) {} 
  Register* emit();
  Register* emitAddress();
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
  ArrayLValue(LValue* lval, Expression* e) : LValue(), lval(lval), e(e) {}
  Register* emit();
  Register* emitAddress();
  std::string getID() override {return lval->getID();}
  std::string getType() override; //{return e->getType();}
//  std::string getBaseType() {return e->getType();}
private:
  LValue* lval;
  Expression* e;
};

class RecordLValue : public LValue
{
public: 
  RecordLValue(LValue* lval, std::string ident);
  Register* emit() override;
  Register* emitAddress() override;
  std::string getType() override;
  std::string getID() override;
private:
  LValue* lval;
  std::string ident;
};




#endif