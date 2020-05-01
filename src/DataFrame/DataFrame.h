#pragma once
#include "Series.h"
#include <vector>
#include <variant>
#include <string>
#include <algorithm>
#include <numeric>


using Row = std::vector<std::variant<int, std::string, float>>;

class DataFrame{
private:
  std::vector<Series *> dataframe_;
  std::vector<std::string> columns_;
  std::string index_;

public:
  DataFrame();
  DataFrame(std::vector<Series *>, std::vector<std::string>, std::string);
  DataFrame(std::string); //read csv

  Series* operator[](int);
  Series* operator[](std::string);
  DataFrame operator[](std::vector<std::string>);

  template<typename T>
  Row loc(T);
  Row iloc(int);
  
  Series* getCol(int);  

  void add(Series*, std::string);
  void drop(std::string);
  void rename(std::string, std::string);

  DataFrame copy();
  DataFrame copy(std::vector<std::string>);

  DataFrame operator+(DataFrame& src2);
  void add(DataFrame& src2);
  template<typename T>
  void add(T src2);

  DataFrame operator-(DataFrame& src2);
  void sub(DataFrame& src2);
  template<typename T>
  void sub(T src2);

  DataFrame operator*(DataFrame& src2);
  void mul(DataFrame& src2);
  template<typename T>
  void mul(T src2);

  DataFrame operator/(DataFrame& src2);
  void div(DataFrame& src2);
  template<typename T>
  void div(T src2);

  void transform(std::string);
  void transform(std::string, std::unordered_map<std::string, DataFrame&>);
  template<typename T>
  void transform(T&&);

  void map(std::unordered_map<int, int>);
  void map(std::unordered_map<float, float>);
  void map(std::unordered_map<std::string, std::string>);
  template<typename T>
  std::unordered_map<std::string, float> apply(T&&);

  void dropNA(float toDrop = 0);
  void fillNA(float Replacement, float toDrop = 0);

  std::unordered_map<std::string, float> sum();
  std::unordered_map<std::string, float> mean();
  std::unordered_map<std::string, float> max();
  std::unordered_map<std::string, float> min();

  std::pair<int, int> shape();
  void printDF();
};


// template<typename T>
struct Sum{
  int operator()(std::vector<int>& vec){
      float x = std::accumulate(vec.begin(), vec.end(), 0);
      return x;
  }

  float operator()(std::vector<float>& vec){
      float x = std::accumulate(vec.begin(), vec.end(), 0);
      return x;
  }
};

// template<typename T>
struct Mean{
  float operator()(std::vector<int>& vec){
      float x = std::accumulate(vec.begin(), vec.end(), 0) / (float) vec.size();
      return x;
  }

  float operator()(std::vector<float>& vec){
      float x = std::accumulate(vec.begin(), vec.end(), 0) / (float) vec.size();
      return x;
  }
};

struct Min{
  int operator()(std::vector<int>& vec){
    return *min_element(vec.begin(), vec.end());
  }

  float operator()(std::vector<float>& vec){
      return *min_element(vec.begin(), vec.end());
  }
};

struct Max{
  int operator()(std::vector<int>& vec){
      return *max_element(vec.begin(), vec.end());
  }

  float operator()(std::vector<float>& vec){
      return *max_element(vec.begin(), vec.end());
  }
};
