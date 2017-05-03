//
//  ProgramPackageCreator.h
//  AudioProgrammePackageCreator
//
//  Created by jiapeng on 14-8-12.
//  Copyright (c) 2014年 jiapeng. All rights reserved.
//
#include "toneCore.h"
#include "rsEncode.h"

#define MAX_AUDIO 10000 //0.8*32768


#define PI 3.1415926535

//#define  TonesSize usefulKK + (tt<<1)

#define  TonesSize 14

#define LONGCOMMAND_TX_PKT_LENGTH (2+TonesSize)*TONE_L

#define SHORTCOMMAND_TX_PKT_LENGTH (2+7)*TONE_L

extern short tx_pkt[ LONGCOMMAND_TX_PKT_LENGTH ] ;
void initAudioCreator();
int createProgramAudioPackage(short *tx_data) ;
int createCommandAudioPackage(short command) ;