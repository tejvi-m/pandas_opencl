#include <CL/opencl.h>
#include <cmath>
SeriesInt::SeriesInt(): size_(0){};

int gpu = 1;
SeriesInt::SeriesInt(std::vector<int> data): series_(data), size_(data.size()){};

std::vector<int>& SeriesInt::getVec(int){
  return this -> series_;
}

long int SeriesInt::size(){
  return this -> size_;
}

void SeriesInt::show(){
  print<int>(this -> series_);
}

void SeriesInt::Index(){
  make_map<int>(this -> series_, this -> index_);
}

vTypes SeriesInt::operator[](int i){
  return this -> series_[i];
}

Series* SeriesInt::operator+(Series* src2){
  Series* dst = new SeriesInt(std::vector<int>(src2 -> getVec(0).size()));
  Add<int>(this -> getVec(0), src2 -> getVec(0), dst -> getVec(0));
  return dst;
}

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
                                                                "\n" ;


void gpu_add(int* array, int* array1,  int n){
  // Length of vectors


  // Device input buffers
  cl_mem d_a;
  cl_mem d_b;
  // Device output buffer
  cl_mem d_c;


  cl_platform_id cpPlatform;        // OpenCL platform

  cl_device_id device_id;           // device ID
  cl_context context;               // context
  cl_command_queue queue;           // command queue
  cl_program program;               // program
  cl_kernel kernel;                 // kernel


  // Size, in bytes, of each vector
  size_t bytes = n*sizeof(int);


  size_t globalSize, localSize;
  cl_int err;

  std::cout << "in gpu \n";

  // Number of work items in each local work group
  localSize = 64;

  // Number of total work items - localSize must be devisor
  globalSize = ceil(n/(float)localSize)*localSize;

  // Bind to platform
  err = clGetPlatformIDs(1, &cpPlatform, NULL);

  // Get ID for the device
  err = clGetDeviceIDs(cpPlatform, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);

  // Create a context
  context = clCreateContext(0, 1, &device_id, NULL, NULL, &err);

  // Create a command queue
  queue = clCreateCommandQueue(context, device_id, 0, &err);

  // Create the compute program from the source buffer
  program = clCreateProgramWithSource(context, 1,
                          (const char **) & kernelSource, NULL, &err);
  // Build the program executable
  clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
 // Create the compute kernel in the program we wish to run
  kernel = clCreateKernel(program, "vecAdd", &err);

  // Create the input and output arrays in device memory for our calculation
  d_a = clCreateBuffer(context, CL_MEM_READ_ONLY, bytes, NULL, NULL);
  d_b = clCreateBuffer(context, CL_MEM_READ_ONLY, bytes, NULL, NULL);
  d_c = clCreateBuffer(context, CL_MEM_WRITE_ONLY, bytes, NULL, NULL);

  // Write our data set into the input array in device memory
  err = clEnqueueWriteBuffer(queue, d_a, CL_TRUE, 0,
                                 bytes, array, 0, NULL, NULL);
  err |= clEnqueueWriteBuffer(queue, d_b, CL_TRUE, 0,
                                 bytes, array1, 0, NULL, NULL);

  // Set the arguments to our compute kernel
  err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_a);
  err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_b);
  err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_c);
  err |= clSetKernelArg(kernel, 3, sizeof(unsigned int), &n);

  // Execute the kernel over the entire range of the data set
  err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, &localSize,
                                                            0, NULL, NULL);

  // Wait for the command queue to get serviced before reading back results
  clFinish(queue);

  // Read the results from the device
  clEnqueueReadBuffer(queue, d_c, CL_TRUE, 0,
                              bytes, array, 0, NULL, NULL );

  //Sum up vector c and print result divided by n, this should equal 1 within error
  // release OpenCL resources
  clReleaseMemObject(d_a);
  clReleaseMemObject(d_b);
  clReleaseMemObject(d_c);
  clReleaseProgram(program);
  clReleaseKernel(kernel);
  clReleaseCommandQueue(queue);
  clReleaseContext(context);



}

void SeriesInt::add(Series* src){
  if(gpu){
    gpu_add(&(this -> getVec(int())[0]), &(src -> getVec(int())[0]), this -> getVec(int()).size());
  }
  else
    Add<int>(this -> getVec(int()), src -> getVec(int()), this -> getVec(int()));
}

SeriesInt SeriesInt::operator+(Series& src2){
  SeriesInt dst(std::vector<int>(src2.getVec(0).size()));
  Add<int>(this -> getVec(0), src2.getVec(0), dst.getVec(0));
  return dst;
}

Series* SeriesInt::operator*(Series* src2){
  Series* dst = new SeriesInt(std::vector<int>(src2 -> getVec(0).size()));
  Mul<int>(this -> getVec(0), src2 -> getVec(0), dst -> getVec(0));
  return dst;
}

void SeriesInt::mul(Series* src2, Series* dst){
  Mul<int>(this -> getVec(0), src2 -> getVec(0), dst -> getVec(0));
}

void SeriesInt::mul(Series* src2){
  Mul<int>(this -> getVec(0), src2 -> getVec(0), this -> getVec(0));
}

void SeriesInt::div(Series* src2){
  Div<int>(this -> getVec(0), src2 -> getVec(0), this -> getVec(0));
}

void SeriesInt::sub(Series* src2){
  Sub<int>(this -> getVec(0), src2 -> getVec(0), this -> getVec(0));
}


Series* SeriesInt::copy(){
  Series* dst = new SeriesInt(std::vector<int>(this -> getVec(int())));
  return dst;
}

void SeriesInt::map(std::unordered_map<int, int> umap){
  MapOp(this -> getVec(int()), umap);
}

int SeriesInt::index(int i){

  std::cout <<  "req: " << i;
  if(this -> index_.find(i) != this -> index_.end()){
    std::cout << "found";
    return this -> index_[i];
  }
  return -1;
}

Series* SeriesInt::append(int ele){
  series_.push_back(ele);
  size_++;
  return this;
}

bool SeriesInt::isArithmetic(){
  return true;
}

template<typename T>
void SeriesInt::transform(T&& Fn){
  for_each(this -> getVec(int()).begin(), this -> getVec(int()).end(), Fn);
}


vTypes SeriesInt::type(){
  return int();
}

template<typename R = int, typename F>
R SeriesInt::apply(F&& Fn){
    return Fn(this -> getVec(0));
}
