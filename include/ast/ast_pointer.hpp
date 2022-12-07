#ifndef ast_pointer_hpp
#define ast_pointer_hpp

#include "ast_base.hpp"

class Pointer : 
    public Node 
{
private:
    int number;

public:
    Pointer(int _number)
    {
        number = _number;
    }
    virtual ~Pointer(){

    }
    virtual void visualise()const override
    {
        std::cout<<"in the Pointer Node" << std::endl;
    }

    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {

    }

    virtual std::string whatAMI() const override
    {
        return std::to_string(number);
    }

    virtual std::vector<NodePtr> returnList() const override
    {

    } //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override{
    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{
        return number;
    }
    virtual std::string getId() const override{

    }
};

class PointerIdentifier : 
    public Node 
{
private:
    std::string* id;
public:

    PointerIdentifier(std::string* _id)
    {
        id = _id;
    }

    virtual ~PointerIdentifier()
    {

    }
    
    virtual void visualise()const override
    {
        std::cout<<"in the identifier block"<<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int")const override
    {
        int variable_memory_slot = c.GetUsedMemorySlot(c, *id);
        dst << "lw " << destReg << "," << variable_memory_slot << "($fp)"<<std::endl;
        dst << "nop " << std::endl;
        dst << "lw " << destReg << ",0(" << destReg <<")" << std::endl;
        dst << "nop" << std::endl;
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

    }
    virtual std::string getId() const override{
        return *id;
    }
};

#endif