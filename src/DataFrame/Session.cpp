#pragma once
#include "Session.h"
#include "gpu/gpu.cpp"
#include <string>
#include <cstring>
#include <unordered_map>
#include <boost/algorithm/string/replace.hpp>

extern Session* _Session;

Session::Session(){
  _Session = this;
}

void Session::addDF(DataFrame* DF){
  if(mapping.find(DF) == mapping.end()){
    this -> toLoad.push_back(DF);
    std::string oldName = "";
    if(genNames.size() == 0){
      oldName = "v0";
    }
    else oldName = genNames.back();
    oldName.erase(0,1);

    std::string newName = "v" + std::__cxx11::to_string(atoi(oldName.c_str()) + 1);
    genNames.push_back(newName);
    mapping[DF] = newName;
  }
}

std::string Session::getGenName(DataFrame* DF, int f = 0){
  if(this -> modifiedDF.find(DF) == modifiedDF.end() || f) return this -> mapping[DF];
  else return this -> mapping[DF] + "_copy";
}

void Session::insertOperation(std::string op,  std::string operation, DataFrame* DF){

  this -> addDF(DF);
  std::string newOp= "" ;
  //first DF is the one that gets updated.
  if(op=="tx"){
    std::string newOp = "";
    if(this -> modifiedDF.find(DF) == this -> modifiedDF.end()){
       boost::replace_all(operation, "x", getGenName(DF) + "[id]");
       newOp = getGenName(DF, 1) + "_copy[id] = " + operation;
    }

    else {
      boost::replace_all(operation, "x", getGenName(DF) + "[id]");
      newOp = getGenName(DF, 1) + "_copy[id] = " + operation;
    }

    this -> modifiedDF.insert(DF);

    this -> Kernel += "\t\t\t" + newOp + ";\n";
  }

}



void Session::insertOperation(std::string op,  std::string operation, std::unordered_map<std::string, DataFrame&> mapping, DataFrame* DF){

  // this -> addDF(DF);
  std::string newOp= "" ;
  //first DF is the one that gets updated.
  if(op=="tx"){

    for(auto key: mapping){
      this -> addDF(&key.second);
      boost::replace_all(operation, key.first, getGenName(&key.second) + "[id]");
    }

    std::string newOp = "";
    if(this -> modifiedDF.find(DF) == this -> modifiedDF.end()){
      //  boost::replace_all(operation, "x", getGenName(DF) + "[id]");
       newOp = getGenName(DF, 1) + "_copy[id] = " + operation;
    }

    else {
      // boost::replace_all(operation, "x", getGenName(DF) + "[id]");
      newOp = getGenName(DF, 1) + "_copy[id] = " + operation;
    }

    this -> modifiedDF.insert(DF);

    this -> Kernel += "\t\t\t" + newOp + ";\n";
  }

}

void Session::insertOperation(std::string operation, DataFrame* DF1, DataFrame* DF2){
  std::unordered_map<std::string, char> operationSymbol({
    {"add", '+'},
    {"sub", '-'},
    {"mul", '*'},
    {"div", '/'}
  });

  this -> addDF(DF1);
  this -> addDF(DF2);
  //first DF is the one that gets updated.
  std::string newOp = "";
  if(this -> modifiedDF.find(DF1) == this -> modifiedDF.end()){
     newOp = getGenName(DF1, 1) + "_copy[id] " + " = " + getGenName(DF1) + "[id] "
                      + operationSymbol[operation] + " "
                      + getGenName(DF2) + "[id]";
  }

  else {
    newOp = getGenName(DF1, 1) + "_copy[id] " + " = " + getGenName(DF1) + "[id] "
                      + operationSymbol[operation] + " "
                      + getGenName(DF2) + "[id]";
  }

  this -> modifiedDF.insert(DF1);

  this -> Kernel += "\t\t\t" + newOp + ";\n";

}

