#ifndef ast_keywords_hpp
#define ast_keywords_hpp

#include "ast_base.hpp"

class Return : 
    public Node
{
private:
    NodePtr return_value;
public:
    Return(NodePtr _return_value)
    {
        return_value = _return_value;
    }

    virtual ~Return()
    {
        delete return_value;
    }
        
    virtual void visualise()const override
    {   
        std::cout<<"in the return node"<<std::endl;
        return_value->visualise();
    }
    
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        if(c.return_type=="int"){
            int reg_index = c.FindRetRegister(c);
            c.FreeRetRegister(c, reg_index);
            std::string dR = c.GetRetRegisterName(c, reg_index);
        
            // std::cout<<"got to here"<<std::endl;
            // std::cout<<return_value->whatAMI()<<std::endl;
            std::cout<<"returning into register: "<< dR <<std::endl;;
            return_value->generateMIPS(dst,dR, c, c.return_type);
            dst << "b " << c.end_of_function_link << std::endl;
            dst << "nop" << std::endl;
            c.FreeRetRegister(c, reg_index);
        }else if(c.return_type=="float"){
            int float_reg_index = c.FindFloatRetRegister(c);
            c.FreeFloatRetRegister(c, float_reg_index);
            std::string dR = c.GetFloatRetRegisterName(c, float_reg_index);
            // std::cout<<"got to here"<<std::endl;
            // std::cout<<return_value->whatAMI()<<std::endl;
            std::cout<<"returning into register: "<< dR <<std::endl;;
            return_value->generateMIPS(dst,dR, c, c.return_type);
            dst << "b " << c.end_of_function_link << std::endl;
            dst << "nop" << std::endl;
            c.FreeRetRegister(c, float_reg_index);
        }
        else if(c.return_type=="double"){
            int float_reg_index = c.FindFloatRetRegister(c);
            c.FreeFloatRetRegister(c, float_reg_index);
            std::string dR = c.GetFloatRetRegisterName(c, float_reg_index);
            // std::cout<<"got to here"<<std::endl;
            // std::cout<<return_value->whatAMI()<<std::endl;
            std::cout<<"returning into register: "<< dR <<std::endl;;
            return_value->generateMIPS(dst,dR, c, c.return_type);
            dst << "b " << c.end_of_function_link << std::endl;
            dst << "nop" << std::endl;
            c.FreeRetRegister(c, float_reg_index);
        }
        else{
            std::cout<<"NO RETURN TYPE LIBTARD"<<std::endl;
        }
    }

    virtual std::string whatAMI() const override
    {
        return "Return";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
        
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override{
    }

    virtual void FunctionCallCheck (Context &c) const override{
        std::cout<<"doing return value function call check"<<std::endl;
        return_value->FunctionCallCheck(c);
    }

    virtual int getValue() const override{

    }
    virtual std::string getId() const override{

    }

};

class Break : 
    public Node 
{
private:

public:
    Break()
    {

    }

    virtual ~Break()
    {

    }
    
    virtual void visualise()const override
    {
        std::cout<<"break statement"<<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int")const override
    {
        dst << "b " << c.break_link << std::endl;
        dst << "nop" << std::endl;
    }

    virtual std::string whatAMI() const override
    {
        return "Break";
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


class Continue : 
    public Node 
{
private:

public:
    Continue()
    {

    }

    virtual ~Continue()
    {

    }
    
    virtual void visualise()const override
    {
        std::cout<<"continue statement"<<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int")const override
    {
        dst << "b " << c.continue_link << std::endl;
        dst << "nop" << std::endl;
    }

    virtual std::string whatAMI() const override
    {
        return "Continue";
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

class ReturnNone : 
    public Node 
{
private:

public:
    ReturnNone()
    {

    }

    virtual ~ReturnNone()
    {

    }
    
    virtual void visualise()const override
    {
        std::cout<<"return none"<<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int")const override
    {
        
    }

    virtual std::string whatAMI() const override
    {
        return "Break";
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


class Default : 
    public Node 
{
private:

public:
    Default()
    {

    }

    virtual ~Default()
    {

    }
    
    virtual void visualise()const override
    {
        std::cout<<"return none"<<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int")const override
    {
        
    }

    virtual std::string whatAMI() const override
    {
        return "Break";
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
