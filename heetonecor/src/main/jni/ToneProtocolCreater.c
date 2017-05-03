//
//  ToneProtocolCreater.c
//  RedisAudioPackageHandlerC
//  2.2.1
//  Created by jiapeng on 16/2/25.
//  Copyright © 2016年 jiapeng. All rights reserved.
//

#include "ToneProtocolCreater.h"
#include "HeelightMath.h"

/*!
 *    长控制包设置灯颜色
 *    @param red   0~2047
 *    @param green 0~2047
 *    @param blue  0~2047
 */
u64 assemMixColorTonePackage(u8 groupID,u16 red , u16 green , u16 blue  ){
    u64 headPart;
    u32 tailPart ;
    headPart = (TONE_TYPE_SET_COLORS<<1) ;
    tailPart = ((red&0x3FF)<<20) + ((green&0x7FF)<<10) + ((blue&0x7FF ));
    headPart = (headPart|(groupID>>1));
    tailPart = (tailPart|(groupID<<31));
    return ((headPart<<32)+tailPart);
}

/*!
 *    @brief 普通动效
 *    @param partIndex      （0~3）
 *    @param nextModel      （0~3）
 *    @param duration       （0~15）亮度动态周期
 *    @param lightnessModel （0~15）亮度动态的模式
 *    @param basecolor      （0~15）基本颜色
 *    @return <#return value description#>
 */
u64 assemDIYEffectTonePackage( u8 diyID ,u8 groupID,  u8 partIndex, u8 nextModel, u8 duration ,u8 lightnessModel, u8 basecolor  ){
    u64 headPart;
    u32 tailPart ;
    u8 tailBytePart[4];
    headPart = ((u64)((TONE_TYPE_SET_DIY << 1)|(groupID>>1)) <<32);
    
    tailPart =  ((TONE_TYPE_SET_DIY_CHILD_LIGHT_EFFECT_WITHOUT_AUDIO&0x07)<<20)+((diyID&0x03)<<18)
                        +((u32)(partIndex&03)<<14) + ((u32)(nextModel&03)<<12)
                        + ((u32)(duration&0x0F)<<8) + ((u32)(lightnessModel&0xF)<<4) + (basecolor) ;
    tailPart<<=(8);
    
    tailPart = ((tailPart|(groupID<<31))&0xFFFFFFFF);
    
    tailBytePart[0] = (tailPart>>24) ;
    tailBytePart[1] = (tailPart>>16);
    tailBytePart[2] = (tailPart>>8) ;
    tailBytePart[3] = crc8Simple( tailBytePart, 3);
    tailPart = (tailBytePart[0]<<24) +(tailBytePart[1]<<16) + (tailBytePart[2]<<8) + (tailBytePart[3]);
    headPart +=tailPart;
    return headPart  ;
}

/*!
 *    @brief 声效动态音频
 *    @param partIndex      （0~3）
 *    @param nextModel      （0~3）
 *    @param audioModel     （0~15）声效动态的模式
 *    @param lightnessModel （0~15）亮度动态的模式
 *    @param basecolor      （0~15）基本颜色
 *    @return
 */
u64 assemDIYAudioEffectTonePackage( u8 diyID,u8 groupID, u8 partIndex, u8 nextModel, u8  audioModel ,u8 lightnessModel, u8 basecolor  ){
    u64 headPart;
    u32 tailPart ;
    u8 tailBytePart[4];
    headPart = ((u64)((TONE_TYPE_SET_DIY << 1)|(groupID>>1)) <<32);
    
    tailPart = ((TONE_TYPE_SET_DIY_CHILD_LIGHT_EFFECT_WITH_AUDIO&0x07)<<20)+((diyID&0x03)<<18)
            +((u32)(partIndex&03)<<14) + ((u32)(nextModel&03)<<12)
            + ((u32)(audioModel&0x0F)<<8) + ((u32)(lightnessModel&0xF)<<4) + (basecolor) ;
    tailPart<<=(8);
    tailPart = ((tailPart|(groupID<<31))&0xFFFFFFFF);
    
    tailBytePart[0] = (tailPart>>24) ;
    tailBytePart[1] = (tailPart>>16);
    tailBytePart[2] = (tailPart>>8) ;
    tailBytePart[3] = crc8Simple( tailBytePart, 3);
    tailPart = (tailBytePart[0]<<24) +(tailBytePart[1]<<16) + (tailBytePart[2]<<8) + (tailBytePart[3]);
    headPart +=tailPart;
    return headPart  ;
    
}

/*!
 *    @brief 设置音乐模式下的颜色.
 *    @param colors     <#colors description#>
 *    @param colorCount <#colorCount description#> (1~4 )
 *    @return <#return value description#>
 */
