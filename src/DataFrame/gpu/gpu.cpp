#include "gpu.h"

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
void gpuArithmetic(std::string operation, std::vector<T>& src1, std::vector<T>& src2, std::vector<T>& dst, cl_mem_flags memFlags){}
