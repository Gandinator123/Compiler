#include "ast.hpp"

extern FILE *yyin;

int main(int argc, char *argv[])
{
    std::ofstream outfile;

    /*Not including any invalid arguments to the command line input...
    --> Assumption is that the correct parameters and arguments are put in place
    */
    //This should allow the parseAST to not need an argument
    yyin = fopen(argv[2], "r");

    //open the file with the output file name --> we can put it in an output directory perhaps...
    outfile.open(argv[4]);
    if (!outfile.is_open())
    {
          std::cout << "Output file not found." << std::endl;
          std::exit(2);
    }

    const Node *ast=parseAST();

    //Initialising the context.hpp 
    Context c;
    
    for(int i = 0; i<8;i++){
        c.temp_reg.push_back(0);
    }

    for(int i = 0; i<2;i++){
        c.ret_reg.push_back(0);
    }

    for(int i = 0; i<8;i++){
        c.float_temp_reg.push_back(0);
    }

    for(int i = 0; i<2;i++){
        c.float_ret_reg.push_back(0);
    }

    //Return register
    c.ret_mappings.insert(std::pair<int, std::string>(0, "$2"));
    c.ret_mappings.insert(std::pair<int, std::string>(1, "$3"));

    c.float_ret_mappings.insert(std::pair<int, std::string>(0, "$f0"));
    c.float_ret_mappings.insert(std::pair<int, std::string>(1, "$f2"));

    //Argument register
    c.arg_mappings.insert(std::pair<int, std::string>(0, "$4"));
    c.arg_mappings.insert(std::pair<int, std::string>(1, "$5"));
    c.arg_mappings.insert(std::pair<int, std::string>(2, "$6"));
    c.arg_mappings.insert(std::pair<int, std::string>(3, "$7"));
    
    c.float_arg_mappings.insert(std::pair<int, std::string>(0, "$f12"));
    c.float_arg_mappings.insert(std::pair<int, std::string>(1, "$f14"));

    c.temp_mappings.insert(std::pair<int, std::string>(0, "$8"));
    c.temp_mappings.insert(std::pair<int, std::string>(1, "$9"));
    c.temp_mappings.insert(std::pair<int, std::string>(2, "$10"));
    c.temp_mappings.insert(std::pair<int, std::string>(3, "$11"));
    c.temp_mappings.insert(std::pair<int, std::string>(4, "$12"));
    c.temp_mappings.insert(std::pair<int, std::string>(5, "$13"));
    c.temp_mappings.insert(std::pair<int, std::string>(6, "$14"));
    c.temp_mappings.insert(std::pair<int, std::string>(7, "$15"));
    c.temp_mappings.insert(std::pair<int, std::string>(8, "$24"));
    c.temp_mappings.insert(std::pair<int, std::string>(9, "$25"));

    c.float_temp_mappings.insert(std::pair<int, std::string>(0, "$f4"));
    c.float_temp_mappings.insert(std::pair<int, std::string>(1, "$f6"));
    c.float_temp_mappings.insert(std::pair<int, std::string>(2, "$f8"));
    c.float_temp_mappings.insert(std::pair<int, std::string>(3, "$f10"));
    

    c.pointer_arithmetic = false;
    c.end_of_case_link = "";
    ////////////
    //Generating MIPS now...
    
    ast->generateMIPS(outfile,"", c);
    //for debugging
    //ast->visualise();
    // ast->generateMIPS(std::cout,"", c);
    // functions/call_identity_internal
    //need to close the outfile.
    outfile.close();
    return 0;
}
