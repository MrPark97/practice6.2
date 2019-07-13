#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void build_approximation_function(unsigned int n, double *x, double *f, double *coefficients, double *ksi);
void calculate_approximation_function(double *coefficients, double a, double b, unsigned int k, int n, double *ksi, double *result);
void visualize_approximation_function(double a, double b, unsigned int k, double *f, int n, double *x, double *ksi, double *coefficients,
        void (*function_pointer) (double *coefficients, double a, double b, unsigned int k, int n, double *ksi, double *result));