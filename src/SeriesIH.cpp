#include<iostream>
#include<unordered_map>
#include<vector>
#include <string>
#include <variant>

using vTypes = std::variant<int, std::string, float>;

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

// void print(std::unordered_map)
class Series{
public:

  virtual ~Series(){}
  virtual std::vector<int>& getVec(int){}
  virtual std::vector<std::string>& getVec(std::string){}
  virtual std::vector<float>& getVec(float){}

  virtual long int size(){}
  virtual void Index(){}
  virtual void show(){}

  virtual vTypes operator[](int){}
  virtual int index(int){}

  // virtual int
  // friend functions?
};

class SeriesInt : public Series{
private:
  std::vector<int> series_;
  int size_;
  std::unordered_map<int, int> index_;
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

  virtual void Index(){
    make_map<int>(this -> series_, this -> index_);
  }

  virtual vTypes operator[](int i){
    return this -> series_[i];
  }

  virtual int index(int i){

    std::cout <<  "req: " << i;
    if(this -> index_.find(i) != this -> index_.end()){
      std::cout << "found";
      return this -> index_[i];
    }
    return -1;
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

  virtual vTypes operator[](int i){
    return this -> series_[i];
  }
};

class SeriesFloat : public Series{
private:
  std::vector<float> series_;
  int size_;
  std::unordered_map<float, int> index_;
public:
  SeriesFloat(): size_(0){};

  SeriesFloat(std::vector<float> data): series_(data), size_(data.size()){};

  virtual std::vector<float>& getVec(float){
    return this -> series_;
  }

  virtual long int size(){
    return this -> size_;
  }

  virtual void show(){
    print<float>(this -> series_);
  }

  virtual void Index(){
    make_map<float>(this -> series_, this -> index_);
  }
  
  virtual vTypes operator[](int i){
    return this -> series_[i];
  }
};

//
// int main(){
//   SeriesInt x({1, 2, 3});
//   x.show();
//   std::vector<Series*> xs({new SeriesInt({2, 3, 4}), new SeriesStr({"1m ", "2"})});
//   xs[1]->show();
//
//   x.Index();
//   int d= x[1];
//
//   std::cout << d << std::endl;
//   std::cout << x.index(2);
//
//
//   xs[0] -> Index();
//   int ss = xs[0]->index(5);
//   std::cout << std::endl << ss;
//   std::cout << (*xs[0])[0] << std::endl;
//
// }
