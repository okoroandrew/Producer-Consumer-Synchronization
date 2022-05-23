#define MAX_CHAR 64
#define MAX_CHAR_BIT 512

char* readFile(char * path){
    /** This is a routine that reads the user input file into memory*/
    char* buffer = 0;
    long length;
    FILE * f = fopen (path, "rb");
    if (f){
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = (char*)malloc ((length+1)*sizeof(char));
        if (buffer){
            fread (buffer, sizeof(char), length, f);
        }
    }
    buffer[length] = '\0';
    return buffer;
}

char *sliceString(char *str, int start, int end){
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


char* stringToBinary(char* s) {
    /** This function is for converting each character in a string to binary and returning a binary string*/
    if(s == NULL) return 0;
    size_t len = strlen(s);
    char *binary = malloc(len*8 + 1); //1 for null terminator
    binary[0] = '\0';
    for(size_t i = 0; i < len; ++i) {
        char ch = s[i];
        for(int j = 6; j >= 0; --j){
            if(ch & (1 << j)) {
                strcat(binary,"1");
            } else {
                strcat(binary,"0");
            }
        }
    }
    return binary;
}

char * addParityBit(char * bitString) {
    /** It checks for odd parity and appends a 1 in front of the bits if even and a 0 if odd.*/
    char *one = "1";
    char *zero = "0";
    char * evenParity = (char *) malloc (sizeof (char) + sizeof (bitString) + 1);
    char * oddParity = (char *) malloc (sizeof (char) + sizeof (bitString) + 1);
    int count = 0;
    for (char *bitStringP = bitString; *bitStringP != '\0'; ++bitStringP){
        if (*bitStringP == '1') count ++;
    }
    if (count % 2 == 0){
        strcat(strcat(evenParity, one), bitString);
        return evenParity;
    }
    else{
        strcat(strcat(oddParity, zero), bitString);
        return oddParity;
    }
}

char * DecimalToBinary(int num) {
    /** This is for converting a decimal to binary, It helps the producer to convert
     * the control digit its 8 bits binary equivalence*/
    int n = num;
    char *s = malloc(sizeof(int) * 8);
    int i, c = 0;

    for (i = sizeof(int) * 2 - 1; i >= 0; i--) {
        n = num >> i;
        *(s + c) = (n & 1) ? '1' : '0';
        c++;
    }
    *(s + c) = NULL;
    return s;
}

char* framing(char * parityBitString, int BitsLeft){
    /** Generates frames for transmission by concatenating the syn bits, control bits, and data bits*/
    char * synBit = "0001011000010110";
    char * controlChar = (BitsLeft >= MAX_CHAR_BIT) ? DecimalToBinary(MAX_CHAR) : DecimalToBinary(
            MAX_CHAR_BIT % BitsLeft);
    char * frame;
    frame = (char *) malloc(sizeof(char) * (strlen(synBit) + strlen(controlChar) + strlen(parityBitString)) + 1);
    strcat(strcat(strcat(frame, synBit), controlChar), parityBitString);
    return frame;
}

void writeFile(char* path, char* text){
    /** A function that writes to an outputfile specified by the path argument*/
    FILE *f = fopen(path, "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f, "%s\n", text);
    fclose(f);
}

