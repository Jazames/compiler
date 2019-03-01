#ifndef
#define

#include<vector>

class Expression
{
private:

public:
	Expression() = default;
	virtual ~Expression() = default;
	virtual void emit() = 0;
	virtual isConst() {return false;}
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
	virtual void emit() = 0;
};

class IdentLValue : public LValue
{
public:
	IdentLValue(Identifier* id, Expression* ex) : LValue(), ident(id), expr(ex) {} 
private:
	Identifier* ident;
	Expression* expr;
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