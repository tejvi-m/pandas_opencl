#include<iostream>
#include<unordered_map>
#include<vector>
#include <string>

template <typename T>
void print(std::vector<T>& data){
  for(int i = 0; i < data.size(); i++){
    std::cout << data[i] << " ";
  }
  std::cout << std::endl;
}

class Series{
public:

  virtual ~Series(){}
  virtual std::vector<int>& getVec(int){}
  virtual std::vector<std::string>& getVec(std::string){}
  virtual std::vector<float>& getVec(float){}

  virtual long int size(){}

  virtual void show(){}

  // virtual int
  // friend functions?
};

class SeriesInt : public Series{
private:
  std::vector<int> series_;
  int size_;

public:
  SeriesInt(): size_(0){};

  SeriesInt(std::vector<int> data): series_(data), size_(data.size()){};

  virtual std::vector<int>& getVec(int){
    return this -> series_;
  }

  virtual long int size(){
    return this -> size_;
  }

  virtual void show(){
    print<int>(this -> series_);
  }
};

class SeriesStr : public Series{
private:
  std::vector<std::string> series_;
  int size_;

public:
  SeriesStr(): size_(0){}

  SeriesStr(std::vector<std::string> data): series_(data), size_(data.size()){};

  virtual std::vector<std::string>& getVec(std::string){
    return this -> series_;
  }

  virtual long int size(){
    return this -> size_;
  }

  virtual void show(){
    print<std::string>(this -> series_);
  }
};
// 
// int main(){
//   SeriesInt x({1, 2, 3});
//   x.show();
//   std::vector<Series*> xs({new SeriesInt({2, 3, 4}), new SeriesStr({"1m ", "2"})});
//   xs[1]->show();
// }
