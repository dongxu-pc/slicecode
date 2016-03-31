/*************************************************************************
	> File Name: 01trie.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月30日 星期三 16时36分20秒
 ************************************************************************/

/**********************************************************
数据结构:
Trie树,又称单词查找树或字典树,是一种树形结构,是一种哈希树的变种;

基本原理：
Trie树的核心思想是空间换时间,利用字符串的公共前缀来降低查询时间的开销以达到提高效率的目的;

应用：
用于统计和排序大量的字符串(但不仅限于字符串),所以经常被搜索引擎系统用于文本词频统计;

优点：
最大限度地减少无谓的字符串比较,查询效率比哈希表高;

基本特性：
(1)根节点不包含字符,除根节点外每一个节点都只包含一个字符;
(2)从根节点到某一节点,路径上经过的字符连接起来,为该节点对应的字符串;
(3)每个节点的所有子节点包含的字符都不相同;

***********************************************************/

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"

#define MAX 26

struct Trie//Trie结点声明
{
    int isStr;//标记该结点处是否构成一个串
    struct Trie* next[MAX];//一个指针数组，存放着指向各个儿子节点的指针
};

void insert(struct Trie *root,const char *s) //将单词s插入到字典树中
{
	int i=0;
    if(root==NULL || *s=='\0')
        return;
    struct Trie *troot = root;
	char *ts = s;
    while(*ts)
    {
        if(troot->next[*ts-'a']==NULL)//如果不存在存储该字符的节点，则建立结点
        {
            struct Trie *temp=(struct Trie*)malloc(sizeof(struct Trie));
            for(i=0; i<MAX; i++)
            {
                temp->next[i]=NULL;
            }
            temp->isStr=0;
            troot->next[*ts-'a']=temp;
            troot=troot->next[*ts-'a'];
        }
        else
        {
            troot=troot->next[*ts-'a'];
        }
        ts++;//让指针s指向下一个字符
    }
    troot->isStr=1;//单词结束的地方标记此处可以构成一个串
}

int search(struct Trie *root,const char *s)//查找某个单词s是否已经存在
{
    struct Trie *troot=root;
	char* ts=s;
    while(troot && *ts)
    {
        troot = troot->next[*ts-'a'];
        ts++;
    }
	if((troot != NULL) && (troot->isStr == 1))
		return 1;
    return 0;  //在单词结束处的标记为true时，单词才存在
}

void del(struct Trie *root)//释放整个字典树占的堆区空间
{
	int i=0;
    for(i=0; i<MAX; i++)
    {
        if(root->next[i]!=NULL)
        {
            del(root->next[i]);
        }
    }
    free(root);
}

int main()
{
    //freopen("C:\\Users\\Administrator\\Desktop\\kd.txt","r",stdin);
    char s[100];
	int i;
    struct Trie* root = (struct Trie*)malloc(sizeof(struct Trie));
    for(i=0; i<MAX; i++)
    {
        root->next[i]=NULL;
    }
    root->isStr=0;
    int n,m; //n为建立Trie树输入的单词数，m为要查找的单词数
    scanf("%d",&n);
    for(i=0; i<n; i++) //先建立字典树
    {
        scanf("%s",s);
        insert(root,s);
    }
	printf("find\n");
    while(~scanf("%d",&m))
    {
        if(!m)
            break;
        for(i=0; i<m; i++) //查找
        {
            scanf("%s",s);
            if(search(root,s))
                printf("YES\n");
            else
                printf("NO\n");
        }
        printf("\n");
    }
    del(root); //释放空间很重要
    return 0;
}

