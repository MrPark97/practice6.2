//
// Created by MrPark on 10.07.2019.
//

#include "interpolation.h"

void calculate_approximation_function(double *coefficients, double a, double b, unsigned int k, int n, double *ksi, double *result)
{
    int i, j, start;
    double cur_x, h = (b - a) / (double) k;

    for (i = 0, cur_x = a; i <= k;  i++)
    {
        start = 0;
        for (j = 0; j < n; j++)
        {
            if (cur_x >= ksi[j])
                start = j;
        }

        result[i] = coefficients[start * 3 + 0] + coefficients[start * 3 + 1] * (cur_x - ksi[start]) + coefficients[start * 3 + 2] * (cur_x - ksi[start]) * (cur_x - ksi[start]);

        cur_x += h;
    }
}