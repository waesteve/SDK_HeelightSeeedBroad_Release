//
//  HeelightMath.c
//  RedisAudioPackageHandlerC
//
//  Created by jiapeng on 11/10/15.
//  Copyright © 2015 jiapeng. All rights reserved.
//

#include "HeelightMath.h"
#include "heelight_types.h"

const short COS_POOL[91]={
    1024,1023,1023,1022,1021,1020,1018,1016,1014,1011,1008,1005,1001,997,993,989,984,979,973,968,962,955,949,942,935,928,920,912,904,895,886,877,868,858,848,838,828,817,806,795,784,772,760,748,736,724,711,698,685,671,658,644,630,616,601,587,572,557,542,527,512,496,480,464,448,432,416,400,383,366,350,333,316,299,282,265,247,230,212,195,177,160,142,124,107,89,71,53,35,17,0,};

short cos_fixed(int value ){
    int radian = ((value%360)+360)%360;
    if(radian < 90){
        return COS_POOL[radian];
    }else if( radian<180 ){
        return 0- COS_POOL[180-radian];
    }else if(radian <270){
        return 0- COS_POOL[radian-180];
    }else{
        return COS_POOL[360-radian];
    }
    return 0;
}

short sin_fixed(int value ){
    return cos_fixed( 90-value );
}

#if (IS_EMBEDDED ==1 )
#include "../../proj/mcu/random.h"
int srandomInt(int seed){
    //((clock_time() & 0xffff) ^ reg_rnd_number);
    //it really a u16.
    return rand()%seed;
}
#else
#include "stdlib.h"
int srandomInt(int seed){
    //srand(seed);
    return  rand()%seed;
}
#endif

const int AUDIOLEVEL_LEVEL_POOL_64[] = {
    3739,4192,4699,5268,5906,6621,7422,8320,9327,10456,
    11722,13141,14732,16515,18514,20755,23267,26083,29240,32779,
    36747,41195,46181,51771,58038,65063,72938,81767,91664,102760,
    115198,129142,144773,162297,181942,203964,228653,256329,287356,322138,
    361130,404842,453845,508780,570364,639402,716797,803559,900824,1009862,
    1132098,1269130,1422748,1594961,1788018,2004444,2247067,2519057,2823970,3165789,
    3548984,3978561,4460135,5000000,
};
const int AUDIOLEVEL_LEVEL_POOL_BIG_64[] = {
41131,44720,48622,52865,57478,62493,67946,73875,80321,87329,
94949,103234,112242,122036,132684,144262,156850,170536,185416,201595,
219185,238311,259105,281714,306295,333021,362080,393673,428024,465372,
505979,550129,598131,650322,707067,768763,835843,908776,988072,1074288,
1168027,1269945,1380756,1501236,1632229,1774651,1929501,2097863,2280916,2479940,
2696332,2931604,3187406,3465528,3767919,4096694,4454158,4842813,5265380,5724819,
6224347,6767463,7357969,8000000,
};

const int AUDIOLEVEL_LEVEL_POOL_128[] = {
    3822, 4059, 4311, 4579, 4863, 5164, 5485, 5825, 6187, 6571,
    6979, 7412, 7872, 8360, 8879, 9430, 10015, 10637, 11297, 11998,
    12742, 13533, 14373, 15265, 16212, 17218, 18287, 19422, 20627, 21907,
    23266, 24710, 26244, 27872, 29602, 31439, 33390, 35462, 37663, 40000,
    42482, 45119, 47919, 50892, 54051, 57405, 60967, 64751, 68769, 73037,
    77569, 82383, 87495, 92925, 98692, 104816, 111321, 118229, 125566, 133359,
    141635, 150424, 159759, 169673, 180203, 191386, 203263, 215877, 229274, 243502,
    258613, 274662, 291707, 309809, 329035, 349454, 371141, 394173, 418634, 444614,
    472205, 501509, 532632, 565685, 600791, 638074, 677671, 719726, 764391, 811827,
    862207, 915713, 972540, 1032894, 1096993, 1165069, 1237371, 1314159, 1395713, 1482327,
    1574317, 1672015, 1775776, 1885977, 2003016, 2127318, 2259335, 2399543, 2548453, 2706604,
    2874570, 3052958, 3242418, 3443634, 3657338, 3884304, 4125354, 4381364, 4653261, 4942031,
    5248721, 5574444, 5920381, 6287785, 6677990, 7092410, 7532548, 8000000 };

