# Force_pp Fall 2024 W4115

### Team:
Kevin Yang; ky2488
Dale Yu; dy2446

## Installation Steps
Needs GCC installed to compile in c++17.

To run tests on Linux/Mac:
./run_tests.sh

**Scroll down to Homework 3 Components at the bottom! Thanks!**


# Homework 1 Components (Tag v0.1-lexer)
> Scroll Down to See Homework 2 Components and Deliverables.
The main files for this part of the homework can be found in `/lexer/lexer.cpp` `/token/token.h` and `/test/lexer_test.cpp`
## Language Components
KEYWORD = while | if | else | for | forn | 
TYPE = int | vector | ll | pair | 
SYMBOL = ( | ) | { | } | ;
OPERATOR = + | - | / | * | = | ==
NUMBER = [0-9]+
IDENTIFIER = [a-z][a-z|0-9]*

#### DFA 
We have the DFA rendered using graphviz and it is in the `/DFA`

*How to create the DFA*
- run the command `dot -Tpng dfa.gv -o dfa.png` 
Here is our DFA that our lexing algorithm is built on:
![DFA picture](/DFA/dfa.png)

This is like the basic structure of the DFA with some additions that we used to come up with our lexing algorithm that is in `/lexer/lexer.cpp`
- We basically check what character we are at and then test the different cases for what it is. If it is an accept state like the operators, then it is just that for the scanning algorithm. Otherwise it will keep trying to read digits or characters to make it an identifier or number.

  
## Lexing Algorithm
Most of the time, the symbol type can be deduced from the first character, so it looks at that first and then does maximal munch to see how much we can take per word. 

## Shell Testing Scripts
testing scripts are found in `/tests`

# Homework 2 Components (Tag v0.2-parser)
**Deliverables:**

### CFG for language 
These CFG's are in BNF (Backus-Naur Form)
```
Program ::= FunctionDefinition*

FunctionDefinition ::= Type Identifier "(" ParameterList? ")" Block

ParameterList ::= Parameter ( "," Parameter )*

Parameter ::= Type Identifier

Block ::= "{" StatementList "}"

StatementList ::= Statement*

Statement ::= VariableDeclaration ";"
            | AssignmentStatement ";"
            | ExpressionStatement ";"
            | ForLoop
            | WhileLoop
            | IfStatement
            | ReturnStatement ";"
            | Block

VariableDeclaration ::= Type Identifier ( "=" Expression )?

AssignmentStatement ::= Identifier "=" Expression

ExpressionStatement ::= Expression

ForLoop ::= "for" "(" ForInit ";" [ Condition ] ";" [ ForUpdate ] ")" Statement
          | "for" "(" Type Identifier ":" Expression ")" Statement
          | "forn" "("Identifier "," <DECIMAL_LITERAL> ")" Statement

ForInit ::= VariableDeclaration
          | AssignmentStatement
          | Expression

ForUpdate ::= AssignmentStatement
            | Expression

Condition ::= Expression

WhileLoop ::= "while" "(" Condition ")" Statement

IfStatement ::= "if" "(" Condition ")" Statement [ "else" Statement ]

ReturnStatement ::= "return" [ Expression ]

Expression ::= FunctionCall
             | Literal
             | Identifier
             | "(" Expression ")"
             | Expression BinaryOperator Expression
             | Expression BooleanOperator Expression
             | UnaryOperator Expression

FunctionCall ::= Identifier "(" ArgumentList? ")"

ArgumentList ::= Expression ( "," Expression )*

Type ::= "int"
       | "float"
       | "char"
       | "bool"
       | "varchar"
       | "vi"        // Vector of integers

BinaryOperator ::= "+" | "-" | "*" | "/" | "%" 

BooleanOperator ::="==" | "!=" | "<" | "<=" | ">" | ">=" | "&&" | "||" 

UnaryOperator ::= "-" | "!"

Identifier ::= <IDENTIFIER_NAME>

Literal ::= <DECIMAL_LITERAL>
          | <FLOAT_LITERAL>
          | <STRING_LITERAL>
          | <CHAR_LITERAL>
          | <BOOLEAN_LITERAL>

<IDENTIFIER_NAME> ::= [a-zA-Z_][a-zA-Z0-9_]*
<DECIMAL_LITERAL> ::= [0-9]+
<FLOAT_LITERAL> ::= [0-9]+"."[0-9]+
<STRING_LITERAL> ::= "\"" [^\"]* "\""
<CHAR_LITERAL> ::= "'" . "'"
<BOOLEAN_LITERAL> ::= "true" | "false"
```

