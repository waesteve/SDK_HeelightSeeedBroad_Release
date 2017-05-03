
#pragma once

typedef unsigned char u8 ;
typedef signed char s8;

typedef unsigned short u16;
typedef signed short s16;

typedef int s32;
typedef unsigned int u32;

typedef long long s64;
typedef unsigned long long u64;

//typedef unsigned char bool;

#ifndef NULL
#define NULL 	0
#endif

#ifndef __cplusplus

typedef u8 bool;

//#ifndef FALSE
#define FALSE 	0
//#endif

//#ifndef TRUE
#define TRUE 	(!FALSE)
//#endif

#define false 	FALSE
#define true 	TRUE


#endif
