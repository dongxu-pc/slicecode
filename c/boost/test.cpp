/*************************************************************************
	> File Name: test.cpp
	> Author: Yandong Xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年01月21日 星期四 14时44分22秒
 ************************************************************************/

#include<iostream>
#include<boost/lexical_cast.hpp>
using namespace std;

int main()
{
	int a = boost::lexical_cast<int>("123456");

	std::cout<< a <<std::endl;
	return 0;
}

