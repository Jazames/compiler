%{
#include <iostream>
#include <map>

#include "symbol_table.hpp"
#include "tree.hpp"
#include "types.hpp"

extern "C" int yylex(void);

void yyerror(const char*);
%}

%union
{
int val;  
char* id;
Expression* expr;
ExpressionList* expr_list;
Statement* stmt;
//Write* write_stmt;
LValue* lval;
LValueList* lval_list;
IdentList* ident_list;
Type* p_type;
//Read* read_stmt;
//Assignment* assign_stmt;
RecordLine* record_line;
RecordList* record_list;
StatementSequence* stmt_sequence;
ElseIfSequence* elsif_sequence;
ElseSequence* else_sequence;
Block* block;
Body* body;
VariableDeclaration* var_decl;
ConstantDeclaration* const_decl;
TypeDeclaration* type_decl;
VarDeclList* var_decl_list;
ConstantDeclList* const_decl_list;
TypeDeclList* type_decl_list;
FormalParameters* formal_param;
ParameterLine* param_line;
}

%token ARRAY_TOKEN
%token BEGIN_TOKEN
%token CHR_TOKEN
%token CONST_TOKEN
%token DO_TOKEN
%token DOWNTO_TOKEN
%token ELSE_TOKEN
%token ELSEIF_TOKEN
%token END_TOKEN
%token FOR_TOKEN
%token FORWARD_TOKEN
%token FUNCTION_TOKEN
%token IF_TOKEN
%token OF_TOKEN
%token ORD_TOKEN
%token PRED_TOKEN
%token PROCEDURE_TOKEN
%token READ_TOKEN
%token RECORD_TOKEN
%token REF_TOKEN
%token REPEAT_TOKEN
%token RETURN_TOKEN
%token STOP_TOKEN
%token SUCC_TOKEN
%token THEN_TOKEN
%token TO_TOKEN
%token TYPE_TOKEN
%token UNTIL_TOKEN
%token VAR_TOKEN
%token WHILE_TOKEN
%token WRITE_TOKEN
%token IDENTIFIER_TOKEN
%token ADD_TOKEN
%token SUB_TOKEN
%token MULT_TOKEN
%token DIV_TOKEN
%token AND_TOKEN
%token OR_TOKEN
%token NOT_TOKEN
%token EQUAL_TOKEN
%token NOT_EQUAL_TOKEN
%token LESS_THAN_TOKEN
%token LESS_THAN_EQUAL_TOKEN
%token GREATER_THAN_TOKEN
%token GREATER_THAN_EQUAL_TOKEN
%token DOT_TOKEN
%token COMMA_TOKEN
%token COLON_TOKEN
%token SEMICOLON_TOKEN
%token OPEN_PAREN_TOKEN
%token CLOSE_PAREN_TOKEN
%token OPEN_BRACKET_TOKEN
%token CLOSE_BRACKET_TOKEN
%token ASSIGNMENT_TOKEN
%token MOD_TOKEN
%token OCTAL_LITERAL_TOKEN
%token HEX_LITERAL_TOKEN
%token DECIMAL_LITERAL_TOKEN;
%token CHAR_LITERAL_TOKEN
%token STRING_LITERAL_TOKEN
%token COMMENT_TOKEN

 //TODO: This is broken and needs designing and this comment needs to be deleted. 
%type <expr> Literal
%type <expr> Expression
%type <id> IDENTIFIER_TOKEN
%type <expr_list> ExpressionList
%type <id> CHAR_LITERAL_TOKEN
%type <val> DECIMAL_LITERAL_TOKEN
%type <val> HEX_LITERAL_TOKEN
%type <val> OCTAL_LITERAL_TOKEN
%type <id> STRING_LITERAL_TOKEN
%type <lval> LValue
%type <lval_list> LValueList
%type <ident_list> IdentList
%type <p_type> Type
%type <p_type> SimpleType
%type <p_type> ArrayType
%type <p_type> RecordType
%type <record_line> RecordLine
%type <record_list> RecordList
%type <stmt_sequence> StatementSequence
%type <stmt> Statement
%type <stmt> Assignment
%type <stmt> IfStatement
%type <stmt> WhileStatement
%type <stmt> RepeatStatement
%type <stmt> ForStatement
%type <stmt> StopStatement
%type <stmt> ReturnStatement
%type <stmt> ReadStatement
%type <stmt> WriteStatement
%type <stmt> ProcedureCall
%type <stmt> NullStatement
%type <elsif_sequence> ElseIfSequence
%type <else_sequence> ElseSequence
%type <block> Block
%type <var_decl> VarDecl
%type <const_decl> ConstantDecl
%type <type_decl> TypeDecl
%type <var_decl_list> VarDeclList
%type <var_decl_list> VarDeclSection
%type <const_decl_list> ConstantDeclList
%type <const_decl_list> ConstantDeclSection
%type <type_decl_list> TypeDeclList
%type <type_decl_list> TypeDeclSection
%type <formal_param> FormalParameters
%type <formal_param> ParameterList
%type <param_line> ParameterLine
%type <body> Body




