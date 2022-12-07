#ifndef ast_program_hpp
#define ast_program_hpp

#include "ast_base.hpp"



// typedef std::vector<NodePtr> StatementList;
// typedef StatementList *StatementListPtr;

class Program : 
public Node
{
private:
  std::vector<NodePtr> list;

public:

  Program(NodePtr _function)
  {
    list.push_back(_function); 
  }

  Program(std::vector<NodePtr> _list, NodePtr _function)
  {
    list = _list;
    list.push_back(_function);
  }

  virtual ~Program()
  {
    for(unsigned i = 0; i < list.size(); i++)
    {
      delete list[i];
    }
  }

  virtual void visualise() const override 
  {
    std::cout<<"in program"<<std::endl;
    std::cout<<"starting going through program"<<std::endl;
    for(int i = 0; i<list.size();i++){
        list[i]->visualise();
    }
    std::cout<<"ended going through program"<<std::endl;
  }

  virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
  {
    if(list.size()==0){
      dst<<"nop"<<std::endl;
    }
    else{
      for(int i = 0; i<list.size();i++)
      {
        list[i]->generateMIPS(dst, destReg, c);
        dst<<std::endl;
      }   
    }


    //displaying the words assiciated with floating points.
    for (auto it = c.float_variables.begin(); it != c.float_variables.end(); it++)
    {      
      dst << it->first << ":" << std::endl;
      dst << ".word " << it->second << std::endl; 
        
    }

    
  } 

  virtual std::string whatAMI() const override
  {
    return "Program";      
  }

  virtual std::vector<NodePtr> returnList() const override
  {
    return list;
  } //used to implement a specific feature in a node

  virtual void countDeclarations(Context &c) const override{
      for(int i = 0; i<list.size();i++)
      {
        list[i]->countDeclarations(c);
      } 
    }
  
  virtual void FunctionCallCheck (Context &c) const override{
        
  }

  virtual int getValue() const override{

  }
    virtual std::string getId() const override{

  }




};

#endif
