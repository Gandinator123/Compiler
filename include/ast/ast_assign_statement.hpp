#ifndef ast_assign_statement_hpp
#define ast_assign_statement_hpp
#include "ast_base.hpp"



class StandardAssignStatement
    : public Node
{
private:
    std::string* identifier;
    NodePtr assignment_expression;
    bool pointer;
public:
    StandardAssignStatement(std::string* _identifier, NodePtr _assignment_expression, bool _pointer = false)
    {
        identifier = _identifier;
        assignment_expression = _assignment_expression;
        pointer=_pointer;
    }
    virtual ~StandardAssignStatement()
    {
        delete assignment_expression;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the standard assign statement node"<<std::endl;
        assignment_expression->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {// e.g x = 2;
        if(!pointer){
            std::string type = c.GetVariableType(c, *identifier);
            c.pointer_arithmetic = false;
            
            int variable_memory_slot = c.GetUsedMemorySlot(c, *identifier);
            if(c.pointers.size()>0){
                for(int i = 0; i<c.pointers.size();i++){
                    if(c.pointers[i]==*identifier){
                        c.pointer_arithmetic = true;
                    }
                }
            }
            if(type == "int"){
                int ret_reg_number = c.FindRetRegister(c);
                std::string ret_reg = c.GetRetRegisterName(c, ret_reg_number);
                assignment_expression->generateMIPS(dst, ret_reg, c, type);
                dst << "sw " << ret_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
                c.FreeRetRegister(c, ret_reg_number);
            }
            else if(type == "float"){
                int float_ret_reg_number = c.FindFloatRetRegister(c);
                std::string float_ret_reg = c.GetFloatRetRegisterName(c, float_ret_reg_number);
                assignment_expression->generateMIPS(dst, float_ret_reg, c, "float");
                dst << "swc1 " << float_ret_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
                c.FreeFloatRetRegister(c, float_ret_reg_number);
            }
            else if(type == "double"){
                int float_ret_reg_number = c.FindFloatTempRegister(c);
                std::string float_ret_reg = c.GetFloatTempRegisterName(c, float_ret_reg_number);
                std::string num_s;
                if(destReg.size()==3){
                    num_s = float_ret_reg.substr(2,1);
                }else{
                    num_s = float_ret_reg.substr(2,2);
                }
                int arg_num = std::stoi(num_s);
                arg_num++;
                std::string float_ret_reg2 = "$f"+std::to_string(arg_num);
                assignment_expression->generateMIPS(dst, float_ret_reg, c, "double");
                dst << "swc1 " << float_ret_reg << "," <<  variable_memory_slot+4 << "($fp)" << std::endl;
                dst << "nop" << std::endl;
                dst << "swc1 " << float_ret_reg2 << "," <<  variable_memory_slot << "($fp)" << std::endl;
                c.FreeFloatRetRegister(c, float_ret_reg_number);
            }
        }else{
            c.pointer_arithmetic = true;
            int variable_memory_slot = c.GetUsedMemorySlot(c, *identifier);
            int temp1_number = c.FindTempRegister(c);
            std::string temp1 = c.GetTempRegisterName(c, temp1_number);
            int temp2_number = c.FindTempRegister(c);
            std::string temp2 = c.GetTempRegisterName(c, temp2_number);
            dst << "lw " << temp1 <<"," << variable_memory_slot << "($fp)" << std::endl;
            assignment_expression->generateMIPS(dst, temp2, c);
            dst << "sw " << temp2 << ",0(" << temp1 << ")" << std::endl;
            c.FreeTempRegister(c, temp1_number);
            c.FreeTempRegister(c, temp2_number);
        }

        
    }
    virtual std::string whatAMI() const override
    {
        return "Standard Assign Statement";
    }

    virtual std::vector<NodePtr> returnList() const override
    {
        
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override{
        //do not do anything
    }

    virtual void FunctionCallCheck (Context &c) const override{
        assignment_expression->FunctionCallCheck(c);
    }

    virtual int getValue() const override{

    }
    virtual std::string getId() const override{

    }

};



class StandardDeclareAssignStatement
    : public Node
{
private:
    NodePtr variable_declare;
    NodePtr assignment_expression;

public:
    StandardDeclareAssignStatement(NodePtr _variable_declare, NodePtr _assignment_expression)
    {
        variable_declare = _variable_declare;
        assignment_expression = _assignment_expression;
    }
    virtual ~StandardDeclareAssignStatement()
    {
        delete variable_declare;
        delete assignment_expression;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the standard declare assign statement node"<<std::endl;
        assignment_expression->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {// e.g int x = 2;
        std::string mytype = variable_declare->whatAMI();
        variable_declare->generateMIPS(dst, destReg, c, mytype); //does the int x part
        std::string id = variable_declare->getId();
        mytype = c.GetVariableType(c, id);
        int variable_memory_slot = c.GetUsedMemorySlot(c, id);
        std::cout << "type is:" << mytype << std::endl;
        if(mytype == "int"){
            int ret_reg_number = c.FindRetRegister(c);
            std::string ret_reg = c.GetRetRegisterName(c, ret_reg_number);
            assignment_expression->generateMIPS(dst,ret_reg,c);
            dst << "sw " << ret_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
            c.FreeRetRegister(c, ret_reg_number);
        }
        else if(mytype == "float"){
            int float_ret_reg_number = c.FindFloatRetRegister(c);
            std::string float_ret_reg = c.GetFloatRetRegisterName(c, float_ret_reg_number);
            assignment_expression->generateMIPS(dst,float_ret_reg,c, "float");
            dst << "swc1 " << float_ret_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
            c.FreeFloatRetRegister(c, float_ret_reg_number);
        }
        else if(mytype == "double"){
            int float_ret_reg_number = c.FindFloatTempRegister(c);
            std::string float_ret_reg = c.GetFloatTempRegisterName(c, float_ret_reg_number);
            std::string num_s;
            if(destReg.size()==3){
                num_s = float_ret_reg.substr(2,1);
            }else{
                num_s = float_ret_reg.substr(2,2);
            }
            int arg_num = std::stoi(num_s);
            arg_num++;
            std::string float_ret_reg2 = "$f"+std::to_string(arg_num);
            assignment_expression->generateMIPS(dst, float_ret_reg, c, "double");
            dst << "swc1 " << float_ret_reg << "," <<  variable_memory_slot+4 << "($fp)" << std::endl;
            dst << "nop" << std::endl;
            dst << "swc1 " << float_ret_reg2 << "," <<  variable_memory_slot << "($fp)" << std::endl;
            c.FreeFloatRetRegister(c, float_ret_reg_number);
        }
    }
    virtual std::string whatAMI() const override
    {
        return "Variable Declare And Assign";
    }

    virtual std::vector<NodePtr> returnList() const override
    {
        
    };

    virtual void countDeclarations(Context &c) const override{
        c.declarations += 1; 
    } 
    
    virtual void FunctionCallCheck (Context &c) const override{
        assignment_expression->FunctionCallCheck(c);
    }

    virtual int getValue() const override{

    }
    virtual std::string getId() const override{

    }

};

///////////////////////////////////////////
///Below are all the types of assigning to variables..
//    : +=
//    : -=
//    : *=
//    : /= 
//    : %=
//    : +=   


// +=
class AddAssignStatement
    : public Node
{
private:
    std::string* identifier;
    NodePtr assignment_expression;
public:
    AddAssignStatement(std::string* _identifier, NodePtr _assignment_expression)
    {
        identifier = _identifier;
        assignment_expression = _assignment_expression;
    }
    virtual ~AddAssignStatement()
    {
        delete assignment_expression;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the add assign statement node"<<std::endl;
        assignment_expression->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {// e.g x += 2;
        int variable_memory_slot = c.GetUsedMemorySlot(c, *identifier);
        int ret_reg_number = c.FindRetRegister(c);
        std::string ret_reg = c.GetRetRegisterName(c, ret_reg_number);
        assignment_expression->generateMIPS(dst, ret_reg, c);
        int variable_register_number  = c.FindTempRegister(c);
        std::string variable_reg = c.GetTempRegisterName(c, variable_register_number);
        dst << "lw " << variable_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
        dst << "addu " << ret_reg << "," << variable_reg << "," <<ret_reg << std::endl;
        dst << "sw " << ret_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
        c.FreeRetRegister(c, ret_reg_number);
        c.FreeTempRegister(c, variable_register_number);
    }
    virtual std::string whatAMI() const override
    {
        return "Add Assign Statement";
    }

    virtual std::vector<NodePtr> returnList() const override
    {
        
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override{
        //do not do anything
    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{

    }
    virtual std::string getId() const override{

    }

};

// -=
class SubAssignStatement
    : public Node
{
private:
    std::string* identifier;
    NodePtr assignment_expression;
public:
    SubAssignStatement(std::string* _identifier, NodePtr _assignment_expression)
    {
        identifier = _identifier;
        assignment_expression = _assignment_expression;
    }
    virtual ~SubAssignStatement()
    {
        delete assignment_expression;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the sub assign statement node"<<std::endl;
        assignment_expression->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {// e.g x += 2;
        int variable_memory_slot = c.GetUsedMemorySlot(c, *identifier);
        int ret_reg_number = c.FindRetRegister(c);
        std::string ret_reg = c.GetRetRegisterName(c, ret_reg_number);
        assignment_expression->generateMIPS(dst, ret_reg, c);
        int variable_register_number  = c.FindTempRegister(c);
        std::string variable_reg = c.GetTempRegisterName(c, variable_register_number);
        dst << "lw " << variable_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
        dst << "subu " << ret_reg << "," << variable_reg << "," <<ret_reg << std::endl;
        dst << "sw " << ret_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
        c.FreeRetRegister(c, ret_reg_number);
        c.FreeTempRegister(c, variable_register_number);
    }
    virtual std::string whatAMI() const override
    {
        return "Sub Assign Statement";
    }

    virtual std::vector<NodePtr> returnList() const override
    {
        
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override{
        //do not do anything
    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{

    }
    virtual std::string getId() const override{

    }

};

// *=
class MulAssignStatement
    : public Node
{
private:
    std::string* identifier;
    NodePtr assignment_expression;
public:
    MulAssignStatement(std::string* _identifier, NodePtr _assignment_expression)
    {
        identifier = _identifier;
        assignment_expression = _assignment_expression;
    }
    virtual ~MulAssignStatement()
    {
        delete assignment_expression;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the mul assign statement node"<<std::endl;
        assignment_expression->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {// e.g x *= 2;
        int variable_memory_slot = c.GetUsedMemorySlot(c, *identifier);
        int ret_reg_number = c.FindRetRegister(c);
        std::string ret_reg = c.GetRetRegisterName(c, ret_reg_number);
        assignment_expression->generateMIPS(dst, ret_reg, c);
        int variable_register_number  = c.FindTempRegister(c);
        std::string variable_reg = c.GetTempRegisterName(c, variable_register_number);
        dst << "lw " << variable_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
        dst << "mult " << ret_reg << "," <<variable_reg << std::endl;
        dst << "mflo "  << ret_reg << std::endl;
        dst << "sw " << ret_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
        c.FreeRetRegister(c, ret_reg_number);
        c.FreeTempRegister(c, variable_register_number);
    }
    virtual std::string whatAMI() const override
    {
        return "Mul Assign Statement";
    }

    virtual std::vector<NodePtr> returnList() const override
    {
        
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override{
        //do not do anything
    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{

    }
    virtual std::string getId() const override{

    }

};

// /=
class DivAssignStatement
    : public Node
{
private:
    std::string* identifier;
    NodePtr assignment_expression;
public:
    DivAssignStatement(std::string* _identifier, NodePtr _assignment_expression)
    {
        identifier = _identifier;
        assignment_expression = _assignment_expression;
    }
    virtual ~DivAssignStatement()
    {
        delete assignment_expression;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the div assign statement node"<<std::endl;
        assignment_expression->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {// e.g x /= 2;
        int variable_memory_slot = c.GetUsedMemorySlot(c, *identifier);
        int ret_reg_number = c.FindRetRegister(c);
        std::string ret_reg = c.GetRetRegisterName(c, ret_reg_number);
        assignment_expression->generateMIPS(dst, ret_reg, c);
        int variable_register_number  = c.FindTempRegister(c);
        std::string variable_reg = c.GetTempRegisterName(c, variable_register_number);
        dst << "lw " << variable_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
        dst << "div "<<"$0"<<","<<variable_reg<<","<<ret_reg<<std::endl;
        dst << "mfhi "<<ret_reg<<std::endl;
        dst << "mflo "<<ret_reg<<std::endl;
        dst << "sw " << ret_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
        c.FreeRetRegister(c, ret_reg_number);
        c.FreeTempRegister(c, variable_register_number);
    }
    virtual std::string whatAMI() const override
    {
        return "Div Assign Statement";
    }

    virtual std::vector<NodePtr> returnList() const override
    {
        
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override{
        //do not do anything
    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{

    }
    virtual std::string getId() const override{

    }

};


// %=
class ModAssignStatement
    : public Node
{
private:
    std::string* identifier;
    NodePtr assignment_expression;
public:
    ModAssignStatement(std::string* _identifier, NodePtr _assignment_expression)
    {
        identifier = _identifier;
        assignment_expression = _assignment_expression;
    }
    virtual ~ModAssignStatement()
    {
        delete assignment_expression;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the div assign statement node"<<std::endl;
        assignment_expression->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {// e.g x += 2;
        int variable_memory_slot = c.GetUsedMemorySlot(c, *identifier);
        int ret_reg_number = c.FindRetRegister(c);
        std::string ret_reg = c.GetRetRegisterName(c, ret_reg_number);
        assignment_expression->generateMIPS(dst, ret_reg, c);
        int variable_register_number  = c.FindTempRegister(c);
        std::string variable_reg = c.GetTempRegisterName(c, variable_register_number);
        dst << "lw " << variable_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
        dst << "div "<<ret_reg<<","<<variable_reg<<","<<ret_reg<<std::endl;
        dst << "mfhi "<<ret_reg<<std::endl;
        dst << "sw " << ret_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
        c.FreeRetRegister(c, ret_reg_number);
        c.FreeTempRegister(c, variable_register_number);
    }
    virtual std::string whatAMI() const override
    {
        return "Div Assign Statement";
    }

    virtual std::vector<NodePtr> returnList() const override
    {
        
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override{
        //do not do anything
    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{

    }
    virtual std::string getId() const override{

    }

};


// <<=
class LeftAssignStatement
    : public Node
{
private:
    std::string* identifier;
    NodePtr assignment_expression;
public:
    LeftAssignStatement(std::string* _identifier, NodePtr _assignment_expression)
    {
        identifier = _identifier;
        assignment_expression = _assignment_expression;
    }
    virtual ~LeftAssignStatement()
    {
        delete assignment_expression;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the left assign statement node"<<std::endl;
        assignment_expression->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {// e.g x += 2;
        int variable_memory_slot = c.GetUsedMemorySlot(c, *identifier);
        int ret_reg_number = c.FindRetRegister(c);
        std::string ret_reg = c.GetRetRegisterName(c, ret_reg_number);
        assignment_expression->generateMIPS(dst, ret_reg, c);
        int variable_register_number  = c.FindTempRegister(c);
        std::string variable_reg = c.GetTempRegisterName(c, variable_register_number);
        dst << "lw " << variable_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
        dst << "sll "<<ret_reg<<","<<variable_reg<<","<<ret_reg<<std::endl;
        dst << "sw " << ret_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
        c.FreeRetRegister(c, ret_reg_number);
        c.FreeTempRegister(c, variable_register_number);
    }
    virtual std::string whatAMI() const override
    {
        return "Left Assign Statement";
    }

    virtual std::vector<NodePtr> returnList() const override
    {
        
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override{
        //do not do anything
    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }
    
    virtual int getValue() const override{

    }
    virtual std::string getId() const override{

    }
};

// >>=
class RightAssignStatement
    : public Node
{
private:
    std::string* identifier;
    NodePtr assignment_expression;
public:
    RightAssignStatement(std::string* _identifier, NodePtr _assignment_expression)
    {
        identifier = _identifier;
        assignment_expression = _assignment_expression;
    }
    virtual ~RightAssignStatement()
    {
        delete assignment_expression;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the right assign statement node"<<std::endl;
        assignment_expression->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {// e.g x += 2;
        int variable_memory_slot = c.GetUsedMemorySlot(c, *identifier);
        int ret_reg_number = c.FindRetRegister(c);
        std::string ret_reg = c.GetRetRegisterName(c, ret_reg_number);
        assignment_expression->generateMIPS(dst, ret_reg, c);
        int variable_register_number  = c.FindTempRegister(c);
        std::string variable_reg = c.GetTempRegisterName(c, variable_register_number);
        dst << "lw " << variable_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
        dst << "sra "<<ret_reg<<","<<variable_reg<<","<<ret_reg<<std::endl;
        dst << "sw " << ret_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
        c.FreeRetRegister(c, ret_reg_number);
        c.FreeTempRegister(c, variable_register_number);
    }
    virtual std::string whatAMI() const override
    {
        return "Right Assign Statement";
    }

    virtual std::vector<NodePtr> returnList() const override
    {
        
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override{
        //do not do anything
    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{

    }
    virtual std::string getId() const override{

    }

};

// &=
class AndAssignStatement
    : public Node
{
private:
    std::string* identifier;
    NodePtr assignment_expression;
public:
    AndAssignStatement(std::string* _identifier, NodePtr _assignment_expression)
    {
        identifier = _identifier;
        assignment_expression = _assignment_expression;
    }
    virtual ~AndAssignStatement()
    {
        delete assignment_expression;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the AND assign statement node"<<std::endl;
        assignment_expression->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {// e.g x += 2;
        int variable_memory_slot = c.GetUsedMemorySlot(c, *identifier);
        int ret_reg_number = c.FindRetRegister(c);
        std::string ret_reg = c.GetRetRegisterName(c, ret_reg_number);
        assignment_expression->generateMIPS(dst, ret_reg, c);
        int variable_register_number  = c.FindTempRegister(c);
        std::string variable_reg = c.GetTempRegisterName(c, variable_register_number);
        dst << "lw " << variable_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
        dst << "and "<<ret_reg<<","<<variable_reg<<","<<ret_reg<<std::endl;
        dst << "sw " << ret_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
        c.FreeRetRegister(c, ret_reg_number);
        c.FreeTempRegister(c, variable_register_number);
    }
    virtual std::string whatAMI() const override
    {
        return "AND Assign Statement";
    }

    virtual std::vector<NodePtr> returnList() const override
    {
        
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override{
        //do not do anything
    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{

    }
    virtual std::string getId() const override{

    }

};

// |=
class OrAssignStatement
    : public Node
{
private:
    std::string* identifier;
    NodePtr assignment_expression;
public:
    OrAssignStatement(std::string* _identifier, NodePtr _assignment_expression)
    {
        identifier = _identifier;
        assignment_expression = _assignment_expression;
    }
    virtual ~OrAssignStatement()
    {
        delete assignment_expression;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the OR assign statement node"<<std::endl;
        assignment_expression->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {// e.g x += 2;
        int variable_memory_slot = c.GetUsedMemorySlot(c, *identifier);
        int ret_reg_number = c.FindRetRegister(c);
        std::string ret_reg = c.GetRetRegisterName(c, ret_reg_number);
        assignment_expression->generateMIPS(dst, ret_reg, c);
        int variable_register_number  = c.FindTempRegister(c);
        std::string variable_reg = c.GetTempRegisterName(c, variable_register_number);
        dst << "lw " << variable_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
        dst << "or "<<ret_reg<<","<<variable_reg<<","<<ret_reg<<std::endl;
        dst << "sw " << ret_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
        c.FreeRetRegister(c, ret_reg_number);
        c.FreeTempRegister(c, variable_register_number);
    }
    virtual std::string whatAMI() const override
    {
        return "OR Assign Statement";
    }

    virtual std::vector<NodePtr> returnList() const override
    {
        
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override{
        //do not do anything
    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{

    }
    virtual std::string getId() const override{

    }

};

// ^=
class XorAssignStatement
    : public Node
{
private:
    std::string* identifier;
    NodePtr assignment_expression;
public:
    XorAssignStatement(std::string* _identifier, NodePtr _assignment_expression)
    {
        identifier = _identifier;
        assignment_expression = _assignment_expression;
    }
    virtual ~XorAssignStatement()
    {
        delete assignment_expression;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the XOR assign statement node"<<std::endl;
        assignment_expression->visualise();
    }
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {// e.g x += 2;
        int variable_memory_slot = c.GetUsedMemorySlot(c, *identifier);
        int ret_reg_number = c.FindRetRegister(c);
        std::string ret_reg = c.GetRetRegisterName(c, ret_reg_number);
        assignment_expression->generateMIPS(dst, ret_reg, c);
        int variable_register_number  = c.FindTempRegister(c);
        std::string variable_reg = c.GetTempRegisterName(c, variable_register_number);
        dst << "lw " << variable_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
        dst << "xor "<<ret_reg<<","<<variable_reg<<","<<ret_reg<<std::endl;
        dst << "sw " << ret_reg << "," <<  variable_memory_slot << "($fp)" << std::endl;
        c.FreeRetRegister(c, ret_reg_number);
        c.FreeTempRegister(c, variable_register_number);
    }
    virtual std::string whatAMI() const override
    {
        return "XOR Assign Statement";
    }

    virtual std::vector<NodePtr> returnList() const override
    {
        
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override{
        //do not do anything
    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{

    }
    virtual std::string getId() const override{

    }

};

#endif
