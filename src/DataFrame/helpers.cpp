#include "helpers.h"
// #include "gpu/gpu.cpp"

template<typename T>
void redirectToGPU(std::string operation, std::vector<T>& src1, std::vector<T>& src2, std::vector<T>& dst, int model){
  if(model == 1){
    // use
    gpuArithmetic(operation, &(src1[0]), &(src2[0]), &(dst[0]),
                src1.size(), false,
                 &(src1[0]),
                 &(src2[0]),
                 &(dst[0]) ,
                 CL_MEM_USE_HOST_PTR,  CL_MEM_USE_HOST_PTR);
  }
  else if(model == 2){
    //alloc
    gpuArithmetic(operation, &(src1[0]), &(src2[0]), &(dst[0]),
                src1.size(), true, NULL, NULL, NULL,
                CL_MEM_ALLOC_HOST_PTR,  CL_MEM_ALLOC_HOST_PTR);
  }
  else if(model == 3){
    //copy
    gpuArithmetic(operation, &(src1[0]), &(src2[0]), &(dst[0]),
                src1.size(), true, NULL, NULL, NULL,
                 CL_MEM_READ_ONLY,  CL_MEM_WRITE_ONLY);
  }
  else{
    // read_write, default
    gpuArithmetic(operation, &(src1[0]), &(src2[0]), &(dst[0]),
                src1.size(), false,
                &(src1[0]),
                &(src2[0]),
                NULL,
                CL_MEM_ALLOC_HOST_PTR | CL_MEM_COPY_HOST_PTR,
                CL_MEM_ALLOC_HOST_PTR);
  }
}

template<typename T>
void redirectToGPUGen(std::string Kernel, std::vector<T>& src1, std::vector<T>& src2, std::vector<T>& dst1, std::vector<T>& dst2, int model = 1){
  if(model == 1){
    // use
    runGeneratedKernel(Kernel, &(src1[0]), &(src2[0]), &(dst1[0]), &(dst2[0]),
                src1.size(), false,
                 &(src1[0]),
                 &(src2[0]),
                 &(dst1[0]),
                 &(dst2[0]),
                 CL_MEM_USE_HOST_PTR,  CL_MEM_USE_HOST_PTR);
  }
  else if(model == 2){
    //alloc
    runGeneratedKernel(Kernel, &(src1[0]), &(src2[0]), &(dst1[0]), &(dst2[0]),
                src1.size(), true, NULL, NULL, NULL,
                CL_MEM_ALLOC_HOST_PTR,  CL_MEM_ALLOC_HOST_PTR);
  }
  else if(model == 3){
    //copy
    runGeneratedKernel(Kernel, &(src1[0]), &(src2[0]), &(dst1[0]), &(dst2[0]),
                src1.size(), true, NULL, NULL, NULL,
                 CL_MEM_READ_ONLY,  CL_MEM_WRITE_ONLY);
  }
  else{
    // read_write, default
    runGeneratedKernel(Kernel, &(src1[0]), &(src2[0]), &(dst1[0]), &(dst2[0]),
                src1.size(), false,
                &(src1[0]),
                &(src2[0]),
                NULL,
                NULL,
                CL_MEM_ALLOC_HOST_PTR | CL_MEM_COPY_HOST_PTR,
                CL_MEM_ALLOC_HOST_PTR);
  }
}

template <typename T>
void Add(std::vector<T>& src1, std::vector<T>& src2, std::vector<T>& dst){

    for(int i = 0; i < src1.size(); i++){
      dst[i] = src1[i] + src2[i];
    }
}

template<typename T>
void Mul(std::vector<T>& src1, std::vector<T>& src2, std::vector<T>& dst){
  for(int i = 0; i < src1.size(); i++){
    dst[i] = src1[i] * src2[i];
  }
}


template<typename T>
void Div(std::vector<T>& src1, std::vector<T>& src2, std::vector<T>& dst){
  for(int i = 0; i < src1.size(); i++){
    dst[i] = src1[i] / src2[i];
  }
}


template<typename T>
void Sub(std::vector<T>& src1, std::vector<T>& src2, std::vector<T>& dst){
  for(int i = 0; i < src1.size(); i++){
    dst[i] = src1[i] - src2[i];
  }
}


template<typename T>
void Mod(std::vector<T>& src1, std::vector<T>& src2, std::vector<T>& dst){
  for(int i = 0; i < src1.size(); i++){
    dst[i] = src1[i] - src2[i];
  }
}

template<typename T>
void MapOp(std::vector<T>& vec, std::unordered_map<T, T>& umap){
  for(int i = 0; i < vec.size(); i++){
    auto replaced = umap.find(vec[i]);
    if(replaced != umap.end()) vec[i] = (*replaced).second;
    // no change if no mapping found
  }
}

template <typename T>
void print(std::vector<T>& data){
  for(int i = 0; i < data.size(); i++){
    std::cout << data[i] << " ";
  }
  std::cout << std::endl;
}

template <typename T>
void make_map(std::vector<T>& data, std::unordered_map<T, int>& umap){
  for(int i = 0; i < data.size(); i++){
    umap[data[i]] = i;
  }
}

void printRow(Row data){

  auto lambdaPrintVisitor = [](auto&& _in){std::cout << _in;};
  for (const auto& nextVariant : data){
          std::visit(lambdaPrintVisitor, nextVariant);
          std::cout << " ";
      }
  std::cout << std::endl;
}

template<typename T, typename F>
void Apply(std::vector<T>& vec, F&& fn){
  for_each(vec.begin(), vec.end(), fn);
}
