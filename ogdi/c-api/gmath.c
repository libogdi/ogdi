/******************************************************************************
 *
 * Component: OGDI Core C API
 * Purpose: Double precision matrix inverse, allocation, multiplication,
 *          and print routines.
 * 
 ******************************************************************************
 * Derived from Numerical methods in C.
 *
 * Copyright (C) 1995 Logiciels et Applications Scientifiques (L.A.S.) Inc
 * Permission to use, copy, modify and distribute this software and
 * its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies, that
 * both the copyright notice and this permission notice appear in
 * supporting documentation, and that the name of L.A.S. Inc not be used 
 * in advertising or publicity pertaining to distribution of the software 
 * without specific, written prior permission. L.A.S. Inc. makes no
 * representations about the suitability of this software for any purpose.
 * It is provided "as is" without express or implied warranty.
 ******************************************************************************
 *
 * $Log$
 * Revision 1.2  2001-04-09 15:04:34  warmerda
 * applied new source headers
 *
 */

/* ------------------------------------------------------------------ */

#include "ecs.h"
#include "gmath.h"   /* include this header in your code too */

ECS_CVSID("$Id$");

/* set stack to a large value (turbo c only)*/

#ifdef __TURBOC__
extern unsigned _stklen = 20000;
#endif

/* ------------------------------------------------------------------ */
/*
   GMATUTIL.C

   Double precision matrix inverse, allocation, multiplication,
   and print routines.

   These use double pointers, matricies sent to these
   routines must be allocated with alloc_matrix

   Derived from Numerical methods in C

   When using these routines, you must allocate your matricies
   with alloc_matrix (double pointers).

   Example:

      mat=alloc_matrix( rows, cols, sizeof(double));

      (this routine will exit on error)

      Using,
      double mat[50][50];
      is not the same because this method uses single pointers not
      double pointers.

      Individual elements can be access just like regular arrays
      eg: mat[3][4] = 3.0;

      Modifications by Christian Larouche: June 1994.
*/

/*******************************************************************
   SUBROUTINE: COPY_MATRIX - Copies a matrix from a static double
                             Dimension array to a double pointer
                             array allocated with alloc_matrix().

   Static arrarys are allocated as follows:
       double matrix[20][20];
   Double pointer arrays are allocated as follows;
       double **matrix;

       matrix = alloc_matrix( cols,rows,sizeof(double) );

   warning: this routine will only work if rows and cols are the
   same as the dimensioned values if src
*/

void copy_dmatrix( dest, src, rows, cols )
     double **dest;
     double *src; 
     int rows; 
     int cols;
{
  int i,j;
  
  for( i=0; i<rows; ++i )
    for( j=0; j<cols; ++j )
      dest[i][j] = *(src + i*cols + j );
}



/**************************************************************************
    SUBROUTINE: CLEAR_MATRIX - fills a matrix with zeros

			 INPUT: mat - matrix
				   rows - rows
				   cols - cols
                       size - size of each element (use sizeof)

**************************************************************************/

void clear_matrix( mat, rows, cols, size )
     void **mat;
     int rows; 
     int cols; 
     int size;
{
  unsigned int i,len;
  
  len = cols * size;
  
  for( i=0; (int) i<rows; ++i )
    memset( (void *) mat[i], 0, len );
}



/**************************************************************************
    SUBROUTINE: CLEAR_DMATRIX - fills a double precision matrix with zeros

			 INPUT: mat - matrix
				   rows - rows
				   cols - cols
                       size - size of each element (use sizeof)

**************************************************************************/

void clear_dmatrix(mat, rows, cols) 
     double **mat;
     int rows; 
     int cols;
{
  unsigned int i,len;
  
  len = cols * sizeof(double);
  
  for( i=0; (int) i<rows; ++i )
    memset( (void *) mat[i], 0, len );
}



/**************************************************************************
    SUBROUTINE: CLEAR_VECTOR - Fills a vector with zeros

			 INPUT: vec - vector
				   num - number of elements
                       size - size of each element (use sizeof)

**************************************************************************/

void clear_vector( vec,num,size )
     void *vec;
     int num; 
     int size;
{
  memset( vec, 0, size*num );
}


