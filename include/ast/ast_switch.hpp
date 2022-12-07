#ifndef ast_switch_hpp
#define ast_switch_hpp
#include "ast_base.hpp"

class SwitchStatement : 
    public Node 
{
private:
    NodePtr expression;
    std::vector<NodePtr> block;
public:

    SwitchStatement(NodePtr _expression, std::vector<NodePtr> _block)
    {
        expression = _expression;
        block = _block;
    }

    virtual ~SwitchStatement()
    {
        delete expression;
    }
    
    virtual void visualise()const override
    {
        std::cout<<"in the switch statement block"<<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int")const override
    {
        c.no_default = true;
        std::string old_end_of_case_link = c.end_of_case_link;
        std::string end_of_switch_label = makeName("$L");
        c.break_link = end_of_switch_label;
        int expression_register_number = c.FindTempRegister(c);
        std::string expression_register = c.GetTempRegisterName(c, expression_register_number);
        c.case_variable_register = expression_register;
        expression->generateMIPS(dst, expression_register, c);
        for(int i = 0; i < block.size(); i++)
        {
            block[i]->generateMIPS(dst, destReg, c);
        }
        if(c.no_default){
           dst << c.end_of_case_link << ":" << std::endl;
        }
        
        dst << end_of_switch_label << ":" << std::endl;



        c.FreeTempRegister(c, expression_register_number);
        c.end_of_case_link = old_end_of_case_link;
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

    }
};

#endif