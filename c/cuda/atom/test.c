/*************************************************************************
	> File Name: test.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年04月19日 星期二 12时30分27秒
 ************************************************************************/

#include<stdio.h>

int add(int *sum,int n)
{
	while(n>0)
	{
		*sum+=n;
		n--;
	}

	return *sum;
}

int main()
{
	int sum = 0;
	add(&sum,10240);
	printf("sum=%d\n",sum);

	return 0;
}
