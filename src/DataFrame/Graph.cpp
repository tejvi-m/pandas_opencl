#pragma once
#include "Graph.h"
#include "gpu/gpu.cpp"
#include <string>
#include <cstring>
#include <unordered_map>

extern Graph* _graph;

Graph::Graph(){
  _graph = this;
}

void Graph::addDF(DataFrame* DF){
  if(mapping.find(DF) == mapping.end()){
    this -> toLoad.push_back(DF);
    std::string oldName;
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

std::string Graph::getGenName(DataFrame* DF, int f = 0){
  if(this -> modifiedDF.find(DF) == modifiedDF.end() || f) return this -> mapping[DF];
  else return this -> mapping[DF] + "_copy";
}

void Graph::insertOperation(std::string operation, DataFrame* DF){

}

void Graph::insertOperation(std::string operation, DataFrame* DF1, DataFrame* DF2){
  std::unordered_map<std::string, char> operationSymbol({
    {"add", '+'},
    {"sub", '-'},
    {"mul", '*'},
    {"div", '/'}
  });

  this -> addDF(DF1);
  this -> addDF(DF2);
  //first DF is the one that gets updated.
  std::string newOp;
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
void Graph::insertOperation(std::string operation, DataFrame* DF1, T constant){
  std::unordered_map<std::string, char> operationSymbol({
    {"add", '+'},
    {"sub", '-'},
    {"mul", '*'},
    {"div", '/'}
  });
  //first DF is the one that gets updated.
  this -> addDF(DF1);
  std::string newOp;
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

std::string Graph::getKernel(std::string dtype){

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


void Graph::compute(){
  this -> compute_with_model(0);
}

void Graph::compute_with_model(int model = 0){

    for(int col = 0; col < (this -> toLoad[0]) -> shape().first; col++){
        DataFrame temp = *(this -> toLoad[0]);
        int n = temp[0] -> getVec(0).size();

        vTypes x = (temp[col]) -> type();
        if(std::holds_alternative<int>(x)){
          DataFrame temp = *(this -> toLoad[0]);
          int n = temp[0] -> getVec(int()).size();

          std::vector<int*> srcVecs(this -> toLoad.size());
          std::vector<int*> dstVecs;
          //temp since it throws compile time errors

          for(int i = 0; i < srcVecs.size(); i++){
            DataFrame temp = *(this -> toLoad[i]);

            srcVecs[i] = &(temp[col] -> getVec(int()))[0];
            if(this -> modifiedDF.find(this -> toLoad[i]) != this -> modifiedDF.end()){
              dstVecs.push_back(&(temp[col] -> getVec(int()))[0]);
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
            DataFrame temp = *(this -> toLoad[0]);
            int n = temp[0] -> getVec(float()).size();

            std::vector<float*> srcVecs(this -> toLoad.size());
            std::vector<float*> dstVecs;
            //temp since it throws compile time errors

            for(int i = 0; i < srcVecs.size(); i++){
              DataFrame temp = *(this -> toLoad[i]);

              srcVecs[i] = &(temp[col] -> getVec(float()))[0];
              if(this -> modifiedDF.find(this -> toLoad[i]) != this -> modifiedDF.end()){
                dstVecs.push_back(&(temp[col] -> getVec(float()))[0]);
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
}
