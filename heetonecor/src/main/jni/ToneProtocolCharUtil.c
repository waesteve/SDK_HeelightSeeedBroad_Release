//
//  ToneProtocolCharUtil.c
//  RedisAudioPackageHandlerC
//  2.2.1
//  Created by jiapeng on 12/28/15.
//  Copyright © 2015 jiapeng. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ToneProtocolTypes.h"
#include "ToneProtocolCharUtil.h"
#include "ToneProtocolCreater.h"
//#include "ToneProtocolUtil.h"
//#include "LEDCalibration.h"
#include "types.h"

#define TONE_PROTOCOL_TYPE_SET_RGBPWM        1
#define TONE_PROTOCOL_TYPE_SET_MUSICEFFECT   3
#define TONE_PROTOCOL_TYPE_SET_EFFECT        4
#define TONE_PROTOCOL_TYPE_SET_AUDIOEFFECT   5
#define TONE_PROTOCOL_TYPE_SET_LIFI          6
#define TONE_PROTOCOL_TYPE_SET_HSV           7
#define TONE_PROTOCOL_TYPE_SET_CT            8
#define TONE_PROTOCOL_TYPE_SET_SIMPLECOMMANDS 9
#define TONE_PROTOCOL_TYPE_SET_LIGHTNESS      10
#define TONE_PROTOCOL_TYPE_SET_DELAY_SWITHER  11
#define TONE_PROTOCOL_TYPE_SET_PATTLE16     12 //调色板16色
#define TONE_PROTOCOL_TYPE_SET_MODELONLYCOLOR     13 //改变模式的唯一颜色
/*
 u64 assemControlModelTonePacakge( short commandValue  );
 u64 assemMixColorTonePackage(u16 red , u16 green , u16 blue  );
 u64 assemEffectTonePackage( u8 partIndex, u8 nextModel, u8 duration ,u8 lightnessModel, u8 basecolor );
 u64 assemAudioEffectTonePackage( u8 partIndex, u8 nextModel, u8  audioModel ,u8 lightnessModel, u8 basecolor );
 u64 assemLifiSettingsTonePackage( u32 data , u8 duration );
 u64 assemMusicModelWithColorTonePacakge( u8 *colors ,u8 colorCount );
 u64 assemChangeLightnessTonePacakge( u8 lightness100);
 u64 assemDelayedLightSwitchTonePacakge( short timeDelay, u8 isON);
 */

/*!
 *
 *    @brief RGB 灯珠PWM 控制.
 *    @brief 生成PWM 控制灯颜色包
 *    @param red       【0~1000】
 *    @param green     【0~1000】
 *    @param blue      【0~1000】
 *    @param resultStr 结果字符串
 */
const char *pSampleProtocol_SET_RGBPWM = "TYPE=1;GROUP=0;RED=100;GREEN=1000;BLUE=1500;";
/*!
 *    @brief 节奏控制
 *    @param CI【0~3】  颜色，取值范围【0~15】
 */
const char *pSampleProtocol_SET_MUSICEFFECT = "TYPE=3;DIYID=1;GROUP=0;CI1=5;CI2=1;CI3=0;CI4=15;CC=1;";
/*!
 *  @brief 控制动效
 *  @param PINDEX  当前的编辑的模式切片的序号 【0~3】
 *  @param NEXT 当前模式切片执行完后，下一步的行为；  0 下一个切片 1 关灯 2 关灯，2秒后重置当前切片
 *  @param DURATION 周期 【0~11】
 *  @param LMID  当前切片的亮度动态曲线【0~15】
 *  @param BCOLOR  当前的基础颜色.
 */
const char *pSampleProtocol_SET_EffECT = "TYPE=4;DIYID=1;GROUP=0;PINDEX=1;NEXT=1;DURATION=2;LMID=3;BCOLOR=4;";
/*!
 *    @brief 声音控制动效
 *    @param AMID  声效动态的ID【0~15】
 */
const char *pSampleProtocol_SET_AUDIOEffECT = "TYPE=5;DIYID=1;GROUP=0;PINDEX=1;NEXT=1;AMID=2;LMID=3;BCOLOR=4;";



/*!
 *    @brief RGB灯珠PWM 控制.
 *    @brief HSV to RGB  PWM
 *    @param H         【0~360】
 *    @param S         【0~100】
 *    @param V         【0~100】
 */
