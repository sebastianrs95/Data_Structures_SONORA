#ifndef LINEAR_H_INCLUDED
#define LINEAR_H_INCLUDED

/**
    This function interchanges a row of a matrix (dynamic array)
    Input:
        - p: a double pointer, the row to be exchanged
        - q: a double pointer, the second row to be exchanged
        - n: the n value of the matrix (dynamic array)
**/
void interchangeRow( double * p, double * q, int n );


/**
    This function creates a dynamic array in memory.

    Input:
        - p: a double pointer
        - m: the m value of the matrix to be simulated
        - n: the n value of the matrix to be simulated
**/
void createMatrix( double *& p, int m, int n );


/**
    This function deletes a dynamic array from memory.

    Input:
        - p: a double pointer, pointing towards the beginning of the requested memory for the dynamic array
**/
void destroyMatrix( double *& p );


/**
    This function makes the pivot of a row one, and then returns its value.

    Input:
        - p: a double pointer
        - n: the n value of the matrix to be simulated
    Output:
        - value: an integer that holds the value of the coefficient needed to make the pivot one
**/
double makePivotOne( double * p, int n );


/**
    This function multiplies a row (p pointer) and then adds its values to another row (q pointer)
    in order to reduce it.

    Input:
        - p: a double pointer, first row
        - q: a double pointer, second row
        - n: the n value of the matrix to be simulated
    Output:
        - value: a double that holds the value of the coefficient needed to alter the B-vector
**/
double rowElimination( double * p, double * q, int n );


/**
    This function prints a matrix (dynamic array) in a proper matrix format

    Input:
        - p: a double pointer that points to the beginning of the array
        - m: the m value of the matrix (dynamic array) to be printed
        - n: the n value of the matrix (dynamic array) to be printed
**/
void prettyMatrix( double * p, int m, int n );


/**
    This function multiplies a row in order to reduce another. It makes the pivot zero.

    Input:
        - p: a double pointer, first row
        - q: a double pointer, second row
        - n: the n value of the matrix (dynamic array)

    Output:
        - value: a double that holds the coefficient needed to modify the B-vector
**/
double rowElimination( double * p, double * q, int n );


/**
    This function reduces a matrix (dynamic array) for further back substitution.

    Input:
        - p: a double pointer, matrix (dynamic array)
        - q: a double pointer, B-vector (dynamic array)
        - n: the n value of the matrix
        - m: the m value of the matrix
**/
void oldReduce( double * p, double * r, int n, int m);


/**
    This function multiplies a row in order to reduce another. It makes the pivot zero.

    Input:
        - column: a double pointer, where the pivot is
        - n: the n value of the matrix (dynamic array)
        - currentRowIndex: the index of the row where the pivot is

    Output:
        - greatest: an integer holding the index where the greatest number of the column is
                    for further use in row interchange.
**/
int partialPivot( double * column, int n, int currentRowIndex );


/**
    This function takes input for the matrix.

    Input:
        - p: a double pointer, the matrix (dynamic array)
        - m: the m value of the matrix
        - n: the n value of the matrix
**/
void assignValuesMatrix( double * p, int m, int n );

/**
    This function takes input for the b Vector.

    Input:
        - r: a double pointer, the b vector(dynamic array)
        - m: the m value of the matrix
**/
void assignValuesBVector( double * r, int m );

/**
    This function modifies a b vector with a coefficient
    that was used in previous gaussian elimination functions.

    Input:
        - r: a double pointer, the b vector (dynamic array)
        - value: the value of the coefficient
**/
void modifyBVector( double * r, double value );

/**
    This function eliminates rows of the b vector accordingly
    to previous gaussian elimination.

    Input:
        - r: a double pointer, the b vector (dynamic array)
        - r1: double pointer, the b vector's row to be eliminated
        - n: the n value of the matrix
**/
void elimBVector( double * r, double * r1, double value );

/**
    This function resolves a system of linear equations.

    Input:
        - p: a double pointer, the matrix (dynamic array)
        - q: a double pointer, the b vector (dynamic array)
        - n: the n value of the matrix

    Output:
        - r: a double pointer, the solution vector (dynamic array)
**/
double * resolve( double * p, double * q, int n );

/**
    This function copies the contents of a vector onto another.

    Input:
        - p: a double pointer, the first vector (dynamic array)
        - q: a double pointer, the second vector (dynamic array)
        - n: the n value of the matrix
**/
void copyContentsVector( double * p, double * q, int n );

/**
    This function multiplies two matrices.

    Input:
        - p: a double pointer, the first matrix (dynamic array)
        - q: a double pointer, the second matrix (dynamic array)
        - n: the n value of both matrices

    Output:
        - result: the product of both matrices
**/
double * multiplyMatrices( double * p, double * q, int n );
double * inverseMatrix( double * p, double * q, int n, int m);
void rowEliminationIdentity( double * p, int n, double coeff, int indexRow );
void modifyIdentityRow( double * r, int n, double value );


#endif // LINEAR_H_INCLUDED
