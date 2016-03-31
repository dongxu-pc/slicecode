/*************************************************************************
	> File Name: 05_0304.cu
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月30日 星期三 13时37分15秒
 ************************************************************************/

#include <stdio.h>
#include <cuda_runtime.h>

cudaError_t addWithCuda(int *c, const int *a);

__global__ void addKernel(int *c, const int *a)
{
	int i = blockIdx.x;
	*c = *a + i;
	printf("thread %d:a=%d,c=%d\n",i,*a,*c);
}

int main()
{
	int a = 1;
	int c = 0;
	cudaError_t cudaStatus;
	int num = 0;
	cudaDeviceProp prop;

	cudaStatus = cudaGetDeviceCount(&num);
	for(int i = 0;i<num;i++)
	{
		cudaGetDeviceProperties(&prop,i);
	}
	cudaStatus = addWithCuda(&c, &a);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "addWithCuda failed!");
		return 1;
	}

	printf("a=%d,c=%d\n",a,c);
	cudaStatus = cudaThreadExit();
	if (cudaStatus != cudaSuccess) 
	{
		fprintf(stderr, "cudaThreadExit failed!");
		return 1;
	}
	return 0;
}

cudaError_t addWithCuda(int *c, const int *a)
{
	int *dev_a = 0;
	int *dev_c = 0;
	cudaError_t cudaStatus;
	cudaStatus = cudaSetDevice(0);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");  
		goto Error; 
	}

	cudaStatus = cudaMalloc((void**)&dev_c, sizeof(int));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc failed!"); 
		goto Error;
	}
	cudaStatus = cudaMalloc((void**)&dev_a, sizeof(int));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc failed!"); 
		goto Error;
	}

	cudaStatus = cudaMemcpy(dev_a, a,sizeof(int), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy failed!"); 
		goto Error;
	}

	cudaStatus = cudaMemcpy(dev_c, c,sizeof(int), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy failed!"); 
		goto Error;
	}

	printf("addKernel<<<7,1>>>(%d,%d)\n",*a,*c);
	addKernel<<<7,1>>>(dev_c,dev_a);
 //   cudaStatus = cudaThreadSynchronize();
	cudaStatus = cudaMemcpy(c, dev_c,sizeof(int), cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy failed!"); 
		goto Error;
	}
	printf("The anwser:%d\n",*c);

	printf("addKernel<<<1,7>>>(%d,%d)\n",*a,*c);
	addKernel<<<1,7>>>(dev_c,dev_a);

    cudaStatus = cudaThreadSynchronize();
	cudaStatus = cudaMemcpy(c, dev_c,sizeof(int), cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy failed!"); 
		goto Error;
	}
	printf("The anwser:%d\n",*c);

Error:
	cudaFree(dev_c);
	cudaFree(dev_a);
	return cudaStatus;

}


