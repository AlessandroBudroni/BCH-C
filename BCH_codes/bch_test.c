/*
 * Generic binary BCH encoding/decoding library
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * This library is a fork of http://lxr.free-electrons.com/source/lib/bch.c
 *
 * Author: Alessandro Budroni
 *
 * Modifications: Creation of two functions to encode/decode 128-bit messages.
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "bch_functions.h"

#define len_msg 16

int main(){
    
    time_t t;
    int i,j, count = 1000, pEncodedLen, pDecodedLen, errors, ret, maxEncodedLen = len_msg+4;
    unsigned char msg[len_msg], original_msg[len_msg];
    unsigned char pEncoded[maxEncodedLen], pDecoded[len_msg];
    
    srand((unsigned) time(&t));
    
    printf("Start testing.\n\n");
    
    printf("Test correcting 0-%d errors:...           ",maxEncodedLen-len_msg);
    for (j = 1; j<=1000; j++) {
    
        // Generate message
    
        for (i = 0; i< len_msg; i++) {
            msg[i] = rand() % 256;
        }
        
        memcpy(original_msg, msg, len_msg);
    
        // Generate the code
        
        GenerateBCH128( msg, len_msg, pEncoded, maxEncodedLen, &pEncodedLen);
        
        // Generate errors
    
        errors = rand() % (maxEncodedLen-len_msg+1);
    
        for (i= 0; i<errors; i++){
            pEncoded[rand() % (pEncodedLen+1)] ^= ((unsigned char) 1 << ((rand() % 8)) & 0xFF);
        }
    
        // Decode and correct
    
        ValidateBCH128(pEncoded, pEncodedLen, pDecoded, maxEncodedLen, &pDecodedLen);
    
        if(strncmp((char*)original_msg, (char*)pDecoded, len_msg)){
            count--;
            printf("     - failed with %d errors test n. %d\n",errors,j-1);
        }
    }
    printf("\nfinished %d tests, %d%% passed!\n\n",j-1, (count)/10);
    
    count = 1000;
    printf("Test detecting more than %d errors:...    \n", maxEncodedLen-len_msg);
    for (j = 1; j<=1000; j++) {
        
        // Generate message
        
        for (i = 0; i< len_msg; i++) {
            msg[i] = rand() % 256;
        }
        
        memcpy(original_msg, msg, len_msg);
        
        // Generate the code
        
        GenerateBCH128( msg, len_msg, pEncoded, maxEncodedLen, &pEncodedLen);
        
        // Generate errors
        
        errors = (rand() % 50);
        
        for (i= 0; i<errors; i++){
            pEncoded[rand() % (pEncodedLen+1)] ^= ((unsigned char) 1 << ((rand() % 8)) & 0xFF);
        }
        
        // Decode and correct
        
        ret = ValidateBCH128(pEncoded, pEncodedLen, pDecoded, maxEncodedLen, &pDecodedLen);
        
        if(ret == 0 && strncmp((char*)original_msg, (char*)pDecoded, len_msg))
        {
            count--;
            printf("     - failed with %d errors, test n. %d\n",errors,j-1);
        }
    }
    printf("finished %d tests, %d%% passed!\n\n",j-1,(count)/10);
    printf("End testing.\n");
    
    return 0;
}



