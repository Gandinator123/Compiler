%code requires{
  #include "ast.hpp"
  #include <cassert>

  extern const Node *g_root; // A way of getting the AST out
  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  //extern FILE *yyin;
  
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  const Node *node;
  double number;
  std::string *string;
}
%token RETURN SEMICOLON LCURLYBRACKET RCURLYBRACKET COMMA RSqrBracket LSqrBracket 
%token TIMES DIVIDE PLUS MINUS MODULUS INCREMENT DECREMENT LEFT_SHIFT_OP RIGHT_SHIFT_OP NOT
%token LBRACKET RBRACKET LESS_THAN_OP GREATER_THAN_OP LESS_THAN_EQUAL_OP GREATER_THAN_EQUAL_OP
%token EQUAL_OP NOT_EQUAL_OP BITWISE_AND EXCLUSIVE_OR BITWISE_OR LOGICAL_AND LOGICAL_OR 
%token INT INT_NUMBER FLOAT FLOAT_NUMBER FLOAT_NUMBER_STRING DOUBLE IDENTIFIER IF ELSE WHILE FOR DO SWITCH CASE DEFAULT COLON BREAK CONTINUE ENUM
%token ADD_ASSIGN SUB_ASSIGN DIV_ASSIGN MUL_ASSIGN MOD_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
// used so far
%token STANDARD_ASSIGN

%type <node> ROOT FUNCTION BLOCK STATEMENT_LIST GENERAL_STATEMENT RETURN_STATEMENT ITERATION_STATEMENT SELECTION_STATEMENT POSTFIX_EXPRESSION
%type <node> ASSIGN_STATEMENT EXPRESSION CONDITIONAL_EXPRESSION LOGICAL_OR_EXPRESSION LOGICAL_AND_EXPRESSION PARAMETER_DECLARATION PARAMETER_LIST
%type <node> INCLUSIVE_OR_EXPRESSION EXCLUSIVE_OR_EXPRESSION AND_EXPRESSION EQUALITY_EXPRESSION RELATIONAL_EXPRESSION 
%type <node> SHIFT_EXPRESSION ADDITIVE_EXPRESSION MULTIPLICATIVE_EXPRESSION UNARY_EXPRESSION CASE_STATEMENT POINTER POINTER_VARIABLE
%type <node> PRIMARY_EXPRESSION LITERAL VARIABLE_DECLARE FUNCTION_CALL PROGRAM JUMP_STATEMENT ENUM_SPECIFIER ENUMERATOR_LIST ENUMERATOR ALLOWED_GLOBAL_STATEMENT
%type <number> INT_NUMBER FLOAT_NUMBER
%type <string> INT IDENTIFIER DATATYPE FLOAT DOUBLE FLOAT_NUMBER_STRING

%start ROOT

%%

DATATYPE : INT {$$ = $1;}
         | FLOAT {$$ = $1;}
         | DOUBLE {$$ = $1;}

   
LITERAL : INT_NUMBER  { $$ = new IntNumber($1);}
        | FLOAT_NUMBER {$$ = new FloatNumber($1);}
        | FLOAT_NUMBER_STRING {std::cout << "here we want" << std::endl;$$ = new FloatNumber($1);}

VARIABLE_DECLARE : DATATYPE IDENTIFIER {$$ = new VariableDeclare($1, $2);} 
                 | DATATYPE POINTER IDENTIFIER {$$ = new VariableDeclare($1, $3, true);}
                 | DATATYPE IDENTIFIER LSqrBracket LITERAL RSqrBracket {std::cout<<"did array declare" << std::endl; $$ = new ArrayDeclare($1, $2, $4);}
    
PRIMARY_EXPRESSION : FUNCTION_CALL {$$ = $1;}
                   | LBRACKET EXPRESSION RBRACKET { $$ = $2; }
                   | IDENTIFIER LSqrBracket EXPRESSION RSqrBracket {$$ = new ArrayAcc($1, $3);}
                   | IDENTIFIER     {$$ = new Identifier($1);}
                   | POINTER IDENTIFIER {$$ = new PointerIdentifier($2);}
                   | LITERAL     {$$ = $1;}
            
