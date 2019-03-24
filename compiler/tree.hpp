#ifndef TREE_HPP
#define TREE_HPP

#include<vector>
#include<string> 
#include"symbol_table.hpp"
#include"utils.hpp"
#include"statements.hpp"




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
	Value emit();
};






//Functions:
void addVarsToSymbolTable(IdentList* identList, Parse_Type* type);

#endif