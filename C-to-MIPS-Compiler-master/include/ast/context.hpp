#ifndef context_hpp
#define context_hpp
#include "ast_base.hpp"

struct Context
{
    //temporary registers
    std::vector<bool> temp_reg;
    std::map<int, std::string> temp_mappings;
    
    //return registers
    std::vector<bool> ret_reg;
    std::map<int, std::string> ret_mappings;

    //argument registers
    std::vector<bool> arg_reg;
    std::map<int, std::string> arg_mappings;

    //floating point ret registers
    std::vector<bool> float_ret_reg;
    std::map<int, std::string> float_ret_mappings;

    //floating point temp registers
    std::vector<bool> float_temp_reg;
    std::map<int, std::string> float_temp_mappings;

    //floating point arg registers
    std::vector<bool> float_arg_reg;
    std::map<int, std::string> float_arg_mappings;
    
    std::string return_type;
    //variable memory allocation
    std::unordered_map<std::string, int> memory;
    std::unordered_map<std::string, std::string> variable_type;
    int next_available_memory_slot;
    std::unordered_map<std::string, int> enum_variables;
    std::vector<std::string> pointers;
    //global variable memory allocation:
    std::unordered_map<std::string, std::vector<int>> global_int_array_variables;
    //variable to hold all the declarations done in a function...
    int declarations;
    //array declarations 
    int array_declarations;
    // end of a function statement 
    std::string end_of_function_link;
    std::string argument_type;
    bool argument_declaration;
    int argument_number;
    std::string break_link;
    std::string continue_link;
    std::string case_variable_register;
    std::string end_of_case_link;
    bool no_default;
    //for function calls
    bool pointer_arithmetic;
    std::vector<int> temp_registers_used;
    std::unordered_map<std::string,int> float_variables;
    int frame_size_for_call;
//================================================================================

    void function_call_register_change(Context &c){
        std::cout<<"doing change"<<std::endl;
        for(int i = 0; i<c.temp_registers_used.size();i++){
            std::cout<<c.temp_registers_used[i]<<std::endl;
            c.temp_reg[c.temp_registers_used[i]]=true;
        }
        std::cout<<"done"<<std::endl;
    }
    //=====================================================================================
    //temp registers
    int FindTempRegister(Context &c){
        for(int i = 0;i<8;i++){
            //first value is free it returns the register
            if(c.temp_reg[i]==0){
                c.temp_reg[i]=1;
                c.temp_registers_used.push_back(i);
                return i;
            }
        }
        return -1;
        
    }


    void FreeTempRegister(Context &c,int i){
        c.temp_reg[i]=0;
    }

    std::string GetTempRegisterName(Context &c,int i){
        auto it = c.temp_mappings.find(i);
        return it->second;
    }

    //FOR THE FLOATS

    //temp registers
    int FindFloatTempRegister(Context &c){
        for(int i = 0;i<8;i++){
            //first value is free it returns the register
            if(c.float_temp_reg[i]==0){
                c.float_temp_reg[i]=1;
                return i;
            }
        }
        return -1;
        
    }


    void FreeFloatTempRegister(Context &c,int i){
        c.float_temp_reg[i]=0;
    }

    std::string GetFloatTempRegisterName(Context &c,int i){
        auto it = c.float_temp_mappings.find(i);
        return it->second;
    }

    //==========================================================================================
    //ret registers
    int FindRetRegister(Context &c){//finds a register that isn't being used and returns its number in our list (need to input number into mapping to get the exact register name)
        for(int i = 0;i<2;i++){
            if(c.ret_reg[i]==0){
                c.ret_reg[i]=1;
                return i;
            }
        }
        return -1;
    }

    void FreeRetRegister(Context &c, int i){
        c.ret_reg[i]=0;
    }

    std::string GetRetRegisterName(Context &c,int i){ //returns the register name mapping of an existing index
        auto it = c.ret_mappings.find(i);
        return it->second;
    }

    //Float registers
    int FindFloatRetRegister(Context &c){//finds a register that isn't being used and returns its number in our list (need to input number into mapping to get the exact register name)
        for(int i = 0;i<2;i++){
            if(c.float_ret_reg[i]==0){
                c.float_ret_reg[i]=1;
                return i;
            }
        }
        return -1;
    }

    void FreeFloatRetRegister(Context &c, int i){
        c.float_ret_reg[i]=0;
    }

    std::string GetFloatRetRegisterName(Context &c,int i){ //returns the register name mapping of an existing index
        auto it = c.float_ret_mappings.find(i);
        return it->second;
    }

    //==========================================================================================
    //arg registers
    int FindArgRegister(Context &c){//finds a register that isn't being used and returns its number in our list (need to input number into mapping to get the exact register name)
        for(int i = 0;i<4;i++){
            if(c.arg_reg[i]==0){
                c.arg_reg[i]=1;
                return i;
            }
        }
        return -1;
    }

    void FreeArgRegister(Context &c, int i){
        c.arg_reg[i]=0;
    }

    std::string GetArgRegisterName(Context &c,int i){ //returns the register name mapping of an existing index
        auto it = c.arg_mappings.find(i);
        return it->second;
    }

    //float arg registers
    int FindFloatArgRegister(Context &c){//finds a register that isn't being used and returns its number in our list (need to input number into mapping to get the exact register name)
        for(int i = 0;i<4;i++){
            if(c.float_arg_reg[i]==0){
                c.float_arg_reg[i]=1;
                return i;
            }
        }
        return -1;
    }

    void FreeFloatArgRegister(Context &c, int i){
        c.float_arg_reg[i]=0;
    }

    std::string GetFloatArgRegisterName(Context &c,int i){ //returns the register name mapping of an existing index
        auto it = c.float_arg_mappings.find(i);
        return it->second;
    }


    //==========================================================================================
    //memory slots
    int GetUsedMemorySlot(Context &c, std::string variable_name){//says what memory index an existing variable is at, or -1 if it doesn't exist
        auto it = c.memory.find(variable_name);
        if(it==c.memory.end()){
            return -1;
        }
        else{
            return it->second;
        }
    }

    std::string GetVariableType(Context &c, std::string variable_name){//says what memory index an existing variable is at, or -1 if it doesn't exist
        auto it = c.variable_type.find(variable_name);
        if(it==c.variable_type.end()){
            std::cout<<"no variable found in variable type"<<std::endl;
            return "no variable";
        }
        else{
            return it->second;
        }
    }

    int NewMemorySlot(Context &c, std::string variable_name, std::string type = "int"){
        c.variable_type.insert({variable_name, type});
        int slot = c.next_available_memory_slot;
        c.memory.insert({variable_name, slot});
        if(type=="int" || type == "float"){
            c.next_available_memory_slot+=4;
        }
        if(type=="double"){
            c.next_available_memory_slot+=8;
        }
        //std::cout<< "variable is: "<<variable_name<< " slot is: "<<slot<<std::endl;
        return slot;
    }

    std::string float_reg(std::string reg){
        return reg.insert(1, "f");
    }
    //converting the float value to IEEE754 representation... 
    

};




#endif