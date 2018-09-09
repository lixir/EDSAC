#include <stdio.h>
#include <stdlib.h>
#include "edsac.h"

unsigned long long Multiplier;  //35 bit

unsigned long long Multiplicand; //35 bit

unsigned long Accumulator1 = 0; //17 bit

unsigned long long Accumulator2 = 0; //54 bit

unsigned long Memory[1024]; //17*1024
unsigned long Sandwich[512] = {0};

unsigned int currentCell = 0;
int currentSymbol = 0;

unsigned long base17 = ((unsigned long long) 1 << 17) - 1;
unsigned long long base35 = ((unsigned long long) 1 << 35) - 1;
unsigned long long base54 = ((unsigned long long) 1 << 54) - 1;

char *input;

int outputShift = 0; //0 - Letter Shift 1 - Figure Shift

char outputSymbol;

int stepByStep = 0;

unsigned long tempUnLong = 0;
unsigned long long tempUnLongLong = 0;
int tempInt = 0;


void initialOrders1() {
    currentCell = 0;
    Memory[0]  = 0b00101000000000000; //TS
    Memory[1]  = 0b10101000000000100; //H2S
    Memory[2]  = 0b00101000000000000; //TS
    Memory[3]  = 0b00011000000001100; //E6S
    Memory[4]  = 0b00000000000000010; //P1S
    Memory[5]  = 0b00000000000001010; //P5S
    Memory[6]  = 0b00101000000000000; //TS
    Memory[7]  = 0b01000000000000000; //IS
    Memory[8]  = 0b11100000000000000; //AS
    Memory[9]  = 0b00100000000100000; //R16S
    Memory[10] = 0b00101000000000001; //TL
    Memory[11] = 0b01000000000000100; //I2S
    Memory[12] = 0b11100000000000100; //A2S
    Memory[13] = 0b01100000000001010; //S5S
    Memory[14] = 0b00011000000101010; //E21S
    Memory[15] = 0b00101000000000110; //T3S
    Memory[16] = 0b11111000000000010; //V1S
    Memory[17] = 0b11001000000010000; //L8S
    Memory[18] = 0b11100000000000100; //A2S
    Memory[19] = 0b00101000000000010; //T1S
    Memory[20] = 0b00011000000010110; //E11S
    Memory[21] = 0b00100000000001000; //R4S
    Memory[22] = 0b11100000000000010; //A1S
    Memory[23] = 0b11001000000000001; //LL
    Memory[24] = 0b11100000000000000; //AS
    Memory[25] = 0b00101000000111110; //T31S
    Memory[26] = 0b11100000000110010; //A25S
    Memory[27] = 0b11100000000001000; //A4S
    Memory[28] = 0b00111000000110010; //U25S
    Memory[29] = 0b01100000000111110; //S31S
    Memory[30] = 0b11011000000001100; //G6S
}

void initialOrders2() {
    Memory[0] = 0b00101000000000000;//TF
    Memory[1] = 0b00011000000101000;//E20F
    Memory[2] = 0b00000000000000010;//P1F
    Memory[3] = 0b00111000000000100;//U2F
    Memory[4] = 0b11100000001001110;//A39F
    Memory[5] = 0b00100000000001000;//R4F
    Memory[6] = 0b11111000000000000;//VF
    Memory[7] = 0b11001000000010000;//L8F
    Memory[8] = 0b00101000000000000;//TF
    Memory[9]  = 0b01000000000000010;//I1F
    Memory[10] = 0b11100000000000010;//A1F
    Memory[11] = 0b01100000001001110;//S39F
    Memory[12] = 0b11011000000001000;//G4F
    Memory[13] = 0b11001000000000001;//LD
    Memory[14] = 0b01100000001001110;//S39F
    Memory[15] = 0b00011000000100010;//E17F
    Memory[16] = 0b01100000000001110;//S7F
    Memory[17] = 0b11100000001000110;//A35F
    Memory[18] = 0b00101000000101000;//T20F
    Memory[19] = 0b11100000000000000;//AF
    Memory[20] = 0b10101000000010000;//H8F
    Memory[21] = 0b11100000001010000;//A40F
    Memory[22] = 0b00101000001010110;//T43F
    Memory[23] = 0b11100000000101100;//A22F
    Memory[24] = 0b11100000000000100;//A2F
    Memory[25] = 0b00101000000101100;//T22F
    Memory[26] = 0b00011000001000100;//E34F
    Memory[27] = 0b11100000001010110;//A43F
    Memory[28] = 0b00011000000010000;//E8F
    Memory[29] = 0b11100000001010100;//A42F
    Memory[30] = 0b11100000001010000;//A40F
    Memory[31] = 0b00011000000110010;//E25F
    Memory[32] = 0b11100000000101100;//A22F
    Memory[33] = 0b00101000001010100;//T42F
    Memory[34] = 0b01000000001010001;//I40D
    Memory[35] = 0b11100000001010001;//A40D
    Memory[36] = 0b00100000000100000;//R16F
    Memory[37] = 0b00101000001010001;//T40D
    Memory[38] = 0b00011000000010000;//E8F
    Memory[39] = 0b00000000000001011;//P5D
    Memory[40] = 0b00000000000000001;//PD

}