### Parsing Algorithm 
You can find our parsing algorithm in `./parser`.
*How our Parsing algorithm works*
Our parser is a recursive descent parser. And it’s a “top down operator precedence” parser, sometimes called “Pratt parser”.

- Our algorthim works through a Pratt Parser. It basically just keeps trying to
  like recursively match the statements and backs off when it can't.

### Sample Input Programs
Our sample input programs can be found in `/test-files/parser_tests` The first 4 are different features and parsing nesting for force_pp. The last 
test file is to show error handling and how we print that out to the user.

Run the sample input programs through `bash ./run_tests.sh`. 
- This just runs the two testing files so far, which are `lexer_tests.cpp` and `parser_tests.cpp`

### Shell script 
Make sure you have C++ 17 installed like earlier and then you can do the same installations steps. 

To run tests on Linux/Mac:
./run_tests.sh

To build and lex any file:
1. make main
2. ./main file_name 

### Demos 
Please use the youtube link. The videos couldn't be added to the repo cause they were too big.
For the deliverables, you can read the above portions and inspect our files in parser and ast. We also have the test files in tests. Thanks!
Look at this youtube link to watch the demo: https://www.youtube.com/watch?v=HVJFjCcfCzY

# Homework 3 Components

*Requirements*
You still only need GCC installed to compile in c++17. If you have issues using
a Windows's Machines' Visual Studio C++ compiler, then try a MacOS or Linux
computer's clang compiler. 

You still can run all the tests need through doing 
`./run_tests.sh` or if you are on fish then `bash ./run_tests.sh`

### Processor Algorithm

Our algorithm works by implementing a recursive depth-first search algorithm on
the Abstract Syntax Tree (AST) that we generated in the previous section. It
then will take the input code from force++ and then convert it into the proper
C++ code.
- The algorithm basically traverses each node of the AST, and then depending on
  the node type (like FUNCTION, FOR, WHILE, etc.), it will output the
  corresponding C++ syntax to an output file. Each one of these nodes will have
  children that might need to be recursively called on. So, if necessary, the
  DFS will continue to call the children recursively to maintain the correct
  code structure. 
- Beyond the normal recursive calls based on the AST, there are optimizations
  and shortcuts based on the special syntax. For instance, there is the
  forn(i,n) loop which gets converted into native, standard C++ for loop with
  the syntax of (for(inti = 0; i < n; i++ )). There is also cout() as a method,
  so you can just quickly print and debug variables and strings.
- Our processor also adds in the necessary C++ boilerplate code automatically,
  so that you can immediately have the basic packages for comp programming
  already there.

> Find these files is the processor folder

##### Input Programs

 You can look at the video to see the different input programs that we are
 testing. You can also look in the `tests/processor_tests/` folder to see the
 different sample files that we are compiling. You can also see what the testing
 code is doing if you want by loooking at `tests/processor_tests.cpp`.

 - The tests will compile it to C++ and then execute the said C++ code.
 - If there are parsing or syntax errors then it will throw an error and return
   that to the user. It does not try to run code that has errors.
 - Our code covers, while, for, forn, function definitions, many types, and many
   shortcuts,
 - Our 5th test, as shown in the video, has a syntax error which results in the
   user seeing where and what that error was. What was expected, and what it
   got.
 - For simplifications, we have a forn() loop which gets rid of extra code, we
   also have shortcuts like cout() and other simplifications.

#### Demo:

You can use the youtube link here. It is an unlisted Youtube video, so this link
should work. Let me know if it doesn't. The rest of the deliverables you can
find above.
https://youtu.be/N7BNVxxCUII

---

##### References

Collection of popular macros in comp programming: https://gist.github.com/abinashmeher999/e5993d17e9d25227cbe3#file-comp_macros-h-L3

How does Infix Parsing work: https://www.chris-j.co.uk/parsing.php

Pratt Parsing example online: https://matklad.github.io/2020/04/13/simple-but-powerful-pratt-parsing.html
