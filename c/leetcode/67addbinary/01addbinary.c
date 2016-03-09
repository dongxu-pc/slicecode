/*************************************************************************
	> File Name: 01addbinary.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月08日 星期二 18时11分36秒
 ************************************************************************/

#include<stdio.h>

char* addBinary(char* a, char* b){
	int lena,lenb,lenc;
	int i;
	char aa,bb,in;
	char* c;

	lena = strlen(a);
	lenb = strlen(b);

	lenc = lena > lenb ? lena+1 : lenb+1;

	c = (char*)malloc((lenc+1)*sizeof(char));
	memset(c,'\0',(lenc+1)*sizeof(char));
	in = 0;
	for(i=0;i<lenc;i++)
	{
		if(i < lena)
			aa = a[lena-1-i] - '0';
		else
			aa = 0;
		if(i < lenb)
			bb = b[lenb-1-i] - '0';
		else
			bb = 0;

		in = aa+bb+in;
		c[lenc-1-i] = in%2 + '0';
		in /= 2;
	}
	if(c[0] != '1')
		c++;
	return c;
}
