/*************************************************************************
	> File Name: hostbyteorder.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月29日 星期二 20时29分32秒
 ************************************************************************/

#include<stdio.h>
#include "stdlib.h"
#include "stdint.h"

int
main(int argc, char** argv)
{
	union{
		short s;
		uint8_t c[sizeof(short)];
	}un;

	un.s=0x0102;
	printf("The machine host byte order:");
	if(sizeof(short) == 2){
		if(un.c[0] == 2 && un.c[1] == 1)
			printf("little-endian\n");
		else if(un.c[0] == 1 && un.c[1] == 2)
			printf("big-endian\n");
		else
			printf("unknow!\n");
	}else
		printf("Size of short is %d\n",sizeof(short));

	return 0;
}
