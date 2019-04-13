#ifndef STATEMENTS_HPP
#define STATEMENTS_HPP

#include <string>
#include <iostream>
#include <vector>
#include "symbol_table.hpp"
#include "leaves.hpp"
#include "expressions.hpp"



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


class Statement
{
private:

public:
  Statement() = default;
  virtual ~Statement() = default;
  virtual void emit() = 0;
};
 
//Statement Helpers

class StatementSequence 
{
public:
  StatementSequence(Statement* s) : list() {list.push_back(s);}
  void addStatement(Statement* s) {list.push_back(s);}
  void emit();
private:
  std::vector<Statement*> list;
};

class ElseIfSequence
{
public:
  ElseIfSequence() : exprs(), stmts() {}
  void addElseIf(Expression* e, StatementSequence* ss) {exprs.push_back(e); stmts.push_back(ss);}
  int getSize() {return exprs.size();}
  Expression* getExpr(int pos) {return exprs[pos];}
  StatementSequence* getSS(int pos) {return stmts[pos];}
private:
  std::vector<Expression*> exprs;
  std::vector<StatementSequence*> stmts;
};

class ElseSequence
{
public:
  ElseSequence();// : ss(new Null()) {} //Put a statement in there that doesn't do anything. It's safe to put these everywhere. 
  ElseSequence(StatementSequence* ss) : ss(ss) {}
  void emitSS() {ss->emit();}
private:
  StatementSequence* ss;
};

//Statement Derivatives

class Assignment : public Statement
{
public:
  Assignment(LValue* l, Expression* e) : Statement(), lval(l), e(e) {}
  void emit() override;
private:
  LValue* lval;
  Expression* e;
};

class If : public Statement
{
public:
  If(Expression* e, StatementSequence* list, ElseIfSequence* eifs, ElseSequence* els)
    : Statement(), e(e), list(list), eifs(eifs), els(els) {}
  void emit() override;
private:
  Expression* e;
  StatementSequence* list;
  ElseIfSequence* eifs;
  ElseSequence* els;
};

class While : public Statement
{
public:
  While(Expression* e, StatementSequence* ss) : Statement(), e(e), ss(ss) {}
  void emit() override;
private:
  Expression* e;
  StatementSequence* ss;
};

class Repeat : public Statement
{
public:
  Repeat(Expression* e, StatementSequence* ss) : Statement(), e(e), ss(ss) {}
  void emit() override;
private:
  Expression* e;
  StatementSequence* ss;
};

class For : public Statement
{
public:
  For(std::string id, Expression* startE, bool downto, Expression* endE, StatementSequence* ss) 
    : Statement(), id(id), startE(startE), downto(downto), endE(endE), ss(ss) {} 
  void emit();
private:
  bool downto;
  StatementSequence* ss;
  Expression* startE;
  Expression* endE;
  std::string id;
};

class Stop : public Statement
{
public:
  Stop() : Statement() {}
  void emit() override {std::cout << "#terminate program\n";std::cout << "li $v0, 10\nsyscall\n\n";}
private:

};

class Return : public Statement
{
public:
  Return(Expression* e) : Statement(), e(e) {}
  void emit() override;
private:
  Expression* e;
};

class Read : public Statement
{
public:
  Read(LValueList* lvl);
  void emit() override;
private:
  std::vector<LValue*> lvalue_list;
};

class Write : public Statement
{
public: 
  Write(ExpressionList* el);
  void emit() override;
private:
  std::vector<Expression*> expression_list;
};

class ProcedureCall : public Statement
{
public:
  ProcedureCall(std::string id, ExpressionList* el) : Statement(), id(id), el(el) {}
  void emit() override;
private:
  ExpressionList* el;
  std::string id;
};

class Null : public Statement
{
public:
  Null() : Statement() {}
  void emit() override {}//Do nothing. 
private:
  //Null Statements don't do anything. 
};



#endif