/*************************************************************************
	> File Name: assert_t01.c
	> Author: Yandong Xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2015年12月11日 星期五 20时06分14秒
 ************************************************************************/

#include<stdio.h>
#include "assert.h"

int main()
{
	char* a;
	printf("asssert\n");
	assert(1);
	assert("assert 1\n");
	assert(-1);
	printf("assert -1\n");
    assert(a);
	printf("assert pointer a\n");
	return 0;
}