const char *pSampleProtocol_SET_HSV = "TYPE=7;GROUP=0;H=100;S=100;V=100;";
/*!
 *    @brief RGB灯珠PWM 控制.
 *    @brief CT( 色温) to RGB PWM
 *    @param CT        【1700~8000】, max can 100~10000,but not real
 *    @param V         【0~100】 value ，亮度
 */
const char *pSampleProtocol_SET_CT = "TYPE=8;GROUP=0;CT=5900;V=100;";

/*!
 *    @brief 当指令转换成长指令
 * @param COMMAND 【0~511】
 */
const char *pSampleProtocol_SET_SIMPLECOMMANDS = "TYPE=9;GROUP=0;COMMAND=1;";
/*!
 *    @brief 单独调节亮度
 * @param LIGHTNESS 【0~100】
 */
const char *pSampleProtocol_SET_LIGHTNESS = "TYPE=10;GROUP=0;LIGHTNESS=100;";
/*!
 *    @brief 设置延时开关
 * @param TIMEDELAY 延时分钟
 * @param ISON  【1 代表开灯，0 代表关灯, 2 代表清除开灯，3代表清除关灯，4代表清除开关灯 】
 */
const char *pSampleProtocol_SET_DELAY_SWITHER = "TYPE=11;GROUP=0;TIMEDELAY=900;CMD=1;";

/*!
 *    @brief 使用调色板上面的16色来调整颜色.
 *    @param CI
 *    @param V         【0~100】 value ，亮度
 */
const char *pSampleProtocol_SET_PATTLE16 = "TYPE=12;GROUP=0;CI=0;V=100;";

/*!
 *    @brief   调整模式的颜色
 *    @param CI       颜色Index，
 *    @param MODELID  模式ID 【1 代表SEX， 2 MUSIC】
 */
const char *pSampleProtocol_SET_MODELONLYCOLOR = "TYPE=13;DIYID=2;GROUP=0;CI=0;MODELID=1;";



const char *pFormat_TYPE = "TYPE=%[^;];";

const char *pFormat_ENCODE_SET_RGBPWM = "TYPE=%[^;];GROUP=%[^;];RED=%[^;];GREEN=%[^;];BLUE=%[^;];";
const char *pFormat_DECODE_SET_RGBPWM = "TYPE=%d;GROUP=%d;RED=%d;GREEN=%d;BLUE=%d;";

//u8 color1, u8 color2, u8 color3, u8 color4,u8 bpmMeduimi, u8 bpmDeflection
const char *pFormat_ENCODE_SET_MUSICEFFECT = "TYPE=%[^;];DIYID=%[^;];GROUP=%[^;];CI1=%[^;];CI2=%[^;];CI3=%[^;];CI4=%[^;];CC=%[^;];" ;
const char *pFormat_DECODE_SET_MUSICEFFECT = "TYPE=%d;DIYID=%d;GROUP=%d;CI1=%d;CI2=%d;CI3=%d;CI4=%d;CC=%d;" ;

//u8 ceID , u8 leID, u8 aeID, u8 ceTranslateFunc, u8 ceperiod, u8 leperiod
const char *pFormat_ENCODE_SET_EFFECT = "TYPE=%[^;];DIYID=%[^;];GROUP=%[^;];PINDEX=%[^;];NEXT=%[^;];DURATION=%[^;];LMID=%[^;];BCOLOR=%[^;];" ;
const char *pFormat_DECODE_SET_EFFECT = "TYPE=%d;DIYID=%d;GROUP=%d;PINDEX=%d;NEXT=%d;DURATION=%d;LMID=%d;BCOLOR=%d;" ;

//u8 ceID , u8 leID, u8 aeID, u8 ceTranslateFunc, u8 ceperiod, u8 leperiod
const char *pFormat_ENCODE_SET_AUDIOEFFECT = "TYPE=%[^;];DIYID=%[^;];GROUP=%[^;];PINDEX=%[^;];NEXT=%[^;];AMID=%[^;];LMID=%[^;];BCOLOR=%[^;];" ;
const char *pFormat_DECODE_SET_AUDIOEFFECT = "TYPE=%d;DIYID=%d;GROUP=%d;PINDEX=%d;NEXT=%d;AMID=%d;LMID=%d;BCOLOR=%d;" ;

