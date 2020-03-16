__kernel void square(__global int * data, __global int * data2, __global int * dest, const unsigned int n) {
    int id = get_global_id(0);
    if(id < n) dest[id] = data2[id] + data[id];
}
