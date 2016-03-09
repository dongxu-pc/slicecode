/*************************************************************************
	> File Name: 01dycombinsum.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月08日 星期二 21时34分10秒
 ************************************************************************/

#include<stdio.h>
#include "stdlib.h"

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int** combinationSum(int* candidates, int candidatesSize, int target, int** columnSizes, int* returnSize) {
	int ** result;
	int renum;
	int i,j,k;
	int *stack = (int *)malloc(candidatesSize*sizeof(int));
	int top=0;
	int sum = 0;
	int col = 0;
	result = (int**)malloc(candidatesSize*candidatesSize*sizeof(int *));
	*returnSize = 0;

	for(i = 0;i < candidatesSize;i++)
	{
		stack[top] = i;
		sum = candidates[stack[top]];
		for(j=i;j<candidatesSize;j++)
		{
			if(sum < target){
				top++;stack[top] = j;
				sum += candidates[stack[top]];
			}else if(sum > target){
				sum -= candidates[stack[top]];top--;
				col = stack[top];sum -= candidates[stack[top]];top--;
				j = col+1; 
				top++;stack[top] = j;sum += candidates[stack[top]];
			}else if(sum == target){
				result[returnSize] = (int*)malloc((top+1)*sizeof(int));
				memcpy(result[returnSize],stack,top+1);
				(*columnSizes)[returnSize]=top+1;
				returnSize++;
				sum -= candidates[stack[top]];top--;
				j
			}
		}
	}


}
