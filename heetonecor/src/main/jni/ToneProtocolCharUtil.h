//
//  ToneProtocolCharUtil.h
//  RedisAudioPackageHandlerC
//  2.2.1
//  Created by jiapeng on 12/28/15.
//  Copyright © 2015 jiapeng. All rights reserved.
//
#pragma once

#ifndef ToneProtocolCharUtil_h
#define ToneProtocolCharUtil_h
#include "HeelightEffectConfig.h"

#include "types.h"
#include "ToneProtocolTypes.h"
void create_RGBPWMSettings_ToneStrPackage(u8 groupID, u16 red , u16 green , u16 blue , char* resultStr );
void create_HSVPWMSettings_ToneStrPackage(u8 groupID, u16 h, u16 s , u16 v , char* resultStr );
void create_CTPWMSettings_ToneStrPackage(u8 groupID, u16 ct, u16 v , char* resultStr );

void create_DIYMusicEffectSettings_ToneStrPackage(u8 diyID,u8 groupID, u8 color1, u8 color2, u8 color3, u8 color4, u8 colorCount, char* resultStr  );

void create_DIYEffectSettings_ToneStrPackage(u8 diyID,u8 groupID, u8 partIndex,
                                          u8 nextModel, u8 duration ,u8 lightnessModel, u8 basecolor , char* resultStr  );
void create_DIYAudioEffectSettings_ToneStrPackage(u8 diyID,u8 groupID, u8 partIndex,
                                               u8 nextModel, u8  audioModel ,u8 lightnessModel, u8 basecolor , char* resultStr );
void create_DIYModelOnlyColor_ToneStrPackage(u8 diyID,u8 groupID, u8 baseColor, u8 modelID, char* resultStr );

void create_ChangeLightness_ToneStrPackage(u8 groupID,u8 lightness100, char* resultStr );
void create_DelayedLightSwitch_ToneStrPackage(u8 groupID,short timeDelay, u8 isON, char* resultStr );
void create_SimpleCommand_ToneStrPackage(u8 groupID, short command, char* resultStr );
void create_LifiSettings_ToneStrPackage( u32 data , u8 duration, char* resultStr );
void create_ChangePattle16_ToneStrPackage(u8 groupID,u8 baseColor, u8 lightness100, char* resultStr );
u64 resolveToneCharsPackage(const char *tone );

void parseU64To512Arrays(u64 sourceData, short *tx_data );


#endif /* ToneProtocolCharUtil_h */