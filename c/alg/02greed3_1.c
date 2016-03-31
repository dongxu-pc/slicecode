/*************************************************************************
	> File Name: 02greed3_1.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月30日 星期三 21时14分05秒
 ************************************************************************/

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"

int gettimes(int a[],int size)
{
	int sum=0;
	int *lt;
	int l2,r1,m3;
	int i;

	lt = (int *)malloc(size*sizeof(int));
	l2=0,r1=0;
	m3=0;

	for(i=0;i<size;i++){
		sum += a[i]/3;
		m3 += a[i]/3;
		if(a[i]%3 == 2)
			l2++;
		else if(a[i]%3 == 1)
			r1++;
	}
	if(m3 > 0)
		sum += l2;/*补全所有%=2的项,m3保持不变*/
	else
		return sum;

	if(m3 > (size-r1+1))
	{
		m3 -= r1;
		sum += r1;
	}else{
		sum += m3-1;
		m3 = 1;
	}
	
	while(m3>1)
	{
		l2=0,r1=0;
		i = m3;
		m3 = i/3;
		sum += i/3;
		if(i%3 == 2 && m3 != 0){
			sum++;
		}
	}
	sum += m3/3;

	printf("sum = %d\n",sum);

	return sum;
}

int main()
{
	int a[]={10,11};

	gettimes(a,2);

	return 0;
}
