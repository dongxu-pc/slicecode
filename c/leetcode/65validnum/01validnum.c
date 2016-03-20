/*************************************************************************
	> File Name: 01validnum.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月20日 星期日 16时27分46秒
 ************************************************************************/

#include<stdio.h>
#include "stdlib.h"
#include "string.h"

bool isNumber(char* s)
{
	int slen = strlen(s);
	if(slen == 0)return false;
	int i=0,dot=0;

	while(s[i]==' ')i++;
	if(s[i] == '-' || s[i] == '+')i++;
	while(s[i]=='.' || (s[i]>='0' && s[i]<='9'))
	{
		if(s[i]=='.')
			dot++;
		i++;
		if(dot > 1)
			return false;
	}
	if(i==slen)
		return true;
	else
		return false;
}


