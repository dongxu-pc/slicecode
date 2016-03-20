/*************************************************************************
	> File Name: 01reverseint.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月20日 星期日 15时33分59秒
 ************************************************************************/

#include<stdio.h>
#include "string.h"
#include "stdlib.h"
#include "limits.h"

int reverse(int x) {
	int xt = x;
	long rt = 0;
	if(xt < 0)
		xt=-xt;
	rt = xt%10;
	xt /= 10;

	while(xt != 0)
	{
		rt *= 10;
		rt += xt%10;
		xt/=10;
	}
	if(x < 0)
		rt = -rt;

	if(rt>INT_MAX || rt<INT_MIN)
		return 0;
	printf("%d:%d\n",x,rt);
	return rt;
}

int main()
{
	int a = 1534236469;
	reverse(a);
	return 0;
}