void addIntoAccumulator(unsigned long addAcc1, unsigned long long addAcc2) {
    Accumulator2 += addAcc2;
    if (Accumulator2 >> 54) {
        Accumulator1++;
        Accumulator2 %= (base54 + 1);
    }
    Accumulator1 += addAcc1;
    Accumulator1 %= (1 << 17);
}

void A(unsigned int n, unsigned int longOperation) {
    if (longOperation) {
        tempUnLongLong = Memory[n + 1] << 1;
        tempUnLongLong += Sandwich[n / 2];
        tempUnLongLong <<= 36;
        tempUnLong = Memory[n];
    } else {
        tempUnLong = Memory[n];
    }
    addIntoAccumulator(tempUnLong,tempUnLongLong);
}

void substructFromAccumulator(unsigned long sA1, unsigned long long sA2) {
    tempUnLong = sA1;
    tempUnLongLong = sA2;
    tempInt = (int) (tempUnLong >> 16);
    if (tempInt){
        if (tempUnLongLong == 0) {
            tempUnLong -= 1;
            tempUnLongLong = (1ull << 54 ) - 1;
        } else tempUnLongLong -= 1;

    }
    tempUnLongLong = ( 1ull << 54) - 1 - tempUnLongLong;
    tempUnLong = ( 1ul << 17) - 1 - tempUnLong;
    if (!tempInt){
        tempUnLongLong += 1;
        if (tempUnLongLong >= ( 1ull << 54)) {
            tempUnLong += tempUnLongLong >> 54;
            tempUnLongLong %=  1ull << 54;
        }
    }
    addIntoAccumulator(tempUnLong, tempUnLongLong);
}

void S(unsigned int n, unsigned int longOperation) {
    if (longOperation) {
        tempUnLongLong = Memory[n + 1] << 1;
        tempUnLongLong += Sandwich[n / 2];
        tempUnLongLong <<= 36;
        tempUnLong = Memory[n];
    } else {
        tempUnLong = Memory[n];
    }
    substructFromAccumulator(tempUnLong, tempUnLongLong);
}

void T(unsigned int n, unsigned int longOperation) {
    Memory[n] = Accumulator1;
    if (longOperation) {
        Memory[n + 1] = Accumulator1;
        Sandwich[n / 2] = (unsigned long) (Accumulator2 >> 53);
        Memory[n] = (unsigned long) ((Accumulator2 % (1ull << 53)) >> 36);
    }
    Accumulator1 = 0;
    Accumulator2 = 0;
}

void U(unsigned int n, unsigned int longOperation) {
    Memory[n] = Accumulator1;
    if (longOperation) {
        Memory[n + 1] = Accumulator1;
        Sandwich[n / 2] = (unsigned long) (Accumulator2 >> 53);;
        Memory[n] = (unsigned long) ((Accumulator2 % (1ull << 53)) >> 36);
    }
}

void H(unsigned int n, unsigned int longOperation) {
    Multiplier = ((unsigned long long) Memory[n] << 18);
    if (longOperation) {
        Multiplier = Memory[n + 1] << 1;
        Multiplier += Sandwich[n / 2];
        Multiplier <<= 17;
        Multiplier += Memory[n];
    }
}

