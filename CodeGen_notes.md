*CodeGen*


-----------
Registers
---------
$0: Set to 0
$at (1): 
$v0-$v1 (2-3): Return value from subroutine (if value is 1 word then only $v0 is needed)
$a0-$a3 (4-7): Function arguments
$t0-$t9 (8-15, 24-25): Temporary registers (whatever we want)
$s0-$s7 (16-23): Saved registers (value is preserved across function calls)
$k0-$k1 (26-27): Don't need
$gp (28): Global pointer
$sp (29): Stack pointer
$fp (30): Frame pointer
$ra (31): Return address in subroutine call



---------------------------------
CONSIDERING INT FUNCTIONS WITH NO ARGUMENTS
-----------------------------------
initially, we make the frame of length 32.
For every 2 variables we initialise, we add 8

first variable declaration int x = 2;  ------> sw $2,8($fp)
second.....................int y = 3; --------> sw $2, 12()


--------------

-------------

int Sequence::countdeclarations(Context& c) const
{
  int size = 0;
  if(components[0] == NULL)
  { return 0; }
  for(unsigned int i = 0; i < components.size(); i++)
  {
    std::string stmt = components[i]->Whatami();
    if((stmt == "VarDeclStmt")||(stmt == "ArrayDeclStmt")||(stmt == "DeclAssignmentStmt"))
    {
      int wsize = 4;
      std::string type = reducetype(c.userdefs, components[i]->MyType(c));
      if(type == "double")
      {   wsize = 8;  }
      else if((isStruct(type))&&(type[type.size()-1] != '*'))
      {
        std::string id = type.substr(7);
        wsize = StructSize(c.userdefs, (c.structs).at(id));
      }
      int decls = components[i]->compsize();
      size += wsize*decls;
    }
    else
    {
      size += components[i]->countdeclarations(c);
    }
  }
    return size;
}


#include "ast/helperfunctions.hpp"
#include "ast/ast_variable_declare.hpp"
#include "ast/ast_assign_statement.hpp"
#include "ast/ast_declare_assign.hpp"




WE SHOULD ADD A MAP RELATING VARIABLE NAME TO VARIABLE TYPE SOON
WE SHOULD ADD A MAP RELATING VARIABLE NAME TO VARIABLE TYPE SOON
WE SHOULD ADD A MAP RELATING VARIABLE NAME TO VARIABLE TYPE SOON
WE SHOULD ADD A MAP RELATING VARIABLE NAME TO VARIABLE TYPE SOON
WE SHOULD ADD A MAP RELATING VARIABLE NAME TO VARIABLE TYPE SOON
WE SHOULD ADD A MAP RELATING VARIABLE NAME TO VARIABLE TYPE SOON
DO ON WEDNESDAY