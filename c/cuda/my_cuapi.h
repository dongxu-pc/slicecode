/*************************************************************************
	> File Name: my_cuapi.h
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年04月08日 星期五 10时35分18秒
 ************************************************************************/

#include "stdio.h"
#include "cuda_runtime.h"
#include "cuda.h"

#ifndef __MY_CUAPI_H__
#define __MY_CUAPI_H__

static void HandleError(cudaError_t err,const char*file,int line)
{
	if(err != cudaSuccess){
		printf("%s in %s at line %d\n",cudaGetErrorString(err),file,line);
		exit(EXIT_FAILURE);
	}
}

static void showIntArray(int* a,int size)
{
	int i=0;
	for(i=0;i<size;i++)
		printf("%d ",a[i]);
}

#ifndef HANDLE_ERROR
#define HANDLE_ERROR(err) (HandleError(err,__FILE__,__LINE__))
#endif



#ifdef DEBUG_FUNC
#define DEBUG_FUNC (printf("debug:%s int %s at line %d\n",__func__,__FILE__,__LINE__))
#endif

#endif
