/*************************************************************************
	> File Name: storge.c
	> Author: Yandong Xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2015年12月10日 星期四 22时38分39秒
 ************************************************************************/

#include<stdio.h>

#include "stdlib.h"
void freestorge(char* c)
{
	free(c);
}
int main()
{
	char * a;
	int i = 0;
	a = (char*)malloc(7);
	for(i = 0;i < 7;i++){
		a[i] = 'A'+i;
	}

	for(i = 0;i < 7;i++){
		printf("%c",a[i]);
	}
	printf("\n");
    freestorge(a);
	for(i = 0;i < 7;i++){
		printf("%c",a[i]);
	}
	printf("\n");

	return 0;
}
