#ifndef ast_functions_hpp
#define ast_functions_hpp
#include "ast_base.hpp"
#include "make_name.hpp"

class FunctionDefinition : 
    public Node 
{
private:
    std::string* datatype;
    std::string* identifier;
    NodePtr function_block;
    NodePtr parameter_list;

public:
    FunctionDefinition(std::string* _datatype, std::string* _identifier, NodePtr _function_block)
    {
        parameter_list = NULL;
        datatype = _datatype;
        identifier = _identifier;
        function_block = _function_block;
    }
    
    FunctionDefinition(std::string* _datatype, std::string* _identifier, NodePtr _parameter_list, NodePtr _function_block)
    {
        datatype = _datatype;
        identifier = _identifier;
        function_block = _function_block;
        parameter_list = _parameter_list;
    }

    virtual ~FunctionDefinition()
    {
        delete function_block;
    }
    
    virtual void visualise()const override
    {
        std::cout<<"In the function definition block"<<std::endl;
        std::cout<<"start of params"<<std::endl;
        std::cout<<"end of params"<<std::endl;
        function_block->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int")const override
    {
        c.return_type = *datatype;
        c.end_of_function_link = makeName("$L");
        c.next_available_memory_slot=8;
        c.declarations = 0;
        c.array_declarations = 0;
         //we are setting the frame pointer to be 32 to accomodate extra room. We add size according to how many assignments there are
        function_block->countDeclarations(c);
        std::cout<<"number of variable declarations: " << c.declarations<<std::endl;
        std::cout<<"number of array declarations: " << c.array_declarations<<std::endl;
        int frame_size;
        int declarations = c.declarations + c.array_declarations;
        if(declarations == 0 || declarations == 1){
            frame_size = 32;
        }
        else{
            frame_size = 32 + int((declarations)/2)*8;
        }
        frame_size+=52;//to allow for saving temp registers during function calls.
        c.frame_size_for_call = frame_size;
        c.argument_declaration = false;
        c.next_available_memory_slot = frame_size;
        
        std::cout<<"frame size: "<< frame_size<<std::endl;
        dst << ".globl " << *identifier <<std::endl;
        dst <<*identifier<<":"<<std::endl;
        dst << "addiu $sp,$sp,-"<< (frame_size) << std::endl;
        dst << "sw $fp,"<< (frame_size-4) <<"($sp)" << std::endl;
        dst << "sw $31," << (frame_size-4) << "($sp)" << std::endl;
        // dst << "move $fp,$sp" << std::endl;
        dst << "sw $fp," << (frame_size-8) << "($sp)" << std::endl;
        dst << "move $fp,$sp" << std::endl;
        if(parameter_list!=NULL){
            parameter_list->generateMIPS(dst, destReg, c);
        }
        c.next_available_memory_slot = 8;
        dst << "nop" <<std::endl;
        function_block->generateMIPS(dst,destReg, c);
        dst << c.end_of_function_link << ":" << std::endl;
        dst << "move $sp,$fp"<< std::endl;
        dst << "lw $fp,"<< (frame_size-4) <<"($sp)"<<std::endl;
        dst << "lw $31,"<< frame_size-4 << "($sp)" << std::endl;
        dst << "lw $fp," << frame_size-8 << "($sp)" << std::endl;
        dst << "addiu $sp,$sp,"<< frame_size << std::endl;
        dst << "j $31"<<std::endl;
        dst << "nop"<<std::endl;
        
    }

    virtual std::string whatAMI() const override
    {
        return "Function Definition";
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

class NullFunctionDefinition : 
    public Node 
{
private:
    std::string* datatype;
    std::string* identifier;
    NodePtr parameter_list;

public:
    NullFunctionDefinition(std::string* _datatype, std::string* _identifier, NodePtr _parameter_list)
    {
        parameter_list = NULL;
        datatype = _datatype;
        identifier = _identifier;
    }
    NullFunctionDefinition(std::string* _datatype, std::string* _identifier)
    {
        datatype = _datatype;
        identifier = _identifier;
    }
    virtual ~NullFunctionDefinition()
    {
    }
    
    virtual void visualise()const override
    {
        std::cout<<"In the null function definition block"<<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int")const override
    {   
    }

    virtual std::string whatAMI() const override
    {
        return "Null Function Definition";
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