const char *pFormat_ENCODE_SET_MODELONLYCOLOR = "TYPE=%[^;];DIYID=%[^;];GROUP=%[^;];CI=%[^;];MODELID=%[^;];" ;
const char *pFormat_DECODE_SET_MODELONLYCOLOR = "TYPE=%d;DIYID=%d;GROUP=%d;CI=%d;MODELID=%d;" ;

const char *pFormat_ENCODE_SET_HSV = "TYPE=%[^;];GROUP=%[^;];H=%[^;];S=%[^;];V=%[^;];";
const char *pFormat_DECODE_SET_HSV = "TYPE=%d;GROUP=%d;H=%d;S=%d;V=%d;";

const char *pFormat_ENCODE_SET_CT = "TYPE=%[^;];GROUP=%[^;];CT=%[^;];V=%[^;];";
const char *pFormat_DECODE_SET_CT = "TYPE=%d;GROUP=%d;CT=%d;V=%d;";

const char *pFormat_ENCODE_SET_PATTLE16 = "TYPE=%[^;];GROUP=%[^;];CI=%[^;];V=%[^;];";
const char *pFormat_DECODE_SET_PATTLE16 = "TYPE=%d;GROUP=%d;CI=%d;V=%d;";

const char *pFormat_ENCODE_SET_SIMPLECOMMANDS = "TYPE=%[^;];GROUP=%[^;];COMMAND=%[^;];";
const char *pFormat_DECODE_SET_SIMPLECOMMANDS = "TYPE=%d;GROUP=%d;COMMAND=%d;";

const char *pFormat_ENCODE_SET_LIGHTNESS = "TYPE=%[^;];GROUP=%[^;];LIGHTNESS=%[^;];";
const char *pFormat_DECODE_SET_LIGHTNESS = "TYPE=%d;GROUP=%d;LIGHTNESS=%d;";

const char *pFormat_ENCODE_SET_DELAYSWITHER = "TYPE=%[^;];GROUP=%[^;];TIMEDELAY=%[^;];CMD=%[^;];";
const char *pFormat_DECODE_SET_DELAYSWITHER = "TYPE=%d;GROUP=%d;TIMEDELAY=%d;CMD=%d;";

//u32 data , u8 duration
const char *pFormat_ENCODE_SET_LIFI = "TYPE=%[^;];LDATA=%[^;];LDURATION=%[^;];";
const char *pFormat_DECODE_SET_LIFI = "TYPE=%d;LDATA=%d;LDURATION=%d;";

/*!
 *    @brief 生成PWM 控制灯颜色包
 *
 *    @param red       【0~1000】
 *    @param green     【0~1000】
 *    @param blue      【0~1000】
 *    @param resultStr 结果字符串
 */
void  create_RGBPWMSettings_ToneStrPackage(u8 groupID, u16 red , u16 green , u16 blue , char* resultStr ){
    sprintf(resultStr, pFormat_DECODE_SET_RGBPWM ,TONE_PROTOCOL_TYPE_SET_RGBPWM,groupID, red, green, blue);
}

/*!
 *    @brief HSV to RGB  PWM
 *    @param h         【0~360】
 *    @param s         【0~100】
 *    @param v         【0~100】
 *    @param resultStr
 */
void create_HSVPWMSettings_ToneStrPackage( u8 groupID,u16 h, u16 s , u16 v , char* resultStr ){
    sprintf(resultStr, pFormat_DECODE_SET_HSV ,TONE_PROTOCOL_TYPE_SET_HSV, groupID,h,s,v);
}

/*!
 *    @brief CT( 色温) to RGB PWM
 *
 *    @param ct        【1700~8000】, max can 100~10000,but not real
 *    @param v          value 亮度
 *    @param resultStr <#resultStr description#>
 */
void create_CTPWMSettings_ToneStrPackage( u8 groupID,u16 ct, u16 v , char* resultStr ){
    sprintf(resultStr, pFormat_DECODE_SET_CT ,TONE_PROTOCOL_TYPE_SET_CT,groupID, ct, v);
}

void create_DIYMusicEffectSettings_ToneStrPackage(u8 diyID,u8 groupID,u8 color1, u8 color2,
                                               u8 color3, u8 color4, u8 colorCount, char* resultStr  ){
    sprintf(resultStr, pFormat_DECODE_SET_MUSICEFFECT , TONE_PROTOCOL_TYPE_SET_MUSICEFFECT,
            diyID,groupID, color1,color2,color3,color4,colorCount );
}

