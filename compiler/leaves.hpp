#ifndef LEAVES_HPP
#define LEAVES_HPP

#include <vector>
#include <string>
#include <iostream>

class IdentList {
public:
  IdentList(std::string id) : id_list() {id_list.push_back(id);}
  std::string get(int i){return id_list[i];}
  void addIdent(std::string id) {id_list.push_back(id);}
  int getSize() {return id_list.size();}
private:
  std::vector<std::string> id_list;
};





class LValue
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




class Parse_Type
{
public:
  Parse_Type() = default;
  virtual ~Parse_Type() = default;
  virtual std::string getTypeID() = 0;
private:
  
};

class SimpleType : public Parse_Type
{
public:
  SimpleType(std::string id) : Parse_Type(), id(id) {}
  std::string getTypeID() {return id;}
private:
  std::string id;
};

class ArrayType : public Parse_Type
{
public:

private:

};

class RecordType : public Parse_Type
{
public:

private:

};

#endif