/**************************************************************************

   PRINT_DMATRIX SUBROUTINE (DOUBLE ONLY) - OUTPUTS MATRIX TO A FILE
	INPUT:    mat    - dimension n,m
	          n      - number of rows
			m      - number of columns
			ffout  - file pointer (use stdout for screen)
			form   - format (const char string)
			         eg.  " %10.3lf"
				    if you are not sure use DEF_FMT
			title  - character string

**************************************************************************/

void print_dmatrix(mat,n,m,ffout,form,title)
     double **mat;
     int n;
     int m;
     FILE *ffout;
     char *form;
     char *title;
{
  int i,j;
  
  fprintf(ffout,"\n          %s\n\n",title);
  
  for( i=0; i<n; i++)
    {
      for( j=0; j<m; j++)
	fprintf(ffout,form, mat[i][j] );
      
      fprintf(ffout,"\n");
    }
  
  fprintf(ffout,"\n");
}



/**************************************************************************

   PRINT_DVECTOR SUBROUTINE (DOUBLE ONLY) - OUTPUTS VECTOR TO A FILE
	INPUT:    vec    - dimension n
	          n      - number of rows
			ffout  - file pointer (use stdout for screen)
			form   - format (const char string)
			         eg.  " %10.3lf"
				    if you are not sure use DEF_FMT
			title  - character string

**************************************************************************/

void print_dvector(vec,n,ffout,form,title)
     double *vec;
     int n;
     FILE *ffout;
     char *form;
     char *title;
{
  int i;
  
  fprintf(ffout,"\n   %s\n\n",title);
  
  for( i=0; i<n; i++)
    {
      fprintf(ffout,form, vec[i] );
      fprintf(ffout,"\n");
    }
  fprintf(ffout,"\n");
}




/********************************************************************

  SUBROUTINE: MULT_DMATRIX - Multiplies two matrices together

		    INPUT: a_mat - first matrix
				 arows - number of rows in a
				 acols - number of columns in a
				 b_mat - seconds matrix
				 brows - number of rows in b
				 bcols - number of rows in b
				 c_mat - result matrix (must be dimentioned properly)
				 op - Operations
					 AA - a_mat * b_mat
					 ATA - a_matT * b_mat
					 AAT - a_mat * b_matT

********************************************************************/


int mult_dmatrix( a_mat, arow, acol, b_mat, brow, bcol, c_mat, op)
     double **a_mat; 
     int arow; 
     int acol;
     double **b_mat; 
     int brow; 
     int bcol;
     double **c_mat; 
     int op;     
{
  int i,j,k;
  
  switch( op )
    {
    case AA:
      if( acol != brow )
	{
	  return FALSE;
	}
      
      clear_dmatrix( c_mat, arow, bcol );

      for( i=0; i<arow; ++i )
	{
	  for( j=0; j<bcol; ++j )
	    {
	      for( k=0; k<acol; ++k )
		c_mat[i][j] += a_mat[i][k] * b_mat[k][j];
	    }
	}
      
      break;
      
    case ATA:
      if( arow != brow )
	{
	  return FALSE;
	}
      
      clear_dmatrix( c_mat, acol, bcol );
      
      for( i=0; i<acol; ++i )
	{
	  for( j=0; j<bcol; ++j )
	    {
	      for( k=0; k<arow; ++k )
		c_mat[i][j] += a_mat[k][i] * b_mat[k][j];
	    }
	}
      
      break;
      
    case AAT:
      if( acol != bcol )
	{
	  return FALSE;
	}
      
      clear_dmatrix( c_mat, arow, brow );
      
      for( i=0; i<arow; ++i )
	{
	  for( j=0; j<brow; ++j )
	    {
	      for( k=0; k<acol; ++k )
		c_mat[i][j] += a_mat[i][k] * b_mat[j][k];
	    }
	}
      
      break;

    default:
      return FALSE;
    }
  
  return TRUE;
}


/********************************************************************

  SUBROUTINE: MULT_DMATVEC - Multiplies a matrix by a vector

		    INPUT: a_mat - first matrix
				 arows - number of rows in a
				 acols - number of columns in a
				 b_vect - second vector
				 brows - number of rows in b (same as acols)
				 c_vect - result vector (must be dimenstioned arows)

********************************************************************/

