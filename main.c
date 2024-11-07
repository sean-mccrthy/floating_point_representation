/*
 * Visualizing Floating-Point Representations
 * Author: Sean McCarthy - mccaramv@bc.edu
 */

#include "fp_analyzer.h"

int main(int argc, char * argv[]) {
    if (argc > 1) {
        if (!strcmp(argv[1], "special")) {
	    Converter special;
	    FP_TYPE specials[] = {1.0/0.0, -1.0/0.0, NAN, -NAN};
	    for (int i = 0; i < 4; i++) {
		special.f = specials[i];
                print_components(special);
		printf("\n");
	    }
	    return EXIT_SUCCESS;
	}
    }
    Converter c;
    printf("Please enter a floating-point number or q to quit.\n> ");
    while (scanf("%"INPUT_FORMAT, &c.f)) {
	print_components(c);
	print_reconstitution(c);
	printf("> ");
    }
    return EXIT_SUCCESS;
}

