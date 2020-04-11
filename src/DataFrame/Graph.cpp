#include "Graph.h"
#include <string>
#include <cstring>
#include <unordered_map>

Graph::Graph(){

}

void Graph::addDF(DataFrame* DF){
  if(mapping.find(DF) == mapping.end()){
    this -> toLoad.push_back(DF);
    std::string oldName;
    if(genNames.size() == 0){
      oldName = "v0";
    }
    else oldName = genNames.back();
    oldName.erase(0,1);
    std::string newName = "v" + std::__cxx11::to_string(atoi(oldName.c_str()) + 1);
    genNames.push_back(newName);
    mapping[DF] = newName;
  }
}

std::string Graph::getGenName(DataFrame* DF){
  return this -> mapping[DF];
}

void Graph::insertOperation(std::string operation, DataFrame* DF){

}

void Graph::insertOperation(std::string operation, DataFrame* DF1, DataFrame* DF2){
  std::unordered_map<std::string, char> operationSymbol({
    {"add", '+'},
    {"sub", '-'},
    {"mul", '*'},
    {"div", '/'}
  });
  //first DF is the one that gets updated.
  std::string newOp;
  if(this -> Kernel == ""){
     newOp = getGenName(DF1) + "_copy[i] " + " = " + getGenName(DF1) + "[i] "
                      + operationSymbol[operation]
                      + getGenName(DF2) + "[i]";

  }
  else {
    newOp = getGenName(DF1) + "_copy[i] " + " = " + getGenName(DF1) + "_copy[i] "
                      + operationSymbol[operation]
                      + getGenName(DF2) + "[i]";

  }

  this -> Kernel += "\t\t\t" + newOp + ";\n";

}

template<typename T>
void Graph::insertOperation(std::string operation, DataFrame* DF1, T constant){
  std::unordered_map<std::string, char> operationSymbol({
    {"add", '+'},
    {"sub", '-'},
    {"mul", '*'},
    {"div", '/'}
  });
  //first DF is the one that gets updated.
  std::string newOp;
  if(this -> Kernel == ""){
     newOp = getGenName(DF1) + "_copy[i] " + " = " + getGenName(DF1) + "[i] "
                      + operationSymbol[operation]
                      + std::__cxx11::to_string(constant);

  }
  else {
    newOp = getGenName(DF1) + "_copy[i] " + " = "+ getGenName(DF1) + "_copy[i] "
                      + operationSymbol[operation]
                      + std::__cxx11::to_string(constant);

  }

  this -> Kernel += "\t\t\t" + newOp + ";\n";

}
std::string Graph::getKernel(std::string dtype){
  std::string fullKernel = std::string("__kernel void genKernel(")
                        + "__global " + dtype + " *v1, \n"
                        + "__global " + dtype + " *v2, \n"
                        + "__global " + dtype + " *v1_copy, \n"
                        + "__global " + dtype + " *v2_copy, \n"
                        + "const unsigned int n){\n"
                        + "\tint i = get_global_id(0);\n"
                        + "\tif(i < n){\n"
                        + this -> Kernel
                        + "\t}\n}";

  return fullKernel;
}
