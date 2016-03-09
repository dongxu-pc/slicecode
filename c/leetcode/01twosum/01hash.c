/*************************************************************************
	> File Name: 01hash.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月08日 星期二 10时46分15秒
 ************************************************************************/

#include<stdio.h>
#include "stdlib.h"
#include "memory.h"
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums,int numsSize,int target)
{
	int i,j,tmp,z,k;
	int *htable;
	int hsize;
	int *rt;

	printf("numsize=%d\n",numsSize);


	hsize = 2*numsSize;
	rt = (int *)malloc(2*sizeof(int));
	htable = (int *)malloc(2*numsSize*sizeof(int));
	memset(htable,'\0',2*numsSize*sizeof(int));

	z = -1;
	for(i = 0;i < numsSize;i++)
	{
		/*0 + target = target*/
		if(nums[i] == 0 || nums[i] == target){
			if(z != -1){
				if((nums[z]+nums[i]) == target){
					rt[0] = i;
					rt[1] = z;
					free(htable);
					return rt;
				}
			}else{
				z = i;
			}
		}

		tmp = ((nums[i]%hsize)+hsize)%hsize;
		if(htable[tmp] == 0)
			htable[tmp] = nums[i];
		else{
			j = 0;
			tmp = (tmp*2+j)%hsize;
			while(htable[tmp] != 0){
				tmp++;
				tmp%=hsize;
		    }
			htable[tmp] = nums[i];
		}
	}

	
	for(i = 0;i < hsize;i++)
		printf("%d ",htable[i]);
	printf("\n");

	for(i = 0;i < numsSize;i++)
	{
		j = 0;
		tmp = (((target-nums[i])%hsize) + hsize)%hsize;
		if(htable[tmp] == 0)
			continue;
		if(htable[tmp] != 0)
		{
			if((htable[tmp]+nums[i]) == target)
			{
				rt[0] = i;
				for(j = 0;j < numsSize;j++){
					if(htable[tmp] == nums[j]){
						rt[1] = j;
						if(rt[0] == rt[1])
							break;
						else{
						free(htable);
						return rt;
						}
					}
				}
			}
			j = 0;
			tmp = (tmp*2+j)%hsize;
			while(htable[tmp] != 0 ){
				if((htable[tmp] + nums[i]) == target){
					rt[0] = i;
					for(k = j;j < numsSize;j++){
						if(htable[tmp] == nums[j]){
							rt[1]=j;
							if(rt[0] == rt[1])
								break;
							else{
								free(htable);
		 						return rt;
							}
					 	}
					}
				}
				tmp++;
				tmp %= hsize;
			}
		}
	}

	printf("Not Found!\n");

	free(htable);

	return rt;
}

int main()
{
	int nums[] = {-1,-2,-3,-4,-5};
	int numsSize = 5;
	int target = -8;
	int *re;
	re = twoSum(nums,numsSize,target);
	if(re != NULL)
		printf("re = [%d,%d]\n",re[0],re[1]);

	return 1;
}
