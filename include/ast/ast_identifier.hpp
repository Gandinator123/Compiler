#ifndef ast_identifier_hpp
#define ast_identifier_hpp
#include "ast_base.hpp"

class Identifier : 
    public Node 
{
private:
    std::string* id;
public:

    Identifier(std::string* _id)
    {
        id = _id;
    }

    virtual ~Identifier()
    {

    }
    
    virtual void visualise()const override
    {
        std::cout<<"in the identifier block"<<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int")const override
    {
        int variable_memory_slot = c.GetUsedMemorySlot(c, *id);
        if(variable_memory_slot!=-1){
            if(type == "int"){
                dst<<"lw "<<destReg<<","<<variable_memory_slot<<"($fp)"<<std::endl;
                dst<<"nop " << std::endl;
            }
            else if(type == "float"){
                dst<<"lwc1 "<<destReg<<","<<variable_memory_slot<<"($fp)"<<std::endl;
                dst<<"nop " << std::endl;
            }else if(type == "double"){
                std::string arg_num_s;
                if(destReg.size()==3){
                arg_num_s = destReg.substr(2,1);
                }else{
                    arg_num_s = destReg.substr(2,2);
                }
                int arg_num = std::stoi(arg_num_s);
                arg_num++;
                std::string destReg2 = "$f"+std::to_string(arg_num);
                dst<<"lwc1 "<<destReg<<","<<variable_memory_slot+4<<"($fp)"<<std::endl;
                dst<<"lwc1 "<<destReg2<<","<<variable_memory_slot<<"($fp)"<<std::endl;
            }
        }else{
            auto it = c.enum_variables.find(*id);
            if(it!=c.enum_variables.end()){
                dst << "li " << destReg << "," << it->second << std::endl;
            }else{//for global loading
                int ret_reg_number = c.FindRetRegister(c);
                std::string ret_reg = c.GetRetRegisterName(c, ret_reg_number);
                dst <<"lui " <<ret_reg << ",%hi(x)" << std::endl;
                c.FreeRetRegister(c, ret_reg_number);
            }
        }
        // int variable_memory_slot = c.GetUsedMemorySlot(c, *id);
        // dst<<"lw "<<destReg<<","<<variable_memory_slot<<"($fp)"<<std::endl;
        // dst<<"nop " << std::endl;
        
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