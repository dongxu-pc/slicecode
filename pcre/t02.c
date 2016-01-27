/*************************************************************************
	> File Name: t02.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年01月25日 星期一 18时57分43秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <hs/hs.h>

static int eventHandler(unsigned int id,unsigned long long from,
		unsigned long long to, unsigned int flags,void *ctx)
{
	printf("Match for pattern \"%s\"  from %llu to %llu:\n",(char *)ctx,from,to);
	return 0;
}

int main()
{
	int orroffset;
	int ovector[30];
	int rc,i;

	hs_database_t *database;
	hs_scratch_t *scratch = NULL;
	hs_compile_error_t *compile_err;
	hs_error_t hs_err;
	

	char buf[128];
	memset(buf,'\0',128);
	char src[] = "<head><title>Hello World!</title>hshhs<title></title></head>";
	char pattern[] = "<title>(.*)</title>";
	//char pattern[] = "[hw]";
	hs_err = hs_compile(pattern,HS_FLAG_DOTALL|HS_FLAG_SOM_LEFTMOST,HS_MODE_BLOCK,NULL,&database,&compile_err);
	if(hs_err != HS_SUCCESS){
		printf("ERROR: Unable to compile pattern \"%s\":%s\n",pattern,compile_err->message);
		hs_free_compile_error(compile_err);
		return -1;
	}

	hs_err = hs_alloc_scratch(database, &scratch);
	if(hs_err != HS_SUCCESS){
		printf("ERROR: Unable to allocate scratch space.Exiting.\n");
		hs_free_database(database);
		return -1;
	}
	printf("src is %s\n",src);
	hs_err = hs_scan(database,src,strlen(src),0,scratch,eventHandler,pattern);
	if(hs_err != HS_SUCCESS){
		printf("ERROR: Unable to scan src.Exiting.\n");
		hs_free_scratch(scratch);
		hs_free_database(database);
		return -1;
	}

	hs_free_scratch(scratch);
	hs_free_database(database);

	printf("Finished!\n");
	return 0;
}
