#include <vector>
#include <iostream>
#include <unordered_map>

template<typename T>
class Series{
public:
  std::vector<T> series_;
  long int size_;
  std::unordered_map<T, long int> index;

public:
  Series(): size_(0){

  }

  Series(long int size): size_(size){
    // with predefined size?

  }

  Series(std::vector<T> data): series_(data), size_(data.size()){

  }

  long int size(){
    return this -> size_;
  }

  std::unordered_map<T, long int> getIndex(){
    for(int i = 0; i < this -> size_; i++){
      index[series_[i]] = i;
    }
  }

  void print(){
    for(T element: series_){
      std::cout << element << " ";
    }
    std::cout << std::endl;
  }

  // TODO implement views
};

int main(){
  std::vector<int> c{1, 2, 3, 4, 5};
  Series s(c);

  s.print();

  return 0;
}
