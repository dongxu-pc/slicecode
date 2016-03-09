/*************************************************************************
	> File Name: storge.c
	> Author: Yandong Xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2015年12月06日 星期日 20时44分10秒
 ************************************************************************/

#include<stdio.h>

int a = 10;
static int b = 100;
void autoincrease()
{
	{
		static int c = 1000;
	    printf("%d %d %d\n",a,b,c);
		c++;
	}
	a++;
	b++;
}
