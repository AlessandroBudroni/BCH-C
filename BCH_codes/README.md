# BCH codes

 * This library is a fork of http://lxr.free-electrons.com/source/lib/bch.c
  
 * Author: Alessandro Budroni
 
 * Recent modification: Creation of two functions to encode/decode 128-bit messages.
 
 ```
 $ make
 $ make test
```

The test performs the following tests on random 128-bit messages with 32-bit of redundancy:
 - correct up to 4 errors
 - detect more than 4 errors 
