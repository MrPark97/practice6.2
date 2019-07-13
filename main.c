#include "interpolation.h"

int main(int argc, char* argv[]) {
    FILE *input_file, *output_file;
    char *input_filename, *output_filename;
    int i;
    unsigned int n, k, P;
    double a, b;
    double *f, *x, *coefficients, *ksi;

    if (argc != 3)
        return 1;

    input_filename = argv[1];
    output_filename = argv[2];

    if ((output_file = fopen(output_filename, "w")) == NULL)
    {
        return 2;
    }

    if ((input_file = fopen(input_filename, "r")) == NULL)
    {
        return 3;
    }

    if (fscanf(input_file, "%d%d", &P, &n) != 2)
    {
        fclose(output_file);
        fclose(input_file);
        return 4;
    }

    if (P != 0)
    {
        fclose(output_file);
        fclose(input_file);
        return 5;
    }

    x = (double *) malloc(n * sizeof(double));
    f = (double *) malloc(n * sizeof(double));
    ksi = (double *) malloc((n+1) * sizeof(double));
    coefficients = (double *) malloc(3 * n * sizeof(double));

    for (i = 0; i < n; i++)
    {
        if (fscanf(input_file, "%lf%lf", &x[i], &f[i]) != 2)
        {
            fclose(output_file);
            fclose(input_file);
            return 4;
        }
    }

    if (fscanf(input_file, "%lf%lf%d", &a, &b, &k) != 3)
    {
        fclose(output_file);
        fclose(input_file);
        return 4;
    }
    fprintf(output_file, "%d\n", n);
    build_approximation_function(n, x, f, coefficients, ksi);

    for (i = 0; i < n; i++)
    {

        fprintf(output_file, "%lf %lf %lf\n", coefficients[i*3 + 0], coefficients[i*3 + 1], coefficients[i*3 + 2]);
    }

    /*for (i = 0; i < n; i++)
    {
        printf("%lf %lf %lf\n", x[i], sin(x[i]), coefficients[i * 3 + 0] + coefficients[i * 3 + 1] * (x[i] - ksi[i]) + coefficients[i * 3 + 2] * (x[i] - ksi[i]) * (x[i] - ksi[i]));
    }*/


    visualize_approximation_function(a, b, k, f, n, x, ksi, coefficients, calculate_approximation_function);

    free(x);
    free(f);
    fclose(output_file);
    fclose(input_file);
    return 0;
}