/*************************************************************************
	> File Name: 07cultime.cu
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年04月08日 星期五 10时18分09秒
 ************************************************************************/

#include <stdio.h>
#include <cuda_runtime.h>

//__global__声明的函数，告诉编译器这段代码交由CPU调用，由GPU执行
__global__ void mul(int *dev_a,const int NUM)
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int dis=blockDim.x * gridDim.x;
    while(idx<NUM)
    {
        dev_a[idx]=dev_a[idx]%23*dev_a[idx]*5%9;
        idx+=dis;
    }
}

int main(void)
{
    const int thread_pre_block = 64;    //每个block的线程数量
    const int block_pre_grid = 8;    //grid中的block数量
    const int NUM = 45056;

    //申请主机内存，并进行初始化
    int host_a[NUM];
    for(int i=0;i<NUM;i++)
        host_a[i]=i;

    //定义cudaError，默认为cudaSuccess(0)
    cudaError_t err = cudaSuccess;

    //申请GPU存储空间
    int *dev_a;
    err=cudaMalloc((void **)&dev_a, sizeof(int)*NUM);
    if(err!=cudaSuccess)
    {
        perror("the cudaMalloc on GPU is failed");
        return 1;
    }

    //将要计算的数据使用cudaMemcpy传送到GPU
    cudaMemcpy(dev_a,host_a,sizeof(host_a),cudaMemcpyHostToDevice);

    dim3 threads = dim3(thread_pre_block);
    dim3 blocks  = dim3(block_pre_grid);

    //使用event计算时间
    float time_elapsed=0;
    cudaEvent_t start,stop;
    cudaEventCreate(&start);    //创建Event
    cudaEventCreate(&stop);

    cudaEventRecord( start,0);    //记录当前时间
    mul<<<blocks, threads, 0, 0>>>(dev_a,NUM);
    cudaEventRecord( stop,0);    //记录当前时间

    cudaEventSynchronize(start);    //Waits for an event to complete.
    cudaEventSynchronize(stop);    //Waits for an event to complete.Record之前的任务
    cudaEventElapsedTime(&time_elapsed,start,stop);    //计算时间差

    cudaMemcpy(&host_a,dev_a,sizeof(host_a),cudaMemcpyDeviceToHost);    //计算结果回传到CPU

    cudaEventDestroy(start);    //destory the event
    cudaEventDestroy(stop);
    cudaFree(dev_a);//释放GPU内存
    printf("执行时间：%f(ms)\n",time_elapsed);
    return 0 ;
}
