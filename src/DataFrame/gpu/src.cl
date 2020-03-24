__kernel void vecAddInt(  __global int *a,
                       __global int *b,
                       __global int *c,
                       const unsigned int n){
    int id = get_global_id(0);

    if (id < n)
        c[id] = a[id] + b[id];
}

__kernel void vecSub(  __global float *a,
                       __global float *b,
                       __global float *c,
                       const unsigned int n){
    int id = get_global_id(0);

    if (id < n)
        c[id] = a[id] - b[id];
}

__kernel void vecDiv(  __global int *a,
                       __global int *b,
                       __global int *c,
                       const unsigned int n){
    int id = get_global_id(0);

    if (id < n)
        c[id] = a[id] / b[id];
}


__kernel void vecMul(  __global int *a,
                       __global int *b,
                       __global int *c,
                       const unsigned int n){

    int id = get_global_id(0);

    if (id < n)
        c[id] = a[id] * b[id];
}
                                                                 ;
