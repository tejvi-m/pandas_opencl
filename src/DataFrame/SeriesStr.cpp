#pragma once
SeriesStr::SeriesStr(): size_(0){}

SeriesStr::SeriesStr(std::vector<std::string> data): series_(data), size_(data.size()){};

std::vector<std::string>& SeriesStr::getVec(std::string){
  return this -> series_;
}

long int SeriesStr::size(){
  return this -> size_;
}

void SeriesStr::show(){
  print<std::string>(this -> series_);
}

vTypes SeriesStr::operator[](int i){
  return this -> series_[i];
}

void SeriesStr::map(std::unordered_map<std::string, std::string> umap){
  MapOp(this -> getVec(std::string()), umap);
}

Series* SeriesStr::copy(){
  Series* dst = new SeriesStr(this -> getVec(std::string()));
  return dst;
}

Series* SeriesStr::append(vTypes ele){
  series_.push_back(std::get<1>(ele));
  size_++;
  return this;
}

bool SeriesStr::isArithmetic(){
  return false;
}

vTypes SeriesStr::type(){
  return std::string();
}

void SeriesStr::getValidity(std::vector<bool>& valid, float toDrop){
    // getValidity<string>(this -> getVec(str()), valid, (int)toDrop);
    return;
}


void  SeriesStr::dropRows(std::vector<bool>& valid){
  drop<std::string>(this ->getVec(std::string()), valid);
}
