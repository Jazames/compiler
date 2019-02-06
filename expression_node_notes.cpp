namespace cs5300
{
	class Type 
	{
		virtual int size() = 0;
	};

	class IntegerType : public Type;
	{
		int size() override {return 4;};
	};

	IntegerType intType;



	class ExprValue //formerly called foo
	{
		virtual Register getValue() = 0; //<-- this is the 'get the into a register function'
		virtual bool isLiteral() = 0;
	};

	class Literal : public ExprValue
	{
		int value; 
		Register getValue()
		{
			auto result = REgisterPool::getReg();
			std::cout << "li " << result << "," << value << "\n";
			return result;
		}

	};

	class Variable: public ExprValue
	{
		std:string reg;
		int offset;
		Register getValue()
		{
			auto result = RegisterPool::getReg();
			std::cout << "lw " << result << "," << offset << "(" << reg << ")\n";
			return result;
		}
	}

	class RegisterValue : public ExprValue
	{
		RegisterValue(Register r) :r(r) {}; //Constructor that builds a REgistervalue by putting the register in the register field. 
		Register r;
		Register getValue(){return r;}
	}

	class Expr
	{
		Type* type;
		Foo* value;
	};

	Expr add(Expr a, Expr b)
	{
		//There's a special case we want to take care of
		if (a.type != b.type) throw "fit"; //Now the code is safe. 
		//The other thing we want to do is to check if those values are literal values or not. 
		if(a.value->isLiteral() && v.value->isLiteral())
		{
			//Literal stuff
			auto lita = dynamic_cast<Literal*> (a.value);
			auto litb = dynamic_cast<Literal*> (b.value); //The lack of cout statements here means that the work is done at compiletime, not runtime. 
			return new LiteralValue(lita.value + litb.value);//just do the work at compiletime. 
		}
		else
		{
			auto aval = a.value.getvalue();
			auto bval = b.value.getValue();
			auto result = RegisterPool::getREg();
			std::cout << "add " << result << "," << aval << "," bval << "\n"; 
			return RegisterValue(result);
		}
	}

	Expr mult(Expr a, Expr b)
	{
		auto aval = a.value.getvalue();
		auto bval = b.value.getValue();
		auto result = RegisterPool::getREg();
		std::cout << "mult " << aval << "," bval << "\n"; 
		std::cout << "mflo " << result << "\n";
		return RegisterValue(result);
	}
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


If building the tree instead:


namespace cs5300
{
	class Type 
	{
		virtual int size() = 0;
	};

	class IntegerType : public Type;
	{
		int size() override {return 4;};
	};

	IntegerType intType;



	class ExprValue //formerly called foo
	{
		virtual Register getValue() = 0; //<-- this is the 'get the into a register function'
		virtual bool isLiteral() = 0;
	};

	class Literal : public ExprValue
	{
		int value; 
		Register getValue()
		{
			auto result = REgisterPool::getReg();
			std::cout << "li " << result << "," << value << "\n";
			return result;
		}

	};

	class Variable: public ExprValue
	{
		std:string reg;
		int offset;
		Register getValue()
		{
			auto result = RegisterPool::getReg();
			std::cout << "lw " << result << "," << offset << "(" << reg << ")\n";
			return result;
		}
	}

	class RegisterValue : public ExprValue
	{
		RegisterValue(Register r) :r(r) {}; //Constructor that builds a REgistervalue by putting the register in the register field. 
		Register r;
		Register getValue(){return r;}
	}

	class Expr
	{
		Type* type;
		Foo* value;
	};

	Expr add(Expr a, Expr b)
	{
		//There's a special case we want to take care of
		if (a.type != b.type) throw "fit"; //Now the code is safe. 
		//The other thing we want to do is to check if those values are literal values or not. 
		if(a.value->isLiteral() && v.value->isLiteral())
		{
			//Literal stuff
			auto lita = dynamic_cast<Literal*> (a.value);
			auto litb = dynamic_cast<Literal*> (b.value); //The lack of cout statements here means that the work is done at compiletime, not runtime. 
			return new LiteralValue(lita.value + litb.value);//just do the work at compiletime. 
		}
		else
		{
			auto aval = a.value.getvalue();
			auto bval = b.value.getValue();
			auto result = RegisterPool::getREg();
			std::ostreamstring oss;
			oss << "add " << result << "," << aval << "," bval << "\n"; 

			Expr* result new Expr;


			return RegisterValue(result);
		}
	}

	Expr mult(Expr a, Expr b)
	{
		auto aval = a.value.getvalue();
		auto bval = b.value.getValue();
		auto result = RegisterPool::getREg();
		std::cout << "mult " << aval << "," bval << "\n"; 
		std::cout << "mflo " << result << "\n";
		return RegisterValue(result);
	}

	////////// This is for building the tree yourself. /////////////////
	class Expr();

	class AddExpr
	{
		Expr* left;
		Expr* right;
	}

	class UnMinus : Expr;
	{
		Expr* value;
	}



}