#include <stdio.h>
#include <gsl/gsl_sf_gamma.h>

int main (void)
{
    double a = 20;
    double b = 1000;
    double x = 0.5;
    double result = gsl_sf_beta_inc(a, b, x);
    printf("%f\n", result);
    return 0;
}