void create_DIYEffectSettings_ToneStrPackage(u8 diyID,u8 groupID, u8 partIndex, u8 nextModel,
                                          u8 duration ,u8 lightnessModel, u8 basecolor , char* resultStr  ){
    sprintf(resultStr, pFormat_DECODE_SET_EFFECT ,TONE_PROTOCOL_TYPE_SET_EFFECT ,
            diyID,groupID,partIndex , nextModel, duration, lightnessModel, basecolor );
    
}
void create_DIYAudioEffectSettings_ToneStrPackage(u8 diyID,u8 groupID,u8 partIndex, u8 nextModel,
                                               u8  audioModel ,u8 lightnessModel, u8 basecolor , char* resultStr ){
    sprintf(resultStr, pFormat_DECODE_SET_AUDIOEFFECT ,TONE_PROTOCOL_TYPE_SET_AUDIOEFFECT,
            diyID,groupID,partIndex , nextModel, audioModel, lightnessModel, basecolor, resultStr );
}
void create_DIYModelOnlyColor_ToneStrPackage(u8 diyID,u8 groupID,u8 baseColor, u8 modelID, char* resultStr ){
    sprintf(resultStr, pFormat_DECODE_SET_MODELONLYCOLOR ,TONE_PROTOCOL_TYPE_SET_MODELONLYCOLOR,
            diyID,groupID,baseColor, modelID );
}

void create_LifiSettings_ToneStrPackage(u32 data , u8 duration, char* resultStr ){
    sprintf(resultStr, pFormat_DECODE_SET_LIFI ,TONE_PROTOCOL_TYPE_SET_LIFI, data , duration );
}

void create_ChangeLightness_ToneStrPackage(u8 groupID,u8 lightness100, char* resultStr ){
    sprintf(resultStr, pFormat_DECODE_SET_LIGHTNESS ,TONE_PROTOCOL_TYPE_SET_LIGHTNESS,groupID, lightness100 );
}

void create_ChangePattle16_ToneStrPackage(u8 groupID,u8 baseColor, u8 lightness100, char* resultStr ){
    sprintf(resultStr, pFormat_DECODE_SET_PATTLE16 ,TONE_PROTOCOL_TYPE_SET_PATTLE16,groupID,baseColor, lightness100 );
}


void create_DelayedLightSwitch_ToneStrPackage(u8 groupID,short timeDelay, u8 cmd, char* resultStr ){
    sprintf(resultStr, pFormat_DECODE_SET_DELAYSWITHER ,TONE_PROTOCOL_TYPE_SET_DELAY_SWITHER, groupID,timeDelay, cmd );
}


void create_SimpleCommand_ToneStrPackage(u8 groupID, short command, char* resultStr ){
    sprintf(resultStr, pFormat_DECODE_SET_SIMPLECOMMANDS ,TONE_PROTOCOL_TYPE_SET_SIMPLECOMMANDS, groupID,command );
}

