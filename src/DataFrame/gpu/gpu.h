#include <CL/opencl.h>
#include <string>
#include <vector>

struct GPU{
  cl_platform_id cpPlatform;
  cl_device_id device_id;
  cl_context context;
  cl_command_queue queue;
  cl_program program;
  size_t globalSize, localSize;
  cl_int err;
  bool use_gpu = false;
};

GPU gpu;


void setup();

template<typename T>
void gpuArithmetic(std::string operation, std::vector<T>& src1, std::vector<T>& src2, std::vector<T>& dst, cl_mem_flags memFlags);

template<typename T>
void runGeneratedKernel(std::string Kernel, std::vector<T*> srcVecs,
                std::vector<T*> dstVecs,
                int n,
                std::vector<T*> hostPtrs,
                bool read = true,
                cl_mem_flags memFlagsSrc =   CL_MEM_ALLOC_HOST_PTR,
                cl_mem_flags memFlagsDst = CL_MEM_ALLOC_HOST_PTR);