int mult_dmatvec(a_mat, arow, acol, b_vect, brow, c_vect) 
     double **a_mat; 
     int arow; 
     int acol;
     double *b_vect; 
     int brow; 
     double *c_vect;
{
  int i,j;

  if( acol != brow )
    {
      return FALSE;
    }
  
  memset( (void *)c_vect, 0, (unsigned int) sizeof(double) * arow );
  
  for( i=0; i<arow; ++i )
    {
      for( j=0; j<acol; ++j )
	c_vect[i] += a_mat[i][j] * b_vect[j];
    }
  
  return TRUE;
}


/*********************************************************************
  SUBROUTINE: INVERT_ERROR - Prints the error message of the
  following invert_dmatrix routine
  
  INPUT: error number
  */

int invert_error( num )
     int num;
{
  switch( num )
    {
    case 0:
      return TRUE;
      
    case 1:
      return FALSE;
      
    case 2:
      return FALSE;

    case 3:
      return FALSE;
      
    case 4:
      return FALSE;
      
    default:
      return FALSE;
    }
  
  return TRUE;
}


/* *******************************************************************

     SUBROUTINE: INVERT_DMATRIX

	INVERT BY CHOLESKY DECOMP
	RETURNS A DOUBLE POINTER TO INVERTED NORMALS
	NORMALS ARE DESTROYED
        BUT THE WHOLE DAMNED INVERSE IS RETURNED...

	RETURNS DIAGONAL ON WHICH SIGULARITY OCCURRED OR ZERO
	IF SUCCESSFULL

	N IS THE SIZE OF THE SQUARE MATRIX IF THE OFFSET WERE 1
	INSTEAD OF ZERO  I.E. THE SIZE YOU WOULD DIMENSION IF FORTRAN

     this inversion requires less memory than the above one, but
     it is slightly slower (~1.5 times as slow)

     RETURN:   0 - success
             else one of the follwing errors will be printed - then exit
               1 - matrix not positive definite
               2 - Singularity
               3 - Can't sqrt a neg. number
               4 - Can't divide by zero


*********************************************************************** */

int invert_dmatrix(mat,n) 
     double **mat; 
     int n;
{
  int i, j, k;
  
  if( !n )  return(0);
  
  /* Check for Positive definiteness */
  for( i = 0; i < n; i++)
    {
      if( mat[i][i] < 0.0)               invert_error(1);
      if( fabs(mat[i][i]) < 1.0e-12 )    invert_error(2);
    }
  
  /* Perform Choleski decomposition */
  for( j = 0; j < n; j++)
    {
      for( k = 0; k < j; k++)
	mat[j][j] -= mat[j][k]*mat[j][k];
      
      if( mat[j][j] < 0.0 )         invert_error(3);
      mat[j][j] = sqrt(mat[j][j]);
      
      for( i = j+1; i < n; i++)
	{
	  for( k = 0; k < j; k++)
	    mat[i][j] -= mat[i][k]*mat[j][k];
	  
	  if( fabs( mat[j][j] ) < 1.0e-12 )  invert_error(4);
	  mat[i][j] /= mat[j][j];
	}
    }
  
  /* Inversion of lower trianglar matrix */
   for( j = 0; j < n; j++)
     {
       mat[j][j] = 1.0/mat[j][j];
       
       for( i = j + 1; i < n; i++)
	 {
	   mat[i][j] = -mat[i][j]*mat[j][j]/mat[i][i];
	   for( k = j + 1; k < i; k++)
	     mat[i][j] -= mat[i][k]*mat[k][j]/mat[i][i];
	 }
     }
  
   /* Construction of lower trianglar inverse matrix */
  for( j = 0; j < n; j++)
    {
      for( i = j; i < n; i++)
	{
	  mat[i][j] = mat[i][i]*mat[i][j];
	  for( k = i + 1; k < n; k++)
	        mat[i][j] += mat[k][i]*mat[k][j];
	}
    }
  
  /* fill upper diagonal */
  for( i = 1; i < n; i++ )
    {
      for( j = 0; j < i; j++ )
	mat[j][i] = mat[i][j];
    }
  
  return(0);
}
/* End Invert*/






