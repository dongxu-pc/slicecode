/*************************************************************************
	> File Name: 01intToRoman.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月08日 星期二 18时38分40秒
 ************************************************************************/

#include<stdio.h>
#include "stdlib.h"
#include "string.h"
/*"I(1),V(5),X(10),L(50),C(100),D(500),M(1000)"*/

char* intToRoman(int num)
{
	int numeral[9]={1,5,10,50,100,500,1000,5000,10000};
	int charnum[7]={'I','V','X','L','C','D','M'};
	char *c;
	int i,j,col,tmp,tmp2;
	c = (char*)malloc(13*sizeof(char));
	memset(c,'\0',13*sizeof(char));
	
	col = 12;
	tmp2 = num;
	for(i = 2;i < 9;i+=2)
	{
		tmp = num%numeral[i];
		tmp2 = tmp/numeral[i-2];
		switch(tmp2)
		{
			case 1:
			case 2:
			case 3:for(j=0;j<tmp2;j++,col--)c[col]=charnum[i-2];break;
			case 4:c[col]=charnum[i-1];col--;c[col]=charnum[i-2];col--;break;
			case 5:
			case 6:
			case 7:
			case 8:for(j=5;j<tmp2;j++,col--)c[col]=charnum[i-2];c[col]=charnum[i-1];col--;break;
			case 9:c[col]=charnum[i-2];col--;c[col]=charnum[i];col--;break;
			default:break;
		}
		printf("%d:%s\n",i,c+col+1);
	}

	while(*c == '\0')
		c++;
	
	return c;
}

int main()
{
	char* s;
	s = intToRoman(3784);
	printf("%s\n",s);

	return 0;
}
