#ifndef STATEMENTS_HPP
#define STATEMENTS_HPP

#include <string>
#include <iostream>
#include <vector>
#include "symbol_table.hpp"
#include "leaves.hpp"
#include "expressions.hpp"


class Statement
{
private:

public:
  Statement() = default;
  virtual ~Statement() = default;
  virtual void emit() = 0;
};
 
class Assignment : public Statement
{
public:
  Assignment(LValue* l, Expression* e) : Statement(), lval(l), e(e) {}
  void emit() override;
private:
  LValue* lval;
  Expression* e;
};

class LValueList
{
public:
  LValueList(LValue* l) {lvalue_list.push_back(l);}
  LValueList* addLValue(LValue* l) {lvalue_list.insert(lvalue_list.begin(),l);}
  int size() {return lvalue_list.size();}
  LValue* get(int pos) {return lvalue_list[pos];}
private:
  std::vector<LValue*> lvalue_list;
};

class Read : public Statement
{
public:
  Read(LValueList* lvl);
  void emit();
private:
  std::vector<LValue*> lvalue_list;
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

class Write : public Statement
{
public: 
  Write(ExpressionList* el);
  void emit();
private:
  std::vector<Expression*> expression_list;
};

class Null : public Statement
{
  //Null Statements don't do anything. 
};


//Functions:
void emitAssignmentStatment(LValue* lval, Expression* e);


#endif