#ifndef _RS_H_
#define _RS_H_

#define _RS_H_
//
//  rs.h
//  ToneCoreMain
//
//  Created by jiapeng on 14-7-21.
//  Copyright (c) 2014jiapeng. All rights reserved.
//

//param1


void rsDecodeInit();
//void rsDecode(int * sourceData , int type, int *resultRsData );
void rsDecode(short * sourceData , int type, short *resultRsData );
#endif
