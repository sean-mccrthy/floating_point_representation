#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DOUBLE
#define FP_TYPE double
#define INT_TYPE long
#define INPUT_FORMAT "lf"
#define OUTPUT_FORMAT "%ld"
#define EXPONENT_SIZE 11
#define ONE 1ul
#define BIAS 1023
#else
#define FP_TYPE float
#define INT_TYPE int
#define INPUT_FORMAT "f"
#define OUTPUT_FORMAT "%d"
#define EXPONENT_SIZE 8
#define ONE 1u 
#define BIAS 127
#endif
#define BITS_PER_BYTE 8
#define FP_SIZE (sizeof(FP_TYPE) * BITS_PER_BYTE)
#define SIGN_SIZE 1
#define MANTISSA_SIZE (FP_SIZE - EXPONENT_SIZE - SIGN_SIZE)

typedef struct Components {
    unsigned INT_TYPE mantissa : MANTISSA_SIZE;
    unsigned INT_TYPE exponent : EXPONENT_SIZE;
    unsigned INT_TYPE sign : SIGN_SIZE;
} Components;

typedef union Converter {
    FP_TYPE f;
    unsigned INT_TYPE u;
    Components components;
} Converter;

FP_TYPE power_of_2(INT_TYPE exponent);

void print_bits(INT_TYPE input, size_t size);

void print_components(Converter c);

void print_normalized(Converter c);

void print_denormalized(Converter c);

void print_reconstitution(Converter c);
