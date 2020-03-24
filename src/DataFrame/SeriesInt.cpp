
#include "gpu/gpu.cpp"
#include <cmath>
SeriesInt::SeriesInt(): size_(0){};

// int gpu = 1;
SeriesInt::SeriesInt(std::vector<int> data): series_(data), size_(data.size()){};

std::vector<int>& SeriesInt::getVec(int){
  return this -> series_;
}

long int SeriesInt::size(){
  return this -> size_;
}

void SeriesInt::show(){
  print<int>(this -> series_);
}

void SeriesInt::Index(){
  make_map<int>(this -> series_, this -> index_);
}

vTypes SeriesInt::operator[](int i){
  return this -> series_[i];
}

Series* SeriesInt::operator+(Series* src2){
  Series* dst = new SeriesInt(std::vector<int>(src2 -> getVec(0).size()));
  Add<int>(this -> getVec(0), src2 -> getVec(0), dst -> getVec(0));
  return dst;
}

void SeriesInt::add(Series* src){
  if(gpu.use_gpu){
    gpuArithmetic("vecAddInt",&(this -> getVec(int())[0]), &(src -> getVec(int())[0]), &(this -> getVec(int())[0]),
                this -> getVec(int()).size(), true, NULL, NULL, NULL,
                 CL_MEM_READ_ONLY,  CL_MEM_WRITE_ONLY);
  }
  else
    Add<int>(this -> getVec(int()), src -> getVec(int()), this -> getVec(int()));
}

SeriesInt SeriesInt::operator+(Series& src2){
  SeriesInt dst(std::vector<int>(src2.getVec(0).size()));
  Add<int>(this -> getVec(0), src2.getVec(0), dst.getVec(0));
  return dst;
}

Series* SeriesInt::operator*(Series* src2){
  Series* dst = new SeriesInt(std::vector<int>(src2 -> getVec(0).size()));
  Mul<int>(this -> getVec(0), src2 -> getVec(0), dst -> getVec(0));
  return dst;
}

void SeriesInt::mul(Series* src2, Series* dst){
  Mul<int>(this -> getVec(0), src2 -> getVec(0), dst -> getVec(0));
}

void SeriesInt::mul(Series* src2){
  Mul<int>(this -> getVec(0), src2 -> getVec(0), this -> getVec(0));
}

void SeriesInt::div(Series* src2){
  Div<int>(this -> getVec(0), src2 -> getVec(0), this -> getVec(0));
}

void SeriesInt::sub(Series* src2){
  Sub<int>(this -> getVec(0), src2 -> getVec(0), this -> getVec(0));
}


Series* SeriesInt::copy(){
  Series* dst = new SeriesInt(std::vector<int>(this -> getVec(int())));
  return dst;
}

void SeriesInt::map(std::unordered_map<int, int> umap){
  MapOp(this -> getVec(int()), umap);
}

int SeriesInt::index(int i){

  std::cout <<  "req: " << i;
  if(this -> index_.find(i) != this -> index_.end()){
    std::cout << "found";
    return this -> index_[i];
  }
  return -1;
}

Series* SeriesInt::append(vTypes ele){
  series_.push_back(std::get<0>(ele));
  size_++;
  return this;
}

bool SeriesInt::isArithmetic(){
  return true;
}

template<typename T>
void SeriesInt::transform(T&& Fn){
  for_each(this -> getVec(int()).begin(), this -> getVec(int()).end(), Fn);
}


vTypes SeriesInt::type(){
  return int();
}

template<typename R = int, typename F>
R SeriesInt::apply(F&& Fn){
    return Fn(this -> getVec(0));
}