POSTFIX_EXPRESSION : PRIMARY_EXPRESSION {$$ = $1;}
                   | POSTFIX_EXPRESSION INCREMENT {$$ = new PostIncrOperator($1);}
                   | POSTFIX_EXPRESSION DECREMENT {$$ = new PostDecrOperator($1);}

UNARY_EXPRESSION  : POSTFIX_EXPRESSION           { $$ = $1; }
                  | MINUS UNARY_EXPRESSION       {$$ = new NegOperator($2);}
                  | NOT UNARY_EXPRESSION         {$$ = new NotOperator($2);}
                  | BITWISE_AND UNARY_EXPRESSION {$$ = new AddressOperator($2);}
                  | INCREMENT PRIMARY_EXPRESSION {$$ = new PreIncrOperator($2);}
                  | DECREMENT PRIMARY_EXPRESSION {$$ = new PreDecrOperator($2);}
      
MULTIPLICATIVE_EXPRESSION : UNARY_EXPRESSION                                   { $$ = $1; }
                          | MULTIPLICATIVE_EXPRESSION TIMES UNARY_EXPRESSION   {$$ = new MulOperator($1, $3); }
                          | MULTIPLICATIVE_EXPRESSION DIVIDE UNARY_EXPRESSION  {$$ = new DivOperator($1, $3); }
                          | MULTIPLICATIVE_EXPRESSION MODULUS UNARY_EXPRESSION  {$$ = new ModOperator($1, $3); }

ADDITIVE_EXPRESSION : MULTIPLICATIVE_EXPRESSION                              { $$ = $1; }//ASSIGNMENT_EXPRESSION needs to be renamed to ADDITIVE_EXPRESSION
                      | ADDITIVE_EXPRESSION PLUS MULTIPLICATIVE_EXPRESSION     {$$ = new AddOperator($1,$3);}
                      | ADDITIVE_EXPRESSION MINUS MULTIPLICATIVE_EXPRESSION    {$$ = new SubOperator($1,$3);}

SHIFT_EXPRESSION : ADDITIVE_EXPRESSION                                        {$$ = $1;}
                 | SHIFT_EXPRESSION LEFT_SHIFT_OP ADDITIVE_EXPRESSION         {$$ = new LeftShiftOperator($1,$3);}
                 | SHIFT_EXPRESSION RIGHT_SHIFT_OP ADDITIVE_EXPRESSION        {$$ = new RightShiftOperator($1,$3);}


RELATIONAL_EXPRESSION : SHIFT_EXPRESSION                                              {$$ = $1;}
                      | RELATIONAL_EXPRESSION LESS_THAN_OP SHIFT_EXPRESSION           {std::cout << "in less than "<< std::endl;$$ = new LessThanOperator($1,$3);}
                      | RELATIONAL_EXPRESSION GREATER_THAN_OP SHIFT_EXPRESSION        {$$ = new GreaterThanOperator($1,$3);}
                      | RELATIONAL_EXPRESSION LESS_THAN_EQUAL_OP SHIFT_EXPRESSION     {$$ = new LessThanEqualOperator($1,$3);}
                      | RELATIONAL_EXPRESSION GREATER_THAN_EQUAL_OP SHIFT_EXPRESSION  {$$ = new GreaterThanEqualOperator($1,$3);}

EQUALITY_EXPRESSION : RELATIONAL_EXPRESSION                                           {$$=$1;}
                    | EQUALITY_EXPRESSION EQUAL_OP RELATIONAL_EXPRESSION              {$$ = new EqualOperator($1,$3);}
                    | EQUALITY_EXPRESSION NOT_EQUAL_OP RELATIONAL_EXPRESSION          {$$ = new NotEqualOperator($1,$3);}

AND_EXPRESSION      : EQUALITY_EXPRESSION                                             {$$ = $1;}
                    | AND_EXPRESSION BITWISE_AND EQUALITY_EXPRESSION                  {$$ = new BitwiseAndOperator($1,$3);}


EXCLUSIVE_OR_EXPRESSION : AND_EXPRESSION                                              {$$=$1;}
                        | EXCLUSIVE_OR_EXPRESSION EXCLUSIVE_OR AND_EXPRESSION         {$$ = new BitwiseXorOperator($1,$3);}        

