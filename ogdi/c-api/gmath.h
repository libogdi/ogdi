/* GMATUTIL.H - Header file for GMATUTIL.C

   Include this file when using matrix routines
*/

#include <stdio.h>     /* for FILE structure */

/* Use these for sending to matrix multiplication routines */
#define AA   0        /* A * A */
#define ATA  1        /* AT * A    Where: AT = transpose(A) */
#define AAT  2        /* A * AT */

#define DEF_FMT " %9.2le"      /* Useful format for mat-print */



/* function prototypes */
void copy_dmatrix( double **dest, double *src, int rows, int cols );
void clear_matrix( void **mat, int rows, int cols, int size );
void clear_dmatrix( double **mat, int rows, int cols );
void clear_vector( void *vec, int num, int size );
void print_dmatrix(double **mat,int n,int m,FILE *ffout,char *form,char *title );
void print_dvector(double *vec,int n,FILE *ffout,char *form,char *title );
int mult_dmatrix( double **a_mat, int arow, int acol,
			double **b_mat, int brow, int bcol,
			double **c_mat, int op );
int mult_dmatvec( double **a_mat, int arow, int acol,
			    double *b_vect, int brow, double *c_vect );
int invert_error( int num );
int invert_dmatrix( double **mat, int n);
void **alloc_matrix( int rows, int cols, int size );
double **alloc_dmatrix( int rows, int cols );

float **alloc_matrix_float( int rows, int cols );
void free_matrix_float( float **m, int rows );

void free_matrix( void **m, int rows );
void free_dmatrix( double **m, int rows );
void *alloc_vector( int num, int size );
void free_vector( void *v );

unsigned char **alloc_matrix_char( int rows, int cols );
unsigned char free_matrix_char( unsigned char **m, int rows );
unsigned char *alloc_vector_char( int num, int size );
unsigned char free_vector_char( unsigned char *v );
unsigned int *alloc_vector_int( int num, int size );
unsigned int free_vector_int( unsigned int *v );
