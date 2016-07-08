

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "rs_functions.h"

int main()
{
    time_t t;
    int encoded_data_len = 0;
    int pp [mm+1] = { 1, 1, 0, 0, 1}, ret ; /* specify irreducible polynomial coeffts */
    int alpha_to [nn+1], index_of [nn+1], gg [nn-kk+1] ;
    unsigned char data [kk], original_data[kk], encoded_data [nn] ;
    int i;
    
    srand((unsigned) time(&t));

    generate_gf(alpha_to, index_of, pp) ;


/* compute the generator polynomial for this RS code */
  gen_poly(alpha_to, index_of, gg) ;


/* for known data, stick a few numbers into a zero codeword. Data is in
   polynomial form.
*/
for  (i=0; i<kk; i++)   data[i] = 0 ;

/* for example, say we transmit the following message (nothing special!) */
data[0] = 8 ;
data[1] = 6 ;
data[2] = 8 ;
data[3] = 1 ;
data[4] = 2 ;
data[5] = 4 ;
data[6] = 15 ;
data[7] = 9 ;
data[8] = 9 ;
    
    for (i=0; i<kk; i++)
        original_data[i] = data[i];

    
    GenerateRS128(data, kk, encoded_data, &encoded_data_len);
    
    for (i = 0; i<3; i++) {
        encoded_data[rand() % nn] = rand() % 128;
    }
    
    
    ret = ValidateRS128(encoded_data, nn, data, kk );
    

    if (ret != 0)
    {
        printf("\n\nFAILED\n");
        return -1;
    }
    
    if(!strncmp((const char*)original_data, (const char*)data, kk))
    {
        printf("\n\nPASSED\n");
        return 0;
    }
    else
        return -1;

}


