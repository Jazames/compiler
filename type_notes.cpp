

//pointers to base class type works gud for doing types. 

class Type {
	virtual int size();
};


class IntType : public Type 
{
	int Type() = default;
	int size() override { return 4;}
};


IntType int_type;




class Array : public Type
{
	Type* elementType;
	int lowerbound;
	int upperbound;
	in size() override {return upperbound - lowerbound + 1;}//+1 to be inclusive

	//to get the offset, need to get the index from the expression, then subtrac
}


//An Lvalue is something that can take an assignment.
class LValue : public Type
{

}
