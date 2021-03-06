/*************************************************************************
	> File Name: 06streampalladd.cu
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月30日 星期三 15时24分54秒
 ************************************************************************/

#include <stdio.h>
#include <cuda_runtime.h>
#include "device_launch_parameters.h"

cudaError_t addWithCuda(int *c, const int *a, const int *b, size_t size);
__global__ void addKernel(int *c, const int *a, const int *b)
{
    int i = blockIdx.x;
    c[i] = a[i] + b[i];
}
__global__ void mulKernel(int *c, const int *a, const int *b)
{
    int i = blockIdx.x;
    c[i] = a[i] - b[i];
}
int main()
{
    const int arraySize = 5;
    const int a[arraySize] = { 1, 2, 3, 4, 5 };
    const int b[arraySize] = { 10, 20, 30, 40, 50 };
    int c[arraySize] = { 0 };
    // Add vectors in parallel.
    cudaError_t cudaStatus;
	int num = 0;
	cudaDeviceProp prop;
	cudaStatus = cudaGetDeviceCount(&num);
	for(int i = 0;i<num;i++)
	{
		cudaGetDeviceProperties(&prop,i);
	}
	cudaStatus = addWithCuda(c, a, b, arraySize);
    if (cudaStatus != cudaSuccess) 
	{
        fprintf(stderr, "addWithCuda failed!");
        return 1;
    }
    printf("{1,2,3,4,5} + {10,20,30,40,50} = {%d,%d,%d,%d,%d}\n",c[0],c[1],c[2],c[3],c[4]);
    // cudaThreadExit must be called before exiting in order for profiling and
    // tracing tools such as Nsight and Visual Profiler to show complete traces.
    cudaStatus = cudaThreadExit();
    if (cudaStatus != cudaSuccess) 
	{
        fprintf(stderr, "cudaThreadExit failed!");
        return 1;
    }
    return 0;
}
// Helper function for using CUDA to add vectors in parallel.
cudaError_t addWithCuda(int *c, const int *a, const int *b, size_t size)
{
    int *dev_a = 0;
    int *dev_b = 0;
    int *dev_c = 0;
    cudaError_t cudaStatus;

    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) 
	{
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }
    // Allocate GPU buffers for three vectors (two input, one output)    .
    cudaStatus = cudaMalloc((void**)&dev_c, size * sizeof(int));
    if (cudaStatus != cudaSuccess) 
	{
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }
    cudaStatus = cudaMalloc((void**)&dev_a, size * sizeof(int));
    if (cudaStatus != cudaSuccess) 
	{
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }
    cudaStatus = cudaMalloc((void**)&dev_b, size * sizeof(int));
    if (cudaStatus != cudaSuccess) 
	{
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }
    // Copy input vectors from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(dev_a, a, size * sizeof(int), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) 
	{
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }
    cudaStatus = cudaMemcpy(dev_b, b, size * sizeof(int), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) 
	{
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }
	cudaStream_t stream[5];
	for(int i = 0;i<5;i++)
	{
		cudaStreamCreate(&stream[i]);	//创建流
	}
    // Launch a kernel on the GPU with one thread for each element.
	for(int i = 0;i<4;i++)
	{
		addKernel<<<1,1,0,stream[i]>>>(dev_c+i, dev_a+i, dev_b+i);	//执行流
	}
	mulKernel<<<1,1,0,stream[4]>>>(dev_c+4,dev_a+4,dev_b+4);
	cudaDeviceSynchronize();
    // cudaThreadSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaThreadSynchronize();
    if (cudaStatus != cudaSuccess) 
	{
        fprintf(stderr, "cudaThreadSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
        goto Error;
    }
    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(c, dev_c, size * sizeof(int), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) 
	{
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }
Error:
	for(int i = 0;i<5;i++)
	{
		cudaStreamDestroy(stream[i]);	//销毁流
	}

    cudaFree(dev_c);
    cudaFree(dev_a);
    cudaFree(dev_b);    
    return cudaStatus;
}

