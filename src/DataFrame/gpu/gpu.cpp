#include "gpu.h"
#include <cmath>
#include <fstream>

extern GPU gpu;


void setup(){
    gpu.localSize = 512;
    // gpu.globalSize = ceil(n/(float)localSize)*localSize;
    std::ifstream in("./src/DataFrame/gpu/src.cl");
    if(!in.is_open()) throw std::runtime_error("Could not open file");

    std::string contents((std::istreambuf_iterator<char>(in)),
                        std::istreambuf_iterator<char>());
    std::cout << "source" << contents;
    gpu.err = clGetPlatformIDs(1, &gpu.cpPlatform, NULL);
    gpu.err = clGetDeviceIDs(gpu.cpPlatform, CL_DEVICE_TYPE_GPU, 1, &gpu.device_id, NULL);
    gpu.context = clCreateContext(0, 1, &gpu.device_id, NULL, NULL, &gpu.err);
    gpu.queue = clCreateCommandQueue(gpu.context, &(*gpu.device_id), 0, &gpu.err);
    gpu.program = clCreateProgramWithSource(gpu.context, 1,
                            (const char **) & contents, NULL, &gpu.err);
    clBuildProgram(gpu.program, 0, NULL, NULL, NULL, NULL);
}

template<typename T>
void gpuArithmetic(std::string operation, T* src1, T* src2, T* dst, int n, bool read, void* hostPtr1, void* hostPtr2, void* hostPtr3, cl_mem_flags memFlagsSrc, cl_mem_flags memFlagsDst){

  cl_mem d_a;
  cl_mem d_b;
  cl_mem d_c;

  setup();

  cl_kernel kernel;


  size_t bytes = n * sizeof(T);
  kernel = clCreateKernel(gpu.program, operation.c_str() , &gpu.err);
  gpu.globalSize = ceil(n/(float)gpu.localSize)*gpu.localSize;

  d_a = clCreateBuffer(gpu.context, memFlagsSrc, bytes, hostPtr1, NULL);
  d_b = clCreateBuffer(gpu.context, memFlagsSrc, bytes, hostPtr2, NULL);
  d_c = clCreateBuffer(gpu.context, memFlagsDst , bytes, hostPtr3, NULL);

  gpu.err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_a);
  gpu.err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_b);
  gpu.err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_c);
  gpu.err |= clSetKernelArg(kernel, 3, sizeof(unsigned int), &n);

  if(read){
      gpu.err = clEnqueueWriteBuffer(gpu.queue, d_a, CL_TRUE, 0,
                                   bytes, src1, 0, NULL, NULL);
      gpu.err |= clEnqueueWriteBuffer(gpu.queue, d_b, CL_TRUE, 0,
                                    bytes, src2, 0, NULL, NULL);
  }

  gpu.err = clEnqueueNDRangeKernel(gpu.queue, kernel, 1, NULL, &gpu.globalSize, &gpu.localSize,
                                                            0, NULL, NULL);
  clFinish(gpu.queue);

  clEnqueueReadBuffer(gpu.queue, d_c, CL_TRUE, 0,
                              bytes, dst, 0, NULL, NULL );
  clReleaseMemObject(d_a);
  clReleaseMemObject(d_b);
  clReleaseMemObject(d_c);
  clReleaseProgram(gpu.program);
  clReleaseKernel(kernel);
  clReleaseCommandQueue(gpu.queue);
  clReleaseContext(gpu.context);
}