u64 resolveToneCharsPackage(const char *tone ){
    /*
     u8 type ;
     u8 color1, color2, color3, color4, bpmMeduimi, bpmDeflection ;
     u16 red , green ,  blue ;
     u8 ceID ,leID, aeID, ceTranslateFunc, ceperiod, leperiod;
     */
    char type[2] ={'\0'};
    
    char typeStr[2]={'\0'};
    sscanf(tone ,pFormat_TYPE ,typeStr);
    //short parsedRGB[3];
    switch ( atoi(typeStr) ) {
        case TONE_PROTOCOL_TYPE_SET_RGBPWM:{
            char groupID[2]={'\0'},red[6]={'\0'},green[6]={'\0'},blue[6]={'\0'} ;
            sscanf(tone ,pFormat_ENCODE_SET_RGBPWM ,type,groupID,red,green,blue);
            //printf("%lu %d\n",strlen(blue), (u16)atoi(blue) );
            if( strlen(type)== 0 ||strlen(red)== 0  ||strlen(green)== 0 ||strlen(blue)== 0 ){
                break;
            }
            return assemMixColorTonePackage((u8)atoi(groupID),(u16)atoi(red),(u16)atoi(green),(u16)atoi(blue));
        }
            
        case TONE_PROTOCOL_TYPE_SET_MUSICEFFECT:{
            char groupID[2]={'\0'},diyID[2]={'\0'},color1[3]={'\0'} , color2[3]={'\0'} , color3[3]={'\0'} , color4[3]={'\0'} , colorCount[3]={'\0'}  ;
            sscanf(tone ,pFormat_ENCODE_SET_MUSICEFFECT ,type,diyID,groupID,color1,color2,color3,color4,colorCount ) ;
            if( strlen(type)== 0 ||strlen(diyID)== 0 ||strlen(color1)== 0  ||strlen(color2)== 0 ||strlen(color3)== 0
               ||strlen(color4)== 0 ||strlen(colorCount)== 0 ){
                break;
            }
            u8 colors[4] = { atoi(color1), atoi(color2),  atoi(color3), atoi(color4) };
            return assemDIYMusicModelWithColorTonePacakge((u8)atoi(diyID),(u8)atoi(groupID),colors, atoi(colorCount));
        }
        case TONE_PROTOCOL_TYPE_SET_AUDIOEFFECT:{
            char groupID[2]={'\0'},diyID[2]={'\0'},partIndex[3]={'\0'} , nextModel[3]={'\0'} , audioModel[3]={'\0'} , lightnessModel[3]={'\0'} , basecolor[3]={'\0'}  ;
            sscanf(tone ,pFormat_ENCODE_SET_AUDIOEFFECT ,type,diyID,groupID,partIndex,nextModel,audioModel,lightnessModel,basecolor ) ;
            if( strlen(type)== 0 ||strlen(diyID)== 0 ||strlen(partIndex)== 0  ||strlen(nextModel)== 0 ||strlen(audioModel)== 0
               ||strlen(lightnessModel)== 0 ||strlen(basecolor)== 0 ){
                break;
            }
            return assemDIYAudioEffectTonePackage((u8)atoi(diyID),(u8)atoi(groupID),atoi(partIndex),
                                               atoi(nextModel), atoi(audioModel), atoi(lightnessModel), atoi( basecolor));
        }
        case TONE_PROTOCOL_TYPE_SET_EFFECT:{
            char groupID[2]={'\0'},diyID[2]={'\0'},partIndex[3]={'\0'} , nextModel[3]={'\0'} , duration[3]={'\0'} , lightnessModel[3]={'\0'} , basecolor[3]={'\0'}  ;
            sscanf(tone ,pFormat_ENCODE_SET_EFFECT ,type,diyID,groupID,partIndex,nextModel,duration,lightnessModel,basecolor ) ;
            if( strlen(type)== 0 ||strlen(diyID)== 0 ||strlen(partIndex)== 0  ||strlen(nextModel)== 0 ||strlen(duration)== 0
               ||strlen(lightnessModel)== 0 ||strlen(basecolor)== 0 ){
                break;
            }
            return assemDIYEffectTonePackage((u8)atoi(diyID),(u8)atoi(groupID),atoi(partIndex),
                                          atoi(nextModel), atoi(duration), atoi(lightnessModel), atoi( basecolor));
        }
        case TONE_PROTOCOL_TYPE_SET_MODELONLYCOLOR:{
            char groupID[2]={'\0'},diyID[2]={'\0'},basecolor[3]={'\0'},modelID[4]={'\0'};
            sscanf(tone ,pFormat_ENCODE_SET_MODELONLYCOLOR,type,diyID,groupID,basecolor,modelID ) ;
            if( strlen(type)== 0 ||strlen(diyID)== 0 ||strlen(basecolor)== 0||strlen(modelID)== 0){
                break;
            }
            return assemDIYModelOnlyColorTonePacakge((u8)atoi(diyID),(u8)atoi(groupID),(u8)atoi(basecolor),(u8)atoi(modelID) );
        }
        case TONE_PROTOCOL_TYPE_SET_SIMPLECOMMANDS:{
            char groupID[2]={'\0'},command[4]={'\0'} ;
            sscanf(tone ,pFormat_ENCODE_SET_SIMPLECOMMANDS ,type,groupID,command) ;
            if( strlen(type)== 0 ||strlen(command)== 0 ){
                break;
            }
            return assemControlModelTonePacakge((u8)atoi(groupID), atoi(command) );
        }
        case TONE_PROTOCOL_TYPE_SET_LIGHTNESS:{
            char groupID[2]={'\0'},lightness[4]={'\0'} ;
            sscanf(tone ,pFormat_ENCODE_SET_LIGHTNESS ,type,groupID,lightness) ;
            if( strlen(type)== 0 ||strlen(lightness)== 0 ){
                break;
            }
            return assemChangeLightnessTonePacakge((u8)atoi(groupID), (u8)atoi(lightness) );
        }
        case TONE_PROTOCOL_TYPE_SET_DELAY_SWITHER:{
            char groupID[2]={'\0'},timeDelay[6]={'\0'} , cmd[2]={'\0'} ;
            sscanf(tone ,pFormat_ENCODE_SET_DELAYSWITHER ,type,groupID,timeDelay, cmd) ;
            if( strlen(type)== 0 ||strlen(timeDelay)== 0 ||strlen(cmd)== 0 ){
                break;
            }
            return assemDelayedLightSwitchTonePacakge((u8)atoi(groupID), atoi(timeDelay), atoi(cmd) );
        }
        case TONE_PROTOCOL_TYPE_SET_HSV:{
            char groupID[2]={'\0'},hue[4]={'\0'}, saturation[4]={'\0'}, value[4]={'\0'};
            sscanf(tone ,pFormat_ENCODE_SET_HSV ,type,groupID,hue,saturation,value ) ;
            if( strlen(type)== 0 ||strlen(hue)== 0  ||strlen(saturation)== 0||strlen(value)== 0){
                break;
            }
#if(IS_USE_ENBEDDED_CALIBRATION)
            return assemHSLTonePacakge((u8)atoi(groupID), (u16)atoi(hue),(u8)atoi(saturation),(u8)atoi(value));
#else
            parseHSV2RGBPWM( (u16)atoi(hue),(u16)atoi(saturation),(u16)atoi(value),parsedRGB );
            return assemMixColorTonePackage((u8)atoi(groupID),(parsedRGB[0]>>4),(parsedRGB[1]>>4),(parsedRGB[2]>>4));
#endif
        }
        case TONE_PROTOCOL_TYPE_SET_CT:{
            char groupID[2]={'\0'},ct[6]={'\0'},value[4]={'\0'};
            sscanf(tone ,pFormat_ENCODE_SET_CT,type,groupID,ct,value ) ;
            if( strlen(type)== 0 ||strlen(ct)== 0||strlen(value)== 0){
                break;
            }
#if(IS_USE_ENBEDDED_CALIBRATION)
            return assemCTTonePacakge((u8)atoi(groupID),(u16)atoi(ct),(u8)atoi(value));
#else
            
            parseCT2RGBPWM( (u16)atoi(ct),(u16)atoi(value),parsedRGB );
            return assemMixColorTonePackage((u8)atoi(groupID),(parsedRGB[0]>>4),(parsedRGB[1]>>4),(parsedRGB[2]>>4));
#endif
            
        }
        case TONE_PROTOCOL_TYPE_SET_PATTLE16:{
            char groupID[2]={'\0'},basecolor[6]={'\0'},value[4]={'\0'};
            sscanf(tone ,pFormat_ENCODE_SET_PATTLE16,type,groupID,basecolor,value ) ;
            if( strlen(type)== 0 ||strlen(basecolor)== 0||strlen(value)== 0){
                break;
            }
            return assemChangePattle16ColorTonePacakge((u8)atoi(groupID),(u8)atoi(basecolor),(u8)atoi(value));
        }
        case TONE_PROTOCOL_TYPE_SET_LIFI:{
            char lifiDuration[4]={'\0'}, lifiData[10]={'\0'};
            sscanf(tone ,pFormat_ENCODE_SET_LIFI ,type,lifiData,lifiDuration ) ;
            if( strlen(type)== 0 ||strlen(lifiDuration)== 0  ||strlen(lifiData)== 0){
                break;
            }
            return assemLifiSettingsTonePackage( atoi(lifiData),atoi(lifiDuration) );
        }
        default:
            return INVALID_TONEPACKAGE;
    }
    return INVALID_TONEPACKAGE;
}

/*!
 *    @brief 将sourceData 中的36bit的数据放到4*short 中，每个short 包含9bit数据
 *
 *    @param sourceData 36bit数据
 *    @param tx_data    <#tx_data description#>
 */
void parseU64To512Arrays(u64 sourceData, short *tx_data ){
    if((sourceData>>36)){
        //source Data error
        //DEBUG_MSG(" parseU64To512Arrays source Data Error ");
        //return TRUE;
    }
    tx_data[0]= (sourceData>>27)&0x01FF ;
    tx_data[1]= (sourceData>>18)&0x01FF ;
    tx_data[2]= (sourceData>>9)&0x01FF ;
    tx_data[3]= (sourceData)&0x01FF ;
    //return
}


