/**
 * @file stats.c
 * @author Billy Labelle, Atlans embedded
 * @date July, 2015
 * @brief This library contains various utility functions to analyse data through statistics
 *
 * @note It should be noted that this library is row major. Matrix must be organized
 * such that the row elements are contiguous in memory.
 * Ex: a 3x4 matrix should be:
 * 1234
 * 5678
 * 9012
 *
 * References:
 * 	
 * 		Normally distributed random numbers: Developpez.com
 * 		http://www.developpez.net/forums/d544518/c-cpp/c/equivalent-randn-matlab-c/
 * 
 **/

#include "stats.h"

 /**
 * void stat_mean(double *a, double *mean, int dim_i, int dim_j)
 * @brief Function to compute the mean of a matrix
 * @param double *a , the matrix
 * @param double *mean (out), the vector that will contain the mean of each column of A
 * @param int dim_i, the number of rows in the matrix
 * @param int dim_j, the number of colomns in the matrix
 */
void stat_mean(double *a, double *mean, int dim_i, int dim_j)
{
	int i = 0, j = 0, n = 0;

	/*initialize the mean vector */
	for (j = 0; j < dim_j; j++) {
		mean[j] = 0;
	}

	/*Sum of each column */
	for (i = 0; i < dim_i; i++) {
		n = i * dim_j;
		for (j = 0; j < dim_j; j++) {
			mean[j] += a[j + n];
		}
	}

	/*Divide to get average */
	for (j = 0; j < dim_j; j++) {
		mean[j] /= dim_i;
	}
}

/**
 * void stat_mean(double *a, double *mean, int dim_i, int dim_j)
 * @brief Function to compute the std deviation vector of a matrix
 * @param double *A , the matrix
 * @param double *mean , the mean vector
 * @param double *std (out), the std vector
 * @param int dim_i, the number of rows in the matrix
 * @param int dim_j, the number of colomns in the matrix
 */
void stat_std(double *a, double *mean, double *std, int dim_i, int dim_j)
{
	int i = 0, j = 0, n = 0;

	/*initialize the std vector */
	for (j = 0; j < dim_j; j++) {
		std[j] = 0;
	}

	/*Sum of each column */
	for (i = 0; i < dim_i; i++) {
		n = i * dim_j;
		for (j = 0; j < dim_j; j++) {
			std[j] += (a[j + n] - mean[j]) * (a[j + n] - mean[j]);
		}
	}

	/*Divide to get average */
	for (j = 0; j < dim_j; j++) {
		std[j] /= (double)(dim_i - 1);
		std[j] = sqrt(std[j]);
	}
}

 /**void remove_mean_col(double *b, double *a, double *mean, int dim_i, int dim_j)
 * @brief Function to remove the mean from every value depending of their columns
 * @param double *a , the matrix contraining the original elements
 * @param double *mean, the matrix containing the mean of the columns of *a
 * @param double *b , the resulting matrix
 * @param int dim_i, the number of rows in the matrix
 * @param int dim_j, the number of colomns in the matrix
 **/
void remove_mean_col(double *a, double *mean, double *b, int dim_i, int dim_j)
{

	int i, j;
	for (i = 0; i < dim_i; i++) {
		for (j = 0; j < dim_j; j++) {
			/*Substraction of the mean of the column from the value */
			b[i * dim_j + j] = a[i * dim_j + j] - mean[j];
		}
	}
}

/**
 * void modify_mean_stdev(double *mtx,double new_mean,double new_stddev, int dim_i, int dim_j)
 * @brief Utility function to modify a matrix to obtain values with a predefined mean 
 * and standard deviation
 * @param mtx, IxJ double array, the matrix containing the values
 * @param new_mean, the mean of the column aimed for the matrix
 * @param new_stddev, the standard deviation aimed for the column of the matrix
 * @param dim_i, the value of I.
 * @param dim_j, the value of J.
 */
void modify_mean_stddev(double *mtx, double new_mean, double new_stddev, int dim_i, int dim_j)
{
	int i, j;
	for (i = 0; i < dim_i; i++) {
		for (j = 0; j < dim_j; j++) {
			mtx[i * dim_i + j] = (mtx[i * dim_j + j] * new_stddev) + new_mean;
		}
	}
}

/**
 * double randn()
 * @brief Utility function to generate a normally distributed number
 */
double randn()
{
	double Twopi = (6.2831853071795864769252867665590057683943387987502);	/* 2 * pi */
	double randmax = RAND_MAX;
	double random = rand();
	double randnorm;

	/*Calculates a normally distributed random number */
	random /= randmax;
	randnorm = (sqrt(-2.0 * log(random)));
	randnorm *= cos(Twopi * random);
	return randnorm;
}

/**
 * void randn_mtx(double *mtx, int dim_i, int dim_j)
 * @brief Utility function to generate a matrix containing normally 
 * distributed numbers
 * @param mtx, IxJ double array, the matrix containing the normally
 * distributed numbers
 * @param dim_i, the value of I.
 * @param dim_j, the value of J.
 */
void randn_mtx(double *mtx, int dim_i, int dim_j)
{
	int i, j;
	for (i = 0; i < dim_i; i++) {
		for (j = 0; j < dim_j; j++) {
			/*Generates a matrix of normally distributed random number */
			mtx[i * dim_j + j] = randn();
		}
	}
}

/**
 * void show_matrix(double *A, int dim_i, int dim_j)
 * @brief Utility function to show the matrix in the command window
 * @param A, IxJ double array, the matrix to be displayed
 * @param dim_i, the value of I.
 * @param dim_j, the value of J.
 */
void show_matrix(double *A, int dim_i, int dim_j)
{
	int i, j;

	/*Displays every element of the matrix */
	for (i = 0; i < dim_i; i++) {
		for (j = 0; j < dim_j; j++)
			printf("%2.5f ", A[i * dim_j + j]);
		printf("\n");
	}
}
