/*************************************************************************
	> File Name: 03qsort_t.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年04月16日 星期六 13时47分22秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>

int intcomp(int *x, int *y)
{
	return *x - *y;
}

int main()
{
	int i,n=10;
	int a[] = {1,45,345,785,2,5345,567,6774654,456,27,24};

	for(i = 0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");

	qsort(a,n,sizeof(int),intcomp);

	for(i = 0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");

	return 0;
}
