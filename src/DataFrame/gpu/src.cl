__kernel void vecAddInt(  __global int *a,
                       __global int *b,
                       __global int *c,
                       const unsigned int n){
    int id = get_global_id(0);

    if (id < n)
        c[id] = a[id] + b[id];
}

__kernel void vecAddFloat(  __global float *a,
                       __global float *b,
                       __global float *c,
                       const unsigned int n){
    int id = get_global_id(0);

    if (id < n)
        c[id] = a[id] + b[id];
}

__kernel void vecSubtInt(  __global int *a,
                       __global int *b,
                       __global int *c,
                       const unsigned int n){
    int id = get_global_id(0);

    if (id < n)
        c[id] = a[id] - b[id];
}

__kernel void vecSubFloat(  __global float *a,
                       __global float *b,
                       __global float *c,
                       const unsigned int n){
    int id = get_global_id(0);

    if (id < n)
        c[id] = a[id] - b[id];
}

__kernel void vecDivInt(  __global int *a,
                       __global int *b,
                       __global int *c,
                       const unsigned int n){
    int id = get_global_id(0);

    if (id < n)
        c[id] = a[id] / b[id];
}

__kernel void vecDivFloat(  __global float *a,
                       __global float *b,
                       __global float *c,
                       const unsigned int n){
    int id = get_global_id(0);

    if (id < n)
        c[id] = a[id] / b[id];
}

__kernel void vecMulInt(  __global int *a,
                       __global int *b,
                       __global int *c,
                       const unsigned int n){

    int id = get_global_id(0);

    if (id < n)
        c[id] = a[id] * b[id];
}


__kernel void vecMulFloat(  __global float *a,
                       __global float *b,
                       __global float *c,
                       const unsigned int n){

    int id = get_global_id(0);

    if (id < n)
        c[id] = a[id] * b[id];
}
