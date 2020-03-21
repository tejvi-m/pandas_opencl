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

Series* SeriesStr::append(std::string ele){
  series_.push_back(ele);
  size_++;
  return this;
}