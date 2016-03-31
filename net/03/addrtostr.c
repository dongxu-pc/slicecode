/*************************************************************************
	> File Name: addrtostr.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月29日 星期二 21时03分48秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int
inet_pton(int family,const char* strptr,void * addrptr)
{
	if(family == AF_INET){
		struct in_addr in_val;

		if(inet_aton(strptr,&in_val)){
			memcpy(addrptr,&in_val,sizeof(struct in_addr));
			return 1;
		}
		return 0;
	}
	return -1;
}

const char*
inet_ntop(int family,const void *addrptr,char *strptr,size_t len)
{
	const uint8_t *p = (const uint8_t *)addrptr;
	if(family == AF_INET){
		char temp[INET_ADDRSTRLEN];
		snprintf(temp,sizeof(temp),"%d.%d.%d.%d",p[0],p[1],p[2],p[3]);
		if(strlen(temp) >= len){
			return NULL;
		}
		strcpy(strptr,temp);
		return strptr;
	}
	return NULL;
}
