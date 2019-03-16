#ifndef TREE_HPP
#define TREE_HPP

#include<vector>



using Value = int;

class Expression
{
private:

public:
	Expression() = default;
	virtual ~Expression() = default;
	virtual Value emit() = 0;
	virtual bool isConst() {return false;}
};

class Identifier {
public:

private:

};

class LValue
{
private:

public:
	LValue() = default;
	virtual ~LValue() = default;
	virtual Value emit() = 0;
	virtual bool isConst() {return false;}
};






class OrExpr : public Expression
{
public:
	OrExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) {}
	Value emit() override; 
	bool isConst() override {return l->isConst() && r->isConst();}
private:
	Expression* l, *r;
}; 

class AndExpr : public Expression
{
public:
	AndExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) {}
	Value emit() override; 
	bool isConst() override {return l->isConst() && r->isConst();}
private:
	Expression* l, *r;
};

class EqualToExpr : public Expression
{
public:
	EqualToExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) {}
	Value emit() override; 
	bool isConst() override {return l->isConst() && r->isConst();}
private:
	Expression* l, *r;
}; 

class NotEqualToExpr : public Expression
{
public:
	NotEqualToExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) {}
	Value emit() override; 
	bool isConst() override {return l->isConst() && r->isConst();}
private:
	Expression* l, *r;
};

class LessThanEqualToExpr : public Expression
{
public:
	LessThanEqualToExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) {}
	Value emit() override; 
	bool isConst() override {return l->isConst() && r->isConst();}
private:
	Expression* l, *r;
};

class GreaterThanEqualToExpr : public Expression
{
public:
	GreaterThanEqualToExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) {}
	Value emit() override; 
	bool isConst() override {return l->isConst() && r->isConst();}
private:
	Expression* l, *r;
};

class LessThanExpr : public Expression
{
public:
	LessThanExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) {}
	Value emit() override; 
	bool isConst() override {return l->isConst() && r->isConst();}
private:
	Expression* l, *r;
};

class GreaterThanExpr : public Expression
{
public:
	GreaterThanExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) {}
	Value emit() override; 
	bool isConst() override {return l->isConst() && r->isConst();}
private:
	Expression* l, *r;
};

class AddExpr : public Expression
{
public:
	AddExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) {}
	Value emit() override; 
	bool isConst() override {return l->isConst() && r->isConst();}
private:
	Expression* l, *r;
};

class SubExpr : public Expression
{
public:
	SubExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) {}
	Value emit() override; 
	bool isConst() override {return l->isConst() && r->isConst();}
private:
	Expression* l, *r;
};

class MultExpr : public Expression
{
public:
	MultExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) {}
	Value emit() override; 
	bool isConst() override {return l->isConst() && r->isConst();}
private:
	Expression* l, *r;
};

class DivExpr : public Expression
{
public:
	DivExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) {}
	Value emit() override; 
	bool isConst() override {return l->isConst() && r->isConst();}
private:
	Expression* l, *r;
};

class ModExpr : public Expression
{
public:
	ModExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) {}
	Value emit() override; 
	bool isConst() override {return l->isConst() && r->isConst();}
private:
	Expression* l, *r;
};

class NotExpr : public Expression
{
public:
	NotExpr(Expression* e) : Expression(), e(e){}
	Value emit() override; 
	bool isConst() override {return e->isConst();}
private:
	Expression* e;
};

class NegationExpr : public Expression
{
public:
	NegationExpr(Expression* e) : Expression(), e(e){}
	Value emit() override; 
	bool isConst() override {return e->isConst();}
private:
	Expression* e;
};

class ParenthesisExpr : public Expression
{
public:
	ParenthesisExpr(Expression* e) : Expression(), e(e){}
	Value emit() override; 
	bool isConst() override {return e->isConst();}
private:
	Expression* e;
};

class FunctionCallExpr : public Expression
{
public:
	
private:
	
};

class ChrExpr : public Expression
{
public:
	ChrExpr(Expression* e) : Expression(), e(e){}
	Value emit() override; 
	bool isConst() override {return e->isConst();}
private:
	Expression* e;
};

class OrdExpr : public Expression
{
public:
	OrdExpr(Expression* e) : Expression(), e(e){}
	Value emit() override; 
	bool isConst() override {return e->isConst();}
private:
	Expression* e;
};

class PredExpr : public Expression
{
public:
	PredExpr(Expression* e) : Expression(), e(e){}
	Value emit() override; 
	bool isConst() override {return e->isConst();}
private:
	Expression* e;
};

class SuccExpr : public Expression
{
public:
	SuccExpr(Expression* e) : Expression(), e(e){}
	Value emit() override; 
	bool isConst() override {return e->isConst();}
private:
	Expression* e;
};

class LValueExpr : public Expression
{
public:
	LValueExpr() : Expression() {}
	Value emit() override; 
	bool isConst() override {return lval->isConst();}
private:
	LValue* lval;
};

class LiteralExpr : public Expression
{
public:
	LiteralExpr(Value val) : Expression(), val(val) {}
	Value emit() override; 
	bool isConst() override {return true;}
private:
	const Value val;
};






class IdentLValue : public LValue
{
public:
	IdentLValue(Identifier* id, bool isDeclConst) : LValue(), ident(id), isDeclConst(isDeclConst) {} 
	Value Emit();
	bool isConst() override {return isDeclConst;}
private:
	Identifier* ident;
	Expression* expr;
	const bool isDeclConst;
};

class ArrayLValue : public LValue
{
public:

private:

};

class MemberLValue : public LValue
{
public:

private:

};

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

class Read : public Statement
{

};

class Write : public Statement
{

};

class Null : public Statement
{

};

class Block
{
private:
	std::vector<Statement> statement_sequence;
public:
	void emit();
};

class ConstantDeclaration
{

};

class TypeDeclaration
{

};

class VariableDeclaration
{

};

class ProcedureDeclaration
{

};

class FunctionDeclaration
{

};


class Program 
{
private:
	std::vector<ConstantDeclaration>   constant_decls;
	std::vector<TypeDeclaration>           type_decls;
	std::vector<VariableDeclaration>   variable_decls;
	std::vector<ProcedureDeclaration> procedure_decls;
	std::vector<FunctionDeclaration>   function_decls;
	Block block;
public: 
	void emit();
};





#endif