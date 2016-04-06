/*************************************************************************
	> File Name: 02cudahashtable.cu
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年04月02日 星期四 21时24分04秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "cuda_runtime.h"


struct Entry{
	unsigned int key;
	void* value;
	struct 	Entry* next;
};

struct Table{
	size_t count;
	struct Entry **entries;
	struct Entry *pool;
	struct Entry *firstFree;
};

void init_table(struct Table* table,int entries,int elements)
{
	if(table == NULL)
		table = (struct Table*)malloc(sizeof(struct Table));
	table->count = entries;
	table->entries = (struct Entry**)calloc(entries,sizeof(struct Entry*));
	table->pool = (struct Entry*)malloc(elements * sizeof(struct Entry));
	table->firstFree = table->pool;
}

void free_table(struct Table* table)
{
	free(table->entries);
	free(table->pool);
	//if(table != NULL)
	//	free(table);
}

size_t hash(const unsigned int key,const size_t count)
{
	return key%count;
}

void add_to_table(struct Table *table,const unsigned int key,void*value)
{
	if(table == NULL){
		printf("Error:table is null\n");
		return;
	}
	size_t hashValue = hash(key,table->count);

	struct Entry* location = table->firstFree++;
	location->key = key;
	location->value = value;

	location->next = table->entries[hashValue];
	table->entries[hashValue] = location;
}

#define SIZE 100*1024*1024
#define ELEMENTS (SIZE/sizeof(unsigned int))

void verify_table(const struct Table *table)
{
	int count = 0;
	size_t i = 0;
	struct Entry* current;

	for(i=0;i<table->count;i++){
		current = table->entries[i];
		while(current != NULL){
			++count;
			if(hash(current->key,table->count) != i)
				printf("%d hashed to %ld,but was located at %ld\n",current->key,hash(current->key,table->count),i);
			current = current->next;
		}
	}

	if(count != ELEMENTS)
		printf("Hash Error!\n");
	else
		printf("Hash Success!\n");
}

#define HASH_ENTRIES 1024

int main()
{
	unsigned int *buffer = (unsigned int*)malloc(SIZE*sizeof(unsigned int));

	int i;
	clock_t start,stop;
	start = clock();

	struct Table* table = (struct Table*)malloc(sizeof(struct Table));
	init_table(table,HASH_ENTRIES,ELEMENTS);

	for(i=0;i<ELEMENTS;i++){
		add_to_table(table,buffer[i],(void*)NULL);
	}

	stop = clock();
	float elapsedTime = (float)(stop-start)/(float)CLOCKS_PER_SEC*1000.0f;
	printf("Time to hash:%3.1f ms\n",elapsedTime);

	verify_table(table);

	free_table(table);
	free(buffer);

	if(table != NULL)
		free(table);

	return 0;
}
