#include "fp_analyzer.h"

FP_TYPE power_of_2(INT_TYPE exponent) {
    FP_TYPE result = 1.0;
    if (exponent >= 0) {
        for (int i = 0; i < exponent; i++) {
	    result *= 2;
	}
    } else {
        for (int i = 0; i < (-1 * exponent); i++) {
	    result /= 2;
	}
    }
    return result;
}

void print_bits(INT_TYPE input, size_t size) {
    unsigned INT_TYPE mask = ONE << (size - 1);
    while (mask) {
        putchar((mask & input) != 0 ? '1' : '0');
	mask >>= 1;
    }
    putchar('\n');
}

void print_components(Converter c) {
    if (c.f == -NAN) {
        printf("%"INPUT_FORMAT"\n", NAN);
    } else {
        printf("%"INPUT_FORMAT"\n", c.f);
    }
    printf("All bits: ");
    print_bits(c.u, FP_SIZE);
    printf("Sign: ");
    print_bits(c.components.sign, SIGN_SIZE);
    printf("Exponent: ");
    print_bits(c.components.exponent, EXPONENT_SIZE);
    printf("Mantissa: ");
    print_bits(c.components.mantissa, MANTISSA_SIZE);
}

void print_normalized(Converter c) {
    INT_TYPE sign = c.components.sign; 
    INT_TYPE exponent = c.components.exponent - BIAS;
    INT_TYPE shift = power_of_2(exponent);
    FP_TYPE mantissa = c.components.mantissa * power_of_2((INT_TYPE)MANTISSA_SIZE * -1) + 1;
    printf("Original value:\n");
    printf("(-1)^{" OUTPUT_FORMAT "} x (1 + %" INPUT_FORMAT ") ", sign, (mantissa - 1));
    printf("x 2^{" OUTPUT_FORMAT " - %d}\n", exponent + BIAS, BIAS);
    if (sign) {
        printf("  = -1 x %" INPUT_FORMAT " x 2^{" OUTPUT_FORMAT "}\n", mantissa, exponent);
	if (c.f == -1.0) {
	    printf("  = -1 x %" INPUT_FORMAT " x " OUTPUT_FORMAT"\n", mantissa, shift);
	} else {
	    printf("  = -1 x %" INPUT_FORMAT " x " OUTPUT_FORMAT"\n", mantissa, shift);
	}
	printf("  = %.45"INPUT_FORMAT"\n", mantissa * shift * -1);
    } else {
        printf("  = 1 x %" INPUT_FORMAT " x 2^{" OUTPUT_FORMAT "}\n", mantissa, exponent);
	if (c.f == 1.0) {
	    printf("  = %" INPUT_FORMAT " x " OUTPUT_FORMAT"\n", mantissa, shift);
	} else {
	    printf("  = 1 x %" INPUT_FORMAT " x " OUTPUT_FORMAT"\n", mantissa, shift);
	}
	printf("  = %.45"INPUT_FORMAT"\n", mantissa * shift);
    }
}

void print_denormalized(Converter c) {
    INT_TYPE sign = c.components.sign;
    INT_TYPE shift = power_of_2(1 - BIAS);
    FP_TYPE mantissa = c.components.mantissa * power_of_2((INT_TYPE)MANTISSA_SIZE * -1);
    if (c.f == 0.0 || c.f == -0.0) {
        printf("Original value: %.1"INPUT_FORMAT"\n", c.f);
    } else {
        printf("Original value:\n");
        printf("(-1)^{" OUTPUT_FORMAT "} x %.45" INPUT_FORMAT " ", sign, mantissa);
        printf("x 2^{1 - %d}\n", BIAS);
        if (sign) {
            printf("  = -1 x %" INPUT_FORMAT " x 2^{%d}\n", mantissa, 1 - BIAS);
	    printf("  = -1 x %" INPUT_FORMAT " x " OUTPUT_FORMAT"\n", mantissa, shift);
	    printf("  = %.45"INPUT_FORMAT"\n", mantissa * shift * -1);
        } else {
            printf("  = 1 x %" INPUT_FORMAT " x 2^{%d}\n", mantissa, 1- BIAS);
	    printf("  = 1 x %" INPUT_FORMAT " x " OUTPUT_FORMAT "\n", mantissa, shift);
	    printf("  = %.45"INPUT_FORMAT"\n", mantissa * shift);
        }
    }
}

void print_reconstitution(Converter c) {
    if (fabs(c.f) == 0.0) {
        print_denormalized(c);
    } else {
        print_normalized(c);
    }
}
