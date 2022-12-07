#ifndef ParameterList_hpp
#define ParameterList_hpp

#include "ast_base.hpp"

class ParameterList : 
public Node
{
private:
  std::vector<NodePtr> list;
public:
  ParameterList(NodePtr _parameter)
  {
    list.push_back(_parameter); 
  }
  ParameterList(std::vector<NodePtr> _parameterlist, NodePtr _parameter)
  {
    list = _parameterlist;
    list.push_back(_parameter);
  }

  virtual ~ParameterList()
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
      std::cout<<"end of parameters list"<<std::endl;
    }
  }


  virtual void generateMIPS(std::ostream &dst,std::string destReg, Context &c, std::string type = "int") const override
  {
    c.argument_declaration = true;
    c.argument_number = 0;
    for(int i = 0; i < list.size() ; i++){
      list[i]->generateMIPS(dst, destReg, c, c.argument_type);
      c.argument_number++;
    }
    c.argument_declaration = false;
  }

  virtual std::string whatAMI() const override
  {
    return "Parameter List";      
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