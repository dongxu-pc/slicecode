/*************************************************************************
	> File Name: 01longsubstr.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月10日 星期四 14时08分29秒
 ************************************************************************/

#include<stdio.h>
#include "string.h"

/**
 * find the longest substring int the string
 * 
 */

nt lengthOfLongestSubstring(char* s){ 
    char* ht; 
    int re,len=strlen(s);
    int tmp,tlen,i;

    ht = (char *)malloc(256*sizeof(char));
    memset(ht,'\0',256*sizeof(char));
    re = 0,tmp=0;tlen=0;i=0;
    
    tlen = 0;
    while(tlen < len){
        if(ht[s[tlen]] == 0){
            ht[s[tlen]] = 1;
            tmp++;
        }else if(re < tmp){
            re = tmp;
            for(i = tlen-1;i >= 0;i--){
                if(s[tlen] == s[i]){
                    tlen = i;
                    break;
                }
            }
            tmp = 0;
            memset(ht,'\0',256*sizeof(char));
        }else{
            for(i = tlen-1;i >= 0;i--){
                if(s[tlen] == s[i]){
                    tlen = i;
                    break;
                }
            }
            tmp = 0;
            memset(ht,'\0',256*sizeof(char));
        }
        
        tlen++;
    }
    if(re < tmp)
        {re = tmp;}
    free(ht);
    return re;
}