%left OR_TOKEN
%left AND_TOKEN
%right NOT_TOKEN
%nonassoc EQUAL_TOKEN NOT_EQUAL_TOKEN LESS_THAN_TOKEN LESS_THAN_EQUAL_TOKEN GREATER_THAN_TOKEN GREATER_THAN_EQUAL_TOKEN
%left ADD_TOKEN SUB_TOKEN
%left MULT_TOKEN DIV_TOKEN MOD_TOKEN 
 //%right SUB_TOKEN
 
%%

Program : ProgramDecls ProFuncDeclSection Block DOT_TOKEN {std::cout << "\n\nrealmain:\n\n"; $3->emit();}
        ;

ProgramDecls : ConstantDeclSection TypeDeclSection VarDeclSection {std::cout << "j realmain\n\n";/*Needed here so that the program assigns constants before skipping functions.*/}
             ;


ConstantDeclSection : CONST_TOKEN ConstantDeclList {$$ = $2;}
                    | {$$ = nullptr;}
                    ;
ConstantDeclList : ConstantDeclList ConstantDecl {$$ = $1; $$->constant_decls.push_back($2);}
                 | {$$ = new ConstantDeclList();}
                 ;
ConstantDecl : IDENTIFIER_TOKEN EQUAL_TOKEN Expression SEMICOLON_TOKEN {$$ = new ConstantDeclaration($1, $3); addConstantToSymbolTable($1, $3);}
             ;

TypeDeclSection : TYPE_TOKEN TypeDeclList {$$ = $2;}
                | {$$ = nullptr;}
                ;
TypeDeclList : TypeDeclList TypeDecl {$$ = $1; $$->type_decls.push_back($2);}
             | {$$ = new TypeDeclList();}
             ;
TypeDecl : IDENTIFIER_TOKEN EQUAL_TOKEN Type SEMICOLON_TOKEN {$$ = new TypeDeclaration($1, $3); SymbolTable::getInstance().addType($1, $3);}
         ;
Type : SimpleType {$$ = $1;}
     | RecordType {}
     | ArrayType {}
     ;
SimpleType : IDENTIFIER_TOKEN {$$ = new SimpleType($1);}
           ;
RecordType : RECORD_TOKEN RecordList END_TOKEN {$$ = new RecordType($2);}
RecordList : RecordList RecordLine {$1->addRecordLine($2); $$ = $1;}
           | {$$ = new RecordList();} 
           ;
RecordLine : IdentList COLON_TOKEN Type SEMICOLON_TOKEN {$$ = new RecordLine($1, $3);}
           ;
ArrayType : ARRAY_TOKEN OPEN_BRACKET_TOKEN Expression COLON_TOKEN Expression CLOSE_BRACKET_TOKEN OF_TOKEN Type {$$ = new ArrayType($3, $5, $8);}
          ;
IdentList : IDENTIFIER_TOKEN  {$$ = new IdentList($1);}
          | IDENTIFIER_TOKEN COMMA_TOKEN IdentList {$3->addIdent($1); $$ = $3;}
          ;

VarDeclSection : VAR_TOKEN VarDeclList {$$ = $2;}
               | {$$ = nullptr;}
               ;
VarDeclList : VarDeclList VarDecl {$$ = $1; $$->variable_decls.push_back($2);}
            | {$$ = new VarDeclList();}
            ;
VarDecl : IdentList COLON_TOKEN Type SEMICOLON_TOKEN {$$ = new VariableDeclaration($1, $3); addVarsToSymbolTable($1, $3);}
        ;

ProFuncDeclSection : ProFuncDeclList {}
                   ;
ProFuncDeclList : ProFuncDeclList ProcedureDecl {}
                | ProFuncDeclList FunctionDecl {}
                | {}
                ;
ProcedureDecl : ProcToke IDENTIFIER_TOKEN OPEN_PAREN_TOKEN FormalParameters CLOSE_PAREN_TOKEN SEMICOLON_TOKEN FORWARD_TOKEN SEMICOLON_TOKEN {}
              | ProcToke IDENTIFIER_TOKEN OPEN_PAREN_TOKEN FormalParameters CLOSE_PAREN_TOKEN SEMICOLON_TOKEN     Body      SEMICOLON_TOKEN {createProcedure($2, $4, $7); SymbolTable::getInstance().leaveScope();}
              ;
