/**
 * File: correlation_coefficient.h
 *
 * Prototype for correlation coefficient and helpful functions.
 */

#ifndef _CORRELATION_COEFFICIENT_H_
#define _CORRELATION_COEFFICIENT_H_

#include <stdint.h>

/**
 * Calculates correlation coefficient between two arrays.
 * 
 * @param n - length of arrays
 * @param x - first input array
 * @param y - second input array
 * @return correlation coefficient between arrays 
 */
double corrcoef(int n, int x[], int y[]);

/**
 * Calculates hamming weight.
 * 
 * @param val - 8 bit number to determine hamming weight of.
 * @return hamming weight 
 */
int hw(uint8_t val);

#endif // _CORRELATION_COEFFICIENT_H_