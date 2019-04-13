#ifndef TREE_HPP
#define TREE_HPP

#include<vector>
#include<string> 
#include"symbol_table.hpp"
#include"utils.hpp"
#include"statements.hpp"




class Block
{
public:
  Block(StatementSequence* ss) : ss(ss) {}
  void emit() {ss->emit();}
private:
	StatementSequence* ss;
};


/*
struct ProcedureDeclaration
{

};

struct FunctionDeclaration
{

};
*/

/*
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
*/




class IdentList 
{
public:
  IdentList(std::string id) : id_list() {id_list.push_back(id);}
  std::string get(int i){return id_list[i];}
  void addIdent(std::string id) {id_list.push_back(id);}
  int getSize() {return id_list.size();}
private:
  std::vector<std::string> id_list;
};


class RecordLine 
{
public:
  RecordLine(IdentList* identList, Type* type) : identList(identList), type(type) {}
  Type* getType() {return type;}
  IdentList* getList() {return identList;}
private:
  IdentList* identList;
  Type* type;
};

class RecordList 
{
public:
  RecordList() : recordLines() {}
  void addRecordLine(RecordLine* line){recordLines.push_back(line);}
  int getSize() {return recordLines.size();}
  RecordLine* get(int pos) {return recordLines[pos];}
private:
  std::vector<RecordLine*> recordLines;
};



class ConstantDeclaration
{
public:
  ConstantDeclaration(std::string id, Expression* e) : id(id), e(e) {}
  std::string id;
  Expression* e;
};

class ConstantDeclList
{
public:
  ConstantDeclList() : constant_decls() {}
  std::vector<ConstantDeclaration* > constant_decls;
};

class TypeDeclaration
{
public:
  TypeDeclaration(std::string id, Type* type) : id(id), type(type) {}
  std::string id;
  Type* type;
};

class TypeDeclList
{
public:
  TypeDeclList() : type_decls() {}
  std::vector<TypeDeclaration* > type_decls;
};

class VariableDeclaration
{
public:
  VariableDeclaration(IdentList* ident_list, Type* type) : ident_list(ident_list), type(type) {}
  IdentList* ident_list;
  Type* type;
};

class VarDeclList
{
public:
  VarDeclList() : variable_decls() {}
  std::vector<VariableDeclaration* > variable_decls;
};


class Body
{
public:
  Body(ConstantDeclList* const_list, TypeDeclList* type_list, VarDeclList* var_list, Block* block) 
    : const_list(const_list), type_list(type_list), var_list(var_list), block(block) {}
  void emit() {block->emit();}
  VarDeclList* getVarList() {return var_list;}
private:
  ConstantDeclList* const_list;
  TypeDeclList* type_list;
  VarDeclList* var_list;
  Block* block;
};


class ParameterLine
{
public:
  ParameterLine(bool isRef, IdentList* ident_list, Type* type) : isRef(isRef), ident_list(ident_list), type(type) {}
  bool isRef;
  IdentList* ident_list;
  Type* type;
};

class FormalParameters 
{
public:
  FormalParameters() : params() {}
  std::vector<ParameterLine* > params;
};




//Functions:
void addDeclarations(ConstantDeclList* constant_decl_list, TypeDeclList* type_decl_list, VarDeclList* var_decl_list);

void addVarsToSymbolTable(IdentList* identList, Type* type);
void addConstantToSymbolTable(std::string id, Expression* e);

void createProcedure(std::string id, FormalParameters* params, Body* body);
void createFunction(std::string id, FormalParameters* params, Type* type, Body* body);
#endif