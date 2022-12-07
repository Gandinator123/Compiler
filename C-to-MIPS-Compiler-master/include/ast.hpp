#ifndef ast_hpp
#define ast_hpp

#include <string>
#include <iostream>
#include <fstream> //for incorporating files
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>

#include "ast/ast_base.hpp"
#include "ast/ast_functions.hpp"
#include "ast/ast_literal.hpp"
#include "ast/ast_statement_list.hpp"
#include "ast/ast_keywords.hpp"
#include "ast/ast_binary_operators.hpp"
#include "ast/ast_unary_operators.hpp"
#include "ast/ast_identifier.hpp"
#include "ast/context.hpp"
#include "ast/ast_assign_statement.hpp"
#include "ast/ast_variable_declare.hpp"
#include "ast/make_name.hpp"
#include "ast/ast_if_else.hpp"
#include "ast/ast_while.hpp"
#include "ast/ast_for.hpp"
#include "ast/ast_parameters.hpp"
#include "ast/ast_function_call.hpp"
#include "ast/ast_program.hpp"
#include "ast/ast_case.hpp"
#include "ast/ast_switch.hpp"
#include "ast/ast_arrays.hpp"
#include "ast/ast_enumerator.hpp"
#include "ast/ast_pointer.hpp"
#include "ast/ast_global.hpp"

extern const Node *parseAST();
#endif

