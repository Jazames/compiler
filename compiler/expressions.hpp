#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP

#include <string>
#include <iostream>
#include "leaves.hpp"
#include "utils.hpp"
#include "symbol_table.hpp"

using Reg = Register;

using Value = int;



class Expression
{
public:
  Expression() = default;
  virtual ~Expression() = default;
  virtual Value getValue() = 0;
  virtual Reg* emit() = 0;
  virtual bool isConst() {return false;}
  virtual std::string getType() = 0;
private:

};

class ExpressionList 
{
public:
  ExpressionList(Expression* e) {expression_list.push_back(e);}
  ExpressionList* addExpression(Expression* e) {expression_list.insert(expression_list.begin(),e);}
  int size() {return expression_list.size();}
  Expression* get(int pos) {return expression_list[pos];}
private:
  std::vector<Expression*> expression_list;
};


class OrExpr : public Expression
{
public:
  OrExpr(Expression* l, Expression* r);// : Expression(), l(l), r(r) {}
  Reg* emit() override; 
  bool isConst() override {return l->isConst() && r->isConst();}
  Value getValue() override;
  std::string getType() override;
private:
  Expression* l, *r;
}; 

class AndExpr : public Expression
{
public:
  AndExpr(Expression* l, Expression* r);// : Expression(), l(l), r(r) {}
  Reg* emit() override; 
  bool isConst() override {return l->isConst() && r->isConst();}
  Value getValue() override;
  std::string getType() override;
private:
  Expression* l, *r;
};

class EqualToExpr : public Expression
{
public:
  EqualToExpr(Expression* l, Expression* r);// : Expression(), l(l), r(r) {}
  Reg* emit() override; 
  bool isConst() override {return l->isConst() && r->isConst();}
  Value getValue() override;
  std::string getType() override;
private:
  Expression* l, *r;
}; 

class NotEqualToExpr : public Expression
{
public:
  NotEqualToExpr(Expression* l, Expression* r);// : Expression(), l(l), r(r) {}
  Reg* emit() override; 
  bool isConst() override {return l->isConst() && r->isConst();}
  Value getValue() override;
  std::string getType() override;
private:
  Expression* l, *r;
};

class LessThanEqualToExpr : public Expression
{
public:
  LessThanEqualToExpr(Expression* l, Expression* r);// : Expression(), l(l), r(r) {}
  Reg* emit() override; 
  bool isConst() override {return l->isConst() && r->isConst();}
  Value getValue() override;
  std::string getType() override;
private:
  Expression* l, *r;
};

class GreaterThanEqualToExpr : public Expression
{
public:
  GreaterThanEqualToExpr(Expression* l, Expression* r);// : Expression(), l(l), r(r) {}
  Reg* emit() override; 
  bool isConst() override {return l->isConst() && r->isConst();}
  Value getValue() override;
  std::string getType() override;
private:
  Expression* l, *r;
};

class LessThanExpr : public Expression
{
public:
  LessThanExpr(Expression* l, Expression* r);// : Expression(), l(l), r(r) {}
  Reg* emit() override; 
  bool isConst() override {return l->isConst() && r->isConst();}
  Value getValue() override;
  std::string getType() override;
private:
  Expression* l, *r;
};

class GreaterThanExpr : public Expression
{
public:
  GreaterThanExpr(Expression* l, Expression* r);// : Expression(), l(l), r(r) {}
  Reg* emit() override; 
  bool isConst() override {return l->isConst() && r->isConst();}
  Value getValue() override;
  std::string getType() override;
private:
  Expression* l, *r;
};

class AddExpr : public Expression
{
public:
  AddExpr(Expression* l, Expression* r);// : Expression(), l(l), r(r) {}
  Reg* emit() override; 
  bool isConst() override {return l->isConst() && r->isConst();}
  Value getValue() override;
  std::string getType() override;
private:
  Expression* l, *r;
};

class SubExpr : public Expression
{
public:
  SubExpr(Expression* l, Expression* r);
  Reg* emit() override; 
  bool isConst() override {return l->isConst() && r->isConst();}
  Value getValue() override;
  std::string getType() override;
private:
  Expression* l, *r;
};

