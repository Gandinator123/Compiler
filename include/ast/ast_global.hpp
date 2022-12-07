#ifndef ast_global_hpp
#define ast_global_hpp

#include "ast_base.hpp"

class globalDeclare
    : public Node
{
private:
    std::string* identifier;
    std::string* datatype;
public:
    globalDeclare(std::string* _datatype,std::string* _identifier){
        identifier = _identifier;
        datatype = _datatype;
    }
    virtual ~globalDeclare(){
        delete identifier;
        delete datatype;
    }

    virtual void visualise() const override
    {   
        std::cout<<"in the global operator node"<<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        dst << *identifier << ":" << std::endl;

    }
    virtual std::string whatAMI() const override
    {
        return "global declare node";
    };

    virtual std::vector<NodePtr> returnList() const override
    {

    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {

    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{
    }
    virtual std::string getId() const override{
        return *identifier;
    }
};

class GlobalVariableAssign
    : public Node
{
private:
    std::string* identifier;
    std::string* datatype;
    NodePtr literal;
    int value;
public:
    GlobalVariableAssign(std::string* _datatype, std::string* _variable, NodePtr _literal){
        identifier = _variable;
        datatype = _datatype;
        literal = _literal;
        value = literal->getValue();
    }
    virtual ~GlobalVariableAssign(){
        delete identifier;
        delete datatype;
        delete literal;
    }

    virtual void visualise() const override
    {   
        std::cout<<"in the global variable assign node"<<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        dst << *identifier << ":" << std::endl;
            dst << "    .word   " << value << std::endl; 

    }
    virtual std::string whatAMI() const override
    {
        return "global variable assign node";
    };

    virtual std::vector<NodePtr> returnList() const override
    {

    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {

    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{
    }
    virtual std::string getId() const override{
    }
};

class GlobalArrayAssign
    : public Node
{
private:
    std::string* identifier;
    std::vector<NodePtr> values;
public:
    GlobalArrayAssign(std::string* _variable, std::vector<NodePtr> _values){
        identifier = _variable;
        values = _values;
    }
    virtual ~GlobalArrayAssign(){
        delete identifier;
        for(int i=0; i<values.size(); i++){
            delete values[i];
        }
    }

    virtual void visualise() const override
    {   
        std::cout<<"in the global array assign node"<<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        dst << *identifier << ":" << std::endl;
        for(int i=0; i<values.size(); i++){
            dst << "    .word   " << values[i]->getValue() << std::endl; 
        }

    }
    virtual std::string whatAMI() const override
    {
        return "global array assign node";
    };

    virtual std::vector<NodePtr> returnList() const override
    {

    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {

    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{
    }
    virtual std::string getId() const override{
    }
};

#endif