INCLUSIVE_OR_EXPRESSION : EXCLUSIVE_OR_EXPRESSION                                     {$$=$1;}
                        | INCLUSIVE_OR_EXPRESSION BITWISE_OR EXCLUSIVE_OR_EXPRESSION  {$$ = new BitwiseOrOperator($1,$3);}
                
LOGICAL_AND_EXPRESSION : INCLUSIVE_OR_EXPRESSION                                      {$$=$1;}
                       | LOGICAL_AND_EXPRESSION LOGICAL_AND INCLUSIVE_OR_EXPRESSION   {$$ = new LogicalAndOperator($1, $3);}    
          
LOGICAL_OR_EXPRESSION  : LOGICAL_AND_EXPRESSION                                       {$$=$1;}
                       | LOGICAL_OR_EXPRESSION LOGICAL_OR LOGICAL_AND_EXPRESSION      {$$ = new LogicalOrOperator($1, $3);}

CONDITIONAL_EXPRESSION : LOGICAL_OR_EXPRESSION {$$ = $1;}


EXPRESSION : CONDITIONAL_EXPRESSION {$$ = $1;}//should be only this

FUNCTION_CALL : IDENTIFIER LBRACKET RBRACKET {$$ = new FunctionCall($1);}
              | IDENTIFIER LBRACKET PARAMETER_LIST RBRACKET {$$ = new FunctionCall($1, $3);}


ASSIGN_STATEMENT   :  VARIABLE_DECLARE STANDARD_ASSIGN EXPRESSION           { $$ = new StandardDeclareAssignStatement($1,$3); }
                   |  IDENTIFIER STANDARD_ASSIGN EXPRESSION                 { $$ = new StandardAssignStatement($1,$3); }
                   |  POINTER IDENTIFIER STANDARD_ASSIGN EXPRESSION         { std::cout<<"yayy"<<std::endl;$$ = new StandardAssignStatement($2,$4, true); }
                   |  IDENTIFIER MUL_ASSIGN EXPRESSION                     { $$ = new MulAssignStatement($1,$3);}
                   |  POINTER IDENTIFIER MUL_ASSIGN EXPRESSION             { $$ = new MulAssignStatement($2,$4);}
                   |  IDENTIFIER DIV_ASSIGN EXPRESSION                     { $$ = new DivAssignStatement($1,$3);} 
                   |  POINTER IDENTIFIER DIV_ASSIGN EXPRESSION             { $$ = new DivAssignStatement($2,$4);} 
                   |  IDENTIFIER MOD_ASSIGN EXPRESSION                     { $$ = new ModAssignStatement($1,$3);}      
                   |  POINTER IDENTIFIER MOD_ASSIGN EXPRESSION             { $$ = new ModAssignStatement($2,$4);}      
                   |  IDENTIFIER ADD_ASSIGN EXPRESSION                     { $$ = new AddAssignStatement($1,$3);} 
                   |  POINTER IDENTIFIER ADD_ASSIGN EXPRESSION             { $$ = new AddAssignStatement($2,$4);} 
                   |  IDENTIFIER SUB_ASSIGN EXPRESSION                     { $$ = new SubAssignStatement($1,$3);}
                   |  POINTER IDENTIFIER SUB_ASSIGN EXPRESSION              { $$ = new SubAssignStatement($2,$4);}
                   |  IDENTIFIER LEFT_ASSIGN EXPRESSION                     { $$ = new LeftAssignStatement($1,$3);}
                   |  POINTER IDENTIFIER LEFT_ASSIGN EXPRESSION              { $$ = new LeftAssignStatement($2,$4);}
                   |  IDENTIFIER RIGHT_ASSIGN EXPRESSION                   { $$ = new RightAssignStatement($1,$3);}
                   |  POINTER IDENTIFIER RIGHT_ASSIGN EXPRESSION            { $$ = new RightAssignStatement($2,$4);}
                   |  IDENTIFIER AND_ASSIGN EXPRESSION                     { $$ = new AndAssignStatement($1,$3);}
                   |  POINTER IDENTIFIER AND_ASSIGN EXPRESSION              { $$ = new AndAssignStatement($2,$4);}
                   |  IDENTIFIER XOR_ASSIGN EXPRESSION                     { $$ = new XorAssignStatement($1,$3);}
                   |  POINTER IDENTIFIER XOR_ASSIGN EXPRESSION              { $$ = new XorAssignStatement($2,$4);}
                   |  IDENTIFIER OR_ASSIGN EXPRESSION                       { $$ = new OrAssignStatement($1,$3);}
                   |  POINTER IDENTIFIER OR_ASSIGN EXPRESSION                { $$ = new OrAssignStatement($2,$4);}
                   |  VARIABLE_DECLARE STANDARD_ASSIGN LCURLYBRACKET PARAMETER_LIST RCURLYBRACKET {std::vector<NodePtr> existingList = $4->returnList(); $$ = new ArrayInit($1, existingList);}
                   |  IDENTIFIER LSqrBracket EXPRESSION RSqrBracket STANDARD_ASSIGN EXPRESSION {std::cout << "Entered array assign" << std::endl;$$ = new ArrayAssign($1, $3, $6);}

