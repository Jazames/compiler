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





class IdentList {
public:
  IdentList(std::string id) : id_list() {id_list.push_back(id);}
  std::string get(int i){return id_list[i];}
  void addIdent(std::string id) {id_list.push_back(id);}
  int getSize() {return id_list.size();}
private:
  std::vector<std::string> id_list;
};


//Functions:
void addVarsToSymbolTable(IdentList* identList, Type* type);
void addConstantToSymbolTable(std::string id, Expression* e);

#endif