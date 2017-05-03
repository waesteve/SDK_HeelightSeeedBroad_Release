//
//  ToneProtocolTypes.h
//  RedisAudioPackageHandlerC
//  2.2.1
//  Created by jiapeng on 16/2/25.
//  Copyright © 2016年 jiapeng. All rights reserved.
//

#ifndef ToneProtocolTypes_h
#define ToneProtocolTypes_h

#include "HeelightEffectConfig.h"
#if (IS_EMBEDDED ==1 )
#include "../../proj/common/types.h"
#else
#include "types.h"
#endif

#define INVALID_TONEPACKAGE 0xFFFFFFFFF

//#define TONE_TYPE_CONTROL_MODULE    0

#define TONE_TYPE_SET_COLORS                            1    //001
#define TONE_TYPE_SET_DIY                               2    //010
#define TONE_TYPE_SET_LIFI                              5
#define TONE_TYPE_SET_OTHERS                            6


#define TONE_TYPE_SET_OTHERS_CHILD_SIMPLECOMMAND        1
#define TONE_TYPE_SET_OTHERS_CHILD_DELAYSWITCH          2
#define TONE_TYPE_SET_OTHERS_CHILD_CHANGELIGHTNESS      3
#define TONE_TYPE_SET_OTHERS_CHILD_HSL                  4
#define TONE_TYPE_SET_OTHERS_CHILD_CT                   5
#define TONE_TYPE_SET_OTHERS_CHILD_PATTLE16             6


#define TONE_TYPE_SET_DIY_CHILD_LIGHT_EFFECT_WITHOUT_AUDIO            1
#define TONE_TYPE_SET_DIY_CHILD_LIGHT_EFFECT_WITH_AUDIO               2
#define TONE_TYPE_SET_DIY_CHILD_MUSIC                                 3
#define TONE_TYPE_SET_DIY_CHILD_CHANGEMODELONLYCOLOR                  4

#define IS_USE_ENBEDDED_CALIBRATION TRUE

/*!
 *    @brief <#Description#>
 *
 *    @param a
 *
 *    @return <#return value description#>
 */
#define isToneTypeSupportCRC(a) ((a==TONE_TYPE_SET_OTHERS||a==TONE_TYPE_SET_LIGHT_EFFECT_WITHOUT_AUDIO||a==TONE_TYPE_SET_LIGHT_EFFECT_WITH_AUDIO)?:TRUE:FALSE )

#endif /* ToneProtocolTypes_h */
