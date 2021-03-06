
#include "ServerEncoderLibrary.h"

#define MAX_CHAR_BITS 512
#define CHAR_BITS 8


char * serverEncoder(char * text){
    char *str = stringToBinary(text);

    /** Slice through the entire binary string,taking 7 bits at a time, add a parity bit in front, and store
     * in bitsToFrame */
    char * bitsToFrame = (char *) malloc(sizeof (char) * strlen(str) + 1);
    int start = 0, end = CHAR_BITS - 2;

    for (int i = 0; i < (strlen(str) + 1) / (CHAR_BITS - 1); i++){
        char * slicedBitsWithParity = addParityBit( sliceString(str, start, end));
        strcat(bitsToFrame, slicedBitsWithParity);
        start += CHAR_BITS - 1; end += CHAR_BITS - 1;
    }

    /** iterate through bitsToFrame, after every 512 bits (64 characters), frame, and store in writeThis.
     * transmit writeThis to a binary (.binf) file */
    char *toFrame;
    char * writeThis = (char *)malloc(sizeof (char) * 8056);
    int begin = 0, stop = MAX_CHAR_BITS - 1, countBitsLeft = (int)strlen(bitsToFrame);
    for (int i = 0; i <= strlen(bitsToFrame) / MAX_CHAR_BITS; i++){
        if(countBitsLeft >= MAX_CHAR_BITS) {
            toFrame = sliceString(bitsToFrame, begin, stop);
        }
        else {
            toFrame = sliceString(bitsToFrame, begin, (begin + countBitsLeft - 1));
        }
        char * toTransmit = framing(toFrame, countBitsLeft);
        strcat(writeThis, toTransmit);
        begin += MAX_CHAR_BITS; stop += MAX_CHAR_BITS; countBitsLeft -= MAX_CHAR_BITS;
    }
    //writeFile(binaryOutputFilePath,  writeThis);
    return writeThis;
}


