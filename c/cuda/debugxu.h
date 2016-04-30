/*************************************************************************
	> File Name: debugxu.h
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年04月08日 星期五 10时48分36秒
 ************************************************************************/

#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"

#ifndef __DEBUGXU_H__
#define __DEBUGXU_H__
 
#ifndef UNDEBUG_FILE
#define DEBUG_FLAG 1
#else
#define DEBUG_FLAG 0
#endif
 
#if (DEBUG_FLAG == 1)
 
static unsigned int __sdebug_time = 0;
#define  __debug_Msg_Size 1024
static char __pdebug_Msg[__debug_Msg_Size];
//注意下面的__attribute__不是C标准。。。。
static void __debug_info(const char *prefix,const char *fmt, ...) __attribute__((format (printf, 2, 3)));
#define __NEXT_DBG_TIME() do{sdebug_time++;}while(0)
#define __PRINT_POS() do {fprintf(stderr,"%s(%d){%s}",__FILE__,__LINE__,__func__);}while(0)
#define __FUNC_LOG() do{__PRINT_POS();fprintf(stderr,": t = %d ",__sdebug_time++);} while(0)
#define __FUNC_LOGn() do{__FUNC_LOG();fprintf(stderr,"\n");} while(0)
#define __PRINT_POS_exp(exp) do{__PRINT_POS();fprintf(stderr,"| (%s):",#exp);}while(0)
#define __PRINT_POS_P_exp(prefix,exp) do{__PRINT_POS();fprintf(stderr,"|<%s> (%s):",prefix,#exp);}while(0)
#define __PRINT_POS_expn(exp)  do{__PRINT_POS_exp(exp);fprintf(stderr,"\n");}while(0)
#define __PRINT_POS_P_expn(prefix,exp) do{__PRINT_POS_P_exp(prefix,exp);fprintf(stderr,"\n");}while(0)
#define __ASSERT(exp) do{if (exp){}else{__PRINT_POS_P_expn("ASSERT ERROR",exp);}}while (0)
#define __ASSERT_EXIT(exp) do{if (exp){}else{__PRINT_POS_P_expn("ASSERT ERROR",exp);exit(1);}}while (0)
 
#define __debug_info_LOG(exp,PREFIX,fmt,...) do{if (exp){__PRINT_POS_P_exp(PREFIX,exp);__debug_info(PREFIX,fmt,__VA_ARGS__);}}while (0)
 
#define __ASSERT_LOG(exp,fmt,...) __debug_info_LOG(exp,"ASSERT!",fmt,__VA_ARGS__)
#define __ERROR_LOG(exp,fmt,...) __debug_info_LOG(exp,"ERROR!",fmt,__VA_ARGS__)
define __BEFORE_LOG(N,fmt,...)  do {__debug_info_LOG((N) < __sdebug_time,"BEFORE!",fmt,__VA_ARGS__);__NEXT_DBG_TIME()}while(0) 
#define __AFTER_LOG(N,fmt,...) do {__debug_info_LOG((N) >= __sdebug_time,"AFTER!",fmt,__VA_ARGS__); __NEXT_DBG_TIME();}while(0) 
static void __debug_info(const char *prefix,const char *fmt, ...) {
    va_list params; 
    va_start(params, fmt);
    __ASSERT_EXIT((__pdebug_Msg) && (__pdebug_Msg_Size ));
    vsnprintf(__pdebug_Msg, __pdebug_Msg_Size, fmt, params);
    if (prefix){
        fprintf(stderr, " %s %s\n", prefix, __pdebug_Msg);
    }else{
        fprintf(stderr, " %s\n", __pdebug_Msg);
    }
    va_end(params);
}
#else
#define __NOP do{}while(0)
#define __NEXT_DEBUG_TIME() __NOP
#define __FUNC_LOGn() __NOP
#define __FUNC_LOG() __NOP
#define __PRINT_POS_Sn(exp)  __NOP
#define __PRINT_POS_S(exp) __NOP
#define __ASSERT(exp) __NOP
#define __ASSERT_EXIT(exp) __NOP
#define __debug_info_LOG(exp,PREFIX,fmt,...) __NOP
#define __ASSERT_LOG(exp,fmt,...) __NOP
#define __ERROR_LOG(exp,fmt,...) __NOP
#define __BEFORE_LOG(N,fmt,...) __NOP 
#define __AFTER_LOG(N,fmt,...) __NOP  
 
#endif

#endif
