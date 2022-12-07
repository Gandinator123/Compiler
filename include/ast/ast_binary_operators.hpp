#ifndef ast_binary_operators_hpp
#define ast_binary_operators_hpp
#include "ast_base.hpp"

class AddOperator
    : public Node
{
private:
    NodePtr left;
    NodePtr right;
public:

    AddOperator(NodePtr _left, NodePtr _right){
        left = _left;
        right = _right;
    }

    virtual ~AddOperator(){
        delete left;
        delete right;
    }

    virtual void visualise() const override
    {   
        std::cout<<"in the add operator node"<<std::endl;
        left->visualise();
        right->visualise(); 
    }
    
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        if(type=="int"){
            int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
            std::string call_left_register, call_right_register, left_register, right_register;
            if(left->whatAMI()=="Function Call"){
                call_left_register_index = c.FindRetRegister(c);
                call_left_register = c.GetRetRegisterName(c, call_left_register_index);
                c.FreeRetRegister(c, call_left_register_index);
                left->generateMIPS(dst, call_left_register, c);
                left_register_index = c.FindTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetTempRegisterName(c, left_register_index);
                dst << "move " << left_register << "," << call_left_register << std::endl; 
            }
            else{
                left_register_index = c.FindTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetTempRegisterName(c, left_register_index);
                left->generateMIPS(dst, left_register, c);
            }
            if(right->whatAMI()=="Function Call"){
                call_right_register_index = c.FindRetRegister(c);
                call_right_register = c.GetRetRegisterName(c, call_right_register_index);
                c.FreeRetRegister(c, call_right_register_index);
                right->generateMIPS(dst, call_right_register, c);
                right_register_index = c.FindTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetTempRegisterName(c, right_register_index);
                dst << "move " << right_register << "," << call_right_register << std::endl; 
            }
            else{
                right_register_index = c.FindTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetTempRegisterName(c, right_register_index);
                right->generateMIPS(dst, right_register, c);
            }
            right->generateMIPS(dst, right_register, c);
            if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
                int temp_index = c.FindTempRegister(c);
                std::string temp = c.GetTempRegisterName(c, temp_index);
                dst << "li " << temp << ",2" << std::endl;
                dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
                c.FreeTempRegister(c, temp_index);
            }
            if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
                int temp_index = c.FindTempRegister(c);
                std::string temp = c.GetTempRegisterName(c, temp_index);
                dst << "li " << temp << ",2" << std::endl;
                dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
                c.FreeTempRegister(c, temp_index);
            }
            dst << "addu "<<destReg<<","<<left_register<<","<<right_register<<std::endl;
            c.FreeTempRegister(c, kill_right_register_index);
            c.FreeTempRegister(c, kill_left_register_index);
        }
        else if(type=="float"){
            int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
            std::string call_left_register, call_right_register, left_register, right_register;
            if(left->whatAMI()=="Function Call"){
                call_left_register_index = c.FindFloatRetRegister(c);
                call_left_register = c.GetFloatRetRegisterName(c, call_left_register_index);
                c.FreeFloatRetRegister(c, call_left_register_index);
                left->generateMIPS(dst, call_left_register, c, "float");
                left_register_index = c.FindFloatTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetFloatTempRegisterName(c, left_register_index);
                dst << "move " << left_register << "," << call_left_register << std::endl; 
            }
            else{
                left_register_index = c.FindFloatTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetFloatTempRegisterName(c, left_register_index);
                left->generateMIPS(dst, left_register, c,"float");
            }
            if(right->whatAMI()=="Function Call"){
                call_right_register_index = c.FindFloatRetRegister(c);
                call_right_register = c.GetFloatRetRegisterName(c, call_right_register_index);
                c.FreeFloatRetRegister(c, call_right_register_index);
                right->generateMIPS(dst, call_right_register, c, "float");
                right_register_index = c.FindFloatTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetFloatTempRegisterName(c, right_register_index);
                dst << "move " << right_register << "," << call_right_register << std::endl; 
            }
            else{
                right_register_index = c.FindFloatTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetFloatTempRegisterName(c, right_register_index);
                right->generateMIPS(dst, right_register, c,"float");
            }
            if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
                int temp_index = c.FindFloatTempRegister(c);
                std::string temp = c.GetFloatTempRegisterName(c, temp_index);
                dst << "li " << temp << ",2" << std::endl;
                dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
                c.FreeFloatTempRegister(c, temp_index);
            }
            if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
                int temp_index = c.FindFloatTempRegister(c);
                std::string temp = c.GetFloatTempRegisterName(c, temp_index);
                dst << "li " << temp << ",2" << std::endl;
                dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
                c.FreeFloatTempRegister(c, temp_index);
            }
            dst << "add.s "<<destReg<<","<<left_register<<","<<right_register<<std::endl;
            c.FreeFloatTempRegister(c, kill_right_register_index);
            c.FreeFloatTempRegister(c, kill_left_register_index);
        }
        else if(type=="double"){
            int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
            std::string call_left_register, call_right_register, left_register, right_register;
            if(left->whatAMI()=="Function Call"){
                call_left_register_index = c.FindFloatRetRegister(c);
                call_left_register = c.GetFloatRetRegisterName(c, call_left_register_index);
                c.FreeFloatRetRegister(c, call_left_register_index);
                left->generateMIPS(dst, call_left_register, c, "double");
                left_register_index = c.FindFloatTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetFloatTempRegisterName(c, left_register_index);
                dst << "move " << left_register << "," << call_left_register << std::endl; 
            }
            else{
                left_register_index = c.FindFloatTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetFloatTempRegisterName(c, left_register_index);
                left->generateMIPS(dst, left_register, c,"double");
            }
            if(right->whatAMI()=="Function Call"){
                call_right_register_index = c.FindFloatRetRegister(c);
                call_right_register = c.GetFloatRetRegisterName(c, call_right_register_index);
                c.FreeFloatRetRegister(c, call_right_register_index);
                right->generateMIPS(dst, call_right_register, c, "double");
                right_register_index = c.FindFloatTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetFloatTempRegisterName(c, right_register_index);
                dst << "move " << right_register << "," << call_right_register << std::endl; 
            }
            else{
                right_register_index = c.FindFloatTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetFloatTempRegisterName(c, right_register_index);
                right->generateMIPS(dst, right_register, c,"double");
            }
                dst << "add.d " << destReg << "," << left_register << "," << right_register << std::endl;
                c.FreeFloatTempRegister(c, kill_right_register_index);
                c.FreeFloatTempRegister(c, kill_left_register_index);
        }
        
    }

    virtual std::string whatAMI() const override
    {
        return "Add Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
        
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {

    }

    virtual void FunctionCallCheck (Context &c) const override{
        std::cout<<"doing add function call check"<<std::endl;
        left->FunctionCallCheck(c);
        right->FunctionCallCheck(c);
    }

    virtual int getValue() const override{
        return left->getValue() + right->getValue();
    }
    virtual std::string getId() const override{

    }
};

