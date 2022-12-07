#ifndef ast_literal_hpp
#define ast_literal_hpp

#include "ast_base.hpp"

class IntNumber : 
    public Node 
{
private:
    int value;

public:
    IntNumber(int _value)
    {
        value = _value;
    }
    virtual ~IntNumber(){}
    virtual void visualise()const override
    {
        std::cout<<"in the IntNumber node"<<std::endl;
    }

    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        if(type == "int"){
            dst <<"li "<<destReg<<","<<value<<std::endl;
        }
        else if(type == "float"){
            //// floating point conversion
            std::string label = makeName("$LC");
            union fconv {
            struct {
            unsigned int mantissa : 23;
            unsigned int exponent : 8;
            unsigned int sign : 1;
            } raw;
            float f;
            } fnumber;

            fnumber.f = value;
            std::string iee = std::to_string(fnumber.raw.sign) + printBinary(fnumber.raw.exponent,8) + printBinary(fnumber.raw.mantissa, 23);
            int fconv = stoi(iee,0,2);
            std::cout << "here is fconv: " << fconv << std::endl;
            c.float_variables.insert({label, fconv});
            int temp_register_index = c.FindTempRegister(c);
            std::string temp_register = c.GetTempRegisterName(c, temp_register_index);
            dst << "lui "<<temp_register << "," << "%hi" << "(" << label << ")" << std::endl;
            dst << "lwc1 " << destReg << ",%lo(" << label << ")(" << temp_register << ")" << std::endl; 
            dst << "nop" << std::endl;
            c.FreeTempRegister(c, temp_register_index);
        }else if(type == "double"){
            
        }
    }

    virtual std::string whatAMI() const override
    {
        return "Int Number";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override{
    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{
        return value;
    }
    virtual std::string getId() const override{

    }

    //helper function for conversion...
    std::string printBinary(int n, int i) const 
    {
    std::string binary;
    // Prints the binary representation
    // of a number n up to i-bits.
    int k;
    for (k = i - 1; k >= 0; k--) {
 
        if ((n >> k) & 1)
            binary.push_back('1');
        else
            binary.push_back('0');
        }
        return binary;
    }

};

class FloatNumber : 
    public Node 
{
private:
    float value;
    std::string label1;
    std::string label2;
public:
    FloatNumber(float _value)
    {
        value = _value;
        label1 = makeName("$LC");
        label2 = makeName("$LC");
    }
    FloatNumber(std::string* _value){
        (_value)->pop_back();
        value = std::stof(*_value);
        label1 = makeName("$LC");
        label2 = makeName("$LC");
    }
    virtual ~FloatNumber(){}
    virtual void visualise()const override
    {
        std::cout<<"in the Float Number node"<<std::endl;
    }

    virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
    {
        if(type=="float"){
            union fconv {
            struct {
            unsigned int mantissa : 23;
            unsigned int exponent : 8;
            unsigned int sign : 1;
            } raw;
            float f;
            } fnumber;

            fnumber.f = value;
            std::string iee = std::to_string(fnumber.raw.sign) + printBinary(fnumber.raw.exponent,8) + printBinary(fnumber.raw.mantissa, 23);
            int fconv = stoi(iee,0,2);
            std::cout << "here is fconv: " << fconv << std::endl;
            c.float_variables.insert({label1, fconv});
            int temp_register_index = c.FindTempRegister(c);
            std::string temp_register = c.GetTempRegisterName(c, temp_register_index);
            dst << "lui "<<temp_register << "," << "%hi" << "(" << label1 << ")" << std::endl;
            dst << "lwc1 " << destReg << ",%lo(" << label1 << ")(" << temp_register << ")" << std::endl; 
            dst << "nop" << std::endl;
            c.FreeTempRegister(c, temp_register_index);
        }
        else if(type=="double"){
            union fconv {
            struct {
            unsigned int mantissa : 52;
            unsigned int exponent : 11;
            unsigned int sign : 1;
            } raw;
            float f;
            } fnumber;

            fnumber.f = value;
            std::string iee = std::to_string(fnumber.raw.sign) + printBinary(fnumber.raw.exponent,11) + printBinary(fnumber.raw.mantissa, 52);
        }
        
    }

    virtual std::string whatAMI() const override
    {
        return "Float Number or Decimal Number";
    };

    virtual std::vector<NodePtr> returnList() const override
    {
    }; //used to implement a specific feature in a node

    virtual void countDeclarations(Context &c) const override{
    }

    virtual void FunctionCallCheck (Context &c) const override{
        
    }

    virtual int getValue() const override{
        return value;
    }
    virtual std::string getId() const override{

    }

    //helper function for conversion...
    std::string printBinary(int n, int i) const 
    {
    std::string binary;
    // Prints the binary representation
    // of a number n up to i-bits.
    int k;
    for (k = i - 1; k >= 0; k--) {
 
        if ((n >> k) & 1)
            binary.push_back('1');
        else
            binary.push_back('0');
        }
        return binary;
    }

};




#endif