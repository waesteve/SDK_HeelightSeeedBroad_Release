#ifndef _RS_H_
#define _RS_H_

#define _RS_H_
//
//  rs.h
//  ToneCoreMain
//
//  Created by jiapeng on 14-7-21.
//  Copyright (c) 2014年 jiapeng. All rights reserved.
//


#include "Config.h"


void rsEncodeInit();
void rsEncode(int  *kkData , int *ttData );
void rsEncodeWithType( short*  fullKKDatas , char type, short *resultFullRsData  );
void testRSEncode();
#endif