class SubOperator
    : public Node
{
private:
    NodePtr left;
    NodePtr right;
public:
    SubOperator(NodePtr _left, NodePtr _right){
        left = _left;
        right = _right;
    }

    virtual ~SubOperator(){
        delete left;
        delete right;
    }

    virtual void visualise() const override
    {   
        std::cout<<"in the sub operator node"<<std::endl;
        left->visualise();
        right->visualise(); 
    }
    
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        if(type=="int"){
            int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
            std::string call_left_register, call_right_register, left_register, right_register;
            if(left->whatAMI()=="Function Call"){
                call_left_register_index = c.FindRetRegister(c);
                call_left_register = c.GetRetRegisterName(c, call_left_register_index);
                c.FreeRetRegister(c, call_left_register_index);
                left->generateMIPS(dst, call_left_register, c);
                left_register_index = c.FindTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetTempRegisterName(c, left_register_index);
                dst << "move " << left_register << "," << call_left_register << std::endl; 
            }
            else{
                left_register_index = c.FindTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetTempRegisterName(c, left_register_index);
                left->generateMIPS(dst, left_register, c);
            }
            if(right->whatAMI()=="Function Call"){
                call_right_register_index = c.FindRetRegister(c);
                call_right_register = c.GetRetRegisterName(c, call_right_register_index);
                c.FreeRetRegister(c, call_right_register_index);
                right->generateMIPS(dst, call_right_register, c);
                right_register_index = c.FindTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetTempRegisterName(c, right_register_index);
                dst << "move " << right_register << "," << call_right_register << std::endl; 
            }
            else{
                right_register_index = c.FindTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetTempRegisterName(c, right_register_index);
                right->generateMIPS(dst, right_register, c);
            }
            right->generateMIPS(dst, right_register, c);
            if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
                int temp_index = c.FindTempRegister(c);
                std::string temp = c.GetTempRegisterName(c, temp_index);
                dst << "li " << temp << ",2" << std::endl;
                dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
                c.FreeTempRegister(c, temp_index);
            }
            if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
                int temp_index = c.FindTempRegister(c);
                std::string temp = c.GetTempRegisterName(c, temp_index);
                dst << "li " << temp << ",2" << std::endl;
                dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
                c.FreeTempRegister(c, temp_index);
            }
            dst << "subu "<<destReg<<","<<left_register<<","<<right_register<<std::endl;
            c.FreeTempRegister(c, kill_right_register_index);
            c.FreeTempRegister(c, kill_left_register_index);
        }
        else if(type=="float"){
            int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
            std::string call_left_register, call_right_register, left_register, right_register;
            if(left->whatAMI()=="Function Call"){
                call_left_register_index = c.FindFloatRetRegister(c);
                call_left_register = c.GetFloatRetRegisterName(c, call_left_register_index);
                c.FreeFloatRetRegister(c, call_left_register_index);
                left->generateMIPS(dst, call_left_register, c, "float");
                left_register_index = c.FindFloatTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetFloatTempRegisterName(c, left_register_index);
                dst << "move " << left_register << "," << call_left_register << std::endl; 
            }
            else{
                left_register_index = c.FindFloatTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetFloatTempRegisterName(c, left_register_index);
                left->generateMIPS(dst, left_register, c,"float");
            }
            if(right->whatAMI()=="Function Call"){
                call_right_register_index = c.FindFloatRetRegister(c);
                call_right_register = c.GetFloatRetRegisterName(c, call_right_register_index);
                c.FreeFloatRetRegister(c, call_right_register_index);
                right->generateMIPS(dst, call_right_register, c, "float");
                right_register_index = c.FindFloatTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetFloatTempRegisterName(c, right_register_index);
                dst << "move " << right_register << "," << call_right_register << std::endl; 
            }
            else{
                right_register_index = c.FindFloatTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetFloatTempRegisterName(c, right_register_index);
                right->generateMIPS(dst, right_register, c,"float");
            }
            if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
                int temp_index = c.FindFloatTempRegister(c);
                std::string temp = c.GetFloatTempRegisterName(c, temp_index);
                dst << "li " << temp << ",2" << std::endl;
                dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
                c.FreeFloatTempRegister(c, temp_index);
            }
            if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
                int temp_index = c.FindFloatTempRegister(c);
                std::string temp = c.GetFloatTempRegisterName(c, temp_index);
                dst << "li " << temp << ",2" << std::endl;
                dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
                c.FreeFloatTempRegister(c, temp_index);
            }
            dst << "sub.s "<<destReg<<","<<left_register<<","<<right_register<<std::endl;
            c.FreeFloatTempRegister(c, kill_right_register_index);
            c.FreeFloatTempRegister(c, kill_left_register_index);
        }
        else if(type=="double"){
            int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
            std::string call_left_register, call_right_register, left_register, right_register;
            if(left->whatAMI()=="Function Call"){
                call_left_register_index = c.FindFloatRetRegister(c);
                call_left_register = c.GetFloatRetRegisterName(c, call_left_register_index);
                c.FreeFloatRetRegister(c, call_left_register_index);
                left->generateMIPS(dst, call_left_register, c, "double");
                left_register_index = c.FindFloatTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetFloatTempRegisterName(c, left_register_index);
                dst << "move " << left_register << "," << call_left_register << std::endl; 
            }
            else{
                left_register_index = c.FindFloatTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetFloatTempRegisterName(c, left_register_index);
                left->generateMIPS(dst, left_register, c,"double");
            }
            if(right->whatAMI()=="Function Call"){
                call_right_register_index = c.FindFloatRetRegister(c);
                call_right_register = c.GetFloatRetRegisterName(c, call_right_register_index);
                c.FreeFloatRetRegister(c, call_right_register_index);
                right->generateMIPS(dst, call_right_register, c, "double");
                right_register_index = c.FindFloatTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetFloatTempRegisterName(c, right_register_index);
                dst << "move " << right_register << "," << call_right_register << std::endl; 
            }
            else{
                right_register_index = c.FindFloatTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetFloatTempRegisterName(c, right_register_index);
                right->generateMIPS(dst, right_register, c,"double");
            }
                dst << "sub.d " << destReg << "," << left_register << "," << right_register << std::endl;
                c.FreeFloatTempRegister(c, kill_right_register_index);
                c.FreeFloatTempRegister(c, kill_left_register_index);
        }
    }

    virtual std::string whatAMI() const override
    {
        return "Sub Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
        
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {
        
    }

    virtual void FunctionCallCheck (Context &c) const override{
        left->FunctionCallCheck(c);
        right->FunctionCallCheck(c);
    }

    virtual int getValue() const override{
         return left->getValue() - right->getValue();
    }
    virtual std::string getId() const override{

    }
};




