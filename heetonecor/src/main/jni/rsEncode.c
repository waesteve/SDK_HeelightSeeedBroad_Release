#include "rsEncode.h"

#include <stdio.h>


#define mm  3           /* RS code over GF(2**4) - change to suit */
#define nn  7          /* nn=2**mm -1   length of codeword */


#define tt  2          /* number of errors that can be corrected */
#define kk  3           /* kk = nn-2*tt  */

#define mm_plusone 4
#define nn_subone 6
#define nn_plusone 8
#define nn_sub_kk 4
#define nn_sub_kk_plusone 6
#define nn_sub_kk_plustwo 6

#define tt_plusone 3
#define usefulKK 3


#define SUCCESS 0
#define Failure -1

//const int pp [mm+1] = { 1, 1, 0, 0, 0, 0, 1} ; /* specify irreducible polynomial coeffts */
const int pp[mm + 1] = {1, 1, 0, 1};
/* specify irreducible polynomial coeffts */


static int alpha_to[nn_plusone], index_of[nn_plusone], gg[nn_sub_kk_plusone];
static int recd[nn], data[kk], bb[nn_sub_kk];
static int elp[nn_sub_kk_plustwo][nn_sub_kk], d[nn_sub_kk_plustwo], l[nn_sub_kk_plustwo], u_lu[nn_sub_kk_plustwo], s[nn_sub_kk_plusone];
static int root[tt], loc[tt], z[tt_plusone], err2[nn], reg[tt_plusone];

//int rx_data_c3[kk];


void rsEncodeInit() {
    register int i, j, mask;

    mask = 1;
    alpha_to[mm] = 0;
    for (i = 0; i < mm; i++) {
        alpha_to[i] = mask;
        index_of[alpha_to[i]] = i;
        if (pp[i] != 0)
            alpha_to[mm] ^= mask;
        mask <<= 1;
    }
    index_of[alpha_to[mm]] = mm;
    mask >>= 1;
    for (i = mm_plusone; i < nn; i++) {
        if (alpha_to[i - 1] >= mask)
            alpha_to[i] = alpha_to[mm] ^ ((alpha_to[i - 1] ^ mask) << 1);
        else alpha_to[i] = alpha_to[i - 1] << 1;
        index_of[alpha_to[i]] = i;
    }
    index_of[0] = -1;


    gg[0] = 2;    /* primitive element alpha = 2  for GF(2**mm)  */
    gg[1] = 1;    /* g(x) = (X+alpha) initially */
    for (i = 2; i <= nn_sub_kk; i++) {
        gg[i] = 1;
        for (j = i - 1; j > 0; j--)
            if (gg[j] != 0) gg[j] = gg[j - 1] ^ alpha_to[(index_of[gg[j]] + i) % nn];
            else gg[j] = gg[j - 1];
        gg[0] = alpha_to[(index_of[gg[0]] + i) % nn];     /* gg[0] can never be zero */
    }
    /* convert gg[] to index form for quicker encoding */
    for (i = 0; i <= nn_sub_kk; i++) gg[i] = index_of[gg[i]];

}


void encode_rs()
/* take the string of symbols in data[i], i=0..(k-1) and encode systematically
 to produce 2*tt parity symbols in bb[0]..bb[2*tt-1]
 data[] is input and bb[] is output in polynomial form.
 Encoding is done by using a feedback shift register with appropriate
 connections specified by the elements of gg[], which was generated above.
 Codeword is   c(X) = data(X)*X**(nn-kk)+ b(X)          */
{
    register int i, j;
    int feedback;

    for (i = 0; i < nn - kk; i++) bb[i] = 0;
    for (i = kk - 1; i >= 0; i--) {
        feedback = index_of[data[i] ^ bb[nn - kk - 1]];
        if (feedback != -1) {
            for (j = nn - kk - 1; j > 0; j--)
                if (gg[j] != -1)
                    bb[j] = bb[j - 1] ^ alpha_to[(gg[j] + feedback) % nn];
                else
                    bb[j] = bb[j - 1];
            bb[0] = alpha_to[(gg[0] + feedback) % nn];
        }
        else {
            for (j = nn - kk - 1; j > 0; j--)
                bb[j] = bb[j - 1];
            bb[0] = 0;
        }
    }
}


