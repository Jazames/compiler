

//pointers to base class type works gud for doing types. 

class Type {
	virtual int size();
};


//This could also be primitive type. 
class IntType : public Type 
{
	int Type() = default;
	int size() override { return 4;}
};


IntType int_type;


/*Declaration of a new type:
Type
	<id> : array[<Expression>...<Expression>] of <Type> //The expression needs to evaluate to a constant, and it's type matters for type checking when indexing the array. 
*/

//be aware, that not all types have to have a name. 
	//example
	//compound : arary[0:10] of array[0:10] of integer

//Arrays in CPSL are not necessarilly zero based. They might go from 5 to 80. 

//Steps to get the 
//There are no type errors in any of the examples, so type checking isn't super important. 

class Array : public Type
{
	Type* indexType;
	Type* elementType;
	int lowerbound;
	int upperbound;
	in size() override {return (upperbound - lowerbound + 1) * elementType->size();}//+1 to be inclusive

	//to get the offset, need to get the index from the expression, then subtrac
}

class Record : public Type 
{
	map<std::string, std::pair<int, type*> > 
	
}

//An Lvalue is something that can take an assignment.
class LValue : public Type
{

}




std::vector<std::map<string, Type*> > st(3);//need local, global, and predefined scopes. 


//Iterating through a vector in backwards order
for(auto iter = st.rbegin(); iter != st.rend(); ++iter)

{
	auto found = iter->find(id);
	if(found != iter->end()) return found->second;
}
throw "undefined id"