class MultExpr : public Expression
{
public:
  MultExpr(Expression* l, Expression* r);
  Reg* emit() override; 
  bool isConst() override {return l->isConst() && r->isConst();}
  Value getValue() override;
  std::string getType() override;
private:
  Expression* l, *r;
};

class DivExpr : public Expression
{
public:
  DivExpr(Expression* l, Expression* r);
  Reg* emit() override; 
  bool isConst() override {return l->isConst() && r->isConst();}
  Value getValue() override;
  std::string getType() override;
private:
  Expression* l, *r;
};

class ModExpr : public Expression
{
public:
  ModExpr(Expression* l, Expression* r);
  Reg* emit() override; 
  bool isConst() override {return l->isConst() && r->isConst();}
  Value getValue() override;
  std::string getType() override;
private:
  Expression* l, *r;
};

class NotExpr : public Expression
{
public:
  NotExpr(Expression* e);// : Expression(), e(e){}
  Reg* emit() override; 
  bool isConst() override {return e->isConst();}
  Value getValue() override;
  std::string getType() override;
private:
  Expression* e;
};

class NegationExpr : public Expression
{
public:
  NegationExpr(Expression* e);// : Expression(), e(e){}
  Reg* emit() override; 
  bool isConst() override {return e->isConst();}
  Value getValue() override;
  std::string getType() override;
private:
  Expression* e;
};

class ParenthesisExpr : public Expression
{
public:
  ParenthesisExpr(Expression* e);// : Expression(), e(e){}
  Reg* emit() override; 
  bool isConst() override {return e->isConst();}
  Value getValue() override;
  std::string getType() override;
private:
  Expression* e;
};

class FunctionCallExpr : public Expression
{
public:
  FunctionCallExpr(std::string id, ExpressionList* el) : Expression(), id(id), el(el) {}
  Reg* emit() override;
  bool isConst() override {return false;}
  Value getValue() override {return 0;}
  std::string getType() override {return SymbolTable::getInstance().retrieveFunctionType(id);}
private:
  std::string id;
  ExpressionList* el;
};

class ChrExpr : public Expression
{
public:
  ChrExpr(Expression* e);// : Expression(), e(e){}
  Reg* emit() override; 
  bool isConst() override {return e->isConst();}
  Value getValue() override;
  std::string getType() override;
private:
  Expression* e;
};

class OrdExpr : public Expression
{
public:
  OrdExpr(Expression* e);// : Expression(), e(e){}
  Reg* emit() override; 
  bool isConst() override {return e->isConst();}
  Value getValue() override;
  std::string getType() override;
private:
  Expression* e;
};

class PredExpr : public Expression
{
public:
  PredExpr(Expression* e) : Expression(), e(e){}
  Reg* emit() override; 
  bool isConst() override {return e->isConst();}
  Value getValue() override;
  std::string getType() override;
private:
  Expression* e;
};

class SuccExpr : public Expression
{
public:
  SuccExpr(Expression* e) : Expression(), e(e){}
  Reg* emit() override; 
  bool isConst() override {return e->isConst();}
  Value getValue() override;
  std::string getType() override;
private:
  Expression* e;
};

class LValueExpr : public Expression
{
public:
  LValueExpr(LValue* lval) : Expression() , lval(lval){}
  Reg* emit() override; 
  bool isConst() override {return SymbolTable::getInstance().retrieveVariableSymbol(lval->getID()).isConst();}
  Value getValue() override;
  std::string getType() override;
  std::string getID() {return lval->getID();}
  LValue* getLValue() {return lval;}
private:
  LValue* lval;
};


class LiteralExpr : public Expression
{
public:
  LiteralExpr(Value val, std::string type);
  LiteralExpr(std::string val, std::string type);
  Reg* emit() override; 
  bool isConst() override {return true;}
  Value getValue() override;
  std::string getType() override;
  std::string getStringValue() {return s_val;}
private:
  const Value val;
  std::string type;
  std::string s_val;
};


#endif