class DivOperator
    : public Node
{
private:
    NodePtr left;
    NodePtr right;
public:
    DivOperator(NodePtr _left, NodePtr _right){
        left = _left;
        right = _right;
    }

    virtual ~DivOperator(){
        delete left;
        delete right;
    }
    

    virtual void visualise() const override
    {   
        std::cout<<"in the div operator node"<<std::endl;
        left->visualise();
        right->visualise(); 
    }
    
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        if(type=="int"){
            int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
            std::string call_left_register, call_right_register, left_register, right_register;
            if(left->whatAMI()=="Function Call"){
                call_left_register_index = c.FindRetRegister(c);
                call_left_register = c.GetRetRegisterName(c, call_left_register_index);
                c.FreeRetRegister(c, call_left_register_index);
                left->generateMIPS(dst, call_left_register, c);
                left_register_index = c.FindTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetTempRegisterName(c, left_register_index);
                dst << "move " << left_register << "," << call_left_register << std::endl; 
            }
            else{
                left_register_index = c.FindTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetTempRegisterName(c, left_register_index);
                left->generateMIPS(dst, left_register, c);
            }
            if(right->whatAMI()=="Function Call"){
                call_right_register_index = c.FindRetRegister(c);
                call_right_register = c.GetRetRegisterName(c, call_right_register_index);
                c.FreeRetRegister(c, call_right_register_index);
                right->generateMIPS(dst, call_right_register, c);
                right_register_index = c.FindTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetTempRegisterName(c, right_register_index);
                dst << "move " << right_register << "," << call_right_register << std::endl; 
            }
            else{
                right_register_index = c.FindTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetTempRegisterName(c, right_register_index);
                right->generateMIPS(dst, right_register, c);
            }
            right->generateMIPS(dst, right_register, c);
            if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
                int temp_index = c.FindTempRegister(c);
                std::string temp = c.GetTempRegisterName(c, temp_index);
                dst << "li " << temp << ",2" << std::endl;
                dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
                c.FreeTempRegister(c, temp_index);
            }
            if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
                int temp_index = c.FindTempRegister(c);
                std::string temp = c.GetTempRegisterName(c, temp_index);
                dst << "li " << temp << ",2" << std::endl;
                dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
                c.FreeTempRegister(c, temp_index);
            }
            dst << "div "<<destReg<<","<<left_register<<","<<right_register<<std::endl;
            dst << "nop" << std::endl;
            dst << "mfhi "<<destReg<<std::endl;
            dst << "nop" << std::endl;
            dst << "mflo "<<destReg<<std::endl;
            dst << "nop" << std::endl;
            c.FreeTempRegister(c, kill_right_register_index);
            c.FreeTempRegister(c, kill_left_register_index);
        }
        else if(type=="float"){
            int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
            std::string call_left_register, call_right_register, left_register, right_register;
            if(left->whatAMI()=="Function Call"){
                call_left_register_index = c.FindFloatRetRegister(c);
                call_left_register = c.GetFloatRetRegisterName(c, call_left_register_index);
                c.FreeFloatRetRegister(c, call_left_register_index);
                left->generateMIPS(dst, call_left_register, c, "float");
                left_register_index = c.FindFloatTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetFloatTempRegisterName(c, left_register_index);
                dst << "move " << left_register << "," << call_left_register << std::endl; 
            }
            else{
                left_register_index = c.FindFloatTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetFloatTempRegisterName(c, left_register_index);
                left->generateMIPS(dst, left_register, c,"float");
            }
            if(right->whatAMI()=="Function Call"){
                call_right_register_index = c.FindFloatRetRegister(c);
                call_right_register = c.GetFloatRetRegisterName(c, call_right_register_index);
                c.FreeFloatRetRegister(c, call_right_register_index);
                right->generateMIPS(dst, call_right_register, c, "float");
                right_register_index = c.FindFloatTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetFloatTempRegisterName(c, right_register_index);
                dst << "move " << right_register << "," << call_right_register << std::endl; 
            }
            else{
                right_register_index = c.FindFloatTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetFloatTempRegisterName(c, right_register_index);
                right->generateMIPS(dst, right_register, c,"float");
            }
            if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
                int temp_index = c.FindFloatTempRegister(c);
                std::string temp = c.GetFloatTempRegisterName(c, temp_index);
                dst << "li " << temp << ",2" << std::endl;
                dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
                c.FreeFloatTempRegister(c, temp_index);
            }
            if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
                int temp_index = c.FindFloatTempRegister(c);
                std::string temp = c.GetFloatTempRegisterName(c, temp_index);
                dst << "li " << temp << ",2" << std::endl;
                dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
                c.FreeFloatTempRegister(c, temp_index);
            }
            dst << "div.s "<<destReg<<","<<left_register<<","<<right_register<<std::endl;
            c.FreeFloatTempRegister(c, kill_right_register_index);
            c.FreeFloatTempRegister(c, kill_left_register_index);
        }
        else if(type=="double"){
            int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
            std::string call_left_register, call_right_register, left_register, right_register;
            if(left->whatAMI()=="Function Call"){
                call_left_register_index = c.FindFloatRetRegister(c);
                call_left_register = c.GetFloatRetRegisterName(c, call_left_register_index);
                c.FreeFloatRetRegister(c, call_left_register_index);
                left->generateMIPS(dst, call_left_register, c, "double");
                left_register_index = c.FindFloatTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetFloatTempRegisterName(c, left_register_index);
                dst << "move " << left_register << "," << call_left_register << std::endl; 
            }
            else{
                left_register_index = c.FindFloatTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetFloatTempRegisterName(c, left_register_index);
                left->generateMIPS(dst, left_register, c,"double");
            }
            if(right->whatAMI()=="Function Call"){
                call_right_register_index = c.FindFloatRetRegister(c);
                call_right_register = c.GetFloatRetRegisterName(c, call_right_register_index);
                c.FreeFloatRetRegister(c, call_right_register_index);
                right->generateMIPS(dst, call_right_register, c, "double");
                right_register_index = c.FindFloatTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetFloatTempRegisterName(c, right_register_index);
                dst << "move " << right_register << "," << call_right_register << std::endl; 
            }
            else{
                right_register_index = c.FindFloatTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetFloatTempRegisterName(c, right_register_index);
                right->generateMIPS(dst, right_register, c,"double");
            }
                dst << "div.d " << destReg << "," << left_register << "," << right_register << std::endl;
                c.FreeFloatTempRegister(c, kill_right_register_index);
                c.FreeFloatTempRegister(c, kill_left_register_index);
        }
        
    }

    virtual std::string whatAMI() const override
    {
        return "Div Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
        
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {
        
    }

    virtual void FunctionCallCheck (Context &c) const override{
        left->FunctionCallCheck(c);
        right->FunctionCallCheck(c);
    }

    virtual int getValue() const override{
         return left->getValue() / right->getValue();
    }
    virtual std::string getId() const override{

    }
};