ProcToke : PROCEDURE_TOKEN {SymbolTable::getInstance().enterScope();}
         ;
FunctionDecl : FuncToke IDENTIFIER_TOKEN OPEN_PAREN_TOKEN FormalParameters CLOSE_PAREN_TOKEN COLON_TOKEN Type SEMICOLON_TOKEN FORWARD_TOKEN SEMICOLON_TOKEN {}
             | FuncToke IDENTIFIER_TOKEN OPEN_PAREN_TOKEN FormalParameters CLOSE_PAREN_TOKEN COLON_TOKEN Type SEMICOLON_TOKEN     Body      SEMICOLON_TOKEN {createFunction($2, $4, $7, $9); SymbolTable::getInstance().leaveScope();}
             ;
FuncToke : FUNCTION_TOKEN {SymbolTable::getInstance().enterScope();}
         ;
FormalParameters : ParameterList {$$ = $1;}
                 | {$$ = nullptr;} 
                 ;
ParameterList : ParameterLine {$$ = new FormalParameters(); $$->params.push_back($1);}
              | ParameterLine SEMICOLON_TOKEN ParameterList {$$ = $3; $$->params.push_back($1);}
              ;
ParameterLine : VAR_TOKEN IdentList COLON_TOKEN Type {$$ = new ParameterLine(false, $2, $4);}
              | REF_TOKEN IdentList COLON_TOKEN Type {$$ = new ParameterLine(true,  $2, $4);}
              |           IdentList COLON_TOKEN Type {$$ = new ParameterLine(false, $1, $3);}
              ;
Body : ConstantDeclSection TypeDeclSection VarDeclSection Block {$$ = new Body($1, $2, $3, $4);}
     ;
Block : BEGIN_TOKEN StatementSequence END_TOKEN {$$ = new Block($2);}
      ;

StatementSequence : Statement {$$ = new StatementSequence($1);}
                  | Statement SEMICOLON_TOKEN StatementSequence {$$ = $3; $$->addStatement($1);}
                  ;

Statement : Assignment {}
          | IfStatement {}
          | WhileStatement {}
          | RepeatStatement {}
          | ForStatement {}
          | StopStatement {}
          | ReturnStatement {}
          | ReadStatement {}
          | WriteStatement {}
          | ProcedureCall {}
          | NullStatement {}
          ;
Assignment : LValue ASSIGNMENT_TOKEN Expression {$$ = new Assignment($1, $3);}
           ;
IfStatement : IF_TOKEN Expression THEN_TOKEN StatementSequence ElseIfSequence ElseSequence END_TOKEN {$$ = new If($2, $4, $5, $6);}
            ;
ElseIfSequence : ELSEIF_TOKEN Expression THEN_TOKEN StatementSequence ElseIfSequence {$$ = $5; $$->addElseIf($2, $4);}
               | {$$ = new ElseIfSequence();}
               ;
ElseSequence : ELSE_TOKEN StatementSequence {$$ = new ElseSequence($2);}
             | {$$ = new ElseSequence();}
             ;
WhileStatement : WHILE_TOKEN Expression DO_TOKEN StatementSequence END_TOKEN {$$ = new While($2, $4);}
               ;
RepeatStatement : REPEAT_TOKEN StatementSequence UNTIL_TOKEN Expression {$$ = new Repeat($4, $2);}
                ;
ForStatement : FOR_TOKEN IDENTIFIER_TOKEN ASSIGNMENT_TOKEN Expression TO_TOKEN     Expression DO_TOKEN StatementSequence END_TOKEN {$$ = new For($2, $4, false, $6, $8);}
             | FOR_TOKEN IDENTIFIER_TOKEN ASSIGNMENT_TOKEN Expression DOWNTO_TOKEN Expression DO_TOKEN StatementSequence END_TOKEN {$$ = new For($2, $4, true,  $6, $8);}
             ;
StopStatement : STOP_TOKEN {$$ = new Stop();}
              ;
ReturnStatement : RETURN_TOKEN Expression {$$ = new Return($2);}
                | RETURN_TOKEN {$$ = new Return(nullptr);}
                ;
ReadStatement : READ_TOKEN OPEN_PAREN_TOKEN LValueList CLOSE_PAREN_TOKEN {$$ = new Read($3);}
              ;
LValueList : LValue {$$ = new LValueList($1);}
           | LValue COMMA_TOKEN LValueList {$3->addLValue($1); $$ = $3;}
           ;
