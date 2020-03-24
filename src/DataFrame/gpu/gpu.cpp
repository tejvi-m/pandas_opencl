#include "gpu.h"
#include <cmath>
extern GPU gpu;
const char *kernelSource =                                       "\n" \
"                 \n" \
"__kernel void vecAdd(  __global double *a,                       \n" \
"                       __global double *b,  __global double *c,           \n" \
"                       const unsigned int n)                    \n" \
"{                                                               \n" \
"    //Get our global thread ID                                  \n" \
"    int id = get_global_id(0);                                  \n" \
"                                                                \n" \
"    //Make sure we do not go out of bounds                      \n" \
"    if (id < n)                                                 \n" \
"        c[id] = a[id] + b[id];                                  \n" \
"}                                                               \n" \
"__kernel void vecSub(  __global float *a,                       \n" \
"                       __global float *b,  __global float *c,           \n" \
"                       const unsigned int n)                    \n" \
"{                                                               \n" \
"    //Get our global thread ID                                  \n" \
"    int id = get_global_id(0);                                  \n" \
"                                                                \n" \
"    //Make sure we do not go out of bounds                      \n" \
"    if (id < n)                                                 \n" \
"        c[id] = a[id] - b[id];                                  \n" \
"}                                                               \n" \
"__kernel void vecDiv(  __global int *a,                       \n" \
"                       __global int *b,  __global int *c,           \n" \
"                       const unsigned int n)                    \n" \
"{                                                               \n" \
"    //Get our global thread ID                                  \n" \
"    int id = get_global_id(0);                                  \n" \
"                                                                \n" \
"    //Make sure we do not go out of bounds                      \n" \
"    if (id < n)                                                 \n" \
"        c[id] = a[id] / b[id];                                  \n" \
"}                                                               \n" \
"__kernel void vecMul(  __global int *a,                       \n" \
"                       __global int *b,  __global int *c,           \n" \
"                       const unsigned int n)                    \n" \
"{                                                               \n" \
"    //Get our global thread ID                                  \n" \
"    int id = get_global_id(0);                                  \n" \
"                                                                \n" \
"    //Make sure we do not go out of bounds                      \n" \
"    if (id < n)                                                 \n" \
"        c[id] = a[id] * b[id];                                  \n" \
"}                                                               \n" \
                                                                "\n" ;


void setup(){
    gpu.localSize = 512;
    // gpu.globalSize = ceil(n/(float)localSize)*localSize;
    gpu.err = clGetPlatformIDs(1, &gpu.cpPlatform, NULL);
    gpu.err = clGetDeviceIDs(gpu.cpPlatform, CL_DEVICE_TYPE_GPU, 1, &gpu.device_id, NULL);
    gpu.context = clCreateContext(0, 1, &gpu.device_id, NULL, NULL, &gpu.err);
    gpu.queue = clCreateCommandQueue(gpu.context, &(*gpu.device_id), 0, &gpu.err);
    gpu.program = clCreateProgramWithSource(gpu.context, 1,
                            (const char **) & kernelSource, NULL, &gpu.err);
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
