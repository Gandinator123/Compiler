#ifndef ast_enumerator_hpp
#define ast_enumerator
#include "ast_base.hpp"

class Enumerator : 
    public Node 
{
private:
    std::string* id;
    NodePtr expression;
public:

    Enumerator(std::string* _id, NodePtr _expression)
    {
        id = _id;
        expression = _expression;
    }

    virtual ~Enumerator()
    {
        delete expression;
    }
    
    virtual void visualise()const override
    {
        std::cout<<"in the enumerator block"<<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int")const override
    {
        
    }

    virtual std::string whatAMI() const override
    {
        return "Identifier";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
        
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override{
    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{
        return expression->getValue();
    }
    virtual std::string getId() const override{
        return *id;
    }
};

class EnumeratorList : 
    public Node 
{
private:
    std::vector<NodePtr> list;
public:

    EnumeratorList(NodePtr _enumerator)
    {
        list.push_back(_enumerator);
    }

    EnumeratorList(std::vector<NodePtr> _list, NodePtr _enumerator)
    {
        list = _list;
        list.push_back(_enumerator);
    }

    virtual ~EnumeratorList()
    {

    }
    
    virtual void visualise()const override
    {
        std::cout<<"in the enumerator list block"<<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int")const override
    {
        
    }

    virtual std::string whatAMI() const override
    {
        return "Enumerator list";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
        return list;
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override{
    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{

    }
    virtual std::string getId() const override{

    }
};

class EnumeratorSpecifier : 
    public Node 
{
private:
    std::vector<NodePtr> list;
public:

    EnumeratorSpecifier(std::vector<NodePtr> _list)
    {
        list = _list;
    }

    virtual ~EnumeratorSpecifier()
    {

    }
    
    virtual void visualise()const override
    {
        std::cout<<"in the enumerator list block"<<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int")const override
    {
        for(int i = 0; i<list.size(); i++){
            c.enum_variables.insert({list[i]->getId(), list[i]->getValue()});
        }
    }

    virtual std::string whatAMI() const override
    {
        return "Enumerator list";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
        return list;
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override{
    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{

    }
    virtual std::string getId() const override{

    }
};


#endif