u64 assemDIYMusicModelWithColorTonePacakge(u8 diyID,u8 groupID, u8 *colors ,u8 colorCount ){
    if( colorCount ==0 ){
        return INVALID_TONEPACKAGE;
    }
    u64 headPart;
    u32 tailPart ;
    u8 tailBytePart[4];
    headPart = ((u64)((TONE_TYPE_SET_DIY << 1)|(groupID>>1)) <<32);
    
    tailBytePart[0] = ( ((groupID<<7)&0xFF) + ((TONE_TYPE_SET_DIY_CHILD_MUSIC&0x07)<<4) +((diyID&0x03)<<2) +(colorCount-1) ) ;
    tailBytePart[1] = (((colors[0]<<4) + (colors[1])) &0xFF);
    tailBytePart[2] = (((colors[2]<<4) + (colors[3])) &0xFF);
    tailBytePart[3] = crc8Simple( tailBytePart, 3);
    
    tailPart = (tailBytePart[0]<<24) +(tailBytePart[1]<<16) + (tailBytePart[2]<<8) + (tailBytePart[3]);
    headPart +=tailPart;
    return headPart  ;
}

/*!
 *    @brief
 *    给特定的模式设置唯一的基色
 *    @param groupID
 *    @param colorIndex 调色板颜色【0~15】
 *    @param modelID    【1 代表sex， 2 代表音乐， 】
 *
 *    @return <#return value description#>
 */
u64 assemDIYModelOnlyColorTonePacakge(u8 diyID, u8 groupID, u8 colorIndex, u8 modelID ){
    u64 headPart;
    u32 tailPart ;
    u8 tailBytePart[4];
    headPart = ((u64)((TONE_TYPE_SET_DIY << 1)|(groupID>>1)) <<32);
    
    tailBytePart[0] = ( ((groupID<<7)&0xFF) + ((TONE_TYPE_SET_DIY_CHILD_CHANGEMODELONLYCOLOR&0x07)<<4) +((diyID&0x03)<<2) ) ;
    tailBytePart[1] = (colorIndex<<4)&0xFF;
    tailBytePart[2] = (modelID&0xFF);
    tailBytePart[3] = crc8Simple( tailBytePart, 3);
    tailPart = (tailBytePart[0]<<24) +(tailBytePart[1]<<16) + (tailBytePart[2]<<8) + (tailBytePart[3]);
    headPart +=tailPart;
    
    return headPart  ;
}



/*!
 *    @brief 用长码代表短码
 */
u64 assemControlModelTonePacakge( u8 groupID,short commandValue){
    u64 headPart;
    u32 tailPart ;
    u8 tailBytePart[4];
    headPart = ((u64)((TONE_TYPE_SET_OTHERS << 1)|(groupID>>1)) <<32);
    
    tailBytePart[0] = ((TONE_TYPE_SET_OTHERS_CHILD_SIMPLECOMMAND<<4)&0xFF)|((groupID<<7)&0xFF);
    tailBytePart[1] = ((commandValue>>8) & 0x01 );
    tailBytePart[2] = (commandValue &0xFF);
    tailBytePart[3] = crc8Simple( tailBytePart, 3);
    tailPart = (tailBytePart[0]<<24) +(tailBytePart[1]<<16) + (tailBytePart[2]<<8) + (tailBytePart[3]);
    headPart +=tailPart;
    return headPart  ;
    
}




/*!
 *    @brief 延时开关灯
 *
 *    @param timeDelay 延时分钟数
 *    @param cmd      1开灯, 0 关灯 ,2 代表清除
 *    @return <#return value description#>
 */
u64 assemDelayedLightSwitchTonePacakge(u8 groupID, short timeDelay, u8 cmd){
    u64 headPart;
    u32 tailPart ;
    u8 tailBytePart[4];
    headPart = ((u64)((TONE_TYPE_SET_OTHERS << 1)|(groupID>>1)) <<32);
    tailBytePart[0] = ((((TONE_TYPE_SET_OTHERS_CHILD_DELAYSWITCH<<4)&0xFF) | (cmd&0x0F))|((groupID<<7)&0xFF));
    tailBytePart[1] = ((timeDelay>>8) &0x07);
    tailBytePart[2] = ((timeDelay) &0xFF);
    tailBytePart[3] = crc8Simple( tailBytePart, 3);
    tailPart = (tailBytePart[0]<<24) +(tailBytePart[1]<<16) + (tailBytePart[2]<<8) + (tailBytePart[3]);
    headPart +=tailPart;
    return headPart  ;
}

/*!
 *    @brief 调节等的亮度.
 *    @param lightness100 0~100
 *    @return
 */
u64 assemChangeLightnessTonePacakge(u8 groupID, u8 lightness100){
    u64 headPart;
    u32 tailPart ;
    u8 tailBytePart[4];
    headPart = ((u64)((TONE_TYPE_SET_OTHERS << 1)|(groupID>>1)) <<32);
   
    tailBytePart[0] = ((((TONE_TYPE_SET_OTHERS_CHILD_CHANGELIGHTNESS<<4)&0xFF))|((groupID<<7)&0xFF));
    tailBytePart[1] = ((lightness100) &0xFF);
    tailBytePart[2] = 0;
    tailBytePart[3] = crc8Simple( tailBytePart, 3);
    tailPart = (tailBytePart[0]<<24) +(tailBytePart[1]<<16) + (tailBytePart[2]<<8) + (tailBytePart[3]);
    headPart +=tailPart;
    return headPart  ;
}


