%{
#include <iostream>
#include <map>

#include "symbol_table.hpp"
#include "tree.hpp"

extern "C" int yylex(void);

void yyerror(const char*);
%}

%union
{
int val;  
char* id;
Expression* expr;
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
%type <val> Literal
%type <expr> Expression
%type <id> IDENTIFIER_TOKEN

 //%right SUB_TOKEN
%left MULT_TOKEN DIV_TOKEN MOD_TOKEN 
%left ADD_TOKEN SUB_TOKEN
%nonassoc EQUAL_TOKEN NOT_EQUAL_TOKEN LESS_THAN_TOKEN LESS_THAN_EQUAL_TOKEN GREATER_THAN_TOKEN GREATER_THAN_EQUAL_TOKEN
%right NOT_TOKEN
%left AND_TOKEN
%left OR_TOKEN

 
%%

Program : ConstantDeclSection TypeDeclSection VarDeclSection ProFuncDeclSection Block {} DOT_TOKEN
        ;

ConstantDeclSection : CONST_TOKEN ConstantDeclList {}
                    | {}
                    ;
ConstantDeclList : ConstantDeclList ConstantDecl {}
                 | {}
                 ;
ConstantDecl : IDENTIFIER_TOKEN EQUAL_TOKEN Expression SEMICOLON_TOKEN {}
             ;

TypeDeclSection : TYPE_TOKEN TypeDeclList
                | {}
                ;
TypeDeclList : TypeDeclList TypeDecl {}
             | {}
             ;
TypeDecl : IDENTIFIER_TOKEN EQUAL_TOKEN Type SEMICOLON_TOKEN {}
         ;
Type : SimpleType {}
     | RecordType {}
     | ArrayType {}
     ;
SimpleType : IDENTIFIER_TOKEN {}
           ;
RecordType : RECORD_TOKEN RecordList END_TOKEN {}
RecordList : RecordList RecordLine {}
           | {} {}
           ;
RecordLine : IdentList COLON_TOKEN Type SEMICOLON_TOKEN {}
           ;
ArrayType : ARRAY_TOKEN OPEN_BRACKET_TOKEN Expression COLON_TOKEN Expression CLOSE_BRACKET_TOKEN OF_TOKEN Type {}
          ;
IdentList : IDENTIFIER_TOKEN  {}
          | IDENTIFIER_TOKEN COMMENT_TOKEN IdentList {}
          ;

VarDeclSection : VAR_TOKEN VarDeclList {}
               | {}
               ;
VarDeclList : VarDeclList VarDecl {}
            | {}
            ;
VarDecl : IdentList COLON_TOKEN Type SEMICOLON_TOKEN {}
        ;

ProFuncDeclSection : ProFuncDeclList {}
                   ;
ProFuncDeclList : ProFuncDeclList ProcedureDecl {}
                | ProFuncDeclList FunctionDecl {}
                | {}
                ;
ProcedureDecl : PROCEDURE_TOKEN IDENTIFIER_TOKEN OPEN_PAREN_TOKEN FormalParameters CLOSE_PAREN_TOKEN SEMICOLON_TOKEN FORWARD_TOKEN SEMICOLON_TOKEN {}
              | PROCEDURE_TOKEN IDENTIFIER_TOKEN OPEN_PAREN_TOKEN FormalParameters CLOSE_PAREN_TOKEN SEMICOLON_TOKEN     Body      SEMICOLON_TOKEN {}
              ;
FunctionDecl : FUNCTION_TOKEN IDENTIFIER_TOKEN OPEN_PAREN_TOKEN FormalParameters CLOSE_PAREN_TOKEN COLON_TOKEN Type SEMICOLON_TOKEN FORWARD_TOKEN SEMICOLON_TOKEN {}
             | FUNCTION_TOKEN IDENTIFIER_TOKEN OPEN_PAREN_TOKEN FormalParameters CLOSE_PAREN_TOKEN COLON_TOKEN Type SEMICOLON_TOKEN     Body      SEMICOLON_TOKEN {}
             ;
FormalParameters : ParameterList {}
                 | {} 
                 ;
ParameterList : ParameterLine {}
              | ParameterLine SEMICOLON_TOKEN ParameterList {}
              ;
ParameterLine : VarOrRef IdentList COLON_TOKEN Type {}
              ;
VarOrRef : VAR_TOKEN {}
         | REF_TOKEN {}
         | {}
         ;
Body : ConstantDeclSection TypeDeclSection VarDeclSection Block {}
     ;
Block : BEGIN_TOKEN StatementSequence END_TOKEN {}
      ;

StatementSequence : Statement {}
                  | Statement SEMICOLON_TOKEN StatementSequence {}
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
Assignment : LValue ASSIGNMENT_TOKEN Expression {}
           ;
IfStatement : IF_TOKEN Expression THEN_TOKEN StatementSequence ElseIfSequence ElseSequence END_TOKEN {}
            ;
ElseIfSequence : ELSEIF_TOKEN Expression THEN_TOKEN StatementSequence ElseIfSequence {}
               | {}
               ;
ElseSequence : ELSE_TOKEN StatementSequence {}
             | {}
             ;
WhileStatement : WHILE_TOKEN Expression DO_TOKEN StatementSequence END_TOKEN {}
               ;
RepeatStatement : REPEAT_TOKEN StatementSequence UNTIL_TOKEN Expression {}
                ;
ForStatement : FOR_TOKEN IDENTIFIER_TOKEN ASSIGNMENT_TOKEN Expression TO_TOKEN     Expression DO_TOKEN StatementSequence END_TOKEN {}
             | FOR_TOKEN IDENTIFIER_TOKEN ASSIGNMENT_TOKEN Expression DOWNTO_TOKEN Expression DO_TOKEN StatementSequence END_TOKEN {}
             ;
StopStatement : STOP_TOKEN {}
              ;
ReturnStatement : RETURN_TOKEN Expression {}
                | RETURN_TOKEN {}
                ;
ReadStatement : READ_TOKEN OPEN_PAREN_TOKEN LValueList CLOSE_PAREN_TOKEN {}
              ;
LValueList : LValue {}
           | LValue COMMA_TOKEN LValueList {}
           ;
WriteStatement : WRITE_TOKEN OPEN_PAREN_TOKEN ExpressionList CLOSE_PAREN_TOKEN {}
               ;
ExpressionList : Expression {}
               | Expression COMMA_TOKEN ExpressionList {}
               ;
ProcedureCall : IDENTIFIER_TOKEN OPEN_PAREN_TOKEN ExpressionList CLOSE_PAREN_TOKEN {}
              | IDENTIFIER_TOKEN OPEN_PAREN_TOKEN                CLOSE_PAREN_TOKEN {}
              ;
NullStatement : {}
              ;

Expression : Expression OR_TOKEN Expression {}
           | Expression AND_TOKEN Expression {}
           | Expression EQUAL_TOKEN Expression {}
           | Expression NOT_EQUAL_TOKEN Expression {}
           | Expression LESS_THAN_EQUAL_TOKEN Expression {}
           | Expression GREATER_THAN_EQUAL_TOKEN Expression {}
           | Expression LESS_THAN_TOKEN Expression {}
           | Expression GREATER_THAN_TOKEN Expression {}
           | Expression ADD_TOKEN Expression {}
           | Expression SUB_TOKEN Expression {}
           | Expression MULT_TOKEN Expression {}
           | Expression DIV_TOKEN Expression {}
           | Expression MOD_TOKEN Expression {}
           | NOT_TOKEN Expression {}
           | SUB_TOKEN Expression {}
           | OPEN_PAREN_TOKEN Expression CLOSE_PAREN_TOKEN  {}
           | IDENTIFIER_TOKEN OPEN_PAREN_TOKEN ExpressionList CLOSE_PAREN_TOKEN {}
           | IDENTIFIER_TOKEN OPEN_PAREN_TOKEN                CLOSE_PAREN_TOKEN {}
           | CHR_TOKEN OPEN_PAREN_TOKEN Expression CLOSE_PAREN_TOKEN {}
           | ORD_TOKEN OPEN_PAREN_TOKEN Expression CLOSE_PAREN_TOKEN {}
           | PRED_TOKEN OPEN_PAREN_TOKEN Expression CLOSE_PAREN_TOKEN {}
           | SUCC_TOKEN OPEN_PAREN_TOKEN Expression CLOSE_PAREN_TOKEN {}
           | LValue {}
           | Literal {}
           ;



LValue : IDENTIFIER_TOKEN {}
       | LValue OPEN_BRACKET_TOKEN Expression CLOSE_BRACKET_TOKEN {}
       | LValue DOT_TOKEN IDENTIFIER_TOKEN {}
       ;


Literal : CHAR_LITERAL_TOKEN {}
       | HEX_LITERAL_TOKEN {}
       | OCTAL_LITERAL_TOKEN {}
       | DECIMAL_LITERAL_TOKEN {}
       | STRING_LITERAL_TOKEN { /*This might be very wrong.*/} 
       ;

%%

void yyerror(const char* msg)
{
  std::cerr << msg << " at line number " << SymbolTable::getInstance().getLineNumber() << std::endl;
}


















