#ifndef make_name_hpp
#define make_name_hpp
#include "ast_base.hpp"

static int makeNameUnq=0;

static std::string makeName(std::string base)
{
    return base+std::to_string(makeNameUnq++);
}


#endif