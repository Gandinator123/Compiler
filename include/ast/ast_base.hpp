#ifndef ast_base_hpp
#define ast_base_hpp

#include "context.hpp"

class Node;

typedef const Node *NodePtr;

class Node
{
public:
    //destructor
    virtual ~Node()
    {}

    //visualiser
    virtual void visualise() const = 0;

    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const = 0;

    virtual std::string whatAMI() const = 0;

    virtual std::vector<NodePtr> returnList() const = 0; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const = 0;

    virtual void FunctionCallCheck(Context &c) const = 0;
    virtual int getValue() const = 0;
    virtual std::string getId() const = 0;
};

#endif

