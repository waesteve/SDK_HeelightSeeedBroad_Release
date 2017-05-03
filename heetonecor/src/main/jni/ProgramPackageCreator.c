//
//  main.c
//  AudioProgrammePackageCreator
//
//  Created by jiapeng on 14-8-11.
//  Copyright (c) 2014年 jiapeng. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "rsEncode.h"
//#include "toneCore.h"
#include "ProgramPackageCreator.h"

int fm[32];
float tone_env[TONE_L];


short tx_pkt[LONGCOMMAND_TX_PKT_LENGTH];


void initAudioCreator() {
    register int i = 0;

    int fmIndex[32] = {16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 33, 35, 37,
                       39, 41, 43, 45, 47, 49, 53, 55, 57, 61, 64, 65, 67};

    //frequency of 32 tones

    for (i = 0; i < 32; i++) {
        fm[i] = fmIndex[i] * FS / COR_L_BS;
    }

    float tempValue = 0;
    for (i = 0; i < TONE_HTL; i++) {
        tempValue = i / (float) TONE_HTL;
        tone_env[i] = tempValue;
        tone_env[TONE_L - 1 - i] = tempValue;
    }
    //memset( tone_env+TONE_L , 1 ,  COR_L );
    for (i = TONE_HTL; i < COR_L_AND_HL; i++) {
        tone_env[i] = 1.0f;
    }

    //tone_env = [(0:(tone_hl-1))/tone_hl ones(1,tone_bl) ((tone_tl-1):-1:0)/tone_tl];




    rsEncodeInit();
}


int createProgramAudioPackage(short *tx_data) {
    register int i = 0;
    register int j = 0;

    int f1_head = 14;
    int f2_head = 10;
    f1_head = fm[f1_head];
    f2_head = fm[f2_head];
    //init f1
    for (i = 0; i < TONE_L; i++) {
        tx_pkt[i] = (MAX_AUDIO * tone_env[i]) * sin(2 * PI * f1_head / (double) FS * i);
        //printf("%d     %d    %f \r\n",i, tx_pkt[i] ,sin(2*PI*f1_head/(double)FS*i) );
    }
    //init f2
    for (i = 0; i < TONE_L; i++) {
        tx_pkt[i + TONE_L] = (MAX_AUDIO * tone_env[i]) * sin(2 * PI * f2_head / (double) FS * i);
    }


    short fullKKDatas[12];
    for (i = 0; i < 4; i++) {
        fullKKDatas[0 + (i * 3)] = (tx_data[i] >> 6) & 0x07;
        fullKKDatas[1 + (i * 3)] = (tx_data[i] >> 3) & 0x07;
        fullKKDatas[2 + (i * 3)] = (tx_data[i]) & 0x07;
    }

    short resultFullRsDatas[28];
    rsEncodeWithType(fullKKDatas, 3, resultFullRsDatas);
    /*
    % the 4n+1 symbols are transmitted with No. 1~8
    tx_f(1,1:2:tone_num) = tx_data_i(1:4:sym_len)+1;
    % the 4n+2 symbols are transmitted with No. 17~24
    tx_f(2,1:2:tone_num) = tx_data_i(2:4:sym_len)+17;
    % the 4n+3 symbols are transmitted with No. 9~16
    tx_f(1,2:2:tone_num) = tx_data_i(3:4:sym_len)+9;
    % the 4n+4 symbols are transmitted with No. 25~32
    tx_f(2,2:2:tone_num) = tx_data_i(4:4:sym_len)+25;
     */
/*
    rsDecodeInit();
    short  resultRsData[13];
    short tempRSData[28]={
        1,0,5,2,1,0,0,
        0, 0,4,0,7,0,6,
        6,7,1,6,5,6,0,
        3,4,6,6,2,7,7
    };
    //rsDecode(resultFullRsDatas, TYPE_RPOGRAM, resultRsData);
    rsDecode(tempRSData, TYPE_RPOGRAM, resultRsData);
  */
    // Modulation
    int tx_f[2][TonesSize] = {0};
    for (i = 0; i < (TonesSize * 2); i += 4) {
        tx_f[0][(i >> 1)] = resultFullRsDatas[i] + 0;
        tx_f[1][(i >> 1)] = resultFullRsDatas[i + 1] + 16;
        tx_f[0][(i >> 1) + 1] = resultFullRsDatas[i + 2] + 8;
        tx_f[1][(i >> 1) + 1] = resultFullRsDatas[i + 3] + 24;
        //printf( "%d \t%d \t%d \n" ,tempValue , ((tempValue&0x38) >> 3)  , (tempValue&0x07)  );
        printf(" %2d \t%2d \n", tx_f[0][i], tx_f[1][i]);
    }

    int hjHeadPartEndIndex = 2 * TONE_L;
    for (i = 0; i < TonesSize; i++) {
        for (j = 0; j < TONE_L; j++) {
            tx_pkt[i * TONE_L + j + hjHeadPartEndIndex] = MAX_AUDIO * tone_env[j] / sqrt(2)
                                                          * (sin(2 * PI * fm[tx_f[0][i]] / FS * j) +
                                                             sin(2 * PI * fm[tx_f[1][i]] / FS * j));
        }
    }

    return 0;
}


int createCommandAudioPackage(short command) {
    register int i = 0;
    register int j = 0;

    int f1_head = 14;
    int f2_head = 8;
    f1_head = fm[f1_head];
    f2_head = fm[f2_head];
    //init f1
    for (i = 0; i < TONE_L; i++) {
        tx_pkt[i] = (MAX_AUDIO * tone_env[i]) * sin(2 * PI * f1_head / (double) FS * i);
    }
    //init f2
    for (i = 0; i < TONE_L; i++) {
        tx_pkt[i + TONE_L] = (MAX_AUDIO * tone_env[i]) * sin(2 * PI * f2_head / (double) FS * i);
    }


    short fullKKDatas[3];
    fullKKDatas[0 ] = (command >> 6) & 0x07;
    fullKKDatas[1 ] = (command >> 3) & 0x07;
    fullKKDatas[2 ] = (command) & 0x07;

    short resultFullRsDatas[14];
    rsEncodeWithType(fullKKDatas, 2, resultFullRsDatas);


    // Modulation
    int tx_f[2][7] = {0};
    for (i = 0; i < 7; i++) {
        tx_f[0][i] = resultFullRsDatas[i] + (i % 2 == 0 ? 0 : 8);
        tx_f[1][i] = resultFullRsDatas[i + 7] + (16 + (i % 2 == 0 ? 0 : 8));

    }
    /*
    printf("\n\n%d\n", command);
    for (i = 0; i < 7; i++) {
        printf("%d " ,tx_f[0][i]+1 );
    }
    printf("\n");
    for (i = 0; i < 7; i++) {
        printf("%d " ,tx_f[0][i+7]+1 );
    }
    printf("\n");
    */


    int hjHeadPartEndIndex = 2 * TONE_L;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < TONE_L; j++) {
            tx_pkt[i * TONE_L + j + hjHeadPartEndIndex] = MAX_AUDIO * tone_env[j] / sqrt(2)
                                                          * (sin(2 * PI * fm[tx_f[0][i]] / FS * j) +
                                                             sin(2 * PI * fm[tx_f[1][i]] / FS * j));
        }
    }

    return 0;
}

