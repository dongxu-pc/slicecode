/*************************************************************************
	> File Name: 08ifadd.cu
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年04月08日 星期五 10时23分20秒
 ************************************************************************/

#include <stdio.h>
#include <cuda_runtime.h>
#include "my_cuapi.h"

__global__ void ifaddKernel(int* c,const int * a,const int* b)
{
	int j = threadIdx.x;
	int i = threadIdx.x+1;
	if(i > 4)
		c[j]=a[j]+b[j];
	else
		c[j]=a[j]+b[j];
}

int main()
{
	int a[7]={1,2,3,4,5,6,7};
	int b[7]={10,20,30,40,50,60,70};
	int c[7];

	cudaError_t cudaStatus;

	int *dev_a;
	int *dev_b;
	int *dev_c;

	cudaStatus = cudaSetDevice(0);
	if(cudaStatus != cudaSuccess){
		printf("There is no cuda devices.\n");
		exit(0);
	}

	cudaStatus = cudaMalloc((void**)&dev_a,7*sizeof(int));
	HANDLE_ERROR(cudaStatus);
	cudaStatus = cudaMalloc((void**)&dev_b,7*sizeof(int));
	HANDLE_ERROR(cudaStatus);
	cudaStatus = cudaMalloc((void**)&dev_c,7*sizeof(int));
	HANDLE_ERROR(cudaStatus);

	cudaStatus = cudaMemcpy(dev_a,a,7*sizeof(int),cudaMemcpyHostToDevice);
	HANDLE_ERROR(cudaStatus);
	cudaStatus = cudaMemcpy(dev_b,b,7*sizeof(int),cudaMemcpyHostToDevice);
	HANDLE_ERROR(cudaStatus);

	cudaEvent_t start,stop;
	float elaspedtime;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	cudaEventRecord(start,0);
	ifaddKernel<<<1,7>>>(dev_c,dev_a,dev_b);
	cudaEventRecord(stop,0);

	cudaEventSynchronize(start);
	cudaEventSynchronize(stop);

	cudaEventElapsedTime(&elaspedtime,start,stop);

	cudaStatus = cudaMemcpy(c,dev_c,7*sizeof(int),cudaMemcpyDeviceToHost);
	HANDLE_ERROR(cudaStatus);

	cudaEventDestroy(start);
	cudaEventDestroy(stop);
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);

	printf("Execute time:%f (ms)\n",elaspedtime);

	printf("a:");
	showIntArray(a,7);
	printf("\nb:");
	showIntArray(b,7);
	printf("\nc:");
	showIntArray(c,7);
	printf("\n");

	return 0;
}
