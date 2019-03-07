#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <string>
#include <vector>
#include <map>



class SymbolTable
{
public:
	static void incrementLineNumber() {line_number++;}
	static int getLineNumber() {return line_number;}
private:
	static int line_number;
}


#endif
