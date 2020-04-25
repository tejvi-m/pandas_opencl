#pragma once
#include "Series.h"
#include <vector>
#include <variant>
#include <string>
#include <algorithm>

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
  template<typename T>
  void transform(T&&);


  template<typename T>
  std::vector<std::pair<std::string, float>> apply(T&&);


  std::pair<int, int> shape();
  void printDF();
};