class MulOperator
    : public Node
{
private:
    NodePtr left;
    NodePtr right;
public:
    MulOperator(NodePtr _left, NodePtr _right)
    {
        left = _left;
        right = _right;
    }
    virtual ~MulOperator(){
        delete left;
        delete right;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the mul operator node"<<std::endl;
        left->visualise();
        right->visualise(); 
    }
    
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        
        if(type=="int"){
            int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
            std::string call_left_register, call_right_register, left_register, right_register;
            if(left->whatAMI()=="Function Call"){
                call_left_register_index = c.FindRetRegister(c);
                call_left_register = c.GetRetRegisterName(c, call_left_register_index);
                c.FreeRetRegister(c, call_left_register_index);
                left->generateMIPS(dst, call_left_register, c);
                left_register_index = c.FindTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetTempRegisterName(c, left_register_index);
                dst << "move " << left_register << "," << call_left_register << std::endl; 
            }
            else{
                left_register_index = c.FindTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetTempRegisterName(c, left_register_index);
                left->generateMIPS(dst, left_register, c);
            }
            if(right->whatAMI()=="Function Call"){
                call_right_register_index = c.FindRetRegister(c);
                call_right_register = c.GetRetRegisterName(c, call_right_register_index);
                c.FreeRetRegister(c, call_right_register_index);
                right->generateMIPS(dst, call_right_register, c);
                right_register_index = c.FindTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetTempRegisterName(c, right_register_index);
                dst << "move " << right_register << "," << call_right_register << std::endl; 
            }
            else{
                right_register_index = c.FindTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetTempRegisterName(c, right_register_index);
                right->generateMIPS(dst, right_register, c);
            }
            right->generateMIPS(dst, right_register, c);
            if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
                int temp_index = c.FindTempRegister(c);
                std::string temp = c.GetTempRegisterName(c, temp_index);
                dst << "li " << temp << ",2" << std::endl;
                dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
                c.FreeTempRegister(c, temp_index);
            }
            if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
                int temp_index = c.FindTempRegister(c);
                std::string temp = c.GetTempRegisterName(c, temp_index);
                dst << "li " << temp << ",2" << std::endl;
                dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
                c.FreeTempRegister(c, temp_index);
            }
            dst << "mult "<<left_register<<","<<right_register<<std::endl;
            dst << "nop" << std::endl;
            dst << "mflo "<<destReg<<std::endl;
            dst << "nop" << std::endl;
            c.FreeTempRegister(c, kill_right_register_index);
            c.FreeTempRegister(c, kill_left_register_index);
        }
        else if(type=="float"){
            int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
            std::string call_left_register, call_right_register, left_register, right_register;
            if(left->whatAMI()=="Function Call"){
                call_left_register_index = c.FindFloatRetRegister(c);
                call_left_register = c.GetFloatRetRegisterName(c, call_left_register_index);
                c.FreeFloatRetRegister(c, call_left_register_index);
                left->generateMIPS(dst, call_left_register, c, "float");
                left_register_index = c.FindFloatTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetFloatTempRegisterName(c, left_register_index);
                dst << "move " << left_register << "," << call_left_register << std::endl; 
            }
            else{
                left_register_index = c.FindFloatTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetFloatTempRegisterName(c, left_register_index);
                left->generateMIPS(dst, left_register, c,"float");
            }
            if(right->whatAMI()=="Function Call"){
                call_right_register_index = c.FindFloatRetRegister(c);
                call_right_register = c.GetFloatRetRegisterName(c, call_right_register_index);
                c.FreeFloatRetRegister(c, call_right_register_index);
                right->generateMIPS(dst, call_right_register, c, "float");
                right_register_index = c.FindFloatTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetFloatTempRegisterName(c, right_register_index);
                dst << "move " << right_register << "," << call_right_register << std::endl; 
            }
            else{
                right_register_index = c.FindFloatTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetFloatTempRegisterName(c, right_register_index);
                right->generateMIPS(dst, right_register, c,"float");
            }
            if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
                int temp_index = c.FindFloatTempRegister(c);
                std::string temp = c.GetFloatTempRegisterName(c, temp_index);
                dst << "li " << temp << ",2" << std::endl;
                dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
                c.FreeFloatTempRegister(c, temp_index);
            }
            if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
                int temp_index = c.FindFloatTempRegister(c);
                std::string temp = c.GetFloatTempRegisterName(c, temp_index);
                dst << "li " << temp << ",2" << std::endl;
                dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
                c.FreeFloatTempRegister(c, temp_index);
            }
            dst << "mul.s "<<destReg<<","<<left_register<<","<<right_register<<std::endl;
            c.FreeFloatTempRegister(c, kill_right_register_index);
            c.FreeFloatTempRegister(c, kill_left_register_index);
        }
        else if(type=="double"){
            int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
            std::string call_left_register, call_right_register, left_register, right_register;
            if(left->whatAMI()=="Function Call"){
                call_left_register_index = c.FindFloatRetRegister(c);
                call_left_register = c.GetFloatRetRegisterName(c, call_left_register_index);
                c.FreeFloatRetRegister(c, call_left_register_index);
                left->generateMIPS(dst, call_left_register, c, "double");
                left_register_index = c.FindFloatTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetFloatTempRegisterName(c, left_register_index);
                dst << "move " << left_register << "," << call_left_register << std::endl; 
            }
            else{
                left_register_index = c.FindFloatTempRegister(c);
                kill_left_register_index = left_register_index;
                left_register = c.GetFloatTempRegisterName(c, left_register_index);
                left->generateMIPS(dst, left_register, c,"double");
            }
            if(right->whatAMI()=="Function Call"){
                call_right_register_index = c.FindFloatRetRegister(c);
                call_right_register = c.GetFloatRetRegisterName(c, call_right_register_index);
                c.FreeFloatRetRegister(c, call_right_register_index);
                right->generateMIPS(dst, call_right_register, c, "double");
                right_register_index = c.FindFloatTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetFloatTempRegisterName(c, right_register_index);
                dst << "move " << right_register << "," << call_right_register << std::endl; 
            }
            else{
                right_register_index = c.FindFloatTempRegister(c);
                kill_right_register_index = right_register_index;
                right_register = c.GetFloatTempRegisterName(c, right_register_index);
                right->generateMIPS(dst, right_register, c,"double");
            }
                dst << "mul.d " << destReg << "," << left_register << "," << right_register << std::endl;
                c.FreeFloatTempRegister(c, kill_right_register_index);
                c.FreeFloatTempRegister(c, kill_left_register_index);
        }
    
    }

    virtual std::string whatAMI() const override
    {
        return "Mul Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
        
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {
        
    }

    virtual void FunctionCallCheck (Context &c) const override{
        left->FunctionCallCheck(c);
        right->FunctionCallCheck(c);
    }

    virtual int getValue() const override{
         return left->getValue() * right->getValue();
    }
    virtual std::string getId() const override{

    }
};

class ModOperator
    : public Node
{
private:
    NodePtr left;
    NodePtr right;
public:
    ModOperator(NodePtr _left, NodePtr _right)
    {
        left = _left;
        right = _right;
    }
    virtual ~ModOperator(){
        delete left;
        delete right;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the modulus operator node"<<std::endl;
        left->visualise();
        right->visualise(); 
    }
    
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
        std::string call_left_register, call_right_register, left_register, right_register;
        if(left->whatAMI()=="Function Call"){
            call_left_register_index = c.FindRetRegister(c);
            call_left_register = c.GetRetRegisterName(c, call_left_register_index);
            c.FreeRetRegister(c, call_left_register_index);
            left->generateMIPS(dst, call_left_register, c);
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            dst << "move " << left_register << "," << call_left_register << std::endl; 
            
        }
        else{
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            left->generateMIPS(dst, left_register, c);
        }
        if(right->whatAMI()=="Function Call"){
            call_right_register_index = c.FindRetRegister(c);
            call_right_register = c.GetRetRegisterName(c, call_right_register_index);
            c.FreeRetRegister(c, call_right_register_index);
            right->generateMIPS(dst, call_right_register, c);
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            dst << "move " << right_register << "," << call_right_register << std::endl; 
    
        }
        else{
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            right->generateMIPS(dst, right_register, c);
        }
        right->generateMIPS(dst, right_register, c);
        if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        dst << "div "<<destReg<<","<<left_register<<","<<right_register<<std::endl;
        dst << "mfhi " << destReg << std::endl;
        //cannnot do modulus on non integer values...
        c.FreeTempRegister(c, left_register_index);
        c.FreeTempRegister(c, right_register_index);
    }

    virtual std::string whatAMI() const override
    {
        return "Modulus Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {
        
    }

    virtual void FunctionCallCheck (Context &c) const override{
        left->FunctionCallCheck(c);
        right->FunctionCallCheck(c);
    }

    virtual int getValue() const override{
         return left->getValue() % right->getValue();
    }
    virtual std::string getId() const override{

    }
};


////////////////////////////////
// Defines classes for bitwise operator classes:
//    - <<: 
//    - >>: 
//    - &:
//    - |:


// << (bitwise)

