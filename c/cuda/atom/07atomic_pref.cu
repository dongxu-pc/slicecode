/*************************************************************************
	> File Name: 07atomic_pref.cu
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年05月24日 星期二 15时49分40秒
 ************************************************************************/

#include <stdio.h>
#include <cuda_runtime.h>

#define GRIDSIZE 20
#define BLOCKSIZE 32

__global__ void atomic_shared_kernel(int* res)
{
	__shared__ int seq;

	if(threadIdx.x == 0)
		seq = 1;
	__syncthreads();

	atomicAdd(&seq,1);
	__syncthreads();

	if(threadIdx.x == 0)
		res[blockIdx.x] = seq;
}

__global__ void atomic_global_kernel(int* res)
{
	atomicAdd(res,1);
}

__global__ void shared_kernel(int* res)
{
	__shared__ int seq;

	if(threadIdx.x == 0)
		seq = blockIdx.x;
	__syncthreads();

	seq++;
	__syncthreads();

	if(threadIdx.x == 0)
		res[blockIdx.x] = seq;
}

__global__ void global_kernel(volatile int* res)
{
	*res++;
}

int main()
{
	int i;

	int* dev_seq_shared;
	int* dev_seq_global;

	int* seq_global;
	int* seq_shared;

	cudaEvent_t start,stop;
	float time;

	cudaError_t cudaStatus;

	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	seq_shared = (int*)malloc(GRIDSIZE*sizeof(int));
	seq_global = (int*)malloc(sizeof(int));

	*seq_global = 2;

	cudaStatus = cudaMalloc((void**)&dev_seq_shared,GRIDSIZE*sizeof(int));
	cudaStatus = cudaMalloc((void**)&dev_seq_global,sizeof(int));
	
	cudaStatus = cudaMemcpy(dev_seq_global,seq_global,sizeof(int),cudaMemcpyHostToDevice);

	cudaEventRecord(start,0);
	global_kernel<<<GRIDSIZE,BLOCKSIZE>>>(dev_seq_global);
	cudaEventRecord(stop,0);

	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&time,start,stop);
	cudaStatus = cudaMemcpy(seq_global,dev_seq_global,sizeof(int),cudaMemcpyDeviceToHost);

	printf("global_kernel:seq = %d,time : %fms.\n",*seq_global,time);

	cudaEventRecord(start,0);
	atomic_global_kernel<<<GRIDSIZE,BLOCKSIZE>>>(dev_seq_global);
	cudaEventRecord(stop,0);

	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&time,start,stop);
	cudaStatus = cudaMemcpy(seq_global,dev_seq_global,sizeof(int),cudaMemcpyDeviceToHost);
	printf("atomic_global_kernel:seq = %d,time : %fms.\n",*seq_global,time);

	
	cudaEventRecord(start,0);
	shared_kernel<<<GRIDSIZE,BLOCKSIZE>>>(dev_seq_shared);
	cudaEventRecord(stop,0);

	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&time,start,stop);
	cudaStatus = cudaMemcpy(seq_shared,dev_seq_shared,GRIDSIZE*sizeof(int),cudaMemcpyDeviceToHost);
	printf("shared_kernel time : %fms.\n",time);
	for(i = 0;i < GRIDSIZE;i++){
		printf("%d ",seq_shared[i]);
		if(i%10 == 9)
			printf("\n");
	}
	printf("\n");

	
	cudaEventRecord(start,0);
	atomic_shared_kernel<<<GRIDSIZE,BLOCKSIZE>>>(dev_seq_shared);
	cudaEventRecord(stop,0);

	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&time,start,stop);
	cudaStatus = cudaMemcpy(seq_shared,dev_seq_shared,sizeof(int),cudaMemcpyDeviceToHost);
	printf("atomic_kernel time : %fms.\n",time);
	for(i = 0;i < GRIDSIZE;i++){
		printf("%d ",seq_shared[i]);
		if(i%10 == 9)
			printf("\n");
	}
	printf("\n");


	//cudaEventDestory(start);
	//cudaEventDestory(stop);

	return 0;
}