/***********************************************************

  ALLOC_MATRIX : ALLOCATES A MATRIX

	    range: rows & cols

	    exits IF NOT ENOUGH MEMORY

  From Numerical Recipes in C

  alloc_matrix first allocates an array of pointers (one for
  each row), then for each row pointer it allocates an array
  of double values (cols).

  size - size of each element (sizeof(double))


************************************************************/


double **alloc_dmatrix( rows, cols )
     int rows; 
     int cols;    
{
  unsigned i,j;
  double **m;
  
  if( !rows || !cols ) {
    return NULL;
  }
  
  m = (double **) malloc((unsigned) rows*sizeof(double *));
  if( m==NULL ) {
    return NULL;
  }

  for ( i=0; (int) i<rows; i++ ) {
    m[i] = (double *) malloc(sizeof(double)*cols);
    
    if( m[i]==NULL ) {
      for(j=0;j<i;j++)
	free(m[j]);
      free(m);
      return NULL;
    }
  }
  
  return m;
}

/***********************************************************

  ALLOC_MATRIX_FLOAT : ALLOCATES A MATRIX OF FLOAT ELEMENTS

	    range: rows & cols

	    exits IF NOT ENOUGH MEMORY

  From Numerical Recipes in C

  alloc_matrix first allocates an array of pointers (one for
  each row), then for each row pointer it allocates an array
  of float values (cols).

  size - size of each element (sizeof(float))

************************************************************/


float **alloc_matrix_float( rows, cols) 
     int rows; 
     int cols;
{
  unsigned i,j;
  float **m;
  
  if( !rows || !cols )
    {
      return NULL;
    }
  
  m = (float **) malloc((unsigned) rows*sizeof(float *));
  if( m==NULL )
    {
      return NULL;
    }
  
  for ( i=0; (int) i<rows; i++ )
    {
      m[i] = (float *) malloc(sizeof(float)*cols);
      
      if( m[i]==NULL )
	{
	  for(j=0;j<i;j++)
	    free(m[j]);
	  free(m);
	  return NULL;
	}
    }
  
  return m;
}



/***********************************************************

  ALLOC_DMATRIX : ALLOCATES A DOUBLE MATRIX

	    range: rows & cols

	    exits IF NOT ENOUGH MEMORY

  From Numerical Recipes in C

  alloc_matrix first allocates an array of pointers (one for
  each row), then for each row pointer it allocates an array
  of double values (cols).

  size - size of each element (sizeof(double))

************************************************************/


void **alloc_matrix( rows, cols, size )
     int rows; 
     int cols; 
     int size;
{
  unsigned i,j;
  void **m;
  
  if( !rows || !cols || !size )
    {
      return NULL;
    }
  
  m = (void **) malloc((unsigned) rows*sizeof(void *));
  if( m==NULL )
    {
      return NULL;
    }
  
  for ( i=0; (int) i<rows; i++ )
    {
      m[i] = (void *) malloc(size*cols);
      
      if( m[i]==NULL )
	{
	  for(j=0;j<i;j++)
	    free(m[j]);
	  free(m);
	  return NULL;
	}
    }
  
  return m;
}

/************************************************************
  ALLOC_MATRIX_CHAR : ALLOCATES A CHAR MATRIX

	    range: rows & cols

	    exits IF NOT ENOUGH MEMORY

  From Numerical Recipes in C

  alloc_matrix first allocates an array of pointers (one for
  each row), then for each row pointer it allocates an array
  of char values (cols).

  size - size of each element (sizeof(double))

************************************************************/


unsigned char **alloc_matrix_char( rows, cols )
     int rows;
     int cols;
{
  unsigned i,j;
  unsigned char **m;
  
  if( !rows || !cols )
    {
      return NULL;
    }
  
  m = (unsigned char **) malloc((unsigned) rows*sizeof(unsigned char *));
  if( m==NULL )
    {
      return NULL;
    }
  
  for ( i=0; (int) i<rows; i++ )
    {
      m[i] = (unsigned char *) malloc(sizeof(unsigned char)*cols);
      
      if( m[i]==NULL )
      {
	for(j=0;j<i;j++)
	  free(m[j]);
	free(m);
	return NULL;
      }
    }
  
  return m;
}



