/*************************************************************************
	> File Name: 01longestpalindsubstr.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月11日 星期五 20时30分25秒
 ************************************************************************/

#include<stdio.h>
#include "stdlib.h"
#include "string.h"

char* longestPalindrome(char* s){
	int len=0,max;
	int i,j;
	int st =0,en;
	int rs,rt;
	char *rts;

	int sl = strlen(s);
	en = sl-1;
	max =0;


	while(en>=(st+max)){
		while(en>=(st+max))
		{
			i=0,j=0;
			while(s[st+i] == s[en-j]){
				i++,j++;
				if((st+i) >= (en-j)){
					break;
				}
			}
			if((st+i) >= (en-j)){
				if(max < (en-st+1)){
					rs = st;
					rt = en;
				 	max = en-st+1;
					break;
				}else{
					en-=j;
					if(j == 0)en--;
				} 
			}else{
				en-=j;
				if(j == 0)en--;
			}
		}
		st++;
		en = sl-1;
	}

	rts = (char*)malloc((max+1)*sizeof(char));
	memcpy(rts,s+rs,max);
	rts[max] = '\0';

	printf("max=%d\n",max);
	printf("%s\n",rts);

	return rts;
}

int main()
{
	//char s[]="aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabcaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
//	char s[]="abcccba";
	char s[]="a";
	longestPalindrome(s);

	return 0;
}
