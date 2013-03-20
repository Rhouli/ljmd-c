/**
 * Helper class
 *
 * @short This class provides a variety of helper functions
 * @authors Ryan Houlihan <ryan.houliha90@gmail.com>
 */

#ifndef MD_HELPER_H
#define MD_HELPER_H

/**
 * read a line and then return
 *  the first string with whitespace stripped off
 * @param Pointer to a FILE
 * @param Pointer to a char buffer
 * @return void
 */
static int get_a_line(FILE *fp, char *buf);

/**
 * Zero out an array
 * @param Pointer to an array
 * @param size of an array
 * @return void
 */
__attribute__((always_inline))
static void azzero(double *d, const int n);

/**
 * Apply minimum image convention
 * @param Double value
 * @param double matrix of box X 2
 * @param double value of box
 * @return The modified double which was given as the first parameter
 */
__attribute__((always_inline,pure))
static double pbc(double x, const double boxby2, const double box);

#endif //> !class

