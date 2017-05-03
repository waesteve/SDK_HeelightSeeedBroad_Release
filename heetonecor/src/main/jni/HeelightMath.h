//
//  HeelightMath.h
//  RedisAudioPackageHandlerC
//
//  Created by jiapeng on 11/10/15.
//  Copyright © 2015 jiapeng. All rights reserved.
//

#ifndef HeelightMath_h
#define HeelightMath_h
#include "HeelightEffectConfig.h"
#if (IS_EMBEDDED ==1 )
#include "../../proj/common/types.h"
#else
#include "types.h"
#endif

#define max3(a,b,c) (a>b?(a>c?a:c):(b>c?b:c))
#define max2(a,b) (a>b?a:b)
short sin_fixed(int value );
short cos_fixed(int value );

#define HM_SIN_MAX 1024

/*!
 *    @brief  translate light
 *
 *    @param index      <#index description#>
 *    @param start      <#start description#>
 *    @param end        <#end description#>
 *    @param totalCount <#totalCount description#>
 *
 *    @return <#return value description#>
 */
#define LINE_TRANSITE(index,start,end,totalCount) (start + ((end -start )*index) / (totalCount))

int srandomInt(int seed);

int getAudioLevelMapping64(int audioLevelData);
int getAudioLevelMapping64WithBS(int audioLevelData);
int getAudioLevelMappingBIG64(int audioLevelData);
int getAudioLevelMappingBIG64WithBS(int audioLevelData);
int getAudioLevelMapping128(int audioLevelData);
int getAudioLevelMapping128WithBS(int audioLevelData);

short getParabola(short index , short xrange, short min, short max);
/*!
 *    @brief 8bit CRC 校验.
 */
unsigned char crc8Simple( unsigned char* data, int size);
unsigned char crc8_lsb(unsigned char poly, unsigned char* data, int size);
unsigned char crc8_msb(unsigned char poly, unsigned char* data, int size);

void quick_sort(int* s, int l, int r);
#if(DEBUG_ENABLE == ENABLE)
void testMath();
#endif
    
#endif /* HeelightMath_h */
