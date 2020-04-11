#include "Graph.h"
#include <string>

std::unordered_map operationSymbol({
      {"add", '+'},
      {"sub", '-'},
      {"mul", '*'},
      {"div", '/'}
})

Graph::Graph(){

}

void Graph::addDF(DataFrame* DF){
  if(mapping.find(DF) == mapping.end()){
    this -> toLoad.push_back(DF);
    std::string oldName = genNames.back();
    string newName = "v" + to_string(atoi(oldName.erase(0, 1)) + 1);
    genNames.push_back(newName);
    mapping[DF] = newName;
  }
}

void Graph::getGenName(DataFrame* DF){
  return this -> mapping[DF];
}

void Graph::insertOperation(std::string operation, DataFrame* DF){

}

void Graph::insertOperation(std::string operation, DataFrame* DF1, DataFrame* DF2){
  //first DF is the one that gets updated.
  std::string newOp = getGenName(DF1) + "[i] " + " = "+ operationSymbol[operation] +


}
