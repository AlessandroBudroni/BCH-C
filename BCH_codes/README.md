BCH codes

 * This library is a fork of http://lxr.free-electrons.com/source/lib/bch.c
  
 * Author: Alessandro Budroni
 
 * Recent modification: Creation of two functions to encode/decode 128-bit messages.
 
 $ make

 $ make test

 The test perform the following thest on random 128-bit messages:
 - correct up to 4 errors
 - detect more than 4 errors 
