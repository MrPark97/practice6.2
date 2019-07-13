//
// Created by MrPark on 10.07.2019.
//

#include "interpolation.h"

void visualize_approximation_function(double a, double b, unsigned int k, double *f, int n, double *x, double *ksi, double *coefficients,
                                      void (*function_pointer) (double *coefficients, double a, double b, unsigned int k, int n, double *ksi, double *result))
{
    double *result = (double *) malloc((k+1) * sizeof(double));

    function_pointer(coefficients, a, b, k, n, ksi, result);

    double max_v = result[0], min_v = result[0], abs_max_v = fabs(result[0]), h = (b - a) / (double) k;
    int i, min_k = 0, max_k = 0, abs_max_k = 0;

    for (i = 0; i <= k; i++)
    {
        if (result[i] > max_v)
        {
            max_v = result[i];
            max_k = i;
        }

        if (result[i] < min_v)
        {
            min_v = result[i];
            min_k = i;
        }

        if (fabs(result[i]) > abs_max_v)
        {
            abs_max_v = fabs(result[i]);
            abs_max_k = i;
        }
    }


    FILE *gnuplot = _popen("F:\\installers\\gnuplot\\bin\\gnuplot.exe -persistent", "w");

    fprintf(gnuplot, "set term wxt title \"Parabolic splines interpolation\"\n");
    fprintf(gnuplot, "set title \"Parabolic splines interpolation\"\n");
    fprintf(gnuplot, "show title\n");
    fprintf(gnuplot, "set zeroaxis\n");
    fprintf(gnuplot, "set xlabel \"x\"\n");
    fprintf(gnuplot, "show xlabel\n");
    fprintf(gnuplot, "set ylabel \"y=f(x)\"\n");
    fprintf(gnuplot, "show ylabel\n");
    fflush(gnuplot);

    fprintf(gnuplot, "set xrange[%.1f:%.1f]\n", a - 0.1, b + 0.1);
    fprintf(gnuplot, "set yrange[%.1f:%.1f]\n", min_v - 0.1, max_v + 0.1);

    fprintf(gnuplot, "plot '-' title \"Pf(x)\" with lines,"
                     "'-' title \"f(x)\" with linespoints,"
                     "'-' title \"Min point\" with points,"
                     "'-' title \"Max point\" with points,"
                     "'-' title \"Absolute max point\" with points\n");
    fflush(gnuplot);

    for (i = 0; i <= k; i++)
    {
        fprintf(gnuplot, "%lf %lf\n", a +  i * h, result[i]);
    }

    fflush(gnuplot);
    fprintf(gnuplot, "e\n");

    for(i = 0; i < n; ++i)
    {
        fprintf(gnuplot, "%lf %lf\n", x[i], f[i]);
    }

    fflush(gnuplot);
    fprintf(gnuplot, "e\n");

    fprintf(gnuplot, "%lf %lf\n", a + min_k * h, min_v);

    fflush(gnuplot);
    fprintf(gnuplot, "e\n");

    fprintf(gnuplot, "%lf %lf\n", a + max_k * h, max_v);

    fflush(gnuplot);
    fprintf(gnuplot, "e\n");

    fprintf(gnuplot, "%lf %lf\n", a + abs_max_k * h, abs_max_v);

    fflush(gnuplot);
    fprintf(gnuplot, "e\n");
}

