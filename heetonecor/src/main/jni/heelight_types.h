#pragma once
#include "HeelightEffectConfig.h"
#if (IS_EMBEDDED ==1 )
#include "../../proj/common/types.h"
#else
#include "types.h"
#endif

#define SUCCESS                   0x00
#define FAILURE                   0x01

#define ENABLE 1
#define DISABLE !ENABLE

#define NEED 1
#define NEEDNOT !NEED
#ifndef lightmode_data_t
typedef u16 lightmode_data_t ;
#endif
#include "HeelightEffectConfig.h"
#if DEBUG_ENABLE
#define DEBUG_MSG printf
#else
#define DEBUG_MSG(...)
#endif


#if ERROR_ENABLE
#define ERROR_MSG printf
#else
#define ERROR_MSG(...)
#endif



typedef enum {
	LMT_UNDEFINED =0, LMT_STATIC=1, LMT_DYNAMIC
}LIGHT_MODE_TYPE;



#ifndef NULL
#define NULL 	0
#endif

/*
 #define LIGHT_OFF 0
 #define LIGHT_ON (!LIGHT_OFF)
 */

#define HEELIGHT_OFF 0
#define HEELIGHT_ON  1
#define HEELIGHT_CHANGING 2

#define PWM_MAX_SCALE 16000



