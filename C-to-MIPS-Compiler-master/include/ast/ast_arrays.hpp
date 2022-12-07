#ifndef ast_arrays_hpp
#define ast_arrays_hpp
#include "ast_base.hpp"

class ArrayDeclare
    : public Node
{
private:
    std::string* datatype;
    std::string* id;
    NodePtr size;
    int val;
public:
    ArrayDeclare(std::string* _datatype, std::string* _id, NodePtr _size)
    {
        datatype = _datatype;
        id = _id;
        size = _size;
        val = size->getValue();
    }
    virtual ~ArrayDeclare()
    {//can be inherited by all

    }
    virtual void visualise() const override
    {   
        std::cout<<"in the array declare node " <<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        //we only add the variable name i.e x[0] to memory and we increment the stackpointer from this memory slot when we need to...
        c.NewMemorySlot(c, *id);
    }
    virtual std::string whatAMI() const override //see why I did this in StandardDeclareAssign
    {
        return "Array Declare";
    }

    virtual std::vector<NodePtr> returnList() const override
    {

    } //used to implement a specific feature in a node
    virtual void countDeclarations(Context &c) const override{
        c.array_declarations += val;
    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{

    }
    virtual std::string getId() const override{
        return *id;
    }
};

class ArrayInit
    : public Node
{
private:
    NodePtr array;
    std::vector<NodePtr> values;
public:
    ArrayInit(NodePtr _array, std::vector<NodePtr> _values)
    {
        array = _array;
        values = _values;
    }
    virtual ~ArrayInit()
    {//can be inherited by all
        delete array;
            for(int i=0; i<values.size(); i++){
                delete values[i];
            }
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the array initialise node " <<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        int ret_reg_number = c.FindRetRegister(c);
        std::string ret_reg = c.GetRetRegisterName(c, ret_reg_number);
        array->generateMIPS(dst, ret_reg, c);
        int frame_size = (c.declarations*4)+8; //so that we start the array assigning after the variable storing...
        frame_size = (c.declarations*4)+8; //
        for(int i=0; i<values.size(); i++){
            values[i]->generateMIPS(dst, destReg, c);
            dst << "sw " << destReg << "," << frame_size << "($fp)" << std::endl;
            frame_size += 4;
        }
        c.FreeRetRegister(c, ret_reg_number);
    }
    virtual std::string whatAMI() const override //see why I did this in StandardDeclareAssign
    {
        return "Array Initialise";
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
        return array->getId();
    }
};

//
class ArrayAssign
    : public Node
{
private:
    std::string* identifier;
    NodePtr size;
    NodePtr assignment_expression;
public:
    ArrayAssign(std::string* _identifier, NodePtr _expression, NodePtr _assignment_expression)
    {
        identifier = _identifier;
        size = _expression;
        assignment_expression = _assignment_expression;
    }
    virtual ~ArrayAssign()
    {//can be inherited by all

    }
    virtual void visualise() const override
    {   
        std::cout<<"in the array assign node " <<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {

        int size_register_index = c.FindTempRegister(c);
        std::string size_register = c.GetTempRegisterName(c, size_register_index);
        int size2_register_index = c.FindTempRegister(c);
        std::string size2_register = c.GetTempRegisterName(c, size2_register_index);
        int variable_memory_slot = c.GetUsedMemorySlot(c, *identifier);
        //MIPS for the size of the array to assign;
        size->generateMIPS(dst, size_register, c);
        dst << "sll " << size_register << "," << size_register << ",2" << std::endl;
        dst << "addiu " << size2_register << ",$fp,8" << std::endl;
        dst << "addu " << size_register << "," << size_register << "," << size2_register << std::endl; 
        int ret_reg_number = c.FindRetRegister(c);
        std::string ret_reg = c.GetRetRegisterName(c, ret_reg_number);
        assignment_expression->generateMIPS(dst, ret_reg, c);
        // havent implemented graceful handling of trying to access variables out of range()
        dst<<"sw "<<ret_reg<<"," << (c.declarations*4)+4 << "(" << size_register<< ")" <<std::endl;    
        c.FreeTempRegister(c, size_register_index);
        c.FreeTempRegister(c, size2_register_index);
        c.FreeRetRegister(c, ret_reg_number);
    }
    virtual std::string whatAMI() const override //see why I did this in StandardDeclareAssign
    {
        return "Array Assign";
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
        return *identifier;
    }
};

//array access
class ArrayAcc
    : public Node
{
private:
    std::string* identifier;
    NodePtr size;
    int size_val;
public:
    ArrayAcc(std::string* _identifier, NodePtr _size)
    {
        identifier = _identifier;
        size = _size;
        size_val = size->getValue();
    }
    virtual ~ArrayAcc()
    {//can be inherited by all

    }
    virtual void visualise() const override
    {   
        std::cout<<"in the array initialise node " <<std::endl;
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        //global stuff
        if(c.GetUsedMemorySlot(c, *identifier)==-1){ 
            int ret_reg_number = c.FindRetRegister(c);
            std::string ret_reg = c.GetRetRegisterName(c, ret_reg_number);
            dst <<"lui " <<ret_reg << ",%hi" << "(" << *identifier <<")" << std::endl;
            dst <<"addiu " <<ret_reg << "," << ret_reg << ",%lo" << "(" << *identifier << ")" << std::endl;
            dst << "lw " << ret_reg << "," << size_val*4 << "(" << ret_reg << ")" << std::endl;
            c.FreeRetRegister(c, ret_reg_number);
        }
        else{
            int register2_index = c.FindTempRegister(c);
            std::string register2 = c.GetTempRegisterName(c, register2_index);
            int register3_index = c.FindTempRegister(c);
            std::string register3 = c.GetTempRegisterName(c, register3_index);
            size->generateMIPS(dst, register2, c);
            dst << "sll " << register2 << "," << register2 << ",2" << std::endl;
            dst << "addiu " << register3 << ",$fp,8" << std::endl;
            dst << "addu " << register2<<","<<register3<<","<<register2<<std::endl;
            dst << "lw " << register2 << "," << (c.declarations*4)+4 <<"(" << register2 << ")" << std::endl;
            dst << "nop" << std::endl;
            dst << "move " << destReg << "," << register2 << std::endl;
            c.FreeTempRegister(c, register2_index);
            c.FreeTempRegister(c, register3_index);
        }
        
        // int size_register_index = c.FindTempRegister(c);
        // std::string size_register = c.GetTempRegisterName(c, size_register_index);
        // int size2_register_index = c.FindTempRegister(c);
        // std::string size2_register = c.GetTempRegisterName(c, size2_register_index);
        // int variable_memory_slot = c.GetUsedMemorySlot(c, *identifier);
        // //MIPS for the size of the array to assign;
        // size->generateMIPS(dst, size_register, c);
        // // int size_val = size->getValue();
        // // dst << "addiu " << size_register << "," << size_val << std::endl; 
        // dst << "sll " << size_register << "," << size_register << ",2" << std::endl;
        // dst << "addiu " << size2_register << ",$fp,8" << std::endl;
        // dst << "addu " << size_register << "," << size_register << "," << size2_register << std::endl; 
        // // int ret_reg_number = c.FindRetRegister(c);
        // // std::string ret_reg = c.GetRetRegisterName(c, ret_reg_number);
        // dst<<"lw "<<size_register<<"," << c.declarations*4 << "(" << size_register<< ")" <<std::endl; 
        // dst<<"nop " << std::endl;
        // c.FreeTempRegister(c, size_register_index);
        // c.FreeTempRegister(c, size2_register_index);
        // // c.FreeRetRegister(c, ret_reg_number);
    }
    virtual std::string whatAMI() const override //see why I did this in StandardDeclareAssign
    {
        return "Array Access";
    }

    virtual std::vector<NodePtr> returnList() const override
    {

    } //used to implement a specific feature in a node
    virtual void countDeclarations(Context &c) const override{
    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{
        return size->getValue();

    }
    virtual std::string getId() const override{
        return *identifier;
    }
};


#endif
