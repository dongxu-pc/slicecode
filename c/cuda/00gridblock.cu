/*************************************************************************
	> File Name: 00gridblock.cu
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月30日 星期三 23时27分51秒
 ************************************************************************/

#include <stdio.h>
#include <cuda_runtime.h>

__global__ void showKernel()
{
	int gdimx=gridDim.x;
	int gdimy=gridDim.y;
	int gdimz=gridDim.z;
	int bdimx=blockDim.x;
	int bdimy=blockDim.y;
	int bdimz=blockDim.z;
	int bidxx=blockIdx.x;
	int bidxy=blockIdx.y;
	int bidxz=blockIdx.z;
	int tidxx=threadIdx.x;
	int tidxy=threadIdx.y;
	int tidxz=threadIdx.z;
	int wsize=warpSize;

	printf("gridDim(%d,%d,%d),blockDim(%d,%d,%d)\nblockIdx(%d,%d,%d),threadIdx(%d,%d,%d)\nwarpSize:%d\n",gdimx,gdimy,gdimz,bdimx,bdimy,bdimz,bidxx,bidxy,bidxz,tidxx,tidxy,tidxz,wsize);
}

__global__ void addKernel(int a,int b,int* c)
{
	*c = a+b;
}

int main()
{
	int c;
	int *dev_c;
	cudaMalloc((void**)&dev_c,sizeof(int));
	showKernel<<<5,3>>>();
	addKernel<<<1,1>>>(2,4,dev_c);

	cudaMemcpy(&c,dev_c,sizeof(int),cudaMemcpyDeviceToHost);
	printf("c=%d\n",c);
	cudaFree(dev_c);

	return 0;
}