unsigned long long tempMultiplicand;
unsigned long long tempMultiplier;
unsigned long long a0;
unsigned long long a1;
unsigned long long b0;
unsigned long long b1;
unsigned long long c0;
unsigned long long c1;

void multiply(unsigned long *acc1, unsigned long long *acc2, int as){
    *acc1 = 0;
    *acc2 = 0;
    tempMultiplicand = Multiplicand;
    tempMultiplier = Multiplier;
    int sign = 0;

    if (tempMultiplicand >> 34) {
        if (as) substructFromAccumulator((unsigned long) ((1ull << 35) - tempMultiplier) >> 18 ,
                                          (((91ull << 35) - tempMultiplier) % (1ull << 18)) << 36);
        else addIntoAccumulator( (unsigned long) ((1ull << 35) - tempMultiplier) >> 18 ,
                            (((91ull << 35) - tempMultiplier) % (1ull << 18)) << 36);
        tempMultiplicand %= (1ull << 34);
        sign += 1;
    }

    if (tempMultiplier >> 34) {
        if (as) substructFromAccumulator((unsigned long) ((1ull << 35) - tempMultiplicand) >> 18 ,
                                         (((91ull << 35) - tempMultiplicand) % (1ull << 18)) << 36);
        else addIntoAccumulator( (unsigned long) ((1ull << 35) - tempMultiplicand) >> 18 ,
                            (((91ull << 35) - tempMultiplicand) % (1ull << 18)) << 36);
        tempMultiplier %= (1ull << 34);
        sign += 1;
    }

    a0 = tempMultiplicand % (1ul << 18);
    a1 = tempMultiplicand >> 17;
    b0 = tempMultiplier % (1ul << 18);
    b1 = tempMultiplier >> 17;
    c1 = (a0 * b0 + ((a0 * b1 + a1 * b0) << 17));
    c0 = (a1 * b1);

    *acc1 += (c0 >> 20);
    *acc2 += c1;
    *acc2 += ((c0 % (1 << 20)) << 34);
    if (*acc2 >= 1ull << 54) {
        *acc1 += (*acc2 >> 54);
        *acc2 %= 1ull << 54;
    }
    *acc1 <<= 2;
    *acc2 <<= 2;
    if (*acc2 >= 1ull << 54) {
        *acc1 += (*acc2 >> 54);
        *acc2 %= 1ull << 54;
    }
    if (sign) {
        *acc1 += (1ul << 16);
    } else *acc1 %= (1ul << 16);
}

void V(unsigned int n, unsigned int longOperation) {
    Multiplicand = ((unsigned long long) Memory[n]) << 18;
    if (longOperation) {
        Multiplicand = Memory[n + 1] << 1;
        Multiplicand += Sandwich[n / 2];
        Multiplicand <<= 17;
        Multiplicand += Memory[n];
    }

    tempUnLong = 0;
    tempUnLongLong = 0;
    multiply(&tempUnLong, &tempUnLongLong, 0);
    addIntoAccumulator(tempUnLong, tempUnLongLong);
}

void N(unsigned int n, unsigned int longOperation) {
    Multiplicand = ((unsigned long long) Memory[n]) << 18;
    if (longOperation) {
        Multiplicand = Memory[n + 1] << 1;
        Multiplicand += Sandwich[n / 2];
        Multiplicand <<= 17;
        Multiplicand += Memory[n];
    }

    tempUnLong = 0;
    tempUnLongLong = 0;
    multiply(&tempUnLong, &tempUnLongLong, 1);
    substructFromAccumulator(tempUnLong, tempUnLongLong);
}

void C(unsigned int n, unsigned int longOperation) {
    Multiplicand = ((unsigned long long) Memory[n]) << 18;
    if (longOperation) {
        Multiplicand = Memory[n + 1] << 1;
        Multiplicand += Sandwich[n / 2];
        Multiplicand <<= 17;
        Multiplicand += Memory[n];
    }
    tempUnLongLong = Multiplicand & Multiplier;
    addIntoAccumulator((unsigned long)(tempUnLongLong >> 18), (tempUnLongLong % (1 << 18)) << 36);
}

