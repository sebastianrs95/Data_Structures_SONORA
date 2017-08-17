#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;
using std::setw;
using std::right;
using std::left;

/*************************************************************************************************************************/

double normVector( double * vec, const unsigned short numEntries )
{
    double sum = 0, * pVec;

    pVec = vec;
    for( int i = 0 ; i < numEntries ; ++i, ++pVec )
    {
        sum += pow(*pVec, 2);
    }
    return sqrt(sum);
}


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

double * scalarProduct( double * mat, const double scalar, int rows, int cols )
{
    double * pMat = mat;
    double * result, *pResult;

    result = (double *) malloc(sizeof(double)*rows*cols);
    pResult = result;

    for( int i = 0 ; i < rows*cols ; ++i, ++pMat, ++pResult )
    {
        *pResult = *pMat * scalar;
    }

    return result;
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
    /*
        ASCII codes:
            179 vertical bar
            218 top left edge
            191 top right edge
            192 lower left edge
            217 lower right edge

    */

    const unsigned short WIDTH = 10;

    // first the upper edges
    cout << char(218);  // upper left edge
    for( int i = 0 ; i < cols ; ++i )
    {
        for( int j = 0 ; j < WIDTH ; ++j )
            cout << " ";
    }
    cout << " " << char(191) << endl;   // upper right edge

    for( int i = 0 ; i < rows ; ++i )
    {
        cout << char(179);  // vertical bar
        for( int j = 0 ; j < cols ; ++j, ++mat )
        {
            cout << setw(WIDTH) << *mat;
        }
        cout << " " << char(179);  // vertical bar
        cout << endl;
    }

    cout << char(192); // lower left edge
    for( int i = 0 ; i < cols ; ++i )
    {
        for( int j = 0 ; j < WIDTH ; ++j )
            cout << " ";
    }
    cout << " " << char(217);
}
