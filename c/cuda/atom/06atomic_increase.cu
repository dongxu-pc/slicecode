/*************************************************************************
	> File Name: 05_0304.cu
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月30日 星期三 13时37分15秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cuda_runtime.h>
#include <cuda.h>

const int gridSize=50,blockSize=1024;
cudaError_t addWithCuda(int *sum);

__global__ void addKernel(int *sum,int *timestamp)
{
	int i = blockIdx.x*blockDim.x +threadIdx.x + 1;
	sum[i] = atomicAdd(timestamp,1);
}

int main()
{
	int sum = 1;
	cudaError_t cudaStatus;
	int num = 0;
	cudaDeviceProp prop;

	cudaStatus = cudaGetDeviceCount(&num);
	for(int i = 0;i<num;i++)
	{
		cudaGetDeviceProperties(&prop,i);
	}
	cudaStatus = addWithCuda(&sum);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "addWithCuda failed!");
		return 1;
	}

	printf("Final sum=%d\n",sum);
	cudaStatus = cudaThreadExit();
	if (cudaStatus != cudaSuccess) 
	{
		fprintf(stderr, "cudaThreadExit failed!");
		return 1;
	}
	return 0;
}

cudaError_t addWithCuda(int *timestamp)
{
	int *dev_sum;
	int *dev_timestamp = 0;
	cudaError_t cudaStatus;
	cudaStatus = cudaSetDevice(0);
	int sum[gridsize*blocksize];

	cudaEvent_t start,stop;
	float elapsedtime;

	clock_t cust,cufin;
	clock_t st,fin;

	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");  
		goto Error; 
	}

	cudaStatus = cudaMalloc((void**)&dev_timestamp, sizeof(int));
	cudaStatus = cudaMalloc((void**)&dev_sum,sizeof(int)*gridSize*blockSize);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc failed!"); 
		goto Error;
	}

	cudaStatus = cudaMemcpy(dev_timestamp,timestamp,sizeof(int), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy failed!"); 
		goto Error;
	}

	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	printf("addKernel<<<%d,%d>>>(%d)\n",gridSize,blockSize,*sum);
	cudaEventRecord(start,0);
	atomic_inc_Kernel<<<gridSize,blockSize>>>(dev_timestamp);
    cudaStatus = cudaThreadSynchronize();
	cudaEventRecord(stop,0);

	cudaEventSynchronize(start);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedtime,start,stop);
	printf("Cuda Execute time:%f (ms)\n",elapsedtime);
	cudaStatus = cudaMemcpy(timestamp,dev_timestamp,sizeof(int),cudaMemcpyDeviceToHost);
	cudaStatus = cudaMemcpy(sum,dev_sum,sizeof(int)*gridSize*blockSize,cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess){
		fprintf(stderr, "cudaMemcpy failed!"); 
		goto Error;
	};

	printf("host sum=%d\n",*timestamp);

	cudaEventDestroy(start);
	cudaEventDestory(stop);

Error:
	cudaFree(dev_sum);
	return cudaStatus;
}


