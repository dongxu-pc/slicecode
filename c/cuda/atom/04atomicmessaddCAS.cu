/*************************************************************************
	> File Name: 05_0304.cu
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月30日 星期三 13时37分15秒
 ************************************************************************/

#include <stdio.h>
#include <cuda_runtime.h>

const int gridSize=7,blockSize=1;
cudaError_t addWithCuda(int *sum);

__global__ void addKernel(int *sum)
{
	int i = blockIdx.x*blockDim.x +threadIdx.x;
	int j=0;
	int tsum = 1;
	//atomicAdd(sum,i);
	//tsum = *tsum + i;
	//atomicCAS(sum,tsum,*sum);
	for(j=0;j<i;j++)
		tsum *=10; 
	for(j=0;j<tsum;j++);
	atomicAdd(sum,i);
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

cudaError_t addWithCuda(int *sum)
{
	int *dev_sum = 0;
	cudaError_t cudaStatus;
	cudaStatus = cudaSetDevice(0);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");  
		goto Error; 
	}

	cudaStatus = cudaMalloc((void**)&dev_sum, sizeof(int));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc failed!"); 
		goto Error;
	}

	cudaStatus = cudaMemcpy(dev_sum,sum,sizeof(int), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy failed!"); 
		goto Error;
	}

	printf("addKernel<<<%d,%d>>>(%d)\n",gridSize,blockSize,*sum);
	addKernel<<<gridSize,blockSize>>>(dev_sum);
    cudaStatus = cudaThreadSynchronize();
	cudaStatus = cudaMemcpy(sum,dev_sum,sizeof(int),cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy failed!"); 
		goto Error;
	}

Error:
	cudaFree(dev_sum);
	return cudaStatus;
}


