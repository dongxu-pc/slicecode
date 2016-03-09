/*************************************************************************
	> File Name: 01hash.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月08日 星期二 10时46分15秒
 ************************************************************************/

#include<stdio.h>
#include "stdlib.h"
#include "uthash.h"
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

struct st_nums{
	int id;
	int value;
	UT_hash_handle hh;
};

struct st_nums *nu = NULL;

void add_num(int id,int v)
{
	struct st_nums *s;
	HASH_FIND_INT(nu,&id,s);
	if(s == NULL){
		s = (struct st_nums *)malloc(sizeof(struct st_nums));
		s->id = id;
		s->value = v;
		HASH_ADD_INT(nu,id,s);
	}
}

struct st_nums *find_num(int id){
	struct st_nums *s = NULL;

	HASH_FIND_INT(nu,&id,s);
	return s;
}

void delete_num(struct st_nums *num)
{
	HASH_DEL(nu,num);
	free(num);
}

void delete_all()
{
	struct st_nums *c_num,*tmp;

	HASH_ITER(hh,nu,c_num,tmp){
		HASH_DEL(nu,c_num);
		free(c_num);
	}
}


int* twoSum(int* nums,int numsSize,int target)
{
	int i,j,tmp,z,k;
	struct st_nums *s;
	int hsize;
	int *rt;
	rt = (int*)malloc(sizeof(int)*2);
	z = -1;
	for(i=0;i<numsSize;i++)
	{
	    if(nums[i] == 0 || nums[i]==target){
	        if(z == -1){
	            z = i;
	        }else if((nums[i]+nums[z]) == target){
	            rt[0] = z;
	            rt[1] = i;
	            if(rt[0] != rt[1])
	            {
	                delete_all();
	                return rt;
	            }
	        }
	    }else{
		    add_num(nums[i],i);
	    }
	}

	for(i=0;i<numsSize;i++)
	{
		s = find_num(target - nums[i]);
		if(s != NULL)
		{
			if((s->id + nums[i]) == target)
			{
				rt[0]=i;
				rt[1]=s->value;;
				if(rt[0] != rt[1])
					break;
			}
		}
	}

	free(s);
	delete_all();
	return rt;
}

int main()
{
	int nums[] = {0,3,4,0};
	int numsSize = 4;
	int target = 0;
	int *re;
	re = twoSum(nums,numsSize,target);
	if(re != NULL)
		printf("re = [%d,%d]\n",re[0],re[1]);

	return 1;
}
