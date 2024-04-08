#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/* This is a sample code that reads a datafile named `data.txt`.
   `data.txt` contains the x and y values for the observation datapoints.
   For example, the velocity of a car in km/hr at different time points.
   We use `data.txt` later on for the analysis.

   This code contains a simple demonstration of:
   > file read using C.
   > Lagrange interpolation.
   > numerical integration using trapezoidal rule.
   

 */

int n; // number of data points
float *xdata, *ydata; // x and y data points
/* function pointer to the interpolation function which takes in a float and returns a float */
typedef float (*func)(float); 

float lagrange(float x) {
    // Lagrange interpolation
    // x: point at which we want to interpolate
    float sum = 0;
    for (int i = 0; i < n; i++) {
        float prod = ydata[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                prod *= (x - xdata[j]) / (xdata[i] - xdata[j]);
            }
        }
        sum += prod;
    }
    return sum;
}

func interp1d(float *x, float *y, int nlines) {
    // prepare the data for interpolation
    // returns a function pointer to the interpolation function
    xdata = x;
    ydata = y;
    n = nlines;
    return lagrange;
}

float trapz(func f, float a, float b, int nzones) {
    // Trapezoidal rule for numerical integration
    // f: function pointer to the function to be integrated
    // a: lower limit of integration
    // b: upper limit of integration
    // nzones: number of zones to divide the integration interval
    float h = (b - a) / nzones;
    float sum = 0;
    for (int i = 0; i < nzones; i++) {
        sum += (f(a + i * h) + f(a + (i + 1) * h)) / 2;
    }
    return h * sum;
}

int main() {
    /* Open the data file to read in the observation values */
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    /* Count number of lines in the data file */
    int nlines = 0;
    while (!feof(file)) {
        char ch = fgetc(file);
        // Count number of newline characters in the file == number of lines
        if (ch == '\n') {
            nlines++;
        }
    }
    if (nlines == 0) {
        // Blank file!
        printf("No data in file\n");
        return 1;
    }
    // Rewind the file pointer to the beginning of the file to read the data
    rewind(file);
    // Dynamically allocate memory for the observation data points
    float *xobs = (float *)malloc(nlines * sizeof(float));
    float *yobs = (float *)malloc(nlines * sizeof(float));

    // Read the data points from the file
    for (int i = 0; i < nlines; i++) {
        fscanf(file, "%f %f", &xobs[i], &yobs[i]);
    }

    // Interpolate the data points
    func f_interp = interp1d(xobs, yobs, nlines);
    
    /*
    // Example usage of the interpolation function:
    for (float x_query = 0; x_query < nlines; x_query+=0.5) {
        printf("f_interp(%.2f) = %.2f\n", x_query, f_interp(x_query));
    }
    */

    // Calculate the distance using numerical integration
    float a = xobs[0];
    float b = xobs[nlines-1];
    // Trapezoidal rule for numerical integration
    float distance = trapz(f_interp, a, b, 1000);
    printf("Distance = %.2f (in arbitrary units)\n", distance);
    // Close the file
    fclose(file);
    // Free the dynamically allocated memory
    free(xobs);
    free(yobs);
    return 0;
}