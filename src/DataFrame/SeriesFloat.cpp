SeriesFloat::SeriesFloat(): size_(float()){};

SeriesFloat::SeriesFloat(std::vector<float> data): series_(data), size_(data.size()){};

std::vector<float>& SeriesFloat::getVec(float){
  return this -> series_;
}

long int SeriesFloat::size(){
  return this -> size_;
}

void SeriesFloat::show(){
  print<float>(this -> series_);
}

void SeriesFloat::Index(){
  make_map<float>(this -> series_, this -> index_);
}

vTypes SeriesFloat::operator[](int i){
  return this -> series_[i];
}

Series* SeriesFloat::operator+(Series* src2){
  Series* dst = new SeriesFloat(std::vector<float>(src2 -> getVec(float()).size()));
  Add<float>(this -> getVec(float()), src2 -> getVec(float()), dst -> getVec(float()));
  return dst;
}

Series* SeriesFloat::operator*(Series* src2){
  Series* dst = new SeriesFloat(std::vector<float>(src2 -> getVec(float()).size()));
  Mul<float>(this -> getVec(float()), src2 -> getVec(float()), dst -> getVec(float()));
  return dst;
}

void SeriesFloat::mul(Series* src2, Series* dst){
  Mul<float>(this -> getVec(float()), src2 -> getVec(float()), dst -> getVec(float()));
}

void SeriesFloat::mul(Series* src2){
  Mul<float>(this -> getVec(float()), src2 -> getVec(float()), this -> getVec(float()));
}

void SeriesFloat::div(Series* src2){
  Div<float>(this -> getVec(float()), src2 -> getVec(float()), this -> getVec(float()));
}

void SeriesFloat::sub(Series* src2){
  Sub<float>(this -> getVec(float()), src2 -> getVec(float()), this -> getVec(float()));
}

int SeriesFloat::index(float i){

  std::cout <<  "req: " << i;
  if(this -> index_.find(i) != this -> index_.end()){
    std::cout << "found";
    return this -> index_[i];
  }
  return -1;
}


Series* SeriesFloat::copy(){
  Series* dst = new SeriesFloat(this -> getVec(float()));
  return dst;
}
