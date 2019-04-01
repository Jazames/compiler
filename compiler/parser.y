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
Write* write_stmt;
LValue* lval;
LValueList* lval_list;
IdentList* ident_list;
Type* p_type;
Read* read_stmt;
Assignment* assign_stmt;
RecordLine* record_line;
RecordList* record_list;
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
%type <write_stmt> WriteStatement
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
%type <read_stmt> ReadStatement
%type <assign_stmt> Assignment
%type <record_line> RecordLine
%type <record_list> RecordList

%left OR_TOKEN
%left AND_TOKEN
%right NOT_TOKEN
%nonassoc EQUAL_TOKEN NOT_EQUAL_TOKEN LESS_THAN_TOKEN LESS_THAN_EQUAL_TOKEN GREATER_THAN_TOKEN GREATER_THAN_EQUAL_TOKEN
%left ADD_TOKEN SUB_TOKEN
%left MULT_TOKEN DIV_TOKEN MOD_TOKEN 
 //%right SUB_TOKEN
 
%%

Program : ConstantDeclSection TypeDeclSection VarDeclSection ProFuncDeclSection Block DOT_TOKEN {}
        ;

ConstantDeclSection : CONST_TOKEN ConstantDeclList {}
                    | {}
                    ;
ConstantDeclList : ConstantDeclList ConstantDecl {}
                 | {}
                 ;
ConstantDecl : IDENTIFIER_TOKEN EQUAL_TOKEN Expression SEMICOLON_TOKEN {addConstantToSymbolTable($1, $3);}
             ;

TypeDeclSection : TYPE_TOKEN TypeDeclList
                | {}
                ;
TypeDeclList : TypeDeclList TypeDecl {}
             | {}
             ;
TypeDecl : IDENTIFIER_TOKEN EQUAL_TOKEN Type SEMICOLON_TOKEN {SymbolTable::getInstance().addType($1, $3);}
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

VarDeclSection : VAR_TOKEN VarDeclList {}
               | {}
               ;
VarDeclList : VarDeclList VarDecl {}
            | {}
            ;
VarDecl : IdentList COLON_TOKEN Type SEMICOLON_TOKEN {addVarsToSymbolTable($1, $3);}
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
Assignment : LValue ASSIGNMENT_TOKEN Expression {$$ = new Assignment($1, $3); $$->emit();}
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
StopStatement : STOP_TOKEN {std::cout << "#terminate program\n";std::cout << "li $v0, 10\nsyscall\n\n";}
              ;
ReturnStatement : RETURN_TOKEN Expression {}
                | RETURN_TOKEN {}
                ;
ReadStatement : READ_TOKEN OPEN_PAREN_TOKEN LValueList CLOSE_PAREN_TOKEN {$$ = new Read($3); $$->emit();}
              ;
LValueList : LValue {$$ = new LValueList($1);}
           | LValue COMMA_TOKEN LValueList {$3->addLValue($1); $$ = $3;}
           ;
WriteStatement : WRITE_TOKEN OPEN_PAREN_TOKEN ExpressionList CLOSE_PAREN_TOKEN {$$ = new Write($3); $$->emit();}
               ;
ExpressionList : Expression {$$ = new ExpressionList($1);}
               | Expression COMMA_TOKEN ExpressionList {$3->addExpression($1); $$ = $3;}
               ;
ProcedureCall : IDENTIFIER_TOKEN OPEN_PAREN_TOKEN ExpressionList CLOSE_PAREN_TOKEN {}
              | IDENTIFIER_TOKEN OPEN_PAREN_TOKEN                CLOSE_PAREN_TOKEN {}
              ;
NullStatement : {}
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
           | IDENTIFIER_TOKEN OPEN_PAREN_TOKEN ExpressionList CLOSE_PAREN_TOKEN {}
           | IDENTIFIER_TOKEN OPEN_PAREN_TOKEN                CLOSE_PAREN_TOKEN {}
           | CHR_TOKEN OPEN_PAREN_TOKEN Expression CLOSE_PAREN_TOKEN {$$ = new ChrExpr($3);}
           | ORD_TOKEN OPEN_PAREN_TOKEN Expression CLOSE_PAREN_TOKEN {$$ = new OrdExpr($3);}
           | PRED_TOKEN OPEN_PAREN_TOKEN Expression CLOSE_PAREN_TOKEN {}
           | SUCC_TOKEN OPEN_PAREN_TOKEN Expression CLOSE_PAREN_TOKEN {}
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


