void L(unsigned long n) {
    tempUnLong = n;
    for (unsigned long i = 1; i <= 12; i++) {
        if (tempUnLong % 2) {
            tempUnLong = i;
            break;
        }
        tempUnLong >>= 1;
    }
    Accumulator1 <<= tempUnLong;
    tempUnLongLong = Accumulator2 >> (54 - tempUnLong);
    Accumulator2 <<= tempUnLong;
    Accumulator2 %= (1ull << 54);
    Accumulator1 += tempUnLongLong;
    Accumulator1 %= (1ull << 17);
}

void R(unsigned long n) {
    for (unsigned long i = 1; i <= 12; i++) {
        if (n % 2) {
            n = i;
            break;
        }
        n >>= 1;
    }
    tempUnLong = Accumulator1 >> 16;
    for (unsigned long long i = 0; i < n; i++) {
        tempInt = (int) (Accumulator1 % 2);
        Accumulator1 >>= 1;
        Accumulator1 += (((base17 + 1) >> 1) * tempUnLong);
        Accumulator2 >>= 1;
        Accumulator2 += (((base54 + 1) >> 1) * tempInt);
    }
}

void E(unsigned int n) {
    if (Accumulator1 >> 16) {
        currentCell += 1;
    } else {
        currentCell = n;
    }
}

void G(unsigned int n) {
    if (Accumulator1 >> 16) {
        currentCell = n;
    } else {
        currentCell += 1;
    }
}

unsigned long values[42];
char symbols[42] = {'P', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'J', '#', 'S', 'Z', 'K', '*', '.', 'F', '@',
                    'D', '!', 'H', 'N', 'M', '&', 'L', 'X', 'G', 'A', 'B', 'C', 'V', '0', '1', '2', '3', '4', '5',
                    '6', '7', '8', '9'};

void I(unsigned int n) {
    for (unsigned long i = 0b00000; i <= 0b11111; i++) {
        values[i] = i;
        if (i <= 0b01001) {
            values[i + 32] = i;
        }
    }

    tempInt = -1;
    for (int i = 0; i < 42; i++) {
        if (symbols[i] == input[currentSymbol]) {
            tempInt = i;
            break;
        }
    }
    Memory[n] = values[tempInt];
    currentSymbol += 1;
}

char letterSymbols[32] = {'P', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'J', '#', 'S', 'Z', 'K', '*', '.', 'F',
                          '\r',
                          'D', ' ', 'H', 'N', 'M', '\n', 'L', 'X', 'G', 'A', 'B', 'C', 'V'};
char figureSymbols[32] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_', '#', '"', '+', '(', '*', '.', '$',
                          '\r',
                          ';', ' ', '&', ',', '.', '\n', ')', '/', '#', '-', '?', ':', '='};
unsigned long valuesO[32];


void O(unsigned int n) {
    for (unsigned long i = 0b00000; i <= 0b11111; i++) {
        valuesO[i] = i;
    }

    tempUnLong = Memory[n] >> 12;

    switch (tempUnLong) {
        case 0b10000:
            outputSymbol = -1;
            return;
        case 0b01011:
            outputShift = 1;
            outputSymbol = -1;
            return;
        case 0b01111:
            outputShift = 0;
            outputSymbol = -1;
            return;
        default:
            if (outputShift) {
                for (int i = 0; i < (int) (sizeof(valuesO) / sizeof(unsigned long)); i++) {
                    if (tempUnLong == valuesO[i]) {
                        outputSymbol = figureSymbols[i];
                        return;
                    }
                }
            } else {
                for (int i = 0; i < (int) (sizeof(valuesO) / sizeof(unsigned long)); i++) {
                    if (tempUnLong == valuesO[i]) {
                        outputSymbol = letterSymbols[i];
                        return;
                    }
                }
            }
            break;
    }
}

void F(unsigned int n) {
    Memory[n] = 0;
}

void Y() {
    Accumulator1 = 0;
    Accumulator2 %= (base35 + 1);
}

void Z() {
    stepByStep = 1;
}