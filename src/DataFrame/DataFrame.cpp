#include "DataFrame.h"
#include <iostream>

DataFrame::DataFrame(): dataframe_({}), columns_({}), index_(""){}

DataFrame::DataFrame(std::vector<Series *> data, std::vector<std::string> columns = {}, std::string index = ""): dataframe_(data), columns_(columns), index_(index){}

Series* DataFrame::operator[](int i){
    return this -> dataframe_[i];
}

Series* DataFrame::operator[](std::string column){
    auto indexIt = std::find(this -> columns_.begin(), this -> columns_.end(), column);
    if(indexIt == this -> columns_.end()) return new Series();
    int indexCol = std::distance(this -> columns_.begin(), indexIt);
    return this -> dataframe_[indexCol];
}


void DataFrame::add(Series* series, std::string name){
  this -> dataframe_.push_back(series);
  this -> columns_.push_back(name);
}

DataFrame DataFrame::operator[](std::vector<std::string> columns){
  DataFrame newDF;
  for(std::string col: columns){
    newDF.add((*this)[col], col);
  }

  return newDF;
}

Row DataFrame::iloc(int index){
  Row row;

  for(int i = 0; i < this -> dataframe_.size(); i++){
    // std::cout << (*(this-> dataframe_[i]))[index] << std::endl;
    row.push_back((*(this-> dataframe_[i]))[index]);
  }

  return row;
}

template<typename T>
Row DataFrame::loc(T value){
  // auto indexCol = std::find(columns.begin(), columns.end(), column);
  int loc = (*this)[this -> index_] -> index(value);
  return this -> iloc(loc);

}

void DataFrame::printDF(){
  for(int i = 0; i < this -> dataframe_.size(); i++){
    this-> dataframe_[i] -> show();
  }
}

void DataFrame::drop(std::string column){
  auto indexIt = std::find(this -> columns_.begin(), this -> columns_.end(), column);
  if(indexIt == this -> columns_.end()) return;
  // should i throw an error message
  int indexCol = std::distance(this -> columns_.begin(), indexIt);

  this -> dataframe_.erase(dataframe_.begin() + indexCol);
  this -> columns_.erase(indexIt);
}

std::pair<int, int> DataFrame::shape(){
    return std::make_pair(this -> columns_.size(), (*this)[0] -> size());
}

DataFrame DataFrame::copy(){
  DataFrame newDF;
  for(auto col: this -> columns_){
    newDF.add((*this)[col] -> copy(), col);
  }
  return newDF;
}

DataFrame DataFrame::copy(std::vector<std::string> columns){
  DataFrame newDF;
  for(auto col: columns){
    newDF.add((*this)[col] -> copy(), col);
  }
  return newDF;
}

void DataFrame::rename(std::string oldName, std::string newName){
  auto indexIt = std::find(this -> columns_.begin(), this -> columns_.end(), oldName);
  if(indexIt == this -> columns_.end()) return;
  *indexIt = newName;
}

DataFrame DataFrame::operator+(DataFrame& src2){
    DataFrame newDF;
    for(auto col: this -> columns_){
      if((*this)[col] -> isArithmetic())
        newDF.add((*(*this)[col]) + (*this)[col], col);
      else
        newDF.add((*(*this)[col]).copy(), col);
    }
    return newDF;
}


void DataFrame::add(DataFrame& src2){
  for(auto col: this -> columns_){
    if((*this)[col] -> isArithmetic())
      (*(*this)[col]).add((*this)[col]);
  }
}

DataFrame DataFrame::operator-(DataFrame& src2){
    DataFrame newDF;
    for(auto col: this -> columns_){
      if((*this)[col] -> isArithmetic())
        newDF.add((*(*this)[col]) - (*this)[col], col);
      else
        newDF.add((*(*this)[col]).copy(), col);
    }
    return newDF;
}


void DataFrame::sub(DataFrame& src2){
  for(auto col: this -> columns_){
    if((*this)[col] -> isArithmetic())
      (*(*this)[col]).sub((*this)[col]);
  }
}

DataFrame DataFrame::operator*(DataFrame& src2){
    DataFrame newDF;
    for(auto col: this -> columns_){
      if((*this)[col] -> isArithmetic())
        newDF.add((*(*this)[col]) * (*this)[col], col);
      else
        newDF.add((*(*this)[col]).copy(), col);
    }
    return newDF;
}


void DataFrame::mul(DataFrame& src2){
  for(auto col: this -> columns_){
    if((*this)[col] -> isArithmetic())
      (*(*this)[col]).mul((*this)[col]);
  }
}

DataFrame DataFrame::operator/(DataFrame& src2){
    DataFrame newDF;
    for(auto col: this -> columns_){
      if((*this)[col] -> isArithmetic())
        newDF.add((*(*this)[col]) / (*this)[col], col);
      else
        newDF.add((*(*this)[col]).copy(), col);
    }
    return newDF;
}


void DataFrame::div(DataFrame& src2){
  for(auto col: this -> columns_){
    if((*this)[col] -> isArithmetic())
      (*(*this)[col]).div((*this)[col]);
  }
}
