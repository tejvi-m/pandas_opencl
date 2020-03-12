#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
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

  void drop(std::string column){
    auto indexIt = std::find(this -> columns_.begin(), this -> columns_.end(), column);
    if(indexIt == this -> columns_.end()) return;
    // should i throw an error message
    int indexCol = std::distance(this -> columns_.begin(), indexIt);

    this -> dataframe_.erase(dataframe_.begin() + indexCol);
    this -> columns_.erase(indexIt);
  }

  void rename(std::string oldName, std::string newName){
    auto indexIt = std::find(this -> columns_.begin(), this -> columns_.end(), oldName);
    if(indexIt == this -> columns_.end()) return;
    *indexIt = newName;
  }
};

int main(){
  DataFrame x({new SeriesInt({1, 2, 3}), new SeriesStr({"11", "22", "22"}), new SeriesInt({0, 0, 0})}, {"a", "b", "c"}, "a");
  x.printDF();

  x.drop("c");

  x.printDF();

  x.rename("a", "i");

  x.drop("i");
  x.printDF();
  return 0;
}
