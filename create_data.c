#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/* This is a sample code that creates a datafile named `data.txt`.
   We use this later on for the analysis.
   This code is a simple demonstration of file write using C.
   Usage:
   Enter the x and y values for the observation datapoint sperated by space.
   Each observation must end with a newline.
   To finish taking data and ending the program enter `-1 -1`.
 */
int main() {
    FILE *fp = fopen("data.txt", "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    printf("Enter data x y\n");
    float x, y;
    while (1) {
        scanf("%f %f", &x, &y);
        if (x == -1 && y == -1) {
            break;
        }
        fprintf(fp, "%f %f\n", x, y);
    }
    fclose(fp); 
    return 0;
}