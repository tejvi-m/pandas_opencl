SeriesFloat::SeriesFloat(): size_(0){};

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