template<typename T>
void Session::insertOperation(std::string operation, DataFrame* DF1, T constant){
  std::unordered_map<std::string, char> operationSymbol({
    {"add", '+'},
    {"sub", '-'},
    {"mul", '*'},
    {"div", '/'}
  });
  //first DF is the one that gets updated.
  this -> addDF(DF1);
  std::string newOp = "";
  if(this -> modifiedDF.find(DF1) == this -> modifiedDF.end()){
     newOp = getGenName(DF1, 1) + "_copy[id] " + " = " + getGenName(DF1) + "[id] "
                      + operationSymbol[operation]
                      + std::__cxx11::to_string(constant);

  }
  else {
    newOp = getGenName(DF1, 1) + "_copy[id] " + " = "+ getGenName(DF1) + "[id] "
                      + operationSymbol[operation]
                      + std::__cxx11::to_string(constant);

  }

  this -> modifiedDF.insert(DF1);
  this -> Kernel += "\t\t\t" + newOp + ";\n";

}

std::string Session::getKernel(std::string dtype){

  std::string fullKernel = std::string("__kernel void genKernel( \n");

  for(auto DF: this -> toLoad){
    fullKernel += std::string("__global " + dtype + " *" + getGenName(DF, 1) + ",\n");
  }

  // to impose some kind of order
  for(auto DF: this -> toLoad){
      if(this -> modifiedDF.find(DF) != this -> modifiedDF.end()){
        fullKernel += std::string("__global " + dtype + " *" + getGenName(DF) + ",\n");
      }
  }

  fullKernel += std::string("const unsigned int n) {\n")
              + "\t int id = get_global_id(0);\n"
              + "\t if (id < n) {\n"
              + this -> Kernel + "\t}\n}";

  return fullKernel;
}


void Session::compute(){
  if(this -> toLoad.size() <= 0) return;
  this -> compute_with_model(0);
}

void Session::compute_with_model(int model = 0){
    // std::cout << "dhspe: " << (this -> toLoad[0]) -> shape().first << std::endl;
    for(int col = 0; col < (this -> toLoad[0]) -> shape().first; col++){
      // DataFrame temp = *(this -> toLoad[0]);
              // int n = temp[0] -> getVec(0).size();

        vTypes x = (this -> toLoad[0] -> getCol(col)) -> type();
        if(std::holds_alternative<int>(x)){
          // DataFrame temp = *(this -> toLoad[0]);
          int n = this -> toLoad[0] -> getCol(col) -> getVec(int()).size();
          // std::cout << "n: " << n << std::endl;
          std::vector<int*> srcVecs(this -> toLoad.size());
          std::vector<int*> dstVecs;
          //temp since it throws compile time errors

          for(unsigned int i = 0; i < srcVecs.size(); i++){
            // DataFrame temp = *(this -> toLoad[i]);

            srcVecs[i] = &((this -> toLoad[i] -> getCol(col) -> getVec(int()))[0]);
            if(this -> modifiedDF.find(this -> toLoad[i]) != this -> modifiedDF.end()){
              dstVecs.push_back(&(this -> toLoad[i] -> getCol(col) -> getVec(int()))[0]);
            }
          }

          runGeneratedKernel(this -> getKernel("int"),
              srcVecs,
              dstVecs,
              n,
              std::vector<int*>({NULL, NULL, NULL, NULL})
              );
        }

        else if(std::holds_alternative<float>(x)){
            // DataFrame temp = *(this -> toLoad[0]);
            int n = this -> toLoad[0] -> getCol(col) -> getVec(float()).size();            // std::cout << "n: " << n << std::endl;

            std::vector<float*> srcVecs(this -> toLoad.size());
            std::vector<float*> dstVecs;
            //temp since it throws compile time errors

            for(unsigned int i = 0; i < srcVecs.size(); i++){
              // DataFrame temp = *(this -> toLoad[i]);

              srcVecs[i] = &(this -> toLoad[i] -> getCol(col) -> getVec(float()))[0];
              if(this -> modifiedDF.find(this -> toLoad[i]) != this -> modifiedDF.end()){
                dstVecs.push_back(&(this -> toLoad[i] -> getCol(col) -> getVec(float()))[0]);
              }
            }

            runGeneratedKernel(this -> getKernel("float"),
                srcVecs,
                dstVecs,
                n,
                std::vector<float*>({NULL, NULL, NULL, NULL})
                );
        }

    }


    // make it the smallest
    this -> toLoad.clear();
    this -> genNames.clear();
    this -> mapping.clear();
    this -> modifiedDF.clear();
    this -> Kernel.clear();
}

void Session::clear(){
  this -> toLoad.clear();
  this -> genNames.clear();
  this -> mapping.clear();
  this -> modifiedDF.clear(); 
  this -> Kernel.clear();
}