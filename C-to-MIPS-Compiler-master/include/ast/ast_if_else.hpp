#ifndef ast_if_else_hpp
#define ast_if_else_hpp
#include "ast_base.hpp"

class IfStatement: 
    public Node 
{
private:
    NodePtr condition;
    NodePtr general_statement;
public:

    IfStatement(NodePtr _condition, NodePtr _general_statement)
    {
        condition = _condition;
        general_statement = _general_statement;
    }

    virtual ~IfStatement()
    {
        delete condition;
        delete general_statement;
    }
    
    virtual void visualise()const override
    {
        std::cout<<"in the if (no else) node"<<std::endl;
        condition->visualise();
        general_statement->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int")const override
    {
        int condition_reg_number = c.FindRetRegister(c);
        std::string condition_reg = c.GetRetRegisterName(c, condition_reg_number);
        condition->generateMIPS(dst, condition_reg, c); //stores x>1 in a register
        std::string jump_label1 = makeName("$L");
        dst << "beq " << condition_reg << ",$0," << jump_label1 << std::endl;
        c.FreeRetRegister(c, condition_reg_number);
        dst << "nop" << std::endl;
        general_statement->generateMIPS(dst, destReg, c);
        dst << jump_label1 << ":" << std::endl;
    }

    virtual std::string whatAMI() const override
    {
        return "If Else Statement";
    }

    virtual std::vector<NodePtr> returnList() const override
    {   
        
    } //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override{
        general_statement->countDeclarations(c);
    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{

    }
    virtual std::string getId() const override{

    }
};

class IfElseStatement: 
    public Node 
{
private:
    NodePtr condition;
    NodePtr if_block;
    NodePtr else_block;
public:

    IfElseStatement(NodePtr _condition, NodePtr _if_block, NodePtr _else_block)
    {
        condition = _condition;
        if_block = _if_block;
        else_block = _else_block;
    }

    virtual ~IfElseStatement()
    {
        delete condition;
        delete if_block;
        delete else_block;
    }
    
    virtual void visualise()const override
    {
        std::cout<<"in the if and else node"<<std::endl;
        condition->visualise();
        if_block->visualise();
        else_block->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int")const override
    {
        int condition_reg_number = c.FindRetRegister(c);
        std::string condition_reg = c.GetRetRegisterName(c, condition_reg_number);
        condition->generateMIPS(dst, condition_reg, c); //stores x>1 in a register
        std::string jump_label1 = makeName("$L");
        dst << "beq " << condition_reg << ",$0," << jump_label1 << std::endl;
        c.FreeRetRegister(c, condition_reg_number);
        dst << "nop" << std::endl;
        if_block->generateMIPS(dst, destReg, c);
        dst << jump_label1 << ":" << std::endl;
        else_block->generateMIPS(dst, destReg, c);
    }

    virtual std::string whatAMI() const override
    {
        return "If Else Statement";
    }

    virtual std::vector<NodePtr> returnList() const override
    {

    } //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override{
        if_block->countDeclarations(c);
        else_block->countDeclarations(c);
    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{

    }
    virtual std::string getId() const override{

    }
};

#endif