
SeriesInt::SeriesInt(): size_(0){};

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
  add<int>(this -> getVec(0), src2 -> getVec(0), dst -> getVec(0));
  return dst;
}

int SeriesInt::index(int i){

  std::cout <<  "req: " << i;
  if(this -> index_.find(i) != this -> index_.end()){
    std::cout << "found";
    return this -> index_[i];
  }
  return -1;
}