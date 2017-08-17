#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED


/**
    \brief Function that assigns memory to a pointer (double) that will further represent a matrix.
    \param rows The number of rows.
    \param rows The number of columns.
    \return A pointer to a double that represents the assigned matrix.
*/
double * makeMatrix( int rows, int cols );

/**
    \brief Function that takes two pointers that represent matrices, and then adds them.
    \param mat A pointer to a double that represents the first matrix.
    \param mat2 A pointer to a double that represents the second matrix.
    \param rows The number of rows.
    \param rows The number of columns.
    \return A pointer to a double that represents the result matrix.
*/
double * sumMatrices( double * mat1, double * mat2, int rows, int cols );


/**
    \brief Function that takes two pointers that represent matrices, and then subtracts them.
    \param mat A pointer to a double that represents the first matrix.
    \param mat2 A pointer to a double that represents the second matrix.
    \param rows The number of rows.
    \param rows The number of columns.
    \return A pointer to a double that represents the result matrix.
*/
double * subtractMatrices( double * mat1, double * mat2, int rows, int cols );


/**
    \brief Function that takes a matrix and a scalar for scalar product.
    \param mat A pointer to a double that represents the matrix.
    \param scalar The scalar (const double).
    \param rows The number of rows.
    \param rows The number of columns.
    \return A pointer to a double that represents the result matrix.
*/
double * scalarProduct( double * mat, const double scalar, int rows, int cols );


/**
    \brief Function that takes two pointers that represent matrices, and then multiplies them.
            Note: Both of them need to be square matrices.
    \param mat A pointer to a double that represents the first matrix.
    \param mat2 A pointer to a double that represents the second matrix.
    \param rows The number of rows.
    \param rows The number of columns.
    \return A pointer to a double that represents the result matrix.
*/
double * matMultiplication( double * mat, double * mat2, int rows, int cols );


/**
    \brief Function that prints a matrix (pointer to a double that represents it).
    \param mat A pointer to a double that represents the first matrix.
    \param rows The number of rows.
    \param rows The number of columns.
*/
void printMatrix( double * mat, int rows, int cols );


/**
    \brief Function that calculates the norm of a vector.
    \param vec A pointer to a double that represents the vector.
    \param numEntries The number of entries of the vector.
    \return The value of the norm of the vector.
*/
double normVector( double * vec, const unsigned short numEntries );


#endif // MATRIX_H_INCLUDED
