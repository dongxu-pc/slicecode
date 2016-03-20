/*************************************************************************
	> File Name: 02mediansortedarray.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月10日 星期四 19时50分47秒
 ************************************************************************/

#include<stdio.h>

double findMedian(int* nums,int size){
	double re;
	int mid,m,n,t;

	mid = size/2;
	t = size%2;
	if(t==0){
		m = nums[mid-1];
		n = nums[mid];
	}else{
		m = nums[mid];
		n = m;
	}
	re =(m+n)/2.0;

	return re;
}

double sortMedian(int* nums,int size)
{
	int i,j,tmp;
	for(i=0;i<size;i++)
		for(j=0;j<size-i-1;j++)
		{
			if(nums[j]>nums[j+1]){
				tmp = nums[j];
				nums[j] = nums[j+1];
				nums[j+1] = tmp;
			}
		}
	for(i=0;i<size;i++)
		printf("%d ",nums[i]);
	printf(":%d\n",size);

	return findMedian(nums,size);
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
	double re;
	int i1,i2,j1,j2,mid,t,m,n;
	int i;
	int tmp[6];

	i1=0,j1=0;
    t = (nums1Size + nums2Size)%2;
	i2=nums1Size-1,j2=nums2Size-1;
	if(i1>i2)
		return findMedian(nums2,nums2Size);
	if(j1>j2)
		return findMedian(nums1,nums1Size);
	if(nums1Size == 1 && nums2Size == 1)
		return (nums1[0]+nums2[0])/2.0;
	if(nums1Size == 1 && nums2Size == 2)
	{
		if(nums1[0] < nums2[0])return nums2[0]*1.0;
		if(nums1[0] > nums2[1])return nums2[1]*1.0;
		return nums1[0]*1.0;
	}

	if(nums2Size == 1 && nums1Size == 2)
	{
		if(nums2[0] < nums1[0])return nums1[0]*1.0;
		if(nums2[0] > nums1[1])return nums1[1]*1.0;
		return nums2[0]*1.0;
	}

	if(t == 0)t = 2;
	while((i2+j2-i1-j1)>t){
		if(nums1[i1]<=nums2[j1]){
			if(i1<=i2)i1++;
	 		else j1++;
		}else{
			if(j1<=j2)j1++;
			else i1++;
		}
		if(nums1[i2]>nums2[j2]){
			if(i1<=i2)i2--;
	 		else j2--;
		}else{
			if(j1<=j2)j2--;
			else i2--;
		}
	}
	for(i=0;i1<=i2;i1++,i++)
		tmp[i] = nums1[i1];
	for(i;j1<=j2;j1++,i++)
		tmp[i] = nums2[j1];
	return sortMedian(tmp,i);
}

int main()
{
    double i;
	int a[4]={1,2,3,4};
	int b[1]={5};
    i = findMedianSortedArrays(a,4,b,1);                                                                           
    printf("median = %f\n",i);

	return 0;
}
