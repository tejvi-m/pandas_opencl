#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include "SeriesIH.cpp"

class DataFrame{
private:
  std::vector<Series *> dataframe_;
  std::vector<std::string> columns_;
  std::string index_;
public:
  DataFrame(): dataframe_({}), columns_({}), index_(""){}

  DataFrame(std::vector<Series *> data, std::vector<std::string> columns = {}, std::string index = ""): dataframe_(data), columns_(columns), index_(index){}

  Series* operator[](int i){
      return this -> dataframe_[i];
  }

  void printDF(){
    for(int i = 0; i < this -> dataframe_.size(); i++){
      this-> dataframe_[i] -> show();
    }
  }

};

int main(){
  DataFrame x({new SeriesInt({1, 2, 3}), new SeriesStr({"11", "22", "22"}), new SeriesInt({0, 0, 0})}, {"a", "b", "c"}, "a");
  x.printDF();

  return 0;
}
