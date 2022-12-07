#ifndef ast_unary_operators_hpp
#define ast_unary_operators_hpp
#include "ast_base.hpp"

// class UnaryOperator
//     : public Node
// {
// private:
//     NodePtr primary;
// public:
//     UnaryOperator(NodePtr _primary){
//         primary = _primary;
//     }
//     virtual ~UnaryOperator(){//can be inherited by all
//         delete primary;
//     }
//     virtual void visualise() const override
//     {   
//         std::cout<<"in the unary operator node"<<std::endl;
//         primary->visualise();
//     }
//     virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c) const override
//     {
        
//     }
//     virtual std::string whatAMI() const override
//     {
        
//     };
//     virtual std::vector<NodePtr> returnList() const override
//     {

//     }; //used to implement a specific feature in a node
//     virtual void countDeclarations(Context &c) const override{
//     }

//     virtual void FunctionCallCheck (Context &c) const override{
        
//     }

//     virtual int getValue() const override{
//         return primary->getValue();
//     }
//     virtual std::string getId() const override{

//     }
// };

// -x
class NegOperator
    : public Node
{
private:
    NodePtr primary;
public:
    NegOperator(NodePtr _primary){
        primary = _primary;
    }
    virtual ~NegOperator(){
        delete primary;
    }

    virtual void visualise() const override
    {   
        std::cout<<"in the neg operator node"<<std::endl;
        primary->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        primary->generateMIPS(dst, destReg, c);
        dst << "subu " << destReg << ",$0," << destReg << std::endl;  
    }
    virtual std::string whatAMI() const override
    {
        return "Neg Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {

    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {

    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{
        return -(primary->getValue());
    }
    virtual std::string getId() const override{

    }
};


//!x

// !x
class NotOperator
    : public Node
{
private:
    NodePtr primary;
public:
    NotOperator(NodePtr _primary){
        primary = _primary;
    }
    virtual ~NotOperator(){
        delete primary;
    }

    virtual void visualise() const override
    {   
        std::cout<<"in the neg operator node"<<std::endl;
        primary->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        std::string mydestReg;
        int ret_reg_index;
        bool single_line = false;
        if(destReg == ""){
            int ret_reg_index = c.FindRetRegister(c);
            mydestReg = c.GetRetRegisterName(c, ret_reg_index);
            single_line = true;
        }else{
            mydestReg = destReg;
        }
        primary->generateMIPS(dst, mydestReg, c);
        dst << "slti " << "," << mydestReg << "," << mydestReg << ",1" << std::endl;  
        dst << "andi " << mydestReg << "," << mydestReg << ",0x00ff" << std::endl;
        if(single_line){
            single_line = false;
            c.FreeRetRegister(c, ret_reg_index);
        }

    }
    virtual std::string whatAMI() const override
    {
        return "Not Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {

    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {

    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{
        // return !(primary->getValue());
    }
    virtual std::string getId() const override{

    }
};


////////
// Increment/Decrement operators
// x++
// x--
// ++x
// --x

//++x
class PreIncrOperator : public Node
{
private:
    NodePtr primary;
public:
    PreIncrOperator(NodePtr _primary)
    {
        primary = _primary;
    }
    virtual ~PreIncrOperator(){
        delete primary;
    }
    virtual void visualise() const override
    {      
        std::cout<<"in the pre-increment operator node"<<std::endl;
        primary->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        std::string mydestReg;
        int ret_reg_index;
        bool single_line = false;
        if(destReg == ""){
            int ret_reg_index = c.FindRetRegister(c);
            mydestReg = c.GetRetRegisterName(c, ret_reg_index);
            single_line = true;
        }else{
            mydestReg = destReg;
        }
        std::string id = primary->getId();
        int memory_slot =  c.GetUsedMemorySlot(c, id);
        primary->generateMIPS(dst, mydestReg, c);
        dst << "addiu " << mydestReg << "," << mydestReg << ",1" << std::endl;
        dst << "sw " << mydestReg << "," << memory_slot << "($fp)" << std::endl;
        dst << "lw " << mydestReg << "," << memory_slot << "($fp)" << std::endl;
        if(single_line){
            single_line = false;
            c.FreeRetRegister(c, ret_reg_index);
        }
    }
    virtual std::string whatAMI() const override
    {
        return "Pre-Increment Operator";
    }

    virtual std::vector<NodePtr> returnList() const override
    {

    } //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {

    }
    virtual void FunctionCallCheck (Context &c) const override{

    }

    virtual int getValue() const override{
        return primary->getValue();
    }
    virtual std::string getId() const override{

    }
};


//--x (NEED TO DOOO)
class PreDecrOperator : public Node
{
private:
    NodePtr primary;
public:
    PreDecrOperator(NodePtr _primary)
    {
        primary = _primary;
    }
    virtual ~PreDecrOperator(){
        delete primary;
    }

    virtual void visualise() const override
    {   
        std::cout<<"in the pre-decrement operator node"<<std::endl;
        primary->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        std::string mydestReg;
        int ret_reg_index;
        bool single_line = false;
        if(destReg == ""){
            int ret_reg_index = c.FindRetRegister(c);
            mydestReg = c.GetRetRegisterName(c, ret_reg_index);
            single_line = true;
        }else{
            mydestReg = destReg;
        }
        std::string id = primary->getId();
        int memory_slot =  c.GetUsedMemorySlot(c, id);
        primary->generateMIPS(dst, mydestReg, c);
        dst << "addiu " << mydestReg << "," << mydestReg << ",-1" << std::endl;
        dst << "sw " << mydestReg << "," << memory_slot << "($fp)" << std::endl;
        dst << "lw " << mydestReg << "," << memory_slot << "($fp)" << std::endl;
        if(single_line){
            single_line = false;
            c.FreeRetRegister(c, ret_reg_index);
        }
    }
    virtual std::string whatAMI() const override
    {
        return "Pre-Decrement Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {

    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {

    }

    virtual void FunctionCallCheck (Context &c) const override{

    }

    virtual int getValue() const override{
        // return primary->getValue();
    }
    virtual std::string getId() const override{

    }
};

//x++
class PostIncrOperator : public Node
{
private:
    NodePtr primary;
public:
    PostIncrOperator(NodePtr _primary)
    {
        primary = _primary;
    }
    virtual ~PostIncrOperator(){
        delete primary;
    }

    virtual void visualise() const override
    {   
        std::cout<<"in the Post-increment operator node"<<std::endl;
        primary->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        std::string mydestReg;
        int ret_reg_index;
        bool single_line = false;
        if(destReg == ""){
            int ret_reg_index = c.FindRetRegister(c);
            mydestReg = c.GetRetRegisterName(c, ret_reg_index);
            single_line = true;
        }else{
            mydestReg = destReg;
        }
        std::string id = primary->getId();
        int memory_slot =  c.GetUsedMemorySlot(c, id);
        primary->generateMIPS(dst, mydestReg, c);
        dst << "addiu " << mydestReg << "," << mydestReg << ",1" << std::endl;
        dst << "sw " << mydestReg << "," << memory_slot << "($fp)" << std::endl;
        if(single_line){
            single_line = false;
            c.FreeRetRegister(c, ret_reg_index);
        }
    }
    virtual std::string whatAMI() const override
    {
        return "Post-Increment Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {

    }; //used to implement a specific feature in a node
    virtual void countDeclarations(Context &c) const override{}
    virtual void FunctionCallCheck (Context &c) const override{

    }
    virtual int getValue() const override{
        return primary->getValue();
    }
    virtual std::string getId() const override{

    }
};

//x--
class PostDecrOperator : public Node
{
private:
    NodePtr primary;
public:
    PostDecrOperator(NodePtr _primary)
    {
        primary = _primary;
    }
    virtual ~PostDecrOperator(){
        delete primary;
    }

    virtual void visualise() const override
    {   
        std::cout<<"in the Post-Decrement operator node"<<std::endl;
        primary->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        std::string mydestReg;
        int ret_reg_index;
        bool single_line = false;
        if(destReg == ""){
            int ret_reg_index = c.FindRetRegister(c);
            mydestReg = c.GetRetRegisterName(c, ret_reg_index);
            single_line = true;
        }else{
            mydestReg = destReg;
        }
        std::string id = primary->getId();
        int memory_slot =  c.GetUsedMemorySlot(c, id);
        primary->generateMIPS(dst, mydestReg, c);
        dst << "addiu " << mydestReg << "," << mydestReg << ",-1" << std::endl;
        dst << "sw " << mydestReg << "," << memory_slot << "($fp)" << std::endl;
        if(single_line){
            single_line = false;
            c.FreeRetRegister(c, ret_reg_index);
        }
    }
    virtual std::string whatAMI() const override
    {
        return "Post-Decrement Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {

    }; //used to implement a specific feature in a node
    virtual void countDeclarations(Context &c) const override{}
    virtual void FunctionCallCheck (Context &c) const override{

    }

    virtual int getValue() const override{
        return primary->getValue();
    }
    virtual std::string getId() const override{

    }
};



///////////////////////////////////////////
// REFERECING...


//&x e.g. int *p = &x;
class AddressOperator :
    public Node
{
private:
    NodePtr primary;
public:
    AddressOperator(NodePtr _primary)
    {
        primary = _primary;
    }
    
    virtual ~AddressOperator(){
        delete primary;
    }

    virtual void visualise() const override
    {   
        std::cout<<"in the Address operator node"<<std::endl;
        primary->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        std::string id = primary->getId();
        int memory_slot =  c.GetUsedMemorySlot(c, id);
        dst << "addiu " << destReg << ",$fp," << memory_slot << std::endl;
    }
    virtual std::string whatAMI() const override
    {
        return "Address Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {

    }; //used to implement a specific feature in a node
    virtual void countDeclarations(Context &c) const override{}
    virtual void FunctionCallCheck (Context &c) const override{

    }

    virtual int getValue() const override{

    }
    virtual std::string getId() const override{
        return primary->getId();
    }
};


#endif