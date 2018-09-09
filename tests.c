#include <stdio.h>
#include "edsac.h"

/*void print2(unsigned long long number){
    unsigned long long temp = number;
    int temp2;
    char text[54] = {'0'};
    for (int i = 0; i < 54; i++){
        text[i] = '0';
    }
    for (int i = 0; i < 54; i++){
        temp2 = (int) (temp % 2);
        temp >>= 1;
        if (temp2) text[53 - i] = '1';
    }
    for (int i = 0; i < 54; i++){
        printf("%c", text[i]);
    }
    printf("\n");
}*/

void test_A_1(){

}

void test_A_2(){
    Accumulator1 = 0b11111100000000000;
    Accumulator2 =  (unsigned long long) 1 << 53;
    Memory[0] = 0b11111000000000001;
    A(0, 0);
    if (Accumulator1 == 0b11110100000000001 && Accumulator2 == (unsigned long long) 1 << 53)
        printf("test A-2 Complete \n");
    else {
        printf("test A-2 failed \n");
        printf("%lu    %llu \n", Accumulator1, Accumulator2);
    }
}

void test_A_3(){
    Accumulator1 =  0b00100000000000010;
    Accumulator2 = 0;
    Memory[0] = 0b01111111111111110;
    A(0, 0);
    if (Accumulator1 == 0b10100000000000000 &&
        Accumulator2 == 0)
        printf("test A-3 Complete \n");
    else {
        printf("test A-3 failed \n");
        printf("%lu    %llu \n", Accumulator1, Accumulator2);
    }
}


void test_S_1(){
    Accumulator1 = 0b11111100000000000;
    Accumulator2 =  (unsigned long long) 1 << 53;
    Memory[0] = 0b11111000000000001;
//    print2(Accumulator1);
//    print2(Accumulator2);
    S(0, 0);
    if (Accumulator1 == 0b000000011111111111 && Accumulator2 == (unsigned long long) 1 << 53)
        printf("test S_1 Complete \n");
    else {
        printf("test S_1 failed \n");
        printf("%lu    %llu \n", Accumulator1, Accumulator2);
//        print2(Accumulator1);
//        print2(Accumulator2);
    }
}

void test_S_2(){
    Accumulator1 = 0b11111100000000000;
    Accumulator2 =  (unsigned long long) 1 << 53;
    Memory[0] = 0b01111000000000001;
//    print2(Accumulator1);
//    print2(Accumulator2);
    S(0, 0);
    if (Accumulator1 == 0b10000011111111111 && Accumulator2 == (unsigned long long) 1 << 53)
        printf("test S_2 Complete \n");
    else {
        printf("test S_2 failed \n");
        printf("%lu    %llu \n", Accumulator1, Accumulator2);
//        print2(Accumulator1);
//        print2(Accumulator2);
    }
}


void test_V_1(){
    Memory[0] = 0b11111000000000001;
    Memory[1] = 0b01111000000000001;
    Memory[2] = 0b11111000000000001;
    Memory[3] = 0b01100000000000000;
    H(0,1);
    V(2,1);
    if (Accumulator1 == 0b01011010000000001 && Accumulator2 == 28235772203073540)
        printf("test V_1 Complete \n");
    else {
        printf("test V_1 failed \n");
        printf("%lu    %llu \n", Accumulator1, Accumulator2);
    }
}

void test_V_2(){
    Memory[0] = 0b11111000000000001;
    Memory[1] = 0b11111000000000001;
    Memory[2] = 0b11111000000000001;
    Memory[3] = 0b01100000000000000;
    H(0,1);
    V(2,1);
    if (Accumulator1 == 0b11111010000000001 && Accumulator2 == 1495580696084484)
        printf("test V_2 Complete \n");
    else {
        printf("test V_2 failed \n");
        printf("%lu    %llu \n", Accumulator1, Accumulator2);
    }
}

void test_V_3(){
    Memory[0] = 0b11111000000000001;
    Memory[1] = 0b11111000000000001;
    Memory[2] = 0b11111000000000001;
    Memory[3] = 0b11100000000000000;
    H(0,1);
    V(2,1);
    if (Accumulator1 == 0b00000001111111111 && Accumulator2 == 10784186208059396)
        printf("test V_3 Complete \n");
    else {
        printf("test V_3 failed \n");
        printf("%lu    %llu \n", Accumulator1, Accumulator2);
    }
}

void test_N(){
    Memory[0] = 0b11111000000000001;
    Memory[1] = 0b01111000000000001;
    Memory[2] = 0b11111000000000001;
    Memory[3] = 0b01100000000000000;
    H(0,1);
    N(2,1);
    if (Accumulator1 == 0b10100101111111110 && Accumulator2 == 7793024815890428)
        printf("test N Complete \n");
    else {
        printf("test N failed \n");
        printf("%lu    %llu \n", Accumulator1, Accumulator2);
    }
}

void test_C_1(){
    Memory[0] = 0b11111000000000001;
    Memory[1] = 0b01111000000000001;
    Memory[2] = 0b11111000000000001;
    Memory[3] = 0b01100000000000000;
    H(0,1);
    C(2,1);
    if (Accumulator1 == 0b01100000000000000 && Accumulator2 == 8725792997507072)
        printf("test C_1 Complete \n");
    else {
        printf("test C_1 failed \n");
        printf("%lu    %llu \n", Accumulator1, Accumulator2);
    }
}

void test_C_2(){
    Memory[0] = 0b11111111111111111;
    Memory[1] = 0b11111111111111111;
    Memory[2] = 0b11111111111111111;
    Memory[3] = 0b11111111111111111;
    Sandwich[0] = 1;
    Sandwich[1] = 1;
    H(0,1);
    C(2,1);
    if (Accumulator1 == 0b11111111111111111 && Accumulator2 == 9007130535264256)
        printf("test C_2 Complete \n");
    else {
        printf("test C_2 failed \n");
        printf("%lu    %llu \n", Accumulator1, Accumulator2);
    }
}

void test_L(){
    Accumulator1 = 0b11111111111111111;
    Accumulator2 = 9007130535264256;
    L(0b100);
    if (Accumulator1 == 0b11111111111111011 && Accumulator2 == 18013848753668096)
        printf("test L Complete \n");
    else {
        printf("test L failed \n");
        printf("%lu    %llu \n", Accumulator1, Accumulator2);
    }
}

void test_R_1(){
    Accumulator1 = 0b11111111111111111;
    Accumulator2 = 9007130535264256;
    R(0b100);
    if (Accumulator1 == 0b11111111111111111 && Accumulator2 == 16888490012704768)
        printf("test R_1 Complete \n");
    else {
        printf("test R_1 failed \n");
        printf("%lu    %llu \n", Accumulator1, Accumulator2);
    }
}

void test_R_2(){
    Accumulator1 = 0b01111111111111111;
    Accumulator2 = 9007130535264256;
    R(0b100);
    if (Accumulator1 == 0b00001111111111111 && Accumulator2 == 16888490012704768)
        printf("test R_2 Complete \n");
    else {
        printf("test R_2 failed \n");
        printf("%lu    %llu \n", Accumulator1, Accumulator2);
    }
}

void  test_I(){
    input = "WFV";
    I(0);
    I(1);
    I(2);
    I(3);

    if (Memory[0] == 0b00010 && Memory[1] == 0b10001 && Memory[2] == 0b11111 && Memory[3] == 0)
        printf("test I Complete \n");
    else {
        printf("test I failed \n");
        printf("%lu    %llu \n", Accumulator1, Accumulator2);
    }
}