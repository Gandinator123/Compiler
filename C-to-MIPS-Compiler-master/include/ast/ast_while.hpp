#ifndef ast_while_hpp
#define ast_while_hpp
#include "ast_base.hpp"

class WhileStatement
    : public Node
{
private:
    NodePtr condition;
    NodePtr block;
public:
    WhileStatement(NodePtr _condition, NodePtr _block){
        condition = _condition;
        block = _block;

    }
    virtual ~WhileStatement(){//can be inherited by all
        delete condition;
        delete block;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the condition block"<<std::endl;
        std::cout<<"condition:"<<std::endl;
        condition->visualise();
        std::cout<<"end of condition"<<std::endl;
        std::cout<<"block:"<<std::endl;
        block->visualise();
        std::cout<<"end of block"<<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        std::string condition_link = makeName("$L");
        std::string block_link = makeName("$L");
        dst << "b " << block_link <<std::endl;
        dst << "nop" << std::endl;
        dst << block_link << ":" << std::endl;
        block->generateMIPS(dst, destReg, c);
        dst << condition_link << ":" << std::endl;
        int condition_reg_number = c.FindRetRegister(c);
        std::string condition_reg = c.GetRetRegisterName(c, condition_reg_number);
        condition->generateMIPS(dst, condition_reg, c); //stores x>1 in a register
        dst << "bne " << condition_reg << ",$0," << block_link << std::endl;
        dst << "nop" << std::endl;
        c.FreeRetRegister(c, condition_reg_number);
    }
    virtual std::string whatAMI() const override
    {
        
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

    }
};

class DoWhileStatement
    : public Node
{
private:
    NodePtr condition;
    NodePtr block;
public:
    DoWhileStatement(NodePtr _condition, NodePtr _block){
        condition = _condition;
        block = _block;

    }
    virtual ~DoWhileStatement(){//can be inherited by all
        delete condition;
        delete block;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the do while condition block"<<std::endl;
        std::cout<<"condition:"<<std::endl;
        condition->visualise();
        std::cout<<"end of condition"<<std::endl;
        std::cout<<"block:"<<std::endl;
        block->visualise();
        std::cout<<"end of block"<<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        block->generateMIPS(dst, destReg, c);
        std::string condition_link = makeName("$L");
        std::string block_link = makeName("$L");
        dst << "b " << block_link <<std::endl;
        dst << "nop" << std::endl;
        dst << block_link << ":" << std::endl;
        block->generateMIPS(dst, destReg, c);
        dst << condition_link << ":" << std::endl;
        int condition_reg_number = c.FindRetRegister(c);
        std::string condition_reg = c.GetRetRegisterName(c, condition_reg_number);
        condition->generateMIPS(dst, condition_reg, c); //stores x>1 in a register
        dst << "bne " << condition_reg << ",$0," << block_link << std::endl;
        dst << "nop" << std::endl;
        c.FreeRetRegister(c, condition_reg_number);
    }
    virtual std::string whatAMI() const override
    {
        
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

    }
};




#endif