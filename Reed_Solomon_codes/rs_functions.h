//
//  rs_lib.h
//  BCH-C
//
//  Created by Alessandro Budroni on 05/07/16.
//  Copyright © 2016 Alessandro Budroni. All rights reserved.
//

#ifndef rs_lib_h
#define rs_lib_h

#include <stdio.h>
#include <string.h>
#include <math.h>

#define mm  4           /* RS code over GF(2**4) - change to suit */
#define nn  15          /* nn=2**mm -1   length of codeword */
#define tt  3           /* number of errors that can be corrected */
#define kk  9           /* kk = nn-2*tt  */

#define FAILED_CORRECTING -99

void generate_gf(int alpha_to[], int index_of[], int pp[]);

void gen_poly(int alpha_to[], int index_of[], int gg[]);

void encode_rs(unsigned char data[], int alpha_to[], int index_of[],int gg[], unsigned char bb[]);

int decode_rs(unsigned char recd[], int alpha_to[], int index_of[]);

void GenerateRS128(const unsigned char* pPayload, int payloadLen, unsigned char* pResult, int* pResultLen );

int ValidateRS128(unsigned char* pInput, int inputLen, unsigned char* pPayload, int maxPayloadLen );

#endif /* rs_lib_h */