class LeftShiftOperator
    : public Node
{
private:
    NodePtr left;
    NodePtr right;
public:
    LeftShiftOperator(NodePtr _left, NodePtr _right)
    {
        left = _left;
        right = _right;
    }
    virtual ~LeftShiftOperator(){
        delete left;
        delete right;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the left shift operator node"<<std::endl;
        left->visualise();
        right->visualise(); 
    }
    
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
        std::string call_left_register, call_right_register, left_register, right_register;
        if(left->whatAMI()=="Function Call"){
            call_left_register_index = c.FindRetRegister(c);
            call_left_register = c.GetRetRegisterName(c, call_left_register_index);
            c.FreeRetRegister(c, call_left_register_index);
            left->generateMIPS(dst, call_left_register, c);
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            dst << "move " << left_register << "," << call_left_register << std::endl; 
            
        }
        else{
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            left->generateMIPS(dst, left_register, c);
        }
        if(right->whatAMI()=="Function Call"){
            call_right_register_index = c.FindRetRegister(c);
            call_right_register = c.GetRetRegisterName(c, call_right_register_index);
            c.FreeRetRegister(c, call_right_register_index);
            right->generateMIPS(dst, call_right_register, c);
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            dst << "move " << right_register << "," << call_right_register << std::endl; 
    
        }
        else{
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            right->generateMIPS(dst, right_register, c);
        }
        right->generateMIPS(dst, right_register, c);
        if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        //cannnot do modulus on non integer values...
        dst << "sllv "<<destReg<<","<<left_register<<","<<right_register<<std::endl;
        c.FreeTempRegister(c, left_register_index);
        c.FreeTempRegister(c, right_register_index);
    }

    virtual std::string whatAMI() const override
    {
        return "Left Shift Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {
        
    }

    virtual void FunctionCallCheck (Context &c) const override{
        left->FunctionCallCheck(c);
        right->FunctionCallCheck(c);
    }

    virtual int getValue() const override{
        return left->getValue() << right->getValue();
    }
    virtual std::string getId() const override{

    }
};

// >> (bitwise)
class RightShiftOperator
    : public Node
{
private:
    NodePtr left;
    NodePtr right;
public:
    RightShiftOperator(NodePtr _left, NodePtr _right)
    {
        left = _left;
        right = _right;
    }
    virtual ~RightShiftOperator(){
        delete left;
        delete right;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the shift right operator node"<<std::endl;
        left->visualise();
        right->visualise(); 
    }
    
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
        std::string call_left_register, call_right_register, left_register, right_register;
        if(left->whatAMI()=="Function Call"){
            call_left_register_index = c.FindRetRegister(c);
            call_left_register = c.GetRetRegisterName(c, call_left_register_index);
            c.FreeRetRegister(c, call_left_register_index);
            left->generateMIPS(dst, call_left_register, c);
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            dst << "move " << left_register << "," << call_left_register << std::endl; 
            
        }
        else{
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            left->generateMIPS(dst, left_register, c);
        }
        if(right->whatAMI()=="Function Call"){
            call_right_register_index = c.FindRetRegister(c);
            call_right_register = c.GetRetRegisterName(c, call_right_register_index);
            c.FreeRetRegister(c, call_right_register_index);
            right->generateMIPS(dst, call_right_register, c);
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            dst << "move " << right_register << "," << call_right_register << std::endl; 
    
        }
        else{
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            right->generateMIPS(dst, right_register, c);
        }
        right->generateMIPS(dst, right_register, c);
        if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        
        dst << "srlv "<<destReg<<","<<left_register<<","<<right_register<<std::endl;
        c.FreeTempRegister(c, left_register_index);
        c.FreeTempRegister(c, right_register_index);
    }

    virtual std::string whatAMI() const override
    {
        return "Right Shift Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {
        
    }

    virtual void FunctionCallCheck (Context &c) const override{
        left->FunctionCallCheck(c);
        right->FunctionCallCheck(c);
    }

    virtual int getValue() const override{
         return left->getValue() >> right->getValue();
    }
    virtual std::string getId() const override{

    }
};

// & (bitwise)
class BitwiseAndOperator
    : public Node
{
private:
    NodePtr left;
    NodePtr right;
public:
    BitwiseAndOperator(NodePtr _left, NodePtr _right)
    {
        left = _left;
        right = _right;
    }
    virtual ~BitwiseAndOperator(){
        delete left;
        delete right;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the AND Bitwise(&) operator node"<<std::endl;
        left->visualise();
        right->visualise(); 
    }
    
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
        std::string call_left_register, call_right_register, left_register, right_register;
        if(left->whatAMI()=="Function Call"){
            call_left_register_index = c.FindRetRegister(c);
            call_left_register = c.GetRetRegisterName(c, call_left_register_index);
            c.FreeRetRegister(c, call_left_register_index);
            left->generateMIPS(dst, call_left_register, c);
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            dst << "move " << left_register << "," << call_left_register << std::endl; 
            
        }
        else{
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            left->generateMIPS(dst, left_register, c);
        }
        if(right->whatAMI()=="Function Call"){
            call_right_register_index = c.FindRetRegister(c);
            call_right_register = c.GetRetRegisterName(c, call_right_register_index);
            c.FreeRetRegister(c, call_right_register_index);
            right->generateMIPS(dst, call_right_register, c);
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            dst << "move " << right_register << "," << call_right_register << std::endl; 
    
        }
        else{
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            right->generateMIPS(dst, right_register, c);
        }
        right->generateMIPS(dst, right_register, c);
        if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        dst << "and "<<destReg<<","<<left_register<<","<<right_register<<std::endl;
        c.FreeTempRegister(c, left_register_index);
        c.FreeTempRegister(c, right_register_index);
    }

    virtual std::string whatAMI() const override
    {
        return "BitwiseAnd (&) Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {
    }

    virtual void FunctionCallCheck (Context &c) const override{
        left->FunctionCallCheck(c);
        right->FunctionCallCheck(c);
    }

    virtual int getValue() const override{
         return (left->getValue())&(right->getValue());
    }
    virtual std::string getId() const override{

    }
};


// | (bitwise)
class BitwiseOrOperator
    : public Node
{
private:
    NodePtr left;
    NodePtr right;
public:
    BitwiseOrOperator(NodePtr _left, NodePtr _right)
    {
        left = _left;
        right = _right;
    }
    virtual ~BitwiseOrOperator(){
        delete left;
        delete right;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the OR bitwise (|) operator node"<<std::endl;
        left->visualise();
        right->visualise(); 
    }
    
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
        std::string call_left_register, call_right_register, left_register, right_register;
        if(left->whatAMI()=="Function Call"){
            call_left_register_index = c.FindRetRegister(c);
            call_left_register = c.GetRetRegisterName(c, call_left_register_index);
            c.FreeRetRegister(c, call_left_register_index);
            left->generateMIPS(dst, call_left_register, c);
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            dst << "move " << left_register << "," << call_left_register << std::endl; 
            
        }
        else{
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            left->generateMIPS(dst, left_register, c);
        }
        if(right->whatAMI()=="Function Call"){
            call_right_register_index = c.FindRetRegister(c);
            call_right_register = c.GetRetRegisterName(c, call_right_register_index);
            c.FreeRetRegister(c, call_right_register_index);
            right->generateMIPS(dst, call_right_register, c);
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            dst << "move " << right_register << "," << call_right_register << std::endl; 
    
        }
        else{
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            right->generateMIPS(dst, right_register, c);
        }
        right->generateMIPS(dst, right_register, c);
        if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        dst << "or "<<destReg<<","<<left_register<<","<<right_register<<std::endl;
        c.FreeTempRegister(c, left_register_index);
        c.FreeTempRegister(c, right_register_index);
    }

    virtual std::string whatAMI() const override
    {
        return "BitwiseOr (|) Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {
    }

    virtual void FunctionCallCheck (Context &c) const override{
        left->FunctionCallCheck(c);
        right->FunctionCallCheck(c);
    }

    virtual int getValue() const override{
         return (left->getValue())|(right->getValue());
    }
    virtual std::string getId() const override{

    }
};