WriteStatement : WRITE_TOKEN OPEN_PAREN_TOKEN ExpressionList CLOSE_PAREN_TOKEN {$$ = new Write($3);}
               ;
ExpressionList : Expression {$$ = new ExpressionList($1);}
               | Expression COMMA_TOKEN ExpressionList {$3->addExpression($1); $$ = $3;}
               ;
ProcedureCall : IDENTIFIER_TOKEN OPEN_PAREN_TOKEN ExpressionList CLOSE_PAREN_TOKEN {$$ = new ProcedureCall($1, $3);}
              | IDENTIFIER_TOKEN OPEN_PAREN_TOKEN                CLOSE_PAREN_TOKEN {$$ = new ProcedureCall($1, nullptr);}
              ;
NullStatement : {$$ = new Null();}
              ;

Expression : Expression OR_TOKEN Expression {$$ = new OrExpr($1,$3);}
           | Expression AND_TOKEN Expression {$$ = new AndExpr($1,$3);}
           | Expression EQUAL_TOKEN Expression {$$ = new EqualToExpr($1,$3);}
           | Expression NOT_EQUAL_TOKEN Expression {$$ = new NotEqualToExpr($1,$3);}
           | Expression LESS_THAN_EQUAL_TOKEN Expression {$$ = new LessThanEqualToExpr($1,$3);}
           | Expression GREATER_THAN_EQUAL_TOKEN Expression {$$ = new GreaterThanEqualToExpr($1,$3);}
           | Expression LESS_THAN_TOKEN Expression {$$ = new LessThanExpr($1,$3);}
           | Expression GREATER_THAN_TOKEN Expression {$$ = new GreaterThanExpr($1,$3);}
           | Expression ADD_TOKEN Expression {$$ = new AddExpr($1,$3);}
           | Expression SUB_TOKEN Expression {$$ = new SubExpr($1,$3);}
           | Expression MULT_TOKEN Expression {$$ = new MultExpr($1,$3);}
           | Expression DIV_TOKEN Expression {$$ = new DivExpr($1,$3);}
           | Expression MOD_TOKEN Expression {$$ = new ModExpr($1,$3);}
           | NOT_TOKEN Expression {$$ = new NotExpr($2);}
           | SUB_TOKEN Expression {$$ = new NegationExpr($2);}
           | OPEN_PAREN_TOKEN Expression CLOSE_PAREN_TOKEN  {$$ = new ParenthesisExpr($2);}
           | IDENTIFIER_TOKEN OPEN_PAREN_TOKEN ExpressionList CLOSE_PAREN_TOKEN {$$ = new FunctionCallExpr($1, $3);}
           | IDENTIFIER_TOKEN OPEN_PAREN_TOKEN                CLOSE_PAREN_TOKEN {$$ = new FunctionCallExpr($1, nullptr);}
           | CHR_TOKEN OPEN_PAREN_TOKEN Expression CLOSE_PAREN_TOKEN {$$ = new ChrExpr($3);}
           | ORD_TOKEN OPEN_PAREN_TOKEN Expression CLOSE_PAREN_TOKEN {$$ = new OrdExpr($3);}
           | PRED_TOKEN OPEN_PAREN_TOKEN Expression CLOSE_PAREN_TOKEN {$$ = new PredExpr($3);}
           | SUCC_TOKEN OPEN_PAREN_TOKEN Expression CLOSE_PAREN_TOKEN {$$ = new SuccExpr($3);}
           | LValue {$$ = new LValueExpr($1);}
           | Literal {$$ = $1;}
           ;

LValue : IDENTIFIER_TOKEN {$$ = new IdentLValue($1);}
       | LValue OPEN_BRACKET_TOKEN Expression CLOSE_BRACKET_TOKEN {$$ = new ArrayLValue($1, $3);}
       | LValue DOT_TOKEN IDENTIFIER_TOKEN {$$ = new RecordLValue($1, $3);}
       ;


Literal : CHAR_LITERAL_TOKEN {$$ = new LiteralExpr($1, "char");}
        | HEX_LITERAL_TOKEN {$$ = new LiteralExpr($1, "integer");}
        | OCTAL_LITERAL_TOKEN {$$ = new LiteralExpr($1, "integer");}
        | DECIMAL_LITERAL_TOKEN {$$ = new LiteralExpr($1, "integer");}
        | STRING_LITERAL_TOKEN {$$ = new LiteralExpr($1, "string");} 
        ;

%%

void yyerror(const char* msg)
{
  std::cerr << msg << " at line number " << SymbolTable::getInstance().getLineNumber() << std::endl;
}


















