// extern int 0 = 2;
#pragma once
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

void SeriesFloat::mul(Series* src){
  if(gpu.use_gpu){
    redirectToGPU("vecMulFloat", this -> getVec(float()), src -> getVec(float()), this -> getVec(float()), 0);
  }
  Mul<float>(this -> getVec(float()), src -> getVec(float()), this -> getVec(float()));
}

void SeriesFloat::div(Series* src){
  if(gpu.use_gpu){
    redirectToGPU("vecDivFloat", this -> getVec(float()), src -> getVec(float()), this -> getVec(float()), 0);
  }
  Div<float>(this -> getVec(float()), src -> getVec(float()), this -> getVec(float()));
}

void SeriesFloat::sub(Series* src){
  if(gpu.use_gpu){
    redirectToGPU("vecSubFloat", this -> getVec(float()), src -> getVec(float()), this -> getVec(float()), 0);
  }
  Sub<float>(this -> getVec(float()), src -> getVec(float()), this -> getVec(float()));
}

int SeriesFloat::index(float i){

  std::cout <<  "req: " << i;
  if(this -> index_.find(i) != this -> index_.end()){
    std::cout << "found";
    return this -> index_[i];
  }
  return -1;
}


void SeriesFloat::map(std::unordered_map<float, float> umap){
  MapOp(this -> getVec(float()), umap);
}

Series* SeriesFloat::copy(){
  Series* dst = new SeriesFloat(this -> getVec(float()));
  return dst;
}

Series* SeriesFloat::append(vTypes ele){
  series_.push_back(std::get<2>(ele));
  size_++;
  return this;
}

bool SeriesFloat::isArithmetic(){
  return true;
}

void SeriesFloat::add(Series* src){
  if(gpu.use_gpu){
    redirectToGPU("vecAddFloat", this -> getVec(float()), src -> getVec(float()), this -> getVec(float()), 0);
  }
  else
    Add<float>(this -> getVec(float()), src -> getVec(float()), this -> getVec(float()));
}

void SeriesFloat::add(float src){
    Add<float>(this -> getVec(float()), src, this -> getVec(float()));
}


void SeriesFloat::sub(float src){
    Sub<float>(this -> getVec(float()), src, this -> getVec(float()));
}


void SeriesFloat::div(float src){
    Div<float>(this -> getVec(float()), src, this -> getVec(float()));
}


void SeriesFloat::mul(float src){
    Mul<float>(this -> getVec(float()), src, this -> getVec(float()));
}

template<typename T>
void SeriesFloat::transform(T&& Fn){
  for_each(this -> getVec(float()).begin(), this -> getVec(float()).end(), Fn);
}

vTypes SeriesFloat::type(){
  return float();
}

template<typename R = int, typename F>
R SeriesFloat::apply(F&& Fn){
    return Fn(this -> getVec(0));
}



void SeriesFloat::getValidity(std::vector<bool>& valid, float toDrop){
    getValidity_generic(this -> getVec(float()), valid, toDrop);
}

void  SeriesFloat::dropRows(std::vector<bool>& valid){
  drop<float>(this ->getVec(float()), valid);
}
