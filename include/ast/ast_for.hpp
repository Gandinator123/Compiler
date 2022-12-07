#ifndef ast_for_hpp
#define ast_for_hpp
#include "ast_base.hpp"

class ForStatement
    : public Node
{
private:
    NodePtr variable_start;
    NodePtr condition;
    NodePtr variable_update;
    NodePtr block;
public:
    ForStatement(NodePtr _variable_start, NodePtr _condition, NodePtr _variable_update, NodePtr _block){
        variable_start = _variable_start;
        condition = _condition;
        variable_update = _variable_update;
        block = _block;
    }
    virtual ~ForStatement(){//can be inherited by all
        delete variable_start;
        delete condition;
        delete variable_update;
        delete block;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in a for loop"<<std::endl;
        std::cout<<"the variable declaration: "<<std::endl;
        variable_start->visualise();
        std::cout<<"the condition: "<<std::endl;
        condition->visualise();
        std::cout<<"the variable update:"<<std::endl;
        variable_update->visualise();
        std::cout<<"the block:"<<std::endl;
        block->visualise();
        std::cout<<"end of for loop"<<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        std::string condition_link = makeName("$L");
        std::string block_link = makeName("$L");
        //initialise variable:
        variable_start->generateMIPS(dst, destReg, c);
        dst << "b " << condition_link << std::endl;
        dst << "nop" << std::endl;
        dst << block_link << ":" << std::endl;
        dst<< "nop" << std::endl;
        dst << "nop" << std::endl;
        //run the block
        block->generateMIPS(dst, destReg, c);
        //update the variable
        dst << "nop" << std::endl;
        dst << "nop" << std::endl;
        int up_num = c.FindTempRegister(c);
        std::string up = c.GetTempRegisterName(c, up_num);
        variable_update->generateMIPS(dst, up, c);
        c.FreeTempRegister(c, up_num);
        dst << condition_link << ":" << std::endl;
        //evaluate the condition
        int condition_reg_number = c.FindRetRegister(c);
        std::string condition_reg = c.GetRetRegisterName(c, condition_reg_number);
        condition->generateMIPS(dst, condition_reg, c); 
        dst << "bne " << condition_reg << ",$0," << block_link << std::endl;
        dst << "nop" << std::endl;
        c.FreeRetRegister(c, condition_reg_number);
    }
    virtual std::string whatAMI() const override
    {
        return "For statement";
    }
    virtual std::vector<NodePtr> returnList() const override
    {
        
    } //used to implement a specific feature in a node
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