/*************************************************************************
	> File Name: 01rmdup.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月08日 星期二 21时13分22秒
 ************************************************************************/

#include<stdio.h>

int removeDuplicates(int* nums, int numsSize) {
	int i,j;
	int col;

	if(numsSize == 0)
		return 0;
	for(i=1,col=nums[0],j=0;i<numsSize;i++)
	{
		if(col != nums[i])
		{
			j++;
			nums[j]=nums[i];
			col = nums[i];
		}
	}

	return j+1;
}
