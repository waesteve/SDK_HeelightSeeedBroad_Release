//
//  main.c
//  AudioProgrammePackageCreator
// 生成编程包.
//  Created by jiapeng on 14-8-11.
//  Copyright (c) 2014年 jiapeng. All rights reserved.
//
#include "createLongControlPackageAudioMain.h"
#include <stdio.h>
#include "ToneProtocolCharUtil.h"

#include "ProgramPackageCreator.h"
#include "make_wav.h"
#include "rsEncode.h"
#include "rsConfig.h"


#define PROTOCOL_VERSION2 2   // 支持多种字符串
#define CUR_PROTOCOL_VERSION PROTOCOL_VERSION2

void doCreateMain( const char  * argv1,  const char  * argv2) {

    initAudioCreator();

    register int i = 0 ;

    short tx_data[4] = { 0 , 0 , 0 ,0
        //0x1FF, 500 ,1 ,250
    };

#if( CUR_PROTOCOL_VERSION == PROTOCOL_VERSION2)

    const char * paramsData1 ;
    if( argv1 == NULL ){
        //if( 1){
        i=0;
        //paramsData1 = "TYPE=1;RED=100;GREEN=1000;BLUE=1500;";
        paramsData1 = "TYPE=6;H=210;S=100;V=99;";
        while(  paramsData1[i] !='\0'){
            i++ ;
        }
    }else{
        i=0;
        while( argv1[i] !='\0'){
            i++ ;
        }
        paramsData1 =argv1;

    }
    if(i >= 20 ){
        unsigned long long audioCode = resolveToneCharsPackage( paramsData1 );
        if(audioCode == INVALID_TONEPACKAGE){
            printf("Parse Tone Package Error ,because of INVALIDATE PARAMS ");
            return ;
        }

        printf("%llu\t",audioCode);
        tx_data[0] = ((audioCode>>27)&0x1FF);
        tx_data[1] = ((audioCode>>18)&0x1FF);
        tx_data[2] = ((audioCode>>9)&0x1FF);
        tx_data[3] = ((audioCode>>0)&0x1FF);
    }
#endif
    printf( "%d %d %d %d \n", tx_data[0],tx_data[1],tx_data[2],tx_data[3]);
    createProgramAudioPackage(tx_data);

    write_wav(argv2, sizeof(tx_pkt)/sizeof(short), tx_pkt, S_RATE);
}


void doCreateShortCommand( int command,  const char  * argv2) {

    initAudioCreator();

    createCommandAudioPackage( command );

    write_wav(argv2, SHORTCOMMAND_TX_PKT_LENGTH, tx_pkt, S_RATE);
}