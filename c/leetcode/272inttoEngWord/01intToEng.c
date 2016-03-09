/*************************************************************************
	> File Name: 01intToEng.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月08日 星期二 20时08分12秒
 ************************************************************************/

#include<stdio.h>
#include "stdlib.h"
#include "string.h"

char* numberToWords(int num) {
	int i,j,tmp,tmp2;
	char* tn[]={"One ","Two ","Three ","Four ","Five ","Six ","Seven ","Eight ","Nine ","Ten ","Eleven ","Twelve ","Thirteen ","Fourteen ","Fifteen ","Sixteen ","Seventeen ","Eighteen ","Nineteen "};
	char* hn[]={"Twenty ","Thirty ","Forty ","Fifty ","Sixty ","Seventy ","Eighty ","Ninety "};
	char* th[]={"Ten ","Hundred ","Thousand ","Million ","Billion "};
	int thn[] = {10,100,1000,1000000,1000000000};
	char* sre;
	sre = (char *)malloc(1000*sizeof(char));
	memset(sre,'\0',1000);

	for(i=4;i>=2;i--){
		tmp = num/thn[i];
		tmp%=1000;
		if(tmp/100 != 0){
			strcat(sre,tn[tmp/100-1]);
			strcat(sre,th[1]);
		}
		tmp%=100;
		if(tmp/10 > 1){
			strcat(sre,hn[tmp/10 -2]);
			if(tmp%10 > 0)
				strcat(sre,tn[tmp%10 -1]);
		}else if(tmp > 0 && tmp<20){
			strcat(sre,tn[tmp-1]);
		}
		if(num/thn[i]>0)
			strcat(sre,th[i]);
	}

    tmp = num%1000;
    if(tmp/100 != 0){ 
        strcat(sre,tn[tmp/100-1]);
		strcat(sre,th[1]);
    }
    tmp%=100;
    if(tmp/10 > 1){ 
        strcat(sre,hn[tmp/10 -2]);
		if(tmp%10 > 0)
			strcat(sre,tn[tmp%10 -1]);
    }else if(tmp > 0 && tmp<20){
        strcat(sre,tn[tmp-1]);
    }   

	sre[strlen(sre)-1]='\0';
	return sre;
}

int main()
{
	int t = 101;
	char *s;

	s = numberToWords(t);
	printf("%d:%s\n",t,s);

	return 1;
}
