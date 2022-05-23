/**
 *
 * CLient Decoder Functions
 *
 * */

char *sliceStringC(char *str, int start, int end){
    /** This is for getting a substring from a string by specifying the parameters - string,
     * where the substring begins (start), and where it should (end)*/
    int i;
    int size = (end - start) + 2;
    char *bitString = (char *)malloc(size * sizeof(char));

    for (i = 0; start <= end; start++, i++){
        
        bitString[i] = str[start];
    }
    bitString[size] = '\0';
    return bitString;
}
char * parityCheck(char * dataString) {
    /** counts the number of 1 in a string bits and return even or odd based on the count*/
    int count = 0;
    for (char *dataStringP = dataString; *dataStringP != '\0'; ++dataStringP){
        if (*dataStringP == '1') count ++;
    }
    return (count % 2 == 0) ? "even parity" : "odd parity";
}

char * deFraming(char * frameString){
    /** from dropping the syn bits and control bits from a frame and returns only the data bits (with parity)*/
    char * syncBit = "0001011000010110";
    if (strcmp(sliceStringC(frameString, 0, 15), syncBit) == 0){
        return sliceStringC(frameString, 24, (int) strlen(frameString));
    }
    else if (strlen(frameString) == 0){
        printf("No frame received\n");
    }
    else printf("error in deFraming, check frame!!!\n");
    return NULL;
}

char * getDataString(char * deFramedString){
    /** Checks for parity,If the parity is odd, it drops the most significant bit and replaces it with a zero.
     * Otherwise, it would report it as a transmission error. All the data bit is merged
     * and ready for conversion into ASCII.*/
    char * dataBits = (char *)malloc(sizeof(char) * strlen(deFramedString) + 1);
    int start = 0, end = 7;
    char * dataStringWithParity;
    for (int i = 0; i < strlen(deFramedString)/8; i++){
        dataStringWithParity = sliceStringC(deFramedString, start, end);
        start += 8, end += 8;
        if (strcmp(parityCheck(dataStringWithParity), "odd parity") == 0){
            char * a = sliceStringC(dataStringWithParity, 1, 7);
            strcat(strcat(dataBits, "0"), a);
        }
        else printf("There's an error in the data bit!!!");
    }
    return dataBits;
}

void BinaryToText(char * bitsToConvert, char * outputFilePath) {
    /** converts each binary bit into an ASCII char, use toupper() function to convert to UPPER CASE
     * and writer the char to the screen as well as to an output file*/
    FILE *f = fopen(outputFilePath, "w");
    char * inputBuffer;
    char temp;
    int start = 0, end = 7;
    if (bitsToConvert == NULL) exit(1);
    unsigned long bitsLeft = strlen(bitsToConvert);
    do {
        inputBuffer = sliceStringC(bitsToConvert, start, end);
        if (bitsLeft < 8)
            break;
        temp = 0;
        for (int i = 0; i < 8; ++i) {
            temp |= (inputBuffer[i] & 1) << (7 - i);
            temp = toupper (temp);              // Converts each character TO UPPER CASE
        }
        bitsLeft -= 8; start += 8, end += 8;
        printf("%c", temp);
        fputc(temp, f);
    } while (1);
    fclose(f);
    printf("\n");
}
