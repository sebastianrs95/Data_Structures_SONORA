#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

/*************************************************************************************************************************/

double * makeMatrix( int rows, int col )
{
    double * matrix;

    matrix = (double*) malloc(sizeof(double)*rows*col);

    return matrix;
}


/*************************************************************************************************************************/

double * sumMatrices( double * mat1, double * mat2, int rows, int cols )
{
    double * resultMat;
    resultMat = (double*) malloc(sizeof(double)*rows*cols);

    double * pMat1, * pMat2, * pResult;
    pMat1 = mat1;
    pMat2 = mat2;
    pResult = resultMat;

    for( int i = 0 ; i < rows*cols ; ++i, ++pMat1, ++pMat2, ++pResult )
    {
        *pResult = *pMat1 + *pMat2;
    }

    return resultMat;
}


/*************************************************************************************************************************/

double * subtractMatrices( double * mat1, double * mat2, int rows, int cols )
{
    double * resultMat;
    resultMat = (double*) malloc(sizeof(double)*rows*cols);

    double * pMat1, * pMat2, * pResult;
    pMat1 = mat1;
    pMat2 = mat2;
    pResult = resultMat;

    for( int i = 0 ; i < rows*cols ; ++i, ++pMat1, ++pMat2, ++pResult )
    {
        *pResult = *pMat1 - *pMat2;
    }

    return resultMat;
}


/*************************************************************************************************************************/

double * matMultiplication( double * mat, double * mat2, int rows, int cols )
{
    double * pMat, * pMat2, * result, * pResult;
    result = (double*) malloc(sizeof(double)*rows*cols);

    pMat = mat;
    pMat2 = mat2;
    pResult = result;

    double entrySum = 0;

    for( int i = 0 ; i < rows ; ++i )
    {
        pMat = mat + i*rows;
        for( int j = 0 ; j < cols ; ++j )
        {
            pMat2 = mat2 + j; // j corresponds to the current column

            for( int k = 0 ; k < rows ; ++k )
            {
                entrySum += (*(pMat + k)) * (*(pMat2 + k*rows ));
            }
            *pResult = entrySum;
            ++pResult;
            entrySum = 0;
        }
        pMat2 = mat2;   // restart the pointer
    }

    return result;
}


/*************************************************************************************************************************/

void printMatrix( double * mat, int rows, int cols )
{
    for( int i = 0 ; i < rows ; ++i )
    {
        for( int j = 0 ; j < cols ; ++j, ++mat )
        {
            cout << *mat << " ";
        }
        cout << endl;
    }
}