const int AUDIOLEVEL_LEVEL_POOL_BIG_128[] = {
    41690,43452,45289,47203,49198,51277,53444,55702,58057,60510,
    63067,65733,68511,71406,74424,77569,80847,84264,87825,91537,
    95405,99437,103640,108020,112585,117343,122302,127471,132858,138473,
    144325,150424,156781,163407,170313,177511,185013,192832,200981,209475,
    218328,227555,237171,247195,257642,268530,279878,291707,304035,316884,
    330276,344234,358782,373944,389748,406219,423387,441280,459929,479367,
    499626,520741,542748,565685,589592,614509,640480,667548,695759,725163,
    755810,787752,821043,855742,891907,929601,968887,1009834,1052512,1096993,
    1143354,1191674,1242036,1294526,1349235,1406256,1465687,1527630,1592190,1659479,
    1729611,1802708,1878893,1958299,2041060,2127318,2217223,2310926,2408590,2510381,
    2616474,2727051,2842301,2962422,3087619,3218107,3354110,3495860,3643601,3797586,
    3958079,4125354,4299699,4481412,4670804,4868200,5073939,5288372,5511868,5744809,
    5987595,6240641,6504381,6779268,7065772,7364383,7675615,8000000, };


const short PARABOLA_POOL[125]={
    0,32,64,96,127,158,188,218,247,275,
    303,331,358,384,410,435,460,484,508,531,
    554,576,597,618,639,659,678,697,716,733,
    751,768,784,799,815,829,843,857,870,883,
    895,906,917,927,937,947,955,964,971,978,
    985,991,997,1002,1006,1010,1014,1017,1019,1021,
    1022,1023,1024,1023,1022,1021,1019,1017,1014,1010,
    1006,1002,997,991,985,978,971,964,955,947,
    937,927,917,906,895,883,870,857,843,829,
    815,799,784,768,751,733,716,697,678,659,
    639,618,597,576,554,531,508,484,460,435,
    410,384,358,331,303,275,247,218,188,158,
    127,96,64,32,0,
};

/*!
 *   二分查找该数组的问题.
 */
int binarySearchMaxMinuend(int array[], int powerOf2 ,int len,int value){
    //int meduimIndex = (len >>1) ;
    //int resultIndex = 0 ;
    /*
    int low = 0;
    int high = len - 1;
    
    for( int i = 0 ; i < powerOf2 ; i++ ){
        DEBUG_MSG(( "%d) %d --- %d \n",meduimIndex, value , array[ meduimIndex ] );
        if( value < array[ meduimIndex ]){
            resultIndex = i ;
            meduimIndex = meduimIndex >> 1;
        }else{
            meduimIndex += (meduimIndex>>1) ;
        }
    }
    return meduimIndex;
    */
    int low = 0;
    int high = 64 -1;
    int meduimIndex= 0;
    int resultIndex = len ;

    for( int i = 0 ; i < powerOf2 ; i++ )
    {
        meduimIndex = (low + high)/2;
        if( low> high){
            break;
        }
        //DEBUG_MSG(( "%d) %d --- %d \n",meduimIndex, value , array[ meduimIndex ] );
        if( value < array[ meduimIndex ]){
            //resultIndex = meduimIndex ;
            resultIndex = meduimIndex ;
            high = meduimIndex - 1;
        }else{
            //meduimIndex += (meduimIndex>>1) ;
            low = meduimIndex + 1;
        }
    }
    return resultIndex;
    
}

int getAudioLevelMapping64(int audioLevelData)
{
    int index = 0;
    
    for (; index < 64; index++)
    {
        if (audioLevelData < AUDIOLEVEL_LEVEL_POOL_64[index])
        {
            break;
        }
    }
    return index;
}

int getAudioLevelMapping64WithBS(int audioLevelData)
{
    int low = 0;
    int high = 64 ;
    int meduimIndex= 0;
    int resultIndex = 64 ;
    
    for( int i = 0 ; i < 7 ; i++ )
    {
        meduimIndex = ((low + high)>>1);
        //DEBUG_MSG(( "%d) %d --- %d \n",meduimIndex, audioLevelData , AUDIOLEVEL_LEVEL_POOL_64[ meduimIndex ] );
        if( audioLevelData < AUDIOLEVEL_LEVEL_POOL_64[ meduimIndex ]){
            //resultIndex = meduimIndex ;
            resultIndex = meduimIndex ;
            high = meduimIndex ;
        }else{
            //meduimIndex += (meduimIndex>>1) ;
            low = meduimIndex + 1;
        }
    }
    return resultIndex;
}

