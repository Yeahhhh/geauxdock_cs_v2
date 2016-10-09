
int
main (int argc, char **argv)
{
    float **a, **b, **c, cc;
    int i, j, k;

    a = alloc_2d_float (SZ, SZ);
    b = alloc_2d_float (SZ, SZ);
    c = alloc_2d_float (SZ, SZ);

    for (i = 0; i < SZ; i++)
        for (j = 0; j < SZ; j++)
            a[i][j] = b[i][j] = rand () * 1.1f;

    launcher (a, b, c);

    for (i = 0; i < SZ; i++)
        for (j = 0; j < SZ; j++)
            cc += c[i][j];
    printf ("cc = %f\n", cc);

    free_2d_float (a);
    free_2d_float (b);
    free_2d_float (c);

    return (0);
}

