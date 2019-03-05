#ifndef
#define

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

}

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
	Value emit(); 
	bool isConst() {return l->isConst() && r->isConst();}
private:
	Expression* l, r;
}; 

class AndExpr : public Expression
{
public:
	AndExpr(Expression* l, Expression* r) : Expression(), l(l), r(r) {}
	Value emit(); 
	bool isConst() {return l->isConst() && r->isConst();}
private:
	Expression* l, r;
};

class EqualToExpr : public Expression
{
public:
	
private:
	Expression* l, r;
}; 

class NotEqualToExpr : public Expression
{
public:
	
private:
	Expression* l, r;
};

class LessThanEqualToExpr : public Expression
{
public:
	
private:
	Expression* l, r;
};

class GreaterThanEqualToExpr : public Expression
{
public:
	
private:
	Expression* l, r;
};

class LessThanExpr : public Expression
{
public:
	
private:
	Expression* l, r;
};

class GreaterThanExpr : public Expression
{
public:
	
private:
	Expression* l, r;
};

class AddExpr : public Expression
{
public:
	
private:
	Expression* l, r;
};

class SubExpr : public Expression
{
public:
	
private:
	Expression* l, r;
};

class MultExpr : public Expression
{
public:
	
private:
	Expression* l, r;
};

class DivExpr : public Expression
{
public:
	
private:
	Expression* l, r;
};

class ModExpr : public Expression
{
public:
	
private:
	Expression* l, r;
};

class NotExpr : public Expression
{
public:
	
private:
	Expression* e;
};

class NegationExpr : public Expression
{
public:
	
private:
	Expression* e;
};

class ParenthesisExpr : public Expression
{
public:
	
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
	
private:
	Expression* e;
};

class OrdExpr : public Expression
{
public:
	
private:
	Expression* e;
};

class PredExpr : public Expression
{
public:
	
private:
	Expression* e;
};

class SuccExpr : public Expression
{
public:
	
private:
	Expression* e;
};

class LValueExpr : public Expression
{
public:
	
private:
	LValue* lval;
};

class LiteralExpr : public Expression
{
public:
	LiteralExpr(int val) : Expression(), val(val) {}
	Value emit(); 
	bool isConst() {return true;}
private:
	int val;
};






class IdentLValue : public LValue
{
public:
	IdentLValue(Identifier* id) : LValue(), ident(id) {} 
	Value Emit();
	bool isConst() {return false;}
private:
	Identifier* ident;
	Expression* expr;
	bool const;
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
private:
	LValue* lval;
	Expression* expr;

public:
	Assignment(Lvalue* l, Expression* e) : Statement(), lval(l), expr(e) {}
	void emit() override;
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