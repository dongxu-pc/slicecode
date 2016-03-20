/*************************************************************************
	> File Name: 03median.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月10日 星期四 21时27分30秒
 ************************************************************************/

#include<stdio.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int l,r;
    int i,j;
    int t;
    int mid;
    int cl,cr;

    i=0,j=0;cl=0,cr=0;
    mid = (nums1Size + nums2Size)/2;
    t  = (nums1Size + nums2Size)%2;
    if((nums1Size == 0)&&(nums2Size == 0))return 0.0;
    if(nums1Size == 0){ 
        l = nums2[0];
        cl=1;
        j=1;

    }   
    if(nums2Size == 0){ 
        l = nums1[0];
        cl=1;
        i=1;
    }
    if(mid == 0)
        return l*1.0;

    while(cl < mid){
        if(i >= nums1Size){
                l = nums2[j+mid-cl-1];
                j += mid-cl;
                cl = mid;
        }else if(j >= nums2Size){
                l = nums1[i+mid-cl-1];
                i += mid-cl;
                cl = mid;
        }else if(nums1[i] <= nums2[j]){
            l = nums1[i];
            i++;
            cl++;
        }else{
            l = nums2[j];
            j++;
            cl++;
        }
    }

    if(i >= nums1Size){
        r = nums2[j];
    }else if(j >= nums2Size){
        r = nums1[i];
    }else if(nums1[i] <= nums2[j]){
        r = nums1[i];
    }else{
        r = nums2[j];
    }


    if(t == 0)
        return (l+r)/2.0;                                                                                          
    else
        return r*1.0;

}

int main()
{
	double re;
	int a[3]={1,2,3};
	int b[2]={1,2};

	re = findMedianSortedArrays(a,3,b,2);
	printf("re = %f\n",re);

}