int getAudioLevelMappingBIG64(int audioLevelData)
{
    int index = 0;
    
    for (; index < 64; index++)
    {
        if (audioLevelData < AUDIOLEVEL_LEVEL_POOL_BIG_64[index])
        {
            break;
        }
    }
    return index;
}

int getAudioLevelMappingBIG64WithBS(int audioLevelData)
{
    int low = 0;
    int high = 64 ;
    int meduimIndex= 0;
    int resultIndex = 64 ;
    
    for( int i = 0 ; i < 7 ; i++ )
    {
        meduimIndex = ((low + high)>>1);
        //DEBUG_MSG(( "%d) %d --- %d \n",meduimIndex, audioLevelData , AUDIOLEVEL_LEVEL_POOL_64[ meduimIndex ] );
        if( audioLevelData < AUDIOLEVEL_LEVEL_POOL_BIG_64[ meduimIndex ]){
            //resultIndex = meduimIndex ;
            resultIndex = meduimIndex ;
            high = meduimIndex ;
        }else{
            //meduimIndex += (meduimIndex>>1) ;
            low = meduimIndex + 1;
        }
    }
    return resultIndex;
}

int getAudioLevelMapping128(int audioLevelData)
{
    int index = 0;
    for (; index < 128; index++)
    {
        if (audioLevelData < AUDIOLEVEL_LEVEL_POOL_128[index])
        {
            break;
        }
    }
    return index;
}

int getAudioLevelMapping128WithBS(int audioLevelData)
{
    int low = 0;
    int high = 128 ;
    int meduimIndex= 0;
    int resultIndex = 128 ;
    
    for( int i = 0 ; i < 8 ; i++ )
    {
        meduimIndex = ((low + high)>>1);
        if( audioLevelData < AUDIOLEVEL_LEVEL_POOL_128[ meduimIndex ]){
            resultIndex = meduimIndex ;
            high = meduimIndex ;
        }else{
            low = meduimIndex + 1;
        }
    }
    return resultIndex;
}

/*!
 *    @brief 获取抛物线.
 *
 *    @param index
 *    @param xrange 将xrange 投射到125分上.  ,125 代表一秒.
 *
 *    @return 0xFF
 */
short getParabola(short index , short xrange, short min, short max){
    //DEBUG_MSG(("|%d|",index);
    if( index < 0 || index >= xrange ){
        return 0xFFFF;
    }
    //DEBUG_MSG(( "-->%d %d %d\n",((index * 125)/xrange ), PARABOLA_POOL[ ((index * 125)/xrange ) ] , (((PARABOLA_POOL[ ((index * 125)/xrange ) ]*(max-min))>>4)>>6) );
    return (min + (((PARABOLA_POOL[ ((index * 125)/xrange ) ]*(max-min))>>4)>>6)) ;
}

const unsigned char crc8Poly = 0x1D ;
unsigned char crc8Simple( unsigned char* data, int size)
{
    /*
    unsigned char crc = 0x00;
    int bit;
    
    while (size--) {
        crc ^= *data++;
        for (bit = 0; bit < 8; bit++) {
            if (crc & 0x01) {
                crc = (crc >> 1) ^ crc8Poly;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
    */
    unsigned char crc = 0x00;
    int bit;
    
    while (size--) {
        crc ^= *data++;
        for (bit = 0; bit < 8; bit++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ crc8Poly;
            } else {
                crc <<= 1;
            }
        }
    }
    
    return crc;
    
}

unsigned char crc8_lsb(unsigned char poly, unsigned char* data, int size)
{
    unsigned char crc = 0x00;
    int bit;
    
    while (size--) {
        crc ^= *data++;
        for (bit = 0; bit < 8; bit++) {
            if (crc & 0x01) {
                crc = (crc >> 1) ^ poly;
            } else {
                crc >>= 1;
            }
        }
    }
    
    return crc;
}

unsigned char crc8_msb(unsigned char poly, unsigned char* data, int size)
{
    unsigned char crc = 0x00;
    int bit;
    
    while (size--) {
        crc ^= *data++;
        for (bit = 0; bit < 8; bit++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ poly;
            } else {
                crc <<= 1;
            }
        }
    }
    
    return crc;
}