// ^ (bitwise)
class BitwiseXorOperator
    : public Node
{
private:
    NodePtr left;
    NodePtr right;
public:
    BitwiseXorOperator(NodePtr _left, NodePtr _right)
    {
        left = _left;
        right = _right;
    }
    virtual ~BitwiseXorOperator(){
        delete left;
        delete right;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the XOR bitwise(^) operator node"<<std::endl;
        left->visualise();
        right->visualise(); 
    }
    
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
        std::string call_left_register, call_right_register, left_register, right_register;
        if(left->whatAMI()=="Function Call"){
            call_left_register_index = c.FindRetRegister(c);
            call_left_register = c.GetRetRegisterName(c, call_left_register_index);
            c.FreeRetRegister(c, call_left_register_index);
            left->generateMIPS(dst, call_left_register, c);
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            dst << "move " << left_register << "," << call_left_register << std::endl; 
            
        }
        else{
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            left->generateMIPS(dst, left_register, c);
        }
        if(right->whatAMI()=="Function Call"){
            call_right_register_index = c.FindRetRegister(c);
            call_right_register = c.GetRetRegisterName(c, call_right_register_index);
            c.FreeRetRegister(c, call_right_register_index);
            right->generateMIPS(dst, call_right_register, c);
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            dst << "move " << right_register << "," << call_right_register << std::endl; 
    
        }
        else{
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            right->generateMIPS(dst, right_register, c);
        }
        right->generateMIPS(dst, right_register, c);
        if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        dst << "xor "<<destReg<<","<<left_register<<","<<right_register<<std::endl; //nothing too taxing i hope..
        c.FreeTempRegister(c, left_register_index);
        c.FreeTempRegister(c, right_register_index);
    }

    virtual std::string whatAMI() const override
    {
        return "BitwiseXor (^) Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {
        
    }

    virtual void FunctionCallCheck (Context &c) const override{
        left->FunctionCallCheck(c);
        right->FunctionCallCheck(c);
    }

    virtual int getValue() const override{
         return (left->getValue())^(right->getValue());
    }
    virtual std::string getId() const override{

    }
};


/////////////////////////////////////////////////////////////////
// Defines classes for bitwise operator classes:
//    - &&: 
//    - ||: 

// && (logical)
class LogicalAndOperator
    : public Node
{
private:
    NodePtr left;
    NodePtr right;
public:
    LogicalAndOperator(NodePtr _left, NodePtr _right)
    {
        left = _left;
        right = _right;
    }
    virtual ~LogicalAndOperator(){
        delete left;
        delete right;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the AND Logical(&&) operator node"<<std::endl;
        left->visualise();
        right->visualise(); 
    }
    
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
        std::string call_left_register, call_right_register, left_register, right_register;
        if(left->whatAMI()=="Function Call"){
            call_left_register_index = c.FindRetRegister(c);
            call_left_register = c.GetRetRegisterName(c, call_left_register_index);
            c.FreeRetRegister(c, call_left_register_index);
            left->generateMIPS(dst, call_left_register, c);
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            dst << "move " << left_register << "," << call_left_register << std::endl; 
            
        }
        else{
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            left->generateMIPS(dst, left_register, c);
        }
        if(right->whatAMI()=="Function Call"){
            call_right_register_index = c.FindRetRegister(c);
            call_right_register = c.GetRetRegisterName(c, call_right_register_index);
            c.FreeRetRegister(c, call_right_register_index);
            right->generateMIPS(dst, call_right_register, c);
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            dst << "move " << right_register << "," << call_right_register << std::endl; 
    
        }
        else{
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            right->generateMIPS(dst, right_register, c);
        }
        right->generateMIPS(dst, right_register, c);
        if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        std::string jump_label = makeName("$L");
        std::string end_jump = makeName("$L");
        dst << "beq " << left_register << ",$0," << jump_label << std::endl;
        dst << "nop" << std::endl;
        dst << "beq " << right_register << ",$0," << jump_label << std::endl;
        dst << "nop" << std::endl;
        dst << "li " << destReg << ", 1" << std::endl;
        dst << "b " << end_jump << std::endl;
        dst << jump_label << ":" << std::endl;
        dst << "li " << destReg << ",0" << std::endl;
        dst << end_jump << ":" << std::endl;
        c.FreeTempRegister(c, left_register_index);
        c.FreeTempRegister(c, right_register_index);
    }

    virtual std::string whatAMI() const override
    {
        return "LogicalAnd (&&) Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {
        
    }

    virtual void FunctionCallCheck (Context &c) const override{
        left->FunctionCallCheck(c);
        right->FunctionCallCheck(c);
    }

    virtual int getValue() const override{
         return (left->getValue())&&(right->getValue());
    }
    virtual std::string getId() const override{

    }
};

// && (logical)
class LogicalOrOperator
    : public Node
{
private:
    NodePtr left;
    NodePtr right;
public:
    LogicalOrOperator(NodePtr _left, NodePtr _right)
    {
        left = _left;
        right = _right;
    }
    virtual ~LogicalOrOperator(){
        delete left;
        delete right;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the OR Logical(||) operator node"<<std::endl;
        left->visualise();
        right->visualise(); 
    }
    
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
        std::string call_left_register, call_right_register, left_register, right_register;
        if(left->whatAMI()=="Function Call"){
            call_left_register_index = c.FindRetRegister(c);
            call_left_register = c.GetRetRegisterName(c, call_left_register_index);
            c.FreeRetRegister(c, call_left_register_index);
            left->generateMIPS(dst, call_left_register, c);
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            dst << "move " << left_register << "," << call_left_register << std::endl; 
            
        }
        else{
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            left->generateMIPS(dst, left_register, c);
        }
        if(right->whatAMI()=="Function Call"){
            call_right_register_index = c.FindRetRegister(c);
            call_right_register = c.GetRetRegisterName(c, call_right_register_index);
            c.FreeRetRegister(c, call_right_register_index);
            right->generateMIPS(dst, call_right_register, c);
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            dst << "move " << right_register << "," << call_right_register << std::endl; 
    
        }
        else{
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            right->generateMIPS(dst, right_register, c);
        }
        right->generateMIPS(dst, right_register, c);
        if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        left->generateMIPS(dst, left_register, c);
        right->generateMIPS(dst, right_register, c);
        std::string jump_label0 = makeName("$L");
        std::string jump_label1 = makeName("$L");
        std::string end_jump = makeName("$L");
        dst << "bne " << left_register << ",$0," << jump_label0 << std::endl;
        dst << "nop" << std::endl;
        dst << "beq " << right_register << ",$0," << jump_label1 << std::endl;
        dst << "nop" << std::endl;
        dst << jump_label0 << ":" << std::endl;
        dst << "li " << destReg << ", 1" << std::endl;
        dst << "b " << end_jump << std::endl;
        dst << jump_label1 << ":" << std::endl;
        dst << "li " << destReg << ", 0" << std::endl;
        dst << end_jump << ":" << std::endl;
        c.FreeTempRegister(c, left_register_index);
        c.FreeTempRegister(c, right_register_index);
    }

    virtual std::string whatAMI() const override
    {
        return "LogicalOr (||) Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {
        
    }

    virtual void FunctionCallCheck (Context &c) const override{
        left->FunctionCallCheck(c);
        right->FunctionCallCheck(c);
    }

    virtual int getValue() const override{
         return (left->getValue())||(right->getValue());
    }
    virtual std::string getId() const override{

    }
};






