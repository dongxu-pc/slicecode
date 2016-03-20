/*************************************************************************
	> File Name: 03longstpalindsubstr.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月19日 星期六 19时00分45秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>

char* longestPalindrome(char* s) {
	int len=0;
	int i,j,le,tmp;
	int mid;
	char *rts;

	int slen = strlen(s);
	if(slen == 0)
		return 0;
	len = 1;
	le = 0;
	mid = 1;
	for(mid = 1;mid < slen;mid++)
	{
		printf("111 %d\n",slen);
		tmp = 0;
		if(s[mid]==s[mid-1])
		{
			tmp = 2;
			for(j=1;(j<mid) && ((mid+j) < slen);j++){
				if(s[mid+j] == s[mid-1-j])
					tmp+=2;
				else
					break;
			}
			if(tmp > len){
				len  = tmp;
				le = mid-j;
			}
		}
		if(((mid+1)<slen) && (s[mid-1] == s[mid+1]))
		{
			printf("222\n");
			tmp=1;
			for(j=1;(j<=mid) && ((mid+j) < slen);j++)
			{
				if(s[mid+j]==s[mid-j])
					tmp+=2;
				else
					break;
			}
			if(tmp > len){
				len = tmp;
				le = mid -j+1;
			}
		}
	}

	rts = (char*)malloc((len+1)*sizeof(char));
	for(i = 0;i < len;i++)
	{
		rts[i] = s[i+le];
	}
	rts[len]='\0';
	printf("%s\n",rts);

	return rts;
}

int main()
{
	char s[]="aa";
	longestPalindrome(s);
	
	return 0;
}
