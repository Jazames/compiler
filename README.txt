

This is a compiler for CS5300

Checkpoints will be tagged via git

%%%%%%%%%%%%%%%%%%%%%%%%%%%
Notes for checkpoints:
---------------------------


%%%%%%%%%%%%%%%%%%%%%%%%%%%
Parsing and Scanning
---------------------------
Scanner groups characters into tokens for the syntax analyzer. 
Strips out white space
The scanner is the only part of the code that knows what the original code looked like.
  It may be a good idea to attach line numbers to to tokens for the sake of diagnostics.
  Sundberg would have a global variable that's the line number. The scanner increments it when it sees a new line. Everything else only reads from it. 
Generates output listing with errors marked
Deletes Comments
Converts numbers to binary form.

Scanner has the job to recognize rules for the words of the language. 

Parser calls scanner which returns the next token. 

Terminology:
  Token - type of word. Implemented as enumeration
  Lexemes
    If the token is the type of word, the lexeme is the word itself. 
    Some kinds of tokens need associated data, some don't.
    Value derived from matched text. 
  Pattern
    Regular expression

  Keywords - related to reserved identifiers. 
    Keywords are recognized by the scanner as some type of token. 
    Reserved words are identifiers where the language has defined an associated value. 
    Difference is that keywords have defined token type. 

  Literals
    String, Character, or numeric. 
    Both token kind and lexeme are significant. 
    lexeme may be intepreted first. 
  
  Operators
    Like separatores. 
    No real difference for lexical analyzer. 

  Identifiers
    rules for identifiers vary by language
    We will use C-style rules for identifiers. 

  Comments have no meaning so we just delete them. 
    Do have to check for lexical errors, such as a multi-line comment that isn't closed. 

How to make a scanner? 
  We're going to use a scanner generator. 
  Flex is our scanner generator. 
  But also possible to hand-write lexical analyzer. 
    Major compilers have hand-written lexical analyzers because it needs to be optimized and this is the bottleneck outside of optimization. 
  
How to specify rules in Unix Tools. (lex) The f is for fast or free. not sure. 
  alternation [xy] x|y
  any character .
  sequence abc
  repitition x* 
  optional x?y+ 
  
  Can look at manual if necessary. 

Flex file has 3 parts
  Definitions
    sub-expressions like character
    include files for rules
  Rules
    Regular Expression.
    Action - what happens when we match the regular expression
    Precedence expressions by order.
      Doesn't actually do this, but acts as if it does. Really just builds massive finite autonoma 
  Code
    Helper code
      This just needs to return some token type. Possibly also return the lexeme, if necessary.

Testing the Scanner:
  There's a file called "lexical test" that just contains one of each token type. 
  Can run that through the scanner to make sure that everything is recognized by the regexes. 







%%%%%%%%%%%%%%%%%%%%%%%%%%%
Simple Expressions
---------------------------

%%%%%%%%%%%%%%%%%%%%%%%%%%%
User Defined Data Types
---------------------------

%%%%%%%%%%%%%%%%%%%%%%%%%%%
Control Structures
---------------------------

%%%%%%%%%%%%%%%%%%%%%%%%%%%
Functions
---------------------------