//////////////////////
///////////////////////

// Defines classes for comparison operator classes:
//    - <: 
//    - >: 
//    - <=: 
//    - >=: 
//    - ==: 
//    - !=: 



class LessThanOperator
    : public Node
{
private:
    NodePtr left;
    NodePtr right;
public:
    LessThanOperator(NodePtr _left, NodePtr _right)
    {
        left = _left;
        right = _right;
    }
    virtual ~LessThanOperator(){
        delete left;
        delete right;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the LessThan operator node"<<std::endl;
        left->visualise();
        right->visualise(); 
    }
    
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
        std::string call_left_register, call_right_register, left_register, right_register;
        if(left->whatAMI()=="Function Call"){
            call_left_register_index = c.FindRetRegister(c);
            call_left_register = c.GetRetRegisterName(c, call_left_register_index);
            c.FreeRetRegister(c, call_left_register_index);
            left->generateMIPS(dst, call_left_register, c);
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            dst << "move " << left_register << "," << call_left_register << std::endl; 
            
        }
        else{
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            left->generateMIPS(dst, left_register, c);
        }
        if(right->whatAMI()=="Function Call"){
            call_right_register_index = c.FindRetRegister(c);
            call_right_register = c.GetRetRegisterName(c, call_right_register_index);
            c.FreeRetRegister(c, call_right_register_index);
            right->generateMIPS(dst, call_right_register, c);
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            dst << "move " << right_register << "," << call_right_register << std::endl; 
    
        }
        else{
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            right->generateMIPS(dst, right_register, c);
        }
        right->generateMIPS(dst, right_register, c);
        if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        left->generateMIPS(dst, left_register, c);
        right->generateMIPS(dst, right_register, c);
        dst << "slt "<<destReg<<","<<left_register<<","<<right_register<<std::endl;
        dst << "andi "<<destReg<<","<<destReg<<",0x00ff"<<std::endl;
        c.FreeTempRegister(c, left_register_index);
        c.FreeTempRegister(c, right_register_index);
    }

    virtual std::string whatAMI() const override
    {
        return "Less than Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {
        
    }

    virtual void FunctionCallCheck (Context &c) const override{
        left->FunctionCallCheck(c);
        right->FunctionCallCheck(c);
    }

    virtual int getValue() const override{
         return left->getValue()<right->getValue();
    }
    virtual std::string getId() const override{

    }

    
};

class GreaterThanOperator
    : public Node
{
private:
    NodePtr left;
    NodePtr right;
public:
    GreaterThanOperator(NodePtr _left, NodePtr _right)
    {
        left = _left;
        right = _right;
    }
    virtual ~GreaterThanOperator(){
        delete left;
        delete right;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the GreaterThan operator node"<<std::endl;
        left->visualise();
        right->visualise(); 
    }
    
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
        std::string call_left_register, call_right_register, left_register, right_register;
        if(left->whatAMI()=="Function Call"){
            call_left_register_index = c.FindRetRegister(c);
            call_left_register = c.GetRetRegisterName(c, call_left_register_index);
            c.FreeRetRegister(c, call_left_register_index);
            left->generateMIPS(dst, call_left_register, c);
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            dst << "move " << left_register << "," << call_left_register << std::endl; 
            
        }
        else{
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            left->generateMIPS(dst, left_register, c);
        }
        if(right->whatAMI()=="Function Call"){
            call_right_register_index = c.FindRetRegister(c);
            call_right_register = c.GetRetRegisterName(c, call_right_register_index);
            c.FreeRetRegister(c, call_right_register_index);
            right->generateMIPS(dst, call_right_register, c);
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            dst << "move " << right_register << "," << call_right_register << std::endl; 
    
        }
        else{
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            right->generateMIPS(dst, right_register, c);
        }
        right->generateMIPS(dst, right_register, c);
        if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        left->generateMIPS(dst, left_register, c);
        right->generateMIPS(dst, right_register, c);
        dst << "slt "<<destReg<<","<<right_register<<","<<left_register<<std::endl; //just swapped right and left...
        dst << "andi "<<destReg<<","<<destReg<<",0x00ff"<<std::endl;
        c.FreeTempRegister(c, left_register_index);
        c.FreeTempRegister(c, right_register_index);
    }

    virtual std::string whatAMI() const override
    {
        return "Greater than Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {
        
    }

    virtual void FunctionCallCheck (Context &c) const override{
        left->FunctionCallCheck(c);
        right->FunctionCallCheck(c);
    }

    virtual int getValue() const override{
        return left->getValue()>right->getValue();
    }
    virtual std::string getId() const override{

    }
};

class LessThanEqualOperator
    : public Node
{
private:
    NodePtr left;
    NodePtr right;
public:
    LessThanEqualOperator(NodePtr _left, NodePtr _right)
    {
        left = _left;
        right = _right;
    }
    virtual ~LessThanEqualOperator(){
        delete left;
        delete right;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the LessThanEqual operator node"<<std::endl;
        left->visualise();
        right->visualise(); 
    }
    
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
        std::string call_left_register, call_right_register, left_register, right_register;
        if(left->whatAMI()=="Function Call"){
            call_left_register_index = c.FindRetRegister(c);
            call_left_register = c.GetRetRegisterName(c, call_left_register_index);
            c.FreeRetRegister(c, call_left_register_index);
            left->generateMIPS(dst, call_left_register, c);
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            dst << "move " << left_register << "," << call_left_register << std::endl; 
            
        }
        else{
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            left->generateMIPS(dst, left_register, c);
        }
        if(right->whatAMI()=="Function Call"){
            call_right_register_index = c.FindRetRegister(c);
            call_right_register = c.GetRetRegisterName(c, call_right_register_index);
            c.FreeRetRegister(c, call_right_register_index);
            right->generateMIPS(dst, call_right_register, c);
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            dst << "move " << right_register << "," << call_right_register << std::endl; 
    
        }
        else{
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            right->generateMIPS(dst, right_register, c);
        }
        right->generateMIPS(dst, right_register, c);
        if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        dst << "slt "<<destReg<<","<<right_register<<","<<left_register<<std::endl; //the right and left registers get swapped
        dst << "xori " <<destReg<< "," <<destReg<< ",0x1" << std::endl; // include this for the greater than equal stuff
        dst << "andi "<<destReg<<","<<destReg<<",0x00ff"<<std::endl;
        c.FreeTempRegister(c, left_register_index);
        c.FreeTempRegister(c, right_register_index);
    }

    virtual std::string whatAMI() const override
    {
        return "LessthanEqual Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {
        
    }

    virtual void FunctionCallCheck (Context &c) const override{
        left->FunctionCallCheck(c);
        right->FunctionCallCheck(c);
    }

    virtual int getValue() const override{
        return left->getValue()>=right->getValue();
    }
    virtual std::string getId() const override{

    }
};

