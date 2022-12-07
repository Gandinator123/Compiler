#ifndef ast_variable_declare_hpp
#define ast_variable_declare_hpp
#include "ast_base.hpp"

class VariableDeclare
    : public Node
{
private:
    std::string *datatype;
    std::string *id;
    bool pointer;
public:
    VariableDeclare(std::string* _datatype, std::string* _id, bool _pointer = false)
    {
        datatype = _datatype;
        id = _id;
        pointer = _pointer;
    }
    virtual ~VariableDeclare()
    {//can be inherited by all

    }
    virtual void visualise() const override
    {   
        std::cout<<"in the variable declare node"<<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        int memory_slot = c.NewMemorySlot(c, *id, *datatype);
        if(c.argument_declaration){
            if(*datatype == "int" || c.argument_number>1){
                std::cout<<"hiii"<<c.argument_number<<std::endl;
                std::string arg_register = c.GetArgRegisterName(c, c.argument_number);
                dst<<"sw "<<arg_register<<","<<memory_slot<<"($fp)"<<std::endl;
            }
            else if(*datatype == "float"){
                std::string float_arg_register = c.GetFloatArgRegisterName(c, c.argument_number);
                dst<<"swc1 "<<float_arg_register<<","<<memory_slot<<"($fp)"<<std::endl;
            }else if(*datatype == "double"){
                std::cout<<"oi"<<std::endl;
                std::string float_arg_register = c.GetFloatArgRegisterName(c, c.argument_number);
                std::string arg_num_s = float_arg_register.substr(2,2);
                int arg_num = std::stoi(arg_num_s);
                arg_num++;
                std::string float_arg_register2 = "$f"+std::to_string(arg_num);
                dst<<"swc1 "<<float_arg_register<<","<<memory_slot+4<<"($fp)"<<std::endl;
                dst<<"swc1 "<<float_arg_register2<<","<<memory_slot<<"($fp)"<<std::endl;
                c.next_available_memory_slot+=4;
            }
            
        }
        else{
            if(*datatype == "double"){
                c.next_available_memory_slot+=4;
            }
        }
        if(pointer){
            c.pointers.push_back(*id);
        }
    }
    virtual std::string whatAMI() const override //see why I did this in StandardDeclareAssign
    {
        std::cout << *datatype << std::endl;
        return *datatype;
    }

    virtual std::vector<NodePtr> returnList() const override
    {

    } //used to implement a specific feature in a node
    virtual void countDeclarations(Context &c) const override{
        c.declarations += 1;
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