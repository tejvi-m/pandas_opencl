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
  std::pair<int, int> shape();
  void printDF();
};
