/*************************************************************************
	> File Name: 01zigzag.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月20日 星期日 14时56分06秒
 ************************************************************************/

#include <stdio.h>
#include "stdlib.h"
#include "string.h"

char* convert(char* s, int numRows) {
	int slen = strlen(s);
	int i,j,k,tmp;

	char *rts = (char*)malloc((slen+1)*sizeof(char));
	rts[slen] = '\0';
	if(numRows == 1){
		memcpy(rts,s,slen);
		return rts;
	}

	for(k = 0,j=0;k < numRows;k++)
	{
		tmp= k%(numRows-1);
		for(i=k;i<slen;j++)
		{	
			if(j == slen)
				return rts;
			rts[j]=s[i];
			i+=2*numRows-2-2*tmp;
			if(i<slen){
				j++;
				if(j == slen)
					return rts;
				rts[j]=s[i];
				if(tmp > 0){
					i+=2*tmp;
				}else{
					j--;
				}
			}
		}
	}

	printf("%s\n",rts);

	return rts;
}

int main()
{
	//char a[]="PAYPALISHIRING";
	char a[]="P";
	convert(a,1);

	return 0;
}
