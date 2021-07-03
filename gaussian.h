/*
 *  (c) 2021 Murata Mitsuharu
 *  Licensed under the MIT License.
 */


#ifndef GAUSSIAN_H
#define GAUSSIAN_H

double* correlate1d(double* input, long input_size, double* weights, long weights_size);
void printd(double d[], long size);
double* dreflect(double *v, long n, long len);
double* dreverse(double v[], long size);
double* gaussian_kernel(double sd, long n);
double* gaussian_filter1d(double* v, long size, double sd);

#endif
