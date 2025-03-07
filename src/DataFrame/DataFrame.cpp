#pragma once
#include "DataFrame.h"
#include "Session.cpp"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>

class Session;
extern Session* _Session;

DataFrame::DataFrame(): dataframe_({}), columns_({}), index_(""){}

DataFrame::DataFrame(std::vector<Series *> data, std::vector<std::string> columns = {}, std::string index = ""): dataframe_(data), columns_(columns), index_(index){}

Series* DataFrame::operator[](int i){
    return this -> dataframe_[i];
}

Series* DataFrame::getCol(int i){
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

  for(unsigned int i = 0; i < this -> dataframe_.size(); i++){
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
  for(unsigned int i = 0; i < this -> dataframe_.size(); i++){
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
        newDF.add((*(*this)[col]) + src2[col], col);
      else
        newDF.add((*(*this)[col]).copy(), col);
    }
    return newDF;
}


void DataFrame::add(DataFrame& src2){
  if(_Session != nullptr){
    _Session -> insertOperation("add", this, &src2);
  }
  else
  for(auto col: this -> columns_){
    if((*this)[col] -> isArithmetic())
      (*(*this)[col]).add(src2[col]);
  }
}

template<typename T>
void DataFrame::add(T src2){
  if(_Session != nullptr){
    _Session -> insertOperation("add", this, src2);
  }
  else
  for(auto col: this -> columns_){
      vTypes x = ((*this)[col]) -> type();
      if(std::holds_alternative<int>(x)){
        (*(*this)[col]).add((int) src2);
      }
      else if(std::holds_alternative<float>(x)){
        (*(*this)[col]).add((float) src2);
      }
    }
}

DataFrame DataFrame::operator-(DataFrame& src2){
    DataFrame newDF;
    for(auto col: this -> columns_){
      if((*this)[col] -> isArithmetic())
        newDF.add((*(*this)[col]) - src2[col], col);
      else
        newDF.add((*(*this)[col]).copy(), col);
    }
    return newDF;
}


void DataFrame::sub(DataFrame& src2){
  if(_Session != nullptr){
    _Session -> insertOperation("sub", this, &src2);
  }
  else
  for(auto col: this -> columns_){
    if((*this)[col] -> isArithmetic())
      (*(*this)[col]).sub(src2[col]);
  }
}

template<typename T>
void DataFrame::sub(T src2){
  if(_Session != nullptr){
    _Session -> insertOperation("sub", this, src2);
  }
  else
  for(auto col: this -> columns_){
      vTypes x = ((*this)[col]) -> type();
      if(std::holds_alternative<int>(x)){
        (*(*this)[col]).sub((int) src2);
      }
      else if(std::holds_alternative<float>(x)){
        (*(*this)[col]).div((float) src2);
      }
    }
}

DataFrame DataFrame::operator*(DataFrame& src2){
    DataFrame newDF;
    for(auto col: this -> columns_){
      if((*this)[col] -> isArithmetic())
        newDF.add((*(*this)[col]) * src2[col], col);
      else
        newDF.add((*(*this)[col]).copy(), col);
    }
    return newDF;
}


void DataFrame::mul(DataFrame& src2){
  if(_Session != nullptr){
    _Session -> insertOperation("mul", this, &src2);
  }
  else
  for(auto col: this -> columns_){
    if((*this)[col] -> isArithmetic())
      (*(*this)[col]).mul(src2[col]);
  }
}

template<typename T>
void DataFrame::mul(T src2){
  if(_Session != nullptr){
    _Session -> insertOperation("mul", this, src2);
  }
  else
  for(auto col: this -> columns_){
    vTypes x = ((*this)[col]) -> type();
    if(std::holds_alternative<int>(x)){
      (*(*this)[col]).mul((int) src2);
    }
    else if(std::holds_alternative<float>(x)){
      (*(*this)[col]).mul((float) src2);
    }
  }
}

DataFrame DataFrame::operator/(DataFrame& src2){
    DataFrame newDF;
    for(auto col: this -> columns_){
      if((*this)[col] -> isArithmetic())
        newDF.add((*(*this)[col]) / src2[col], col);
      else
        newDF.add((*(*this)[col]).copy(), col);
    }
    return newDF;
}


void DataFrame::div(DataFrame& src2){
  if(_Session != nullptr){
    _Session -> insertOperation("div", this, &src2);
  }
  else
  for(auto col: this -> columns_){
    if((*this)[col] -> isArithmetic())
      (*(*this)[col]).div(src2[col]);
  }
}

template<typename T>
void DataFrame::div(T src2){
  if(_Session != nullptr){
    _Session -> insertOperation("div", this, src2);
  }
  else
  for(auto col: this -> columns_){
      vTypes x = ((*this)[col]) -> type();
      if(std::holds_alternative<int>(x)){
        (*(*this)[col]).div((int) src2);
      }
      else if(std::holds_alternative<float>(x)){
        (*(*this)[col]).div((float) src2);
      }
    }
}


void DataFrame::transform(std::string operation){
  // only GPU mode supported.
  if(_Session != nullptr){
    _Session -> insertOperation("tx", operation, this);
  }
}

void DataFrame::transform(std::string operation, std::unordered_map<std::string, DataFrame&> mapping){
  if(_Session != nullptr){
    _Session -> insertOperation("tx", operation, mapping, this);
  }
}

template<typename F>
void DataFrame::transform(F&& fn){
  for(auto col: this -> columns_){
    vTypes x = ((*this)[col]) -> type();
    if(std::holds_alternative<int>(x)){
      std::for_each((*this)[col] -> getVec(int()).begin(), (*this)[col] -> getVec(int()).end(), fn);
    }
    else if(std::holds_alternative<float>(x)){
      std::for_each((*this)[col] -> getVec(float()).begin(), (*this)[col] -> getVec(float()).end(), fn);
    }
  }
}

template<typename T>
std::unordered_map<std::string, float> DataFrame::apply(T&& Fn){
  std::unordered_map<std::string, float> results;

  for(auto col: this -> columns_){

    vTypes x = ((*this)[col]) -> type();

    if(std::holds_alternative<int>(x)){
      float res = Fn((*this)[col] -> getVec(int()));
      results["col"] = res;
    }
    else if(std::holds_alternative<float>(x)){
      float res = Fn((*this)[col] -> getVec(float()));
      results["col"] = res;
    }
  }
  return results;
}

std::unordered_map<std::string, float> DataFrame::sum(){
  return this -> apply(Sum());
}


std::unordered_map<std::string, float> DataFrame::mean(){
  return this -> apply(Mean());
}


std::unordered_map<std::string, float> DataFrame::max(){
  return this -> apply(Max());
}


std::unordered_map<std::string, float> DataFrame::min(){
  return this -> apply(Min());
}

void DataFrame::map(std::unordered_map<int, int> Map){
  for(auto col: this -> columns_){
    vTypes x = ((*this)[col]) -> type();
    if(std::holds_alternative<int>(x)){
      (*this)[col] -> map(Map);
    }
  }
}

void DataFrame::map(std::unordered_map<float, float> Map){
  for(auto col: this -> columns_){
    vTypes x = ((*this)[col]) -> type();
    if(std::holds_alternative<float>(x)){
      (*this)[col] -> map(Map);
    }
  }
}



void DataFrame::map(std::unordered_map<std::string, std::string> Map){
  for(auto col: this -> columns_){
    vTypes x = ((*this)[col]) -> type();
    if(std::holds_alternative<std::string>(x)){
      (*this)[col] -> map(Map);
    }
  }
}


std::stringstream& operator>>(std::stringstream& os, vTypes *v)
{
  std::visit([&os](auto &e){ os >> e; }, *v);
  return os;
}

DataFrame::DataFrame(const std::string filename)
{
    std::ifstream myFile(filename);
    if(!myFile.is_open()) throw std::runtime_error("Could not open file");

    std::string line, col;
    std::string val;

    /*
    The first of line input contains the column name and type in the format:
    Col_Name : DType, Col_Name : DType, ...
    where DType = INT, FLOAT, STRING
    */
    if(myFile.good())
    {
        std::vector<int> dtypes;
        std::vector<Series *> data;

        // Extract the first line in the file
        std::getline(myFile, line);
        std::stringstream ss(line);

        while(std::getline(ss, col, ','))
        {
            std::stringstream ss1(col);
            ss1 >> val; //Column Name
            columns_.push_back(val);
            ss1 >> val; // ':' character
            ss1 >> val; //DType
            if(!(val.compare("INT")))
                dataframe_.push_back(new SeriesInt());
            else if(!(val.compare("FLOAT")))
                dataframe_.push_back(new SeriesFloat());
            else if(!(val.compare("STRING")))
                dataframe_.push_back(new SeriesStr());
            else
                throw std::runtime_error("Invalid data type");
        }
        int i;
        while(std::getline(myFile, line))
        {
            std::stringstream ss(line);
            i = 0;
            while(std::getline(ss, col, ','))
            {
                vTypes v = dataframe_[i]->type();
                std::stringstream ss1(col);
                std::visit([&ss1](auto &e){ ss1 >> e; }, v);
                dataframe_[i]->append(v);
                i++;
            }
        }
    }
    myFile.close();
}


void DataFrame::dropNA(float toDrop){
  std::vector<bool> valid(this -> shape().second, true);

  for(unsigned int i = 0; i < this -> shape().first; i++){
    (*this)[i] -> getValidity(valid, toDrop);
  }

  // std::cout<<" valid:\n";
  // for(bool b: valid){
  //   std::cout << b << std::endl;
  // }

  for(unsigned int i = 0; i < this -> shape().first; i++){
    (*this)[i] -> dropRows(valid);
  }

  // std::cout << "shape " << this -> shape().first << this -> shape().second << std::endl;
}

void DataFrame::fillNA(float Replacement, float toDrop){
  std::unordered_map<int, int> iMap{{(int) toDrop, (int) Replacement}};
  std::unordered_map<int, int> fMap{{toDrop, Replacement}};

  this -> map(iMap);
  this -> map(fMap);
}