/***
 *param kkData:需要RS编码的值
 *param ttData：RS纠错码
 */
void rsEncode(int *kkData, int *ttData) {
    register int i;

    //doInit();
    /* for known data, stick a few numbers into a zero codeword. Data is in
     polynomial form.
     */
    for (i = 0; i < kk; i++) {
        data[i] = 0;
    }

    //init kkData;
    for (i = 0; i < usefulKK; i++) {
        data[i + (kk - usefulKK)] = *(kkData + usefulKK - 1 - i);
    }

    /* encode data[] to produce parity in bb[].  Data input and parity output
     is in polynomial form
     */
    encode_rs();

    for (i = 0; i < nn - kk; i++) {
        *(ttData + (tt << 1) - 1 - i) = bb[i];
    }
}

const signed char ditl_tab[28] = {
        0, 7, 10, 13, 16, 23, 26,
        1, 4, 11, 14, 17, 20, 27,
        2, 5, 8, 15, 18, 21, 24,
        3, 6, 9, 12, 19, 22, 25};

int sourceData[28];

void rsEncodeWithType(short *fullKKDatas, char type, short *resultFullRsData) {
    int kkData[usefulKK];
    int ttData[2 * tt];
    int i;
    int kLoop;
    switch (type) {
        case 3:
            for (kLoop = 0; kLoop < 4; kLoop++) {
                for (i = 0; i < usefulKK; i++) {
                    kkData[i] = *(fullKKDatas + kLoop * 3 + i);
                    sourceData[kLoop * 7 + i] = kkData[i];
                }
                rsEncode(kkData, ttData);
                for (i = 0; i < 2 * tt; i++) {
                    sourceData[kLoop * 7 + usefulKK + i] = ttData[i];
                }
            }
            //交织
            for (i = 0; i < 28; i++) {
                resultFullRsData[ditl_tab[i]] = sourceData[i];
            }
            break;
        case 2:
            for (i = 0; i < usefulKK; i++) {
                kkData[i] = *(fullKKDatas + i);
                sourceData[+i] = kkData[i];
            }
            rsEncode(kkData, ttData);
            for (i = 0; i < 2 * tt; i++) {
                sourceData[usefulKK + i] = ttData[i];
            }

            //{a,b,c,d,e,f,g},{e,f,g,a,b,c,d}
            //交织
            resultFullRsData[0] = (char)sourceData[0];
            resultFullRsData[1] = (char)sourceData[1];
            resultFullRsData[2] = (char)sourceData[2];
            resultFullRsData[3] = (char)sourceData[3];
            resultFullRsData[4] = (char)sourceData[4];
            resultFullRsData[5] = (char)sourceData[5];
            resultFullRsData[6] = (char)sourceData[6];
            resultFullRsData[0 + 7] = (char)sourceData[4];
            resultFullRsData[1 + 7] = (char)sourceData[5];
            resultFullRsData[2 + 7] = (char)sourceData[6];
            resultFullRsData[3 + 7] = (char)sourceData[0];
            resultFullRsData[4 + 7] = (char)sourceData[1];
            resultFullRsData[5 + 7] = (char)sourceData[2];
            resultFullRsData[6 + 7] = (char)sourceData[3];

            break;

    }
}

//int resultData[ usefulKK + 1] ;
void testRSEncode() {
    rsEncodeInit();
    short fullKKDatas[12] = {
            1, 2, 3, 3, 2, 1, 4, 5, 6, 6, 5, 4
    };
    short resultFullRsDatas[28];
    rsEncodeWithType(fullKKDatas, 3, resultFullRsDatas);
    printf("\r\n\r\n\r\n---\r\n");
    for (int i = 0; i < 28; i++) {
        //printf("%d %d \n", i , resultFullRsDatas[i]);
        printf("%d,", sourceData[i]);

    }
    printf("\r\n");
    for (int i = 0; i < 28; i++) {
        //printf("%d %d \n", i , resultFullRsDatas[i]);
        printf("%d,", resultFullRsDatas[i]);
    }
    printf("\r\n");
}