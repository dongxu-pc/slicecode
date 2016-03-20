/*************************************************************************
	> File Name: 01shortestPalindrome.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月19日 星期六 20时00分14秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>
#include <stdlib.h>

char* shortestPalindrome(char *s)
{
	int len,re;
	int i;
	int mid;
	char* rts;

	int slen = strlen(s);

	if(slen == 0)
		return NULL;

	len = 0;
	re = 0;
	for(mid=1;mid < slen;mid++)
	{
		if(s[mid] == s[mid-1])
		{
			for(i = 1;(i<mid) && (s[mid+i] == s[mid-1-i]);i++);
			if(i == mid)
				re = 2*mid-1;
		}
		if(((mid+1)<slen) && s[mid+1]==s[mid-1])
		{
			for(i = 1;((i<=mid) && (s[mid+i] == s[mid-i]));i++);
			if(i == (mid+1))
				re = 2*mid;
		}
	}

	len = slen+slen-re-1;

	rts = (char*)malloc((len+1)*sizeof(char));
	for(i = 0;i < slen-re-1;i++)
	{
		rts[i] = s[slen-i-1];
	}
	for(i;i<len;i++)
	{
		rts[i]=s[i-slen+re+1];
	}
	rts[len]='\0';

	printf("%d:%s\n",len,rts);
}
int main()
{
	char a[]="aaaaa";
	shortestPalindrome(a);
	return 0;
}

