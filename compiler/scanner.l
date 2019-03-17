%{
#include <cstdlib>
#include <iostream>
#include "tree.hpp"
#include "symbol_table.hpp"

//This needs to be included last
#include "parser.hpp"

#define DEBUG false

extern "C" int yylex();

%}

%%


[\t ]*      {/* ignore whitespace */}

"array"     {return ARRAY_TOKEN;}
"ARRAY"     {return ARRAY_TOKEN;}
"begin"     {return BEGIN_TOKEN;}
"BEGIN"     {return BEGIN_TOKEN;}
"chr"       {return CHR_TOKEN;}
"CHR"       {return CHR_TOKEN;}
"const"     {return CONST_TOKEN;}
"CONST"     {return CONST_TOKEN;}
"do"        {return DO_TOKEN;}
"DO"        {return DO_TOKEN;}
"downto"    {return DOWNTO_TOKEN;}
"DOWNTO"    {return DOWNTO_TOKEN;}
"else"      {return ELSE_TOKEN;}
"ELSE"      {return ELSE_TOKEN;}
"elseif"    {return ELSEIF_TOKEN;}
"ELSEIF"    {return ELSEIF_TOKEN;}
"end"       {return END_TOKEN;}
"END"       {return END_TOKEN;}
"for"       {return FOR_TOKEN;}
"FOR"       {return FOR_TOKEN;}
"forward"   {return FORWARD_TOKEN;}
"FORWARD"   {return FORWARD_TOKEN;}
"function"  {return FUNCTION_TOKEN;}
"FUNCTION"  {return FUNCTION_TOKEN;}
"if"        {if(DEBUG) std::cout << "found if_token" << std::endl;return IF_TOKEN;}
"IF"        {if(DEBUG) std::cout << "found if_token" << std::endl;return IF_TOKEN;}
"of"        {return OF_TOKEN;}
"OF"        {return OF_TOKEN;}
"ord"       {return ORD_TOKEN;}
"ORD"       {return ORD_TOKEN;}
"pred"      {return PRED_TOKEN;}
"PRED"      {return PRED_TOKEN;}
"procedure" {return PROCEDURE_TOKEN;}
"PROCEDURE" {return PROCEDURE_TOKEN;}
"read"      {return READ_TOKEN;}
"READ"      {return READ_TOKEN;}
"record"    {return RECORD_TOKEN;}
"RECORD"    {return RECORD_TOKEN;}
"ref"       {return REF_TOKEN;}
"REF"       {return REF_TOKEN;}
"repeat"    {return REPEAT_TOKEN;}
"REPEAT"    {return REPEAT_TOKEN;}
"return"    {return RETURN_TOKEN;}
"RETURN"    {return RETURN_TOKEN;}
"stop"      {return STOP_TOKEN;}
"STOP"      {return STOP_TOKEN;}
"succ"      {return SUCC_TOKEN;}
"SUCC"      {return SUCC_TOKEN;}
"then"      {if(DEBUG) std::cout << "found then_token" << std::endl;return THEN_TOKEN;}
"THEN"      {if(DEBUG) std::cout << "found then_token" << std::endl;return THEN_TOKEN;}
"to"        {return TO_TOKEN;}
"TO"        {return TO_TOKEN;}
"type"      {return TYPE_TOKEN;}
"TYPE"      {return TYPE_TOKEN;}
"until"     {return UNTIL_TOKEN;}
"UNTIL"     {return UNTIL_TOKEN;}
"var"       {return VAR_TOKEN;}
"VAR"       {return VAR_TOKEN;}
"while"     {return WHILE_TOKEN;}
"WHILE"     {return WHILE_TOKEN;}
"write"     {return WRITE_TOKEN;}
"WRITE"     {return WRITE_TOKEN;}

[a-zA-Z][a-zA-Z0-9_]* {if(DEBUG) std::cout << "found id_token" << std::endl;yylval.id = strdup(yytext);return IDENTIFIER_TOKEN;}


"+" {return ADD_TOKEN;}
"-" {return SUB_TOKEN;}
"*" {return MULT_TOKEN;}
"/" {return DIV_TOKEN;}
"&" {return AND_TOKEN;}
"|" {if(DEBUG) std::cout << "found or_token" << std::endl;return OR_TOKEN;}
"~" {return NOT_TOKEN;}
"=" {return EQUAL_TOKEN;}
"<>" {return NOT_EQUAL_TOKEN;}
"<" {if(DEBUG) std::cout << "found less_than_token" << std::endl;return LESS_THAN_TOKEN;}
"<=" {return LESS_THAN_EQUAL_TOKEN;}
">" {if(DEBUG) std::cout << "found greater_than_token" << std::endl;return GREATER_THAN_TOKEN;}
">=" {return GREATER_THAN_EQUAL_TOKEN;}
"." {return DOT_TOKEN;}
"," {return COMMA_TOKEN;}
":" {return COLON_TOKEN;}
";" {return SEMICOLON_TOKEN;}
"(" {return OPEN_PAREN_TOKEN;}
")" {return CLOSE_PAREN_TOKEN;}
"[" {return OPEN_BRACKET_TOKEN;}
"]" {return CLOSE_BRACKET_TOKEN;}
":=" {return ASSIGNMENT_TOKEN;}
"%" {return MOD_TOKEN;}

"0"[0-9]* {yylval.val = atoi(yytext);return OCTAL_LITERAL_TOKEN;}
"0"[xX][0-9]+ {yylval.val = atoi(yytext);return HEX_LITERAL_TOKEN;}
[0-9]+ {yylval.val = atoi(yytext);return DECIMAL_LITERAL_TOKEN;} 

"\'"[ -~]"\'" {yylval.id = strdup(yytext); return CHAR_LITERAL_TOKEN;}

"\'\\"[ -~]"\'" {yylval.id = strdup(yytext); return CHAR_LITERAL_TOKEN;}

"\""([ !#-~]|"\\\"")*"\"" {yylval.id = strdup(yytext); return STRING_LITERAL_TOKEN;}

"\$"[ -~]*"\n" {SymbolTable::getInstance().incrementLineNumber(); /*return COMMENT_TOKEN;*/}

"\n" {SymbolTable::getInstance().incrementLineNumber();}


%%

// "\""[ -~]*"\"" {yylval.id = strdup(yytext); return STRING_LITERAL_TOKEN;}



