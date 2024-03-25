#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "log2_lshift16.h"
#include "log2fix.h"


#define PRECISION 16
#define XEEOF -1
#define SAMPLES 1000

int main()
{
    FILE *file = fopen("log2.csv", "w");
    double scale_16 = 1U << PRECISION;
    double scale1_8 = 1U << PRECISION / 2;
    double scale1_4 = 1U << PRECISION / 4;
    double scale1_2 = 1U << PRECISION / 8;

    if (file == NULL) {
        printf("fail to open\n");
        return 1;
    }

    for (int i = 100; i <= SAMPLES; i = i + 5) {
        fprintf(file, "%d %f %f %f %f %f\n", i, log2(i),
                log2fix(i * scale_16, 16) / scale_16,
                log2fix(i * scale1_8, 8) / scale1_8,
                log2fix(i * scale1_4, 4) / scale1_4,
                log2fix(i * scale1_2, 2) / scale1_2);
    }
    fclose(file);

    return 0;
}