class GreaterThanEqualOperator
    : public Node
{
private:
    NodePtr left;
    NodePtr right;
public:
    GreaterThanEqualOperator(NodePtr _left, NodePtr _right)
    {
        left = _left;
        right = _right;
    }
    virtual ~GreaterThanEqualOperator(){
        delete left;
        delete right;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the GreaterthanEqual  operator node"<<std::endl;
        left->visualise();
        right->visualise(); 
    }
    
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
        std::string call_left_register, call_right_register, left_register, right_register;
        if(left->whatAMI()=="Function Call"){
            call_left_register_index = c.FindRetRegister(c);
            call_left_register = c.GetRetRegisterName(c, call_left_register_index);
            c.FreeRetRegister(c, call_left_register_index);
            left->generateMIPS(dst, call_left_register, c);
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            dst << "move " << left_register << "," << call_left_register << std::endl; 
            
        }
        else{
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            left->generateMIPS(dst, left_register, c);
        }
        if(right->whatAMI()=="Function Call"){
            call_right_register_index = c.FindRetRegister(c);
            call_right_register = c.GetRetRegisterName(c, call_right_register_index);
            c.FreeRetRegister(c, call_right_register_index);
            right->generateMIPS(dst, call_right_register, c);
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            dst << "move " << right_register << "," << call_right_register << std::endl; 
    
        }
        else{
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            right->generateMIPS(dst, right_register, c);
        }
        right->generateMIPS(dst, right_register, c);
        if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        left->generateMIPS(dst, left_register, c);
        right->generateMIPS(dst, right_register, c);
        dst << "slt "<<destReg<<","<<left_register<<","<<right_register<<std::endl; //the right and left registers get swapped
        dst << "xori " <<destReg<< "," <<destReg<< ",0x1" << std::endl; // include this for the greater than equal stuff       
        dst << "andi "<<destReg<<","<<destReg<<",0x00ff"<<std::endl;
        c.FreeTempRegister(c, left_register_index);
        c.FreeTempRegister(c, right_register_index);
    }

    virtual std::string whatAMI() const override
    {
        return "Greater than Equal Operator";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {
        
    }

    virtual void FunctionCallCheck (Context &c) const override{
        left->FunctionCallCheck(c);
        right->FunctionCallCheck(c);
    }

    virtual int getValue() const override{
        return left->getValue()<=right->getValue();
    }
    virtual std::string getId() const override{

    }
};

//==
class EqualOperator
    : public Node
{
private:
    NodePtr left;
    NodePtr right;
public:
    EqualOperator(NodePtr _left, NodePtr _right)
    {
        left = _left;
        right = _right;
    }
    virtual ~EqualOperator(){
        delete left;
        delete right;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the Equal (==) operator node"<<std::endl;
        left->visualise();
        right->visualise(); 
    }
    
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
        std::string call_left_register, call_right_register, left_register, right_register;
        if(left->whatAMI()=="Function Call"){
            call_left_register_index = c.FindRetRegister(c);
            call_left_register = c.GetRetRegisterName(c, call_left_register_index);
            c.FreeRetRegister(c, call_left_register_index);
            left->generateMIPS(dst, call_left_register, c);
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            dst << "move " << left_register << "," << call_left_register << std::endl; 
            
        }
        else{
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            left->generateMIPS(dst, left_register, c);
        }
        if(right->whatAMI()=="Function Call"){
            call_right_register_index = c.FindRetRegister(c);
            call_right_register = c.GetRetRegisterName(c, call_right_register_index);
            c.FreeRetRegister(c, call_right_register_index);
            right->generateMIPS(dst, call_right_register, c);
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            dst << "move " << right_register << "," << call_right_register << std::endl; 
    
        }
        else{
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            right->generateMIPS(dst, right_register, c);
        }
        right->generateMIPS(dst, right_register, c);
        if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        left->generateMIPS(dst, left_register, c);
        right->generateMIPS(dst, right_register, c);
        dst << "xor " << destReg << ","<< left_register<<","<<right_register<< std::endl; //not sure if it matters the position of left and right...
        c.FreeTempRegister(c, left_register_index);
        c.FreeTempRegister(c, right_register_index);
        dst << "sltu " << destReg << "," << destReg << ",1" << std::endl;
        dst << "andi " << destReg << "," << destReg << ",0x00ff" << std::endl;
    }

    virtual std::string whatAMI() const override
    {
        return "Equal Operator (==)";
    };

    virtual std::vector<NodePtr> returnList() const override
    {

    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {
        
    }

    virtual void FunctionCallCheck (Context &c) const override{
        left->FunctionCallCheck(c);
        right->FunctionCallCheck(c);
    }

    virtual int getValue() const override{
        return left->getValue()==right->getValue();
    }
    virtual std::string getId() const override{

    }
};

//!=
class NotEqualOperator
    : public Node
{
private:
    NodePtr left;
    NodePtr right;
public:
    NotEqualOperator(NodePtr _left, NodePtr _right)
    {
        left = _left;
        right = _right;
    }
    virtual ~NotEqualOperator(){
        delete left;
        delete right;
    }
    virtual void visualise() const override
    {   
        std::cout<<"in the NotEqual (!=) operator node"<<std::endl;
        left->visualise();
        right->visualise();
    }
    
    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        int call_left_register_index, call_right_register_index, left_register_index, right_register_index, kill_right_register_index, kill_left_register_index;
        std::string call_left_register, call_right_register, left_register, right_register;
        if(left->whatAMI()=="Function Call"){
            call_left_register_index = c.FindRetRegister(c);
            call_left_register = c.GetRetRegisterName(c, call_left_register_index);
            c.FreeRetRegister(c, call_left_register_index);
            left->generateMIPS(dst, call_left_register, c);
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            dst << "move " << left_register << "," << call_left_register << std::endl; 
            
        }
        else{
            left_register_index = c.FindTempRegister(c);
            kill_left_register_index = left_register_index;
            left_register = c.GetTempRegisterName(c, left_register_index);
            left->generateMIPS(dst, left_register, c);
        }
        if(right->whatAMI()=="Function Call"){
            call_right_register_index = c.FindRetRegister(c);
            call_right_register = c.GetRetRegisterName(c, call_right_register_index);
            c.FreeRetRegister(c, call_right_register_index);
            right->generateMIPS(dst, call_right_register, c);
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            dst << "move " << right_register << "," << call_right_register << std::endl; 
    
        }
        else{
            right_register_index = c.FindTempRegister(c);
            kill_right_register_index = right_register_index;
            right_register = c.GetTempRegisterName(c, right_register_index);
            right->generateMIPS(dst, right_register, c);
        }
        right->generateMIPS(dst, right_register, c);
        if(left->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << left_register << "," << left_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        if(right->whatAMI() == "Int Number" && c.pointer_arithmetic){
            int temp_index = c.FindTempRegister(c);
            std::string temp = c.GetTempRegisterName(c, temp_index);
            dst << "li " << temp << ",2" << std::endl;
            dst << "sll " << right_register << "," << right_register << "," << temp << std::endl;
            c.FreeTempRegister(c, temp_index);
        }
        left->generateMIPS(dst, left_register, c);
        right->generateMIPS(dst, right_register, c);
        dst << "xor " << destReg << "," << left_register<<","<<right_register<< std::endl; //not sure if it matters the position of left and right...
        dst << "sltu " << destReg << ",$0," << destReg <<  std::endl;  //we stlu with the $0 for this operation..
        dst << "andi " << destReg << "," << destReg << ",0x00ff" << std::endl;
        c.FreeTempRegister(c, left_register_index);
        c.FreeTempRegister(c, right_register_index);
    }

    virtual std::string whatAMI() const override
    {
        return "NotEqual Operator (!=)";
    };

    virtual std::vector<NodePtr> returnList() const override
    {

    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override
    {
        
    }

    virtual void FunctionCallCheck (Context &c) const override{
        left->FunctionCallCheck(c);
        right->FunctionCallCheck(c);
    }

    virtual int getValue() const override{
        return left->getValue()!=right->getValue();
    }
    virtual std::string getId() const override{

    }
};

////////////////////////////////////////////////////////////////////////////////



#endif