ENUM_SPECIFIER : ENUM LCURLYBRACKET ENUMERATOR_LIST RCURLYBRACKET SEMICOLON{std::vector<NodePtr> list = $3->returnList(); $$ = new EnumeratorSpecifier(list);}
               | ENUM IDENTIFIER LCURLYBRACKET ENUMERATOR_LIST RCURLYBRACKET SEMICOLON{std::cout<<"made enum" << std::endl; std::vector<NodePtr> list = $4->returnList(); $$ = new EnumeratorSpecifier(list);}
               /* | ENUM IDENTIFIER */

ENUMERATOR_LIST : ENUMERATOR {$$ = new EnumeratorList($1);} 
                | ENUMERATOR_LIST COMMA ENUMERATOR {std::vector<NodePtr> list = $1->returnList(); $$ = new EnumeratorList(list, $3);}

ENUMERATOR : IDENTIFIER {std::cout<<"made enum identifier" << std::endl; NodePtr expression = new IntNumber(0); $$ = new Enumerator($1, expression); }
           | IDENTIFIER STANDARD_ASSIGN EXPRESSION {$$ = new Enumerator($1, $3);}

CASE_STATEMENT : CASE EXPRESSION COLON {$$ = new CaseStatement($2);}
               | DEFAULT COLON         { $$ = new DefaultCaseStatement();}

POINTER : TIMES {$$ = new Pointer(1);}
        | POINTER TIMES {int old_number = $1->getValue(); $$ = new Pointer(1+old_number);} 
  
                              
ITERATION_STATEMENT : WHILE LBRACKET EXPRESSION RBRACKET GENERAL_STATEMENT { std::cout << "in while" << std::endl;$$ = new WhileStatement($3, $5);}
                    | DO GENERAL_STATEMENT WHILE LBRACKET EXPRESSION RBRACKET SEMICOLON {$$ = new DoWhileStatement($5, $2);}
                    | FOR LBRACKET ASSIGN_STATEMENT SEMICOLON EXPRESSION SEMICOLON ASSIGN_STATEMENT RBRACKET GENERAL_STATEMENT { $$ = new ForStatement($3, $5, $7, $9);}
                    | FOR LBRACKET ASSIGN_STATEMENT SEMICOLON EXPRESSION SEMICOLON EXPRESSION RBRACKET GENERAL_STATEMENT { $$ = new ForStatement($3, $5, $7, $9);}

RETURN_STATEMENT   : RETURN EXPRESSION SEMICOLON { $$ = new Return($2);}


GENERAL_STATEMENT  : RETURN_STATEMENT     {$$ = $1;}
                   | VARIABLE_DECLARE SEMICOLON {$$ = $1;}
                   | ASSIGN_STATEMENT SEMICOLON    { $$ = $1;}
                   | SELECTION_STATEMENT { $$ = $1; }
                   | ITERATION_STATEMENT { $$ = $1; }
                   | JUMP_STATEMENT {$$ = $1;}
                   | CASE_STATEMENT {$$ = $1;}
                   | BLOCK               { $$ = $1; }
                   | POSTFIX_EXPRESSION SEMICOLON {$$ = $1;}
                   

