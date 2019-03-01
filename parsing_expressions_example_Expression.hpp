#ifndef EXPRESSION
#define EXPRESSION


#include <iosream>
#include <string>

//If we decide we want something more out of Value, then we can update it. 
using Value = int;

Value getNextValue();


class Expr
{
	Expr() = default;
	virtual ~Expr() = default;
	virtual Value emit() = 0;
	virtual bool isConst() {return false;} 
};




class Add : public Expr
{
public:
	Add(Expr*l, Expr* r):Expr(),l(l),r(r){}
	Value emit() override;

private:
	Expr* l, *r;
}


class Sub : public Expr
{
public:
	Sub(Expr*l, Expr* r):Expr(),l(l),r(r){}
	Value emit() override;

private:
	Expr*l, *r;
}



class Mult : public Expr
{
public:
	Mult(Expr*l, Expr* r):Expr(),l(l),r(r){}
	Value emit() override;

private:
	Expr*l, *r;
}


class Div : public Expr
{
public:
	Div(Expr*l, Expr* r):Expr(),l(l),r(r){}
	Value emit() override;

private:
	Expr*l, *r;
}



class Add : public Expr
{
public:
	Add(Expr*l, Expr* r):Expr(),l(l),r(r){}
	Value emit() override;

private:
	Expr*l, *r;
}

class Literal : public Expr
{
public:
	Literal(float v): Expr(),v(v) {}
	const float v;
	Value emit() override;
	bool isConst() override {return true;}
}

class Variable : public Expr
{
public: 
	Var(std::string name): Expr(),name(name){}
	const std::string name;
	Value emit() override;
}



//Factory pattern.
Expr* makeAdd(Expr*l, Expr*r);
Expr* makeSub(Expr*l, Expr*r);
Expr* makeMult(Expr*l, Expr*r);
Expr* makeDiv(Expr*l, Expr*r);

#endif 