/*!
 *    @brief HSL
 *
 *    @param groupID
 *    @param h        hue 0~360
 *    @param s        saturation 0~100
 *    @param v        value 0~100
 *
 *    @return <#return value description#>
 */
u64 assemHSLTonePacakge( u8 groupID, short h, u8 s,u8 v ){
    u64 headPart;
    u32 tailPart ;
    u8 tailBytePart[4];
    headPart = ((u64)((TONE_TYPE_SET_OTHERS << 1)|(groupID>>1)) <<32);
    
    tailBytePart[0] = (((TONE_TYPE_SET_OTHERS_CHILD_HSL<<4)&0xFF)|((groupID<<7)&0xFF));
    tailBytePart[1] = (h>>1)&0xFF;
    tailBytePart[2] = ((h&0x01)<<7) + (s&0x7F);
    tailBytePart[3] = (v&0xFF);
    tailPart = (tailBytePart[0]<<24) +(tailBytePart[1]<<16) + (tailBytePart[2]<<8) + (tailBytePart[3]);
    headPart +=tailPart;
    
    return headPart  ;
}


/*!
 *    @brief CT
 *
 *    @param groupID
 *    @param ct      色温  1700~8000
 *    @param v       value
 *
 *    @return <#return value description#>
 */
u64 assemCTTonePacakge( u8 groupID, short ct, u8 v ){
    u64 headPart;
    u32 tailPart ;
    u8 tailBytePart[4];
    headPart = ((u64)((TONE_TYPE_SET_OTHERS << 1)|(groupID>>1)) <<32);
    
    tailBytePart[0] = (((TONE_TYPE_SET_OTHERS_CHILD_CT<<4)&0xFF)|((groupID<<7)&0xFF));
    tailBytePart[1] = (ct>>8)&0xFF;
    tailBytePart[2] = (ct&0xFF);
    tailBytePart[3] = (v&0xFF);
    tailPart = (tailBytePart[0]<<24) +(tailBytePart[1]<<16) + (tailBytePart[2]<<8) + (tailBytePart[3]);
    headPart +=tailPart;
    
    return headPart  ;

    
}

/*!
 *    @brief 使用调色板的16色调色 和亮度.
 *
 *    @param groupID      <#groupID description#>
 *    @param colorIndex   <#colorIndex description#>
 *    @param lightness100 <#lightness100 description#>
 *    @return <#return value description#>
 */
u64 assemChangePattle16ColorTonePacakge( u8 groupID, u8 colorIndex, u8 lightness100 ){
    u64 headPart;
    u32 tailPart ;
    u8 tailBytePart[4];
    headPart = ((u64)((TONE_TYPE_SET_OTHERS << 1)|(groupID>>1)) <<32);
    
    tailBytePart[0] = (((TONE_TYPE_SET_OTHERS_CHILD_PATTLE16<<4)&0xFF)|((groupID<<7)&0xFF));
    tailBytePart[1] = ((lightness100) &0xFF);
    tailBytePart[2] = ((colorIndex<<4)&0xFF);
    tailBytePart[3] = crc8Simple( tailBytePart, 3);
    tailPart = (tailBytePart[0]<<24) +(tailBytePart[1]<<16) + (tailBytePart[2]<<8) + (tailBytePart[3]);
    headPart +=tailPart;
    return headPart  ;
}




/*
u64 assemChangeLightnessTonePacakge(u8 groupID, short h, short s, short v ){
    u64 headPart;
    u32 tailPart ;
    u8 tailBytePart[4];
    //headPart = ((u64)(TONE_TYPE_SET_OTHERS << 1) <<32);
    headPart = ((u64)((TONE_TYPE_SET_OTHERS << 1)|(groupID>>1)) <<32);
    
    tailBytePart[0] = ((0b01010000)|((groupID<<7)&0xFF));
    tailBytePart[1] = ((lightness100) &0xFF);
    tailBytePart[2] = 0;
    tailBytePart[3] = crc8Simple( tailBytePart, 3);
    tailPart = (tailBytePart[0]<<24) +(tailBytePart[1]<<16) + (tailBytePart[2]<<8) + (tailBytePart[3]);
    headPart +=tailPart;
    return headPart  ;
}

*/

u64 assemLifiSettingsTonePackage( u32 data , u8 duration ){
    u64 headPart;
    u32 tailPart ;
    
    headPart = (TONE_TYPE_SET_LIFI<<1) ;
    tailPart = ( ((duration&0xFF)<<24)+ (data&0xFFFFFF) );
    
    
    return ((u64)(headPart<<32))+( tailPart);
}

