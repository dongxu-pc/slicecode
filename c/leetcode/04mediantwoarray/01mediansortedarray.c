/*************************************************************************
	> File Name: 01mediansortedarray.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月10日 星期四 15时01分47秒
 ************************************************************************/

#include<stdio.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
	int i,j,k,mid,t;
    int m,n;
    double re;
    
	m = nums1[0],n=nums2[0];i=0,j=0,k=1;
    mid = (nums1Size + nums2Size)/2;
    t = (nums1Size + nums2Size)%2;

    if(nums1Size == 0){
        if(t == 0){
            m = nums2[mid-1];
            n = nums2[mid];
        }else{
            m = nums2[mid];
            n = m;
        }
        re = (m+n)/2.0;
        return re;
    }else if(nums2Size == 0){
        if(t == 0){
            m = nums1[mid-1];
            n = nums1[mid];
        }else{
            m = nums1[mid];
            n = m;
        }
        re = (m+n)/2.0;
        return re;
    }

    while(k < mid){
        if(i >= (nums1Size-1))
		{n=nums2[j];j++;}
        else if(j >= (nums2Size-1)){
			m=nums1[i];
			i++;
		}
        else if((nums1[i] <= nums2[j]) && (nums1[i+1] <= nums2[j]))
		{m=nums1[i];i++;}
        else
		{n=nums2[j];j++;}
        k++;
    }

	printf("i=%d,j=%d,k=%d,mid=%d\n",i,j,k,mid);
    if(t == 0){
		if(m > n){
			if((j+1)<nums2Size)
				if(m > nums2[j+1]){
					m = nums2[j+1];
				}
			if((i>0)&&(m == nums1[i]))
				if(n < nums1[i-1]){
					n = nums1[i-1];
				}
		}else{
			if((i+1)<nums1Size)
				if(n > nums1[i+1]){
					n = nums1[i+1];
				}
			if((j>0)&&(n == nums2[j]))
				if(m < nums2[j-1])
					m = nums2[j-1];
		}
    }else{
		if(i==0 || j==0){
			if(i == 0 && m > n && (j+1)<nums2Size){
				m = m<nums2[j+1]?m:nums2[j+1];
			}
			if(j == 0 && n > m && (i+1)<nums1Size){
			    n = n<nums1[i+1]?n:nums1[i+1];
			}
		}
		m = m>n?m:n;
		n=m;
    }

    re = (m+n)/2.0;
    return re;
}

int main()
{
	double i;
	int a[2]={1,1};
	int b[1]={3};

	i = findMedianSortedArrays(a,2,b,1);

	printf("median = %f\n",i);

	return 0;
}
