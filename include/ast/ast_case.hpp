#ifndef ast_case_hpp
#define ast_case_hpp
#include "ast_base.hpp"

class CaseStatement : 
    public Node 
{
private:
    NodePtr condition;
public:

    CaseStatement(NodePtr _condition)
    {
        condition = _condition;
    }

    virtual ~CaseStatement()
    {
        delete condition;
    }
    
    virtual void visualise()const override
    {
        std::cout<<"in the Case block"<<std::endl;
        condition->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int")const override
    {
        // if(!c.case_section){
        //     int value_register_number = c.FindTempRegister(c);
        //     std::string value_register = c.GetTempRegisterName(c, value_register_number);
        //     condition->generateMIPS(dst, value_register, c);
        //     dst << "beq "<< c.case_variable_register << "," << value_register << "," << destReg << std::endl;
        //     dst << "nop" << std::endl;
        //     c.FreeTempRegister(c, value_register_number);
        // }
        // else{
        //     dst << destReg << ":" << std::endl;
        //     block->generateMIPS(dst, destReg, c);
        // }
        if(c.end_of_case_link.size()>0){
            dst << c.end_of_case_link << ":" << std::endl;
        }
        std::string not_matched = makeName("$L");
        c.end_of_case_link = not_matched;
        int value_register_number = c.FindTempRegister(c);
        std::string value_register = c.GetTempRegisterName(c, value_register_number);
        condition->generateMIPS(dst, value_register, c);
        c.FreeTempRegister(c, value_register_number);
        dst << "bne " << value_register << "," << c.case_variable_register << "," <<not_matched << std::endl; 
    }

    virtual std::string whatAMI() const override
    {
        return "case block";
    };

    virtual std::vector<NodePtr> returnList() const override
    {

    }; 

    virtual void countDeclarations(Context &c) const override{
    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{

    }
    virtual std::string getId() const override{

    }
};

class DefaultCaseStatement : 
    public Node 
{
private:
public:

    DefaultCaseStatement()
    {
    }

    virtual ~DefaultCaseStatement()
    {
    }
    
    virtual void visualise()const override
    {
        std::cout<<"in the Default block"<<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int")const override
    {
        c.no_default = false;
        dst << c.end_of_case_link << ":" << std::endl;
    }

    virtual std::string whatAMI() const override
    {
        return "default block";
    };

    virtual std::vector<NodePtr> returnList() const override
    {

    }; 

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