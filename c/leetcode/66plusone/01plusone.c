/*************************************************************************
	> File Name: 01plusone.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月08日 星期二 17时52分15秒
 ************************************************************************/

#include<stdio.h>

/**
 *
 *  * Return an array of size *returnSize.
 *
 *   * Note: The returned array must be malloced, assume caller calls free().
 *
 *    */

int* plusOne(int* digits, int digitsSize, int* returnSize)
{
	int i,in;
	int *tmp;

	for(i = 0;i < digitsSize && (digits[i] == 9);i++);
	if(i == digitsSize){
		tmp = (int *)malloc((digitsSize+1)*sizeof(int));
		tmp[0] = 1;
		for(i=0;i<digitsSize;i++)
			tmp[i+1]=0；
		*returnSize = digitsSize+1;
		return tmp;
	}
	*returnSize = digitsSize;
	tmp = (int *)malloc(digitsSize*sizeof(int));
	in = 1;
	for(i = 0;i < digitsSize ;i++)
	{
		in = digits[digitsSize-i-1]+in;
		tmp[digitsSize-i-1] = in%10;
		in /= 10;
	}

	return tmp;
}
