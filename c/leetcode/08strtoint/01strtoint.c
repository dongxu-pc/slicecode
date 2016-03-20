/*************************************************************************
	> File Name: 01strtoint.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月20日 星期日 16时01分35秒
 ************************************************************************/

#include<stdio.h>
#include "string.h"
#include "stdlib.h"

int myAtoi(char* str) {
	int i,j;
	int tmp;
	int slen=strlen(str);
	int rt;
	rt = 0;
	if(str[0]=='-' || str[0]=='+')
		i=1;
	else i=0;
	for(i;i<slen;i++){
		rt *= 10;
		rt += str[i]-'0';
	}

	if(str[0] == '-')
		rt = -rt;

	return rt;
}

int main()
{
	char a[]="1234";
	printf("%d\n",myAtoi(a));

	return 0;
}
