#include <stdlib.h>
#include <stdio.h>

#define SZ 500



// allocate a contiguous region of 2D array
float** alloc_2d_float (const int rows, const int cols)
{
    float *data;
    float **a;
    int r;

    data = (float *) malloc (sizeof (float) * rows * cols);
    a = (float **) malloc (sizeof (float *) * rows);

    for (r = 0; r < rows; ++r)
        a[r] = &(data[cols * r]);
    return a;
}


void free_2d_float (float** a)
{
    free (a[0]);
    free (a);
}




static void
mmm (float **a, float **b, float **c)
{
    int i, j, k;
    for (i = 0; i < SZ; i++)
        for (j = 0; j < SZ; j++) {
            c[i][j] = 0.0f;
            for (k = 0; k < SZ; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
}


