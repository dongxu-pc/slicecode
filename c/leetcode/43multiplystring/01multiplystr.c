/*************************************************************************
	> File Name: 01multiplystr.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月08日 星期二 16时54分06秒
 ************************************************************************/

#include<stdio.h>
#include "stdlib.h"
#include "string.h"


char* multiply(char* num1,char* num2)
{
	int len,len1,len2;
	char* re;
	int i,j,k,cls;
	char c1,c2,in,out;
	len1 = strlen(num1);
	len2 = strlen(num2);
	len = len1+len2;
	i = 0;
	j = 0;
	cls = 0;
	in = 0;

	re = (char*)malloc((len+1)*sizeof(char));
	memset(re,'0',len*sizeof(char)+1);
	re[len]='\0';
	
	for(i=len2-1;i>=0;i--,cls++)
	{
		c2 = num2[i]-'0';
		in=0;
		for(j=len1-1,k=0;j>=0;j--,k++)
		{
			c1 = num1[j]-'0';
			out = c1*c2 + in + re[len-1-cls-k]-'0';
			re[len-1-cls-k]= (char)(out % 10+'0');
			in = out/10;
		}
		while(in > 0)
		{
			out = in+re[len-1-cls-k] - '0';
			re[len-1-cls-k] = (char)(out % 10+'0');
			in = out/10;
		}

	}

	while(*re == '0')
		re++;
	return re;
}

int main()
{
	char *a="23";
	char *b="34";
	char *c;
	c = multiply(a,b);
	printf("%s * %s\n=%s\n",a,b,c);

	return 1;
}
