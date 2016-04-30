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

__global__ void addKernel(int *sum)
{
	int i = blockIdx.x*blockDim.x +threadIdx.x + 1;
	//int j=0;
	//int tsum = 1;
	atomicAdd(sum,i);
	//tsum = *tsum + i;
	//atomicCAS(sum,tsum,*sum);
	//for(j=0;j<i;j++)
	//	tsum *=10; 
	//for(j=0;j<tsum;j++);
	//atomicAdd(sum,i);
}

void add(int *sum,int n)
{
	while(n>0)
	{
		*sum+=n;
		n--;
	}
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

	cudaEvent_t start,stop;
	float elapsedtime;

	clock_t cust,cufin;
	clock_t st,fin;

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

	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	printf("addKernel<<<%d,%d>>>(%d)\n",gridSize,blockSize,*sum);
	cudaEventRecord(start,0);
	cust = clock();
	addKernel<<<gridSize,blockSize>>>(dev_sum);
    cudaStatus = cudaThreadSynchronize();
	cufin = clock();
	cudaEventRecord(stop,0);

	cudaEventSynchronize(start);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedtime,start,stop);
	printf("Cuda Execute time:%f (ms)\n",elapsedtime);
	elapsedtime = (float)(cufin-cust)*100/CLOCKS_PER_SEC;
	printf("Ho cuda Execute time:%f (ms)\n",elapsedtime);
	cudaStatus = cudaMemcpy(sum,dev_sum,sizeof(int),cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess){
		fprintf(stderr, "cudaMemcpy failed!"); 
		goto Error;
	};

	printf("cuda sum=%d\n",*sum);
	*sum = 1;

	st = clock();
	add(sum,gridSize*blockSize);
	fin = clock();
	elapsedtime = (float)(fin-st)*100/CLOCKS_PER_SEC;
	printf("Host Execute time:%f (ms)\n",elapsedtime);
	printf("host sum=%d\n",*sum);

//	cudaEventDestroy(start);
//	cudaEventDestory(stop);

Error:
	cudaFree(dev_sum);
	return cudaStatus;
}


