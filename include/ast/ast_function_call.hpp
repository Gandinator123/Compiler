#ifndef ast_function_call_hpp
#define ast_function_call_hpp
#include "ast_base.hpp"

class FunctionCall : 
    public Node 
{
private:
    std::string* id;
    std::vector<NodePtr> parameter_list;
public:

    FunctionCall(std::string* _id)
    {
        id = _id;
    }

    FunctionCall(std::string* _id, NodePtr _parameter_list)
    {
        id = _id;
        parameter_list = _parameter_list->returnList();
    }


    virtual ~FunctionCall()
    {

    }
    
    virtual void visualise()const override
    {
        std::cout<<"in the function call block"<<std::endl;
        std::cout<<"id is: "<< *id << std::endl;
    }

    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int")const override
    {
        

        dst << "sw " << "$8," << c.frame_size_for_call-48<<"($sp)"<< std::endl;
        dst << "nop" << std::endl;
        dst << "sw " << "$9," << c.frame_size_for_call-44<<"($sp)"<< std::endl;
        dst << "nop" << std::endl;
        dst << "sw " << "$10," << c.frame_size_for_call-40<<"($sp)"<< std::endl;
        dst << "nop" << std::endl;
        dst << "sw " << "$11," << c.frame_size_for_call-36<<"($sp)"<< std::endl;
        dst << "nop" << std::endl;
        dst << "sw " << "$12," << c.frame_size_for_call-32<<"($sp)"<< std::endl;
        dst << "nop" << std::endl;
        dst << "sw " << "$13," << c.frame_size_for_call-28<<"($sp)"<< std::endl;
        dst << "nop" << std::endl;
        dst << "sw " << "$14," << c.frame_size_for_call-24<<"($sp)"<< std::endl;
        dst << "nop" << std::endl;
        dst << "sw " << "$15," << c.frame_size_for_call-20<<"($sp)"<< std::endl;
        dst << "nop" << std::endl;
        dst << "sw " << "$24," << c.frame_size_for_call-16<<"($sp)"<< std::endl;
        dst << "nop" << std::endl;
        dst << "sw " << "$25," << c.frame_size_for_call-12<<"($sp)"<< std::endl;
        dst << "nop" << std::endl;

        if(parameter_list.size()>0){
            std::string argument_register;
            for(int i = 0; i<parameter_list.size(); i++)
            {
                argument_register = c.GetArgRegisterName(c, i);
                parameter_list[i]->generateMIPS(dst, argument_register, c);
                dst << "nop" << std::endl;
            }
        }

        dst<<"jal " << *id << std::endl;
        dst<<"nop"<<std::endl;

        
        dst << "lw " << "$8," << c.frame_size_for_call-48<<"($sp)"<< std::endl;
        dst << "nop" << std::endl;
        dst << "lw " << "$9," << c.frame_size_for_call-44<<"($sp)"<< std::endl;
        dst << "nop" << std::endl;
        dst << "lw " << "$10," << c.frame_size_for_call-40<<"($sp)"<< std::endl;
        dst << "nop" << std::endl;
        dst << "lw " << "$11," << c.frame_size_for_call-36<<"($sp)"<< std::endl;
        dst << "nop" << std::endl;
        dst << "lw " << "$12," << c.frame_size_for_call-32<<"($sp)"<< std::endl;
        dst << "nop" << std::endl;
        dst << "lw " << "$13," << c.frame_size_for_call-28<<"($sp)"<< std::endl;
        dst << "nop" << std::endl;
        dst << "lw " << "$14," << c.frame_size_for_call-24<<"($sp)"<< std::endl;
        dst << "nop" << std::endl;
        dst << "lw " << "$15," << c.frame_size_for_call-20<<"($sp)"<< std::endl;
        dst << "nop" << std::endl;
        dst << "lw " << "$24," << c.frame_size_for_call-16<<"($sp)"<< std::endl;
        dst << "nop" << std::endl;
        dst << "lw " << "$25," << c.frame_size_for_call-12<<"($sp)"<< std::endl;
        dst << "nop" << std::endl;

    }

    virtual std::string whatAMI() const override
    {
        return "Function Call";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
        
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override{
    }

    virtual void FunctionCallCheck (Context &c) const override{
        std::cout << "Function Call" << std::endl;
        c.function_call_register_change(c);
    }

    virtual int getValue() const override{

    }
    virtual std::string getId() const override{

    }
};

#endif