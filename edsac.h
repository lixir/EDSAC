#include <stdio.h>

#ifndef EDSAC_H
#define EDSAC_H

unsigned long long Multiplier;

unsigned long long Multiplicand;

unsigned long Accumulator1;

unsigned long long Accumulator2;

unsigned long Memory[1024];

unsigned long Sandwich[512];

unsigned int currentCell;

int currentSymbol;

unsigned long base17;
unsigned long long base35;
unsigned long long base54;

char *input;

int outputShift;

char outputSymbol;

int stepByStep;

unsigned long tempUnLong;
unsigned long long tempUnLongLong;
int tempInt;


void initialOrders1();

void initialOrders2();

void A(unsigned int n, unsigned int longOperation);

void S(unsigned int n, unsigned int longOperation);

void T(unsigned int n, unsigned int longOperation);

void U(unsigned int n, unsigned int longOperation);

void H(unsigned int n, unsigned int longOperation);

void V(unsigned int n, unsigned int longOperation);

void N(unsigned int n, unsigned int longOperation);

void C(unsigned int n, unsigned int longOperation);

void L(unsigned long n);

void R(unsigned long n);

void E(unsigned int n);

void G(unsigned int n);

void I(unsigned int n);

void O(unsigned int n);

void F(unsigned int n);

void Y();

void Z();


#endif
