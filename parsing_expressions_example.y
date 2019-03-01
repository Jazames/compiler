%{
#include <iostream>
#include <map>

#include "symbol_table.hpp"
#inclucde "Expression.hpp"
extern "C" int yylex();
void yyerror(const char*);





%}

%union
{
float val;
char* id;
Expr* expr;
}

%token ADD
%token SUB
%token MULT
%token DIV
%token OPEN
%token CLOSE
%token DONE
%token NUMBER
%token ID
%token EQUAL
%token LET

%type <val> NUMBER
%type <expr> Expression
%type <expr> Factor
%type <expr> Term
%type <id> ID

%%
Program : StatementList SHOW Done {};

StatementList : StatementList Statement{}
              | {};
Statement : Expression DONE {std::cout << $1 << std::endl;}
          | LET ID EQUAL Expression DONE{symbol_table.store($2,$4);delete($2);}
          | DONE{};
Expression : Expression ADD Term {$$ = makeAdd($1,$3);}
           | Expression SUB Term {$$ = makeSub($1,$3);}
           | Term {$$ = $1;};

Term : Term MULT Factor { $$ = makeMult($1,$3);}
     | Term Factor { $$ = makeMult($1,$2);}
     | Term DIV Factor { $$ = makeDiv($1,$3);}
     | Factor {$$ = $1;}
     ;
Factor : OPEN Expression CLOSE {$$ = $2;}
       | NUMBER {$$ = new Literal($1);}
       | ID {$$ = new Var($1);}
       ;

%%

void yyerror(const char* msg)
{
  std::cerr << msg << std::endl;
}
