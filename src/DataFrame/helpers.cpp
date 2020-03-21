#include "helpers.h"
// #include "chlorine.hpp"
// #include "boost/compute.hpp"

// namespace compute = boost::compute;

template <typename T>
void Add(std::vector<T>& src1, std::vector<T>& src2, std::vector<T>& dst){
  //
  // compute::device gpu = compute::system::default_device();
  //
  //    // create a compute context and command queue
  //    compute::context ctx(gpu);
  //    compute::command_queue queue(ctx, gpu);
  //
  //    compute::vector<T> device_vector_src1(src1.size(), ctx);
  //    compute::vector<T> device_vector_src2(src2.size(), ctx);
  //    compute::vector<T> device_vector_dst(dst.size(), ctx);
  //
  //
  //    compute::copy(
  //       src1.begin(), src1.end(), device_vector_src1.begin(), queue
  //   );
  //
  //   compute::copy(
  //       src2.begin(), src2.end(), device_vector_src2.begin(), queue
  //   );
  //
  //   BOOST_COMPUTE_FUNCTION(int, add_four, (int x, int y),
  //     {
  //   return x + y;
  //     });
  //
  //     boost::compute::transform(device_vector_src1.begin(), device_vector_src1.end(), device_vector_src2.begin(), device_vector_src2.end(),output.begin(), add_four, queue);
  //   compute::copy(
  //          device_vector_dst.begin(), device_vector_dst.end(),dst.begin(), queue
  //   );


    for(int i = 0; i < src1.size(); i++){
      std::cout << "adding" << std::endl;
      dst[i] = src1[i] + src2[i];
    }
    // ch::Worker worker("kernel.cl");
    // auto event = worker.call("add", src1, src2, dst, n);
    // std::cout << "Elapsed Time: " << ch::elapsed(event) << "ns\n";
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