//快速排序
void quick_sort(int* s, int l, int r)
{
    if (l < r)
    {
        //Swap(s[l], s[(l + r) / 2]); //将中间的这个数和第一个数交换 参见注1
        int i = l, j = r, x = s[l];
        while (i < j)
        {
            while (i < j && s[j] >= x) // 从右向左找第一个小于x的数
                j--;
            if (i < j)
                s[i++] = s[j];
            while (i < j && s[i] < x) // 从左向右找第一个大于等于x的数
                i++;
            if (i < j)
                s[j--] = s[i];
        }
        s[i] = x;
        quick_sort(s, l, i - 1); // 递归调用
        quick_sort(s, i + 1, r);
    }
}



#if(DEBUG_ENABLE == ENABLE)
#include <math.h>
void testMath(){
    /*
    //test sin and cos
    for(int i = -720 ; i < 720 ; i++ ){
        //DEBUG_MSG("%d %d %d \n",i,(int)(SIN_MAX*cos((i*3.1415926)/180.0f)),(int)(cos_fixed(i)));
        DEBUG_MSG("%d %d %d \n",i,(int)(HM_SIN_MAX*sin((i*3.1415926)/180.0f)),(int)(sin_fixed(i)));
     
        //DEBUG_MSG("%d," ,(int)(SIN_MAX*sin((i*3.1415926)/180.0f)));
        //DEBUG_MSG("%d," ,(int)(SIN_MAX*cos((i*3.1415926)/180.0f)));
     
    }
     */
    /*
    for(int i = 0 ; i <= 12 ; i++ ){
        short value1 = LINE_TRANSITE( i , 256 , 0 , 12);
        u16   value2 = LINE_TRANSITE( i , 256 , 0 , 12);
        DEBUG_MSG ( " %d %d %d\n",i,value1,value2 );
    }
    */
    /*
    int value = 12353200 ;
    int tempValue = binarySearchMaxMinuend( AUDIOLEVEL_LEVEL_POOL_64, 6, 64, value );
    DEBUG_MSG ( "Result: %d %d %d\n", tempValue, value , AUDIOLEVEL_LEVEL_POOL_64[tempValue]  );
    */
   	unsigned char data[3] = {0x01, 0x02,0x01};
    //*255*255
    for( int i = 0 ; i < 255;i++){
        //data[0] = (unsigned char)((i>>16)&0xFF);
        //data[1] = (unsigned char)((i>>8)&0xFF);
        data[0] = (unsigned char)((i>>0)&0xFF);
        if( i %16 ==0 ){
             DEBUG_MSG ( "\n" );
        }
        printf("%2x " ,crc8Simple( data, 3));
        
    }
    /*
    for( int i = 0 ; i < 10 ; i++ ){
        int value = srandomInt(10000);
        int a =0 ,b = 0;
        
        struct timeval startTime, meduimTime, endTime;
      
        long time_Us1 = 0,time_Us2 = 0;
        
        gettimeofday( &startTime, NULL );
        for( int j = 0 ; j < 100000;j++){
            //a = getAudioLevelMapping64( value);
            a = getAudioLevelMapping128( value);
        }
        gettimeofday( &meduimTime, NULL );
        
        for( int j = 0 ; j < 100000;j++){
            //b = getAudioLevelMapping64WithBS( value);
            b = getAudioLevelMapping128WithBS( value);
        }
        gettimeofday( &endTime, NULL );

        time_Us1 = 1000000 * ( meduimTime.tv_sec - startTime.tv_sec ) + meduimTime.tv_usec - startTime.tv_usec;
        time_Us2 = 1000000 * ( endTime.tv_sec - meduimTime.tv_sec )   + endTime.tv_usec - meduimTime.tv_usec;
        
        //a = getAudioLevelMapping64( value);
        //a = getAudioLevelMapping64( value);
        
        if( time_Us1 < time_Us2 ){
            DEBUG_MSG("---->方法1 快");
        }else{
            DEBUG_MSG("---->方法2 快");
        }
        DEBUG_MSG("  %d) %d:%d\n",value, time_Us1, time_Us2  );
        
        if(a != b){
            DEBUG_MSG("Not Equal.\n");
        }else{
            DEBUG_MSG("Equal\n");
        }
        
        DEBUG_MSG((" a:b = %d:%d\n",a ,b);
    }
    DEBUG_MSG("\n\n");
     */

}
#endif