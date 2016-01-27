/*************************************************************************
	> File Name: t01.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年01月24日 星期日 21时20分42秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcre.h>

int main()
{
	pcre *re;
	const char* error;
	int erroffset;
	int ovector[30];
	int rc,i;

	char buffer[128];
	memset(buffer,'\0',128);
	char src[] = "<head><title>Hello World</title>hshss<title>a</title></head>";
	char pattern [] = "<title>(.*)</title>";

	printf("String : %s\n",src);
	printf("Pattern : %s\n",pattern);

	re = pcre_compile(pattern,0,&error,&erroffset,NULL);
	if(NULL == re){
		printf("PCRE compilation failed at offset %d: %s\n",erroffset,error);
		return 1;
	}

	rc = pcre_exec(re,NULL,src,strlen(src),0,0,ovector,30);
	if(rc < 0){
		if(rc == PCRE_ERROR_NOMATCH)
			printf("Sorry,no match...\n");
		else
			printf("Oh,matching error %d\n",rc);
		return 1;
	}

	printf("Ok,matched ...\n");
	printf("count=%d\n",rc);
	for(i = 0;i < 10;i++)
		printf("%d ",ovector[i]);
	printf("\n");
	for(i = 0;i < rc;i++)
	{
		char *substring_start = src + ovector[2*i];
		int substring_length = ovector[2*i+1] - ovector[2*i];
		printf("%2d: %.*s\n", i, substring_length, substring_start);
	}

	free(re);

	printf("This is a pcre testing code.\n");
	return 0;
}
