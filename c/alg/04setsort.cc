/*************************************************************************
	> File Name: 04setsort.cc
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年04月16日 星期六 13时57分24秒
 ************************************************************************/

#include <iostream>
#include <set>
using namespace std;

int main()
{
	int i,n=11;
	int a[]={2,6,3,7,4234,2341,123,23,5,1,35};
	set<int> S;
	set<int>::iterator j;

	for(i = 0;i<n;i++)
		S.insert(a[i]);

	for(j=S.begin();j!=S.end();j++)
		cout<<*j<<" ";
	cout<<endl;
	return 0;

}
