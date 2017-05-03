/* make_wav.h
 * Fri Jun 18 17:06:02 PDT 2010 Kevin Karplus
 */
 
#ifndef MAKE_WAV_H
#define MAKE_WAV_H


#define S_RATE  22500
//#define BUF_SIZE 15136 /* 2 second buffer */

void write_wav(const char * filename, unsigned long num_samples, short int * data, int s_rate);
    /* open a file named filename, write signed 16-bit values as a
        monoaural WAV file at the specified sampling rate
        and close the file
    */
 
#endif
