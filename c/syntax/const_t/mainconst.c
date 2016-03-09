/*************************************************************************
	> File Name: mainconst.c
	> Author: Yandong Xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2015年12月06日 星期日 22时03分51秒
 ************************************************************************/

#include<stdio.h>

int main()
{
	char c;
	const char * a = &c;
	c = 'A';
	//*a = &c;
	printf("%c\n",*a);
	c = 'B';
	printf("%c\n",*a);
	//(*a) = 'C';

	printf("%c\n",*a);

	return 0;
}
