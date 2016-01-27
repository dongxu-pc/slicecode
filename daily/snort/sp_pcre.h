/*
** Copyright (C) 2003 Brian Caswell <bmc@snort.org>
** Copyright (C) 2003 Michael J. Pomraning <mjp@securepipe.com>
** Copyright (C) 2014-2015 Cisco and/or its affiliates. All rights reserved.
** Copyright (C) 2003-2013 Sourcefire, Inc.
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License Version 2 as
** published by the Free Software Foundation.  You may not use, modify or
** distribute this program under any other version of the GNU General
** Public License.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

/*  I N C L U D E S
**********************************************************/

/*  D E F I N E S
************************************************************/
#ifndef __SNORT_PCRE_H__
#define __SNORT_PCRE_H__

// low nibble must be same as HTTP_BUFFER_*
// see detection_util.h for enum
#define SNORT_PCRE_HTTP_URI         0x00001 // check URI buffers
#define SNORT_PCRE_HTTP_HEADER      0x00002 // Check HTTP header buffer
#define SNORT_PCRE_HTTP_BODY        0x00003 // Check HTTP body buffer
#define SNORT_PCRE_HTTP_METHOD      0x00004 // Check HTTP method buffer
#define SNORT_PCRE_HTTP_COOKIE      0x00005 // Check HTTP cookie buffer
#define SNORT_PCRE_HTTP_STAT_CODE   0x00006
#define SNORT_PCRE_HTTP_STAT_MSG    0x00007
#define SNORT_PCRE_HTTP_RAW_URI     0x00008
#define SNORT_PCRE_HTTP_RAW_HEADER  0x00009
#define SNORT_PCRE_HTTP_RAW_COOKIE  0x0000A
#define SNORT_PCRE_HTTP_BUFS        0x0000F
#define SNORT_PCRE_RELATIVE         0x00010 // relative to the end of the last match
#define SNORT_PCRE_INVERT           0x00020 // invert detect
#define SNORT_PCRE_RAWBYTES         0x00040 // Don't use decoded buffer (if available)
#define SNORT_PCRE_ANCHORED         0x00080
#define SNORT_OVERRIDE_MATCH_LIMIT  0x00100 // Override default limits on match & match recursion

void SetupPcre(void);

#include <pcre.h>
typedef struct _PcreData
{
    pcre *re;           /* compiled regex */
    pcre_extra *pe;     /* studied regex foo */
    int options;        /* sp_pcre specfic options (relative & inverse) */
    char *expression;
    uint32_t search_offset;
} PcreData;

void PcreCapture(struct _SnortConfig *sc, const void *code, const void *extra);
void PcreFree(void *d);
uint32_t PcreHash(void *d);
int PcreCompare(void *l, void *r);
void PcreDuplicatePcreData(void *src, PcreData *pcre_dup);
int PcreAdjustRelativeOffsets(PcreData *pcre, uint32_t search_offset);
void PcreCheckAnchored(PcreData *);

#endif /* __SNORT_PCRE_H__ */


5. 使用PCRE在C语言中实现正则表达式的解析
上述讲了这么多PCRE相关函数的介绍，目的还是为了能够运用上，所以这里就先讲解下使用PCRE的过程。主要过程分三步走第一步编译正则表达式；第二匹配正则表达式；第三步释放正则表达式。
1．编译正则表达式
为了提高效率，在将一个字符串与正则表达式进行比较之前，首先要用pcre_compile() /pcre_compile2() 函数对它时行编译，转化成PCRE引擎能够识别的结构（struct real_pcre）。
这里还可以调用pcre_study()函数，对编译后的正则表达式结构（struct real_pcre）时行分析和学习，学习的结果是一个数据结构（struc pcre_extra），这个数据结构连同编译后的规则（struct real_pcre）可以一起送给pcre_exec单元进行匹配。
2. 匹配正则表达式
一旦用函数pcre_compile() /pcre_compile2()成功地编译了正则表达式，接下来就可以调用pcre_exec（）函数完成模式匹配。根据正则表达式到指定的字符串中进行查找和匹配,并输出匹配的结果。
3. 释放正则表达式
无论什么时候，当不再需要已经编译过的正则表达式时，都应该调用函数free()将其释放，以免产生内在泄漏。