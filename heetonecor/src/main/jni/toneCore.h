#ifndef _TONECORE_H_
#define _TONECORE_H_

//transmitter sampling frequency
#define FS  22500

#define COR_L_BS 180
// Repeat number for base length
#define RPT_NUM 6
// Correlation length
#define COR_L COR_L_BS*RPT_NUM
// Head and tail length
#define TONE_HTL 23

#define COR_L_AND_HL COR_L+TONE_HTL
// Tone length
#define TONE_L (2*TONE_HTL+COR_L)

#endif