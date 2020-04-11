#include "DataFrame.h"
#include <vector>
#include <unordered_map>

class Graph{
private:
  std::vector<DataFrame*> toLoad;
  std::vector<std::string> genNames;
  std::unordered_map<DataFrame*, std::string> mapping;

  // std::vector<std::pair<std::string, std::vector<DataFrame*>>> operations;

  std::string Kernel;

public:
  Graph();
  void addDF(DataFrame*);
  void getGenName(DataFrame*);
  void insertOperation(std::string, DataFrame*);
  void insertOperation(std::string, DataFrame*, DataFrame*);
  std::string getKernel(std::string);

}
