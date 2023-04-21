/**
 * File: correlation_coefficient.c
 *
 * Implementation of correlation coefficient and helpful functions.
 */

#include <math.h>

#include "correlation_coefficient.h"

double corrcoef(int n, int x[], int y[]) {

    int sum_x = 0;
    int sum_y = 0;
    int sum_xy = 0;
    int squareSum_x = 0;
    int squareSum_y = 0;
    
    // calculate sums
    for (int i = 0; i < n; i++)
    {
        sum_x = sum_x + x[i];
        sum_y = sum_y + y[i];
        sum_xy = sum_xy + x[i] * y[i];
        squareSum_x = squareSum_x + x[i] * x[i];
        squareSum_y = squareSum_y + y[i] * y[i];
    }
 
    // calculate correlation
    double correlation = (double)(n * sum_xy - sum_x * sum_y) 
        / sqrt((n * squareSum_x - sum_x * sum_x)
        * (n * squareSum_y - sum_y * sum_y));
 
    return correlation;
}

int hw(uint8_t val)
{
  return ((0x876543210 >>
    (((0x4332322132212110 >> ((val & 0xF) << 2)) & 0xF) << 2)) >>
    ((0x4332322132212110 >> (((val & 0xF0) >> 2)) & 0xF) << 2))
    & 0xf;
}