/******************************************************************

    FREE_MATRIX :  FREES A MATRIX ALLOCATED WITH ALLOC_MATRIX

    From: Numerical Recipes in C

******************************************************************/

void free_matrix(m, rows)
     void **m; int rows;
{
  int i;
  
  for ( i=rows-1; i>=0; i-- )
    free( m[i] );
  
  if( m )
    free( m );
}

/******************************************************************

    FREE_MATRIX_CHAR :  FREES A MATRIX ALLOCATED WITH ALLOC_MATRIX

    From: Numerical Recipes in C

******************************************************************/

unsigned char free_matrix_char(m,rows)
     unsigned char **m;
     int rows;
{
   int i;

   for ( i=rows-1; i>=0; i-- )
	  free( m[i] );

   if( m )    free( m );

   return 0;
}

/******************************************************************

    FREE_DMATRIX :  FREES A DOUBLE MATRIX ALLOCATED WITH ALLOC_MATRIX

    From: Numerical Recipes in C

******************************************************************/

void free_dmatrix( m, rows) 
     double **m; int rows;
{
  int i;
  
  for ( i=rows-1; i>=0; i-- )
    free( m[i] );
  
  if( m )
    free( m );
}

/******************************************************************

    FREE_MATRIX_FLOAT :  FREES A FLOAT MATRIX ALLOCATED WITH
			 ALLOC_MATRIX_FLOAT

    From: Numerical Recipes in C

******************************************************************/

void free_matrix_float( m, rows)
     float **m; 
     int rows;
{
  int i;
  
  for ( i=rows-1; i>=0; i-- )
    free( m[i] );
  
  if( m )    free( m );
}



/******************************************************************
    SUBROUTINE: ALLOC_VECTOR - Allocates a vector

    INPUT:  num - number of elements
	    size - size of each element

    OUTPUT: Pointer to vector
*/

void *alloc_vector(num, size)
     int num;
     int size;
{
  void *v;
  
  if( !num || !size )
    {
      return FALSE;
    }
  
  if( (v=malloc(num*size)) == NULL )
    {
      return FALSE;
    }
  
  return(v);
}


/******************************************************************
    SUBROUTINE: ALLOC_VECTOR_CHAR - Allocates a vector

    INPUT:  num - number of elements
	    size - size of each element

    OUTPUT: Pointer to vector
*/

unsigned char *alloc_vector_char( num, size)
     int num; 
     int size;
{
  unsigned char *v;
  
  if( !num || !size )
    {
      return FALSE;
    }
  
  if( (v=(unsigned char *)malloc(num*size)) == NULL )
    {
      return FALSE;
    }
  
  return(v);
}


/******************************************************************
    SUBROUTINE: ALLOC_VECTOR_INT - Allocates a vector

    INPUT:  num - number of elements
	    size - size of each element

    OUTPUT: Pointer to vector
*/

unsigned int *alloc_vector_int(num, size)
     int num; 
     int size;
{
  unsigned int *v;
  
  if( !num || !size )
    {
      return FALSE;
    }
  
  if( (v=(unsigned int *)malloc(num*size)) == NULL )
    {
      return FALSE;
    }
  
  return(v);
}

/******************************************************************
    SUBROUTINE: FREE_VECTOR - Frees the memory of a vector

    INPUT:  v - pointer to vector
*/

void free_vector(v)
     void *v;
{
  free(v);
}

/******************************************************************
    SUBROUTINE: FREE_VECTOR_CHAR - Frees the memory of a vector

    INPUT:  v - pointer to vector
*/

unsigned char free_vector_char( v )
     unsigned char *v;
{
  free(v);
  return 0;
}

/******************************************************************
    SUBROUTINE: FREE_VECTOR_INT - Frees the memory of a vector

    INPUT:  v - pointer to vector
*/

unsigned int free_vector_int( v )
     unsigned int *v;
{
  free(v);
  return 0;
}

