/*************************************************************************
	> File Name: sto_main.c
	> Author: Yandong Xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2015年12月06日 星期日 20时45分59秒
 ************************************************************************/

#include<stdio.h>

int main()
{
	extern int a;
	autoincrease();
	printf("a = %d\n",a);
	a++;
	autoincrease();

	printf("a = %d\n",a);
	a++;
	autoincrease();
	autoincrease();
	autoincrease();
	autoincrease();
	autoincrease();
	autoincrease();
	autoincrease();

	return 0;
}
