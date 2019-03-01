

#include "Expressions.hpp"



templat<typename ExprT, typename F>
Expr* make(Expr*l,Expr*r,F f)
{
	if(l->isConst() && r->())
	{
		//if they are constant, then create a new literal value with the 
		//  value of the two literals and the function acting on them.
		auto litL = dynamic_cast<Literal*>(l);
		auto litR = dynamic_cast<Literal*>(r);
		return new Literal(f(litL->v,litR->v));//creates a new literal from a function. 
	}
	else
	{
		return new ExprT(l,r);
	}
}

Value getNextValue()
{
	static Value cur = 0;
	return cur++;
}

//Calls the 
Expr* makeAdd(Expr*l, Expr*r)
{
	return make<Add>(l,r,[](float a, float b){return a+b;})
}
Expr* makeSub(Expr*l, Expr*r)
{
	return make<Sub>(l,r,[](float a, float b){return a-b;})
}
Expr* makeMult(Expr*l, Expr*r)
{
	return make<Mult>(l,r,[](float a, float b){return a*b;})
}
Expr* makeDiv(Expr*l, Expr*r)
{
	return make<Div>(l,r,[](float a, float b){return a/b;})
}


//Gotta emit assembly.
Value Add::emit()
{
	auto lv = l->emit();
	auto rv = r->emit();
	auto result = getNextValue();
	std::cout << "add " << result << "," << lv << "," << rv << '\n'; //newline to not flush stream.
	return result;
}

Value Sub::emit()
{
	auto lv = l->emit();
	auto rv = r->emit();
	auto result = getNextValue();
	std::cout << "sub " << result << "," << lv << "," << rv << '\n'; //newline to not flush stream.
	return result;
}

Value Mult::emit()
{
	auto lv = l->emit();
	auto rv = r->emit();
	auto result = getNextValue();
	std::cout << "mult " << "," << lv << "," << rv << '\n'; //newline to not flush stream.
	std::cout << "mflo " << result << '\n';
	return result;
}

Value Div::emit()
{
	auto lv = l->emit();
	auto rv = r->emit();
	auto result = getNextValue();
	std::cout << "div " << "," << lv << "," << rv << '\n'; //newline to not flush stream.
	std::cout << "mfhi " << result << '\n';
	return result;
}

Value Literal::emit()
{
	auto result = getNextValue();
	std::cout << "li " << result << "," << v << '\n';
	return result;
}

Value Var::emit()
{
	auto result = getNextValue();
	std::cout << "lw " << result << "," << name << '\n';
	return result;
}








