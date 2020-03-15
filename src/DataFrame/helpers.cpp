#include "helpers.h"

template <typename T>
void add(std::vector<T>& src1, std::vector<T>& src2, std::vector<T>& dst){
    for(int i = 0; i < src1.size(); i++){
      dst[i] = src1[i] + src2[i];
      std::cout << src1[i] << src2[i] << std::endl;
    }
}

template <typename T>
void print(std::vector<T>& data){
  for(int i = 0; i < data.size(); i++){
    std::cout << data[i] << " ";
  }
  std::cout << std::endl;
}

template <typename T>
void make_map(std::vector<T>& data, std::unordered_map<T, int>& umap){
  for(int i = 0; i < data.size(); i++){
    umap[data[i]] = i;
  }
}

void printRow(Row data){

  auto lambdaPrintVisitor = [](auto&& _in){std::cout << _in;};
  for (const auto& nextVariant : data){
          std::visit(lambdaPrintVisitor, nextVariant);
          std::cout << " ";
      }
  std::cout << std::endl;
}
