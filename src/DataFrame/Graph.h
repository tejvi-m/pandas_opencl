// #include "DataFrame.h"

// #include "gpu/gpu.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

class DataFrame;

class Graph{
private:
  std::vector<DataFrame*> toLoad;
  std::vector<std::string> genNames;
  std::unordered_map<DataFrame*, std::string> mapping;
  std::unordered_set<DataFrame*> modifiedDF;

  // std::vector<std::pair<std::string, std::vector<DataFrame*>>> operations;

  std::string Kernel;

public:
  Graph();
  void addDF(DataFrame*);
  std::string getGenName(DataFrame*, int);
  void insertOperation(std::string, DataFrame*);
  void insertOperation(std::string, DataFrame*, DataFrame*);
  void compute();

  template<typename T>
  void insertOperation(std::string operation, DataFrame* DF1, T constant);
  std::string getKernel(std::string);

};

Graph* _graph = nullptr;
