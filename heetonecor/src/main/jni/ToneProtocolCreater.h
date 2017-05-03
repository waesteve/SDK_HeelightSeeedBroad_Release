//
//  ToneProtocolCreater.h
//  RedisAudioPackageHandlerC
//  2.2.1
//  Created by jiapeng on 16/2/25.
//  Copyright © 2016年 jiapeng. All rights reserved.
//

#ifndef ToneProtocolCreater_h
#define ToneProtocolCreater_h
#include "ToneProtocolTypes.h"

u64 assemControlModelTonePacakge( u8 groupID, short commandValue  );
u64 assemMixColorTonePackage( u8 groupID,u16 red , u16 green , u16 blue  );

u64 assemDIYEffectTonePackage( u8 diyID, u8 groupID ,  u8 partIndex, u8 nextModel, u8 duration ,u8 lightnessModel, u8 basecolor );
u64 assemDIYAudioEffectTonePackage( u8 diyID, u8 groupID,u8 partIndex, u8 nextModel, u8  audioModel ,u8 lightnessModel, u8 basecolor );
u64 assemDIYMusicModelWithColorTonePacakge(u8 diyID, u8 groupID, u8 *colors ,u8 colorCount );
u64 assemDIYModelOnlyColorTonePacakge(u8 diyID, u8 groupID, u8 colorIndex, u8 modelID );

u64 assemChangeLightnessTonePacakge(  u8 groupID,u8 lightness100);
u64 assemDelayedLightSwitchTonePacakge( u8 groupID, short timeDelay, u8 cmd);
u64 assemCTTonePacakge( u8 groupID, short ct, u8 v );
u64 assemHSLTonePacakge( u8 groupID, short h, u8 s,u8 v );
u64 assemChangePattle16ColorTonePacakge( u8 groupID, u8 colorIndex, u8 lightness100 );


u64 assemLifiSettingsTonePackage( u32 data , u8 duration );


#endif /* ToneProtocolCreater_h */
