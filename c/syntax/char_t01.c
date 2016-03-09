/*************************************************************************
	> File Name: char_t01.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2015年11月27日 星期五 22时20分35秒
 ************************************************************************/

#include<stdio.h>

int main()
{
	char a;
	char b[]="abcd";

	int c;
	int d;

	a = 67;

	c = a;
	printf("a = %x,c = %d \n",a,c);
	a = -12;
	
	c = a;
	printf("a = %x,c = %d \n",a,c);

	return 0;
}
