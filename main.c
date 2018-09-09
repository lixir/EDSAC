#include <stdlib.h>
#include <stdio.h>
#include "edsac.h"


void print2(unsigned long long number, int n, FILE *fo){
    tempUnLongLong = number;
    char text[54] = {'0'};
    for (int i = 0; i < n; i++){
        text[i] = '0';
    }
    for (int i = 0; i < n; i++){
        tempInt = (int) (tempUnLongLong % 2);
        tempUnLongLong >>= 1;
        if (tempInt) text[n - 1 - i] = '1';
    }
    for (int i = 0; i < n; i++){
        putc(text[i], fo);
    }
}

void printInt(int number, FILE *fo){
    putc('0' + number / 1000, fo);
    putc('0' + (number / 100) % 10, fo);
    putc('0' + (number / 10) % 10, fo);
    putc('0' + number % 10, fo);
}

FILE *fo;
void printOut(char fileName[]){
    fo = fopen(fileName, "w");
    fwrite("\n========================================================================================================",
            sizeof(char), 80, fo);
    fwrite("\nMultiplier   = ", sizeof(char), 16, fo);
    print2(Multiplier, 35, fo);
    fwrite("\nMultiplicand = ", sizeof(char), 16, fo);
    print2(Multiplicand, 35, fo);
    fwrite("\nAccumulator  = ", sizeof(char), 16, fo);
    print2(Accumulator1, 17, fo);
    print2(Accumulator2, 54, fo);
    fwrite("\nMemory:      \n", sizeof(char), 15, fo);
    for (int i = 0; i < 1024; i += 2){
        printInt(i + 1, fo);
        fwrite("  |  ", sizeof(char), 6, fo);
        print2(Memory[i + 1], 17, fo);
        fwrite("  |  ", sizeof(char), 6, fo);
        print2(Sandwich[i /2], 1, fo);
        fwrite("  |  ", sizeof(char), 6, fo);
        printInt(i, fo);
        fwrite("  |  ", sizeof(char), 6, fo);
        print2(Memory[i], 17, fo);
        fwrite("\n", sizeof(char), 1, fo);
    }


    fwrite("\n========================================================================================================",
           sizeof(char), 80, fo);
    fclose(fo);
}


int main(int argc, char *argv[]) {

    if (argv[4][0] == '1') initialOrders1();
    else if (argv[4][0] == '2') initialOrders2();
    else exit(1);

    FILE *f = fopen(argv[1], "r");
    int size = ftell(f);
    input = calloc((size_t) 1024, sizeof(char));
    fgets(input, 1024, f);
    fclose(f);

    FILE *teleprinter = fopen(argv[3], "w");
    unsigned long memoryValue;
    unsigned long lastBit;
    unsigned long temp;

    while (currentCell < 1024) {
        memoryValue = (Memory[currentCell] % (1 << 12)) >> 1;
        lastBit = Memory[currentCell] % 2;
        temp = Memory[currentCell];
        tempUnLong = 0;
        tempUnLongLong = 0;
        tempInt = 0;

        switch (temp >> 12) {
            case 0b11100:
                if (lastBit) memoryValue = (memoryValue / 2) * 2;
                A(memoryValue, lastBit);
                currentCell++;
                break;
            case 0b01100:
                if (lastBit) memoryValue = (memoryValue / 2) * 2;
                S(memoryValue, lastBit);
                currentCell++;
                break;
            case 0b00101:
                if (lastBit) memoryValue = (memoryValue / 2) * 2;
                T(memoryValue, lastBit);
                currentCell++;
                break;
            case 0b00111:
                if (lastBit) memoryValue = (memoryValue / 2) * 2;
                U(memoryValue, lastBit);
                currentCell++;
                break;
            case 0b10101:
                if (lastBit) memoryValue = (memoryValue / 2) * 2;
                H(memoryValue, lastBit);
                currentCell++;
                break;
            case 0b11111:
                if (lastBit) memoryValue = (memoryValue / 2) * 2;
                V(memoryValue, lastBit);
                currentCell++;
                break;
            case 0b10110:
                if (lastBit) memoryValue = (memoryValue / 2) * 2;
                N(memoryValue, lastBit);
                currentCell++;
                break;
            case 0b11110:
                if (lastBit) memoryValue = (memoryValue / 2) * 2;
                C(memoryValue, lastBit);
                currentCell++;
                break;
            case 0b11001:
                L((memoryValue << 1) + lastBit);
                currentCell++;
                break;
            case 0b00100:
                R((memoryValue << 1) + lastBit);
                currentCell++;
                break;
            case 0b00011:
                E(memoryValue);
                break;
            case 0b11011:
                G(memoryValue);
                break;
            case 0b01000:
                I(memoryValue);
                currentCell++;
                break;
            case 0b01001:
                O(memoryValue);
                putc(outputSymbol, teleprinter);
                currentCell++;
                break;
            case 0b10001:
                F(memoryValue);
                currentCell++;
                break;
            case 0b00110:
                Y();
                currentCell++;
                break;
            case 0b01101:
                Z();
                currentCell++;
                break;
            default:
                currentCell++;
        }
        if (stepByStep) printOut(argv[2]);
    }
    fclose(teleprinter);
    printOut(argv[2]);
}