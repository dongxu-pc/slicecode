/*************************************************************************
	> File Name: 02dps.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月09日 星期三 14时00分15秒
 ************************************************************************/

#include<stdio.h>

/* A simple quick sort */
void sort(int* nums,int begin,int end)
{
	int l=begin,r=end;
	int tmp;
	int v=nums[l+(r-l)/2];
	while(l <= r)
	{
		while(nums[l] < v)l++;
		while(nums[r] > v)r--;
		if(l <= r)
		{
			tmp = nums[l];
			nums[l] = nums[r];
			nums[r] = tmp;
			l++;r--;
		}
	}
	if(begin < r)
		sort(nums,begin,r);
	if(l < end)
		sort(nums,l,end);
}

int** combinationSun(int* nums,int size,int target,int** colSizes,int* returnSize)
{
	sort(nums,0,size-1);
	int** arr =(int**)malloc(sizeof(int*));
	*returnSize = 0;
	int* stack = (int*)
}
