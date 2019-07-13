//
// Created by MrPark on 10.07.2019.
//

#include "interpolation.h"

const double DBL_EPSILON = 2.2204460492503131e-016;

void build_approximation_function(unsigned int n, double *x, double *f, double *coefficients, double *ksi)
{


    int i, j, k;
    double first_elem, first_coeff, cur_sum;
    double *v = (double *) malloc((n+1) * sizeof(double));
    double *A = (double *) calloc((n+1)*(n+1), sizeof(double));
    double *B = (double *) malloc((n+1) * sizeof(double));

    for (i = 1; i < n; i++)
    {
        ksi[i] = (x[i-1] + x[i]) / 2.0;
    }
    ksi[0] = x[0] - (ksi[1] - x[0]);
    ksi[n] = x[n-1] + (x[n-1] - ksi[n-1]);

    A[0] = 1.0/(ksi[1]-ksi[0])/(x[0]-ksi[0]);
    A[1] = 1.0/(ksi[1]-ksi[0])/(ksi[1]-x[0])-1.0/(ksi[2]-ksi[1])/(x[1]-ksi[1]);
    A[2] = -1.0/(ksi[2]-ksi[1])/(ksi[2]-x[1]);
    B[0] = (1.0/(ksi[1]-ksi[0])/(ksi[1]-x[0]) + 1.0/(ksi[1]-ksi[0])/(x[0]-ksi[0]))*f[0]-(1.0/(ksi[2]-ksi[1])/(ksi[2]-x[1]) + 1.0/(ksi[2]-ksi[1])/(x[1]-ksi[1]))*f[1];

    A[(n+1)*n + n-2] = 1.0/(ksi[n-1]-ksi[n-2])/(x[n-2]-ksi[n-2]);
    A[(n+1)*n + n-1] = 1.0/(ksi[n-1]-ksi[n-2])/(ksi[n-1]-x[n-2])-1.0/(ksi[n]-ksi[n-1])/(x[n-1]-ksi[n-1]);
    A[(n+1)*n + n] = -1.0/(ksi[n]-ksi[n-1])/(ksi[n]-x[n-1]);
    B[n] = (1.0/(ksi[n-1]-ksi[n-2])/(ksi[n-1]-x[n-2]) + 1.0/(ksi[n-1]-ksi[n-2])/(x[n-2]-ksi[n-2]))*f[n-2]-(1.0/(ksi[n]-ksi[n-1])/(ksi[n]-x[n-1]) + 1.0/(ksi[n]-ksi[n-1])/(x[n-1]-ksi[n-1]))*f[n-1];

    for (i = 1; i < n; i++)
    {
        A[(n+1)*i + i - 1] = 1.0 / (x[i-1]-ksi[i-1]) - 1.0 / (ksi[i] - ksi[i-1]);
        A[(n+1)*i + i] = 1.0 / (ksi[i]-x[i-1]) + 1.0 / (ksi[i] - ksi[i-1]) + 1.0 / (x[i]-ksi[i]) + 1.0 / (ksi[i+1] - ksi[i]);
        A[(n+1)*i + i+1] = 1.0 / (ksi[i+1] - x[i]) - 1.0 / (ksi[i+1] - ksi[i]);
        B[i] = (1.0 / (x[i-1] - ksi[i-1]) + 1.0 / (ksi[i] - x[i-1])) * f[i-1] + (1.0 / (x[i] - ksi[i]) + 1.0 / (ksi[i+1] - x[i])) * f[i];
    }

    // forward elimination
    for (k = 0; k <= n; k++)
    {
        first_elem = A[k*(n+1) + k];

        for (i = k; i <= n; i++)
            A[k*(n+1) + i] /= first_elem;
        B[k] /= first_elem;

        for (i = k+1; i <= n; i++)
        {
            first_coeff = A[i*(n+1) + k];
            for (j = k; j <= n; j++)
            {
                A[i*(n+1) + j] -= first_coeff * A[k * (n+1) + j];
            }
            B[i] -= first_coeff * B[k];
        }
    }

    // back substitution
    for (i = n; i >= 0; i--)
    {
        cur_sum = 0.0;
        for (j = i + 1; j <= n; j++)
        {
            cur_sum += A[i*(n+1) + j] * v[j];
        }
        v[i] = (B[i] - cur_sum) / A[i*(n+1) + i];

    }

    for (i = 0; i < n; i++)
    {
        coefficients[i*3 + 0] = v[i];
        coefficients[i*3 + 1] = (f[i] - v[i]) / (x[i] - ksi[i]) - (x[i] - ksi[i]) / (ksi[i+1] - ksi[i]) * ((v[i+1]-f[i])/(ksi[i+1]-x[i]) - (f[i]-v[i])/(x[i]-ksi[i]));
        coefficients[i*3 + 2] = 1.0 / (ksi[i+1] - ksi[i]) * ((v[i+1] - f[i]) / (ksi[i+1] - x[i]) - (f[i] - v[i]) / (x[i] - ksi[i]));
    }

    free(v);
    free(A);
    free(B);
}