STATEMENT_LIST     : GENERAL_STATEMENT       {$$ = new CreateStatementList($1);}
                   | STATEMENT_LIST GENERAL_STATEMENT {std::vector<NodePtr> existingList = $1->returnList(); $$ = new CreateStatementList(existingList, $2);}

              

SELECTION_STATEMENT : IF LBRACKET EXPRESSION RBRACKET GENERAL_STATEMENT { $$ = new IfStatement($3, $5);}
                    | IF LBRACKET EXPRESSION RBRACKET GENERAL_STATEMENT ELSE GENERAL_STATEMENT {$$ = new IfElseStatement($3,$5,$7);}
                    | SWITCH LBRACKET EXPRESSION RBRACKET GENERAL_STATEMENT {std::vector<NodePtr> list = $5->returnList(); $$ = new SwitchStatement($3, list);}


BLOCK : LCURLYBRACKET STATEMENT_LIST RCURLYBRACKET {$$ = $2;}//BLOCK is equal to COMPOUND_STATEMENT
      | LCURLYBRACKET RCURLYBRACKET {$$ = new CreateStatementList();}

JUMP_STATEMENT : CONTINUE SEMICOLON {$$ = new Continue();}
               | BREAK SEMICOLON  {$$ = new Break();}
               | RETURN SEMICOLON {$$ = new ReturnNone();}

PARAMETER_DECLARATION : VARIABLE_DECLARE {$$ = $1;} //may need to change for scoped variables...
                      | EXPRESSION {$$ = $1;}

PARAMETER_LIST : PARAMETER_DECLARATION                             {$$ = new ParameterList($1);}
               | PARAMETER_LIST COMMA PARAMETER_DECLARATION        { std::vector<NodePtr> existingList = $1->returnList(); $$ = new ParameterList(existingList, $3);} 

FUNCTION : DATATYPE IDENTIFIER LBRACKET RBRACKET BLOCK {$$ = new FunctionDefinition($1, $2, $5);}
         | DATATYPE IDENTIFIER LBRACKET PARAMETER_LIST RBRACKET BLOCK {$$ = new FunctionDefinition($1, $2, $4, $6);} 

ALLOWED_GLOBAL_STATEMENT : FUNCTION {$$ = $1;}
                         | ENUM_SPECIFIER {$$ = $1;}
                         | DATATYPE IDENTIFIER SEMICOLON {$$ = new globalDeclare($1, $2);}
                         | DATATYPE IDENTIFIER LSqrBracket LITERAL RSqrBracket SEMICOLON {$$ = new globalDeclare($1, $2);}
                         | DATATYPE POINTER IDENTIFIER SEMICOLON {$$ = new globalDeclare($1, $3);}
                         | DATATYPE IDENTIFIER STANDARD_ASSIGN LITERAL SEMICOLON         { $$ = new GlobalVariableAssign($1,$2, $4); }
                         | DATATYPE IDENTIFIER LSqrBracket LITERAL RSqrBracket STANDARD_ASSIGN LCURLYBRACKET PARAMETER_LIST RCURLYBRACKET SEMICOLON {std::vector<NodePtr> existingList = $8->returnList(); $$ = new GlobalArrayAssign($2, existingList);} //global array assign
                         | DATATYPE IDENTIFIER LBRACKET PARAMETER_LIST RBRACKET SEMICOLON {$$ = new NullFunctionDefinition($1, $2, $4);}
                         | DATATYPE IDENTIFIER LBRACKET RBRACKET SEMICOLON  {$$ = new NullFunctionDefinition($1, $2);}



PROGRAM : ALLOWED_GLOBAL_STATEMENT {$$ = new Program($1);}
        | PROGRAM ALLOWED_GLOBAL_STATEMENT {std::vector<NodePtr> existingProgram = $1->returnList(); $$ = new Program(existingProgram, $2); } 



ROOT :  PROGRAM  {g_root = $1; }

%%

const Node *g_root; 

const Node *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
};
