/*************************************************************************
	> File Name: char_t02.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2015年11月27日 星期五 22时43分59秒
 ************************************************************************/

#include<stdio.h>

#include "string.h"
#include "stdint.h"

int main(void)
{
	unsigned char text[] = "MOTO宣布强势回归中国";
	int i;
	int text_length;

	text_length = strlen((char *)text);
	printf("string length:%d\n",text_length);
	//text_length = strlen((signed char *)text);
	printf("string length:%d\n",text_length);
	//text_length = strlen((signed char)((unsigned char *)text));
	//key_length = strlen((const char *)key);
	printf("string length:%d\n",text_length);
	printf("char 类型输出: \n");
	for (i = 0; i < text_length; i++)
		printf("%02X", text[i]);
	printf("\n");

	printf("unsigned char 类型输出: \n");
	for (i = 0; i < text_length; i++)
		printf("%02X", (unsigned char)text[i]);
	printf("\n");

	printf("uint8_t 类型输出: \n");
	for (i = 0; i < text_length; i++)
		printf("%02X", (uint8_t)text[i]);
	printf("\n");

	return 0;
}
