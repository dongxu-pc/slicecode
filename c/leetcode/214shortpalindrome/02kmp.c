/*************************************************************************
	> File Name: 02kmp.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月19日 星期六 21时06分54秒
 ************************************************************************/

#include<stdio.h>

char* shortestPalindrome(char* s) {
	if (!s || !*s) return strdup("");
    const int N = strlen(s);
    const int HN = (N >> 1);
    int pi[HN], k, i, ch;

    // Get prefix array
    k = pi[0] = 0;
    for (i = 1; i < HN; i++) {
        ch = s[i];
        while ((k > 0) && (ch != s[k])) k = pi[k - 1];
        if (ch == s[k]) k++;
        pi[i] = k;
    }

    // Match in reverse order
    for (i = N - 1, k = 0; i >= k; i--) {
        ch = s[i];
        while ((k > 0) && (ch != s[k])) k = pi[k - 1];
        if (ch == s[k]) k++;
    }

    // Finally, only (N - i - k - 1) chars need to be added to make the shortest palindrome
    int len = N - (i + k);
    char* ret = (char*)malloc((len + N)* sizeof(char));
    if (ret != NULL) {
        char* p = ret;
        for (i = N - 1; i > N - len; i--) *p++ = s[i];
        strcpy(p, s);
    }

    return ret;
}
