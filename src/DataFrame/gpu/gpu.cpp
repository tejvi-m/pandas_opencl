#include "gpu.h"
#include <cmath>
#include <fstream>

extern GPU gpu;


void setup(){
    std::ifstream in("./src/DataFrame/gpu/src.cl");
    if(!in.is_open()) throw std::runtime_error("Could not open file");

    gpu.localSize = 64;

    std::string contents((std::istreambuf_iterator<char>(in)),
                        std::istreambuf_iterator<char>());

    gpu.err = clGetPlatformIDs(1, &gpu.cpPlatform, NULL);

    gpu.err = clGetDeviceIDs(gpu.cpPlatform, CL_DEVICE_TYPE_GPU, 1, &gpu.device_id, NULL);

    gpu.context = clCreateContext(0, 1, &gpu.device_id, NULL, NULL, &gpu.err);

    gpu.queue = clCreateCommandQueue(gpu.context, &(*gpu.device_id), 0, &gpu.err);

    gpu.program = clCreateProgramWithSource(gpu.context, 1,
                            (const char **) & contents, NULL, &gpu.err);

    clBuildProgram(gpu.program, 0, NULL, NULL, NULL, NULL);

    gpu.use_gpu = true;
}


/*
Model 1: use
read: false
hostptrs: src1, src2, src1
flags: use

Model 0:
read: true
hostptrs: NULL
flags: read only, write only

Model 2: alloc
read: true
hostptrs: NULL
flags: alloc host ptr for both


model 4: copy
read: false
hostptrs: src1, src2, NULL
flags: CL_MEM_ALLOC_HOST_PTR | CL_MEM_COPY_HOST_PTR, CL_MEM_ALLOC_HOST_PTR
*/

template<typename T>
void gpuArithmetic(std::string operation, T* src1, T* src2, T* dst, int n, bool read = true, void* hostPtr1 = NULL, void* hostPtr2 = NULL, void* hostPtr3 = NULL, cl_mem_flags memFlagsSrc = CL_MEM_READ_ONLY, cl_mem_flags memFlagsDst = CL_MEM_WRITE_ONLY){

  cl_mem d_a;
  cl_mem d_b;
  cl_mem d_c;

  // setup();

  cl_kernel kernel;

  std::cout << "running on gpu: "<< operation << std::endl;
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
  // clReleaseProgram(gpu.program);
  clReleaseKernel(kernel);
  // clReleaseCommandQueue(gpu.queue);
  // clReleaseContext(gpu.context);
}

template<typename T>
void runGeneratedKernel(std::string Kernel, T* src1, T* src2,
                T* dst1, T* dst2,
                int n,
                bool read = true,
                void* hostPtr1 = NULL,
                void* hostPtr2 = NULL,
                void* hostPtr3 = NULL,
                void* hostPtr4 = NULL,
                cl_mem_flags memFlagsSrc = CL_MEM_READ_ONLY,
                cl_mem_flags memFlagsDst = CL_MEM_WRITE_ONLY){

  cl_mem d_a;
  cl_mem d_b;
  cl_mem d_c;
  cl_mem d_d;

  // setup();

  cl_kernel kernel;

  std::cout << "running on gpu: "<< std::endl;
  size_t bytes = n * sizeof(T);

  gpu.program = clCreateProgramWithSource(gpu.context, 1,
                              (const char **) & Kernel, NULL, &gpu.err);

  std::string k= "genKernel";
  kernel = clCreateKernel(gpu.program, "genKernel" , &gpu.err);
  gpu.globalSize = ceil(n/(float)gpu.localSize)*gpu.localSize;

  d_a = clCreateBuffer(gpu.context, memFlagsSrc, bytes, hostPtr1, NULL);
  d_b = clCreateBuffer(gpu.context, memFlagsSrc, bytes, hostPtr2, NULL);
  d_c = clCreateBuffer(gpu.context, memFlagsDst , bytes, hostPtr3, NULL);
  d_d = clCreateBuffer(gpu.context, memFlagsDst , bytes, hostPtr3, NULL);

  gpu.err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_a);
  gpu.err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_b);
  gpu.err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_c);
  gpu.err |= clSetKernelArg(kernel, 3, sizeof(cl_mem), &d_d);
  gpu.err |= clSetKernelArg(kernel, 4, sizeof(unsigned int), &n);

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
                              bytes, dst1, 0, NULL, NULL );

  clEnqueueReadBuffer(gpu.queue, d_d, CL_TRUE, 0,
                              bytes, dst2, 0, NULL, NULL );

  clReleaseMemObject(d_a);
  clReleaseMemObject(d_b);
  clReleaseMemObject(d_c);
  clReleaseMemObject(d_d);
  // clReleaseProgram(gpu.program);
  clReleaseKernel(kernel);
  // clReleaseCommandQueue(gpu.queue);
  // clReleaseContext(gpu.context);
}
