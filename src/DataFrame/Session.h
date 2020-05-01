#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>


class Session{
private:
  std::vector<DataFrame*> toLoad;
  std::vector<std::string> genNames;
  std::unordered_map<DataFrame*, std::string> mapping;
  std::unordered_set<DataFrame*> modifiedDF;

  // std::vector<std::pair<std::string, std::vector<DataFrame*>>> operations;

  std::string Kernel;

  void run();
public:
  Session();
  void addDF(DataFrame*);
  std::string getGenName(DataFrame*, int);
  void insertOperation(std::string, std::string, DataFrame*);
  void insertOperation(std::string, DataFrame*, DataFrame*);
  void insertOperation(std::string, std::string, std::unordered_map<std::string, DataFrame&>, DataFrame*);
  void compute_with_model(int);
  void compute();
  void clear();

  template<typename T>
  void insertOperation(std::string operation, DataFrame* DF1, T constant);
  std::string getKernel(std::string);

};

Session* _Session = nullptr;
