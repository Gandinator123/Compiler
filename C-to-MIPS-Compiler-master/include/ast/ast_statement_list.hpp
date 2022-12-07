#ifndef statement_list_hpp
#define statement_list_hpp

#include "ast_base.hpp"



// typedef std::vector<NodePtr> StatementList;
// typedef StatementList *StatementListPtr;

class CreateStatementList : 
public Node
{
private:
  std::vector<NodePtr> list;


public:

  CreateStatementList(NodePtr _general_statement)
  {
    list.push_back(_general_statement); 
  }
  CreateStatementList(std::vector<NodePtr> _statement_list, NodePtr _general_statement)
  {
    list = _statement_list;
    list.push_back(_general_statement);
  }
  CreateStatementList()
  {
  }

  virtual ~CreateStatementList()
  {
    for(unsigned i = 0; i < list.size(); i++)
    {
      delete list[i];
    }
  }

  virtual void visualise() const override 
  {
    for(int i = 0; i<list.size();i++){
      list[i]->visualise();
      std::cout<<"end of statement list"<<std::endl;
    }
  }

  virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
  {
    if(list.size()==0){
      dst<<"nop"<<std::endl;
    }
    else{
      for(int i = 0; i<list.size();i++)
      {
        std::cout<<"i is "<<i<<std::endl;
        list[i]->generateMIPS(dst, destReg, c);
      }   
    } 
  } 

  virtual std::string whatAMI() const override
  {
    return "Create Statement List";      
  };

  virtual std::vector<NodePtr> returnList() const override
  {
    return list;
  }; //used to implement a specific feature in a node

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
