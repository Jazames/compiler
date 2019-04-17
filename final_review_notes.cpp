
Scanning, Parsing
  Regular Expressions <==> Finite automata
  Context Free Grammar

  < 20% of the test.

Code Generation
  Expressions
  Control Flow
  User Defined Types
  Functions

Optimization
  Register Allocation
  Common Sub Expression Elimination
  Function Inlining
    It is as if the function call body was placed in the code at the line of the function call. 
  Other manipulations
    Basic Block Folding
    Loop Unrolling
    Super Block Strategies
      making biggest basic blocks that you can. 
    Loop Hoisting
      Pull things that are the same across loop iterations out of the loop and to the header/preamble. 
    Induction Analysis
    Strength Reduction
      Replacing an expensive instruction with a less expensive instruction. 

  Single Stack Assignment
  Phi Functions
  Control Flow Graphs 
  Data Flow Analysis
    Propogate data changes through the code. It is useful to show where phi functions should exist. 
  Dead Code Elimination

Career Advice #1: Talk to people, look stupid, it's okay, so is everyone else. 
Career Advice #2: Your crystal ball is broken, just like everyone else's. So don't write code unless there's an immediate use for it. 
  Assume that Future you is a better developer. 
  Do your best to not try to look into the future. 

SUBLEQ, is a complete instruction set with one instruction. 
  subtract, and if less-than-equal, branch to location. 
  Accepts 3 memory locations as arguments. 



Loop unrolling pattern
  run loop, checking against less-than last - n, where n is amount of loop unrolling
  When the above test fails, go to the normal loop to get through the last few iterations. 
  