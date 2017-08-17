#include <cstdlib>
#include <iostream>
#include "matrix.h"

using namespace std;


int main ()
{
    double * mat, * mat2;
    int rows = 4;
    int cols = 4;
    mat = makeMatrix(rows,cols);
    mat2 = makeMatrix(rows,cols);

    double * pMat, * pMat2;

    pMat = mat;
    pMat2 = mat2;

    for( int i = 1 ; i <= rows*cols ; ++i, ++pMat, ++pMat2 )
    {
        *pMat = i;
        *pMat2 = i;
    }

    double * result;
    result = matMultiplication(mat, mat2, rows, cols);
    //printMatrix(mat, rows, cols);
    printMatrix( result, rows, cols );


    free(mat);
    free(mat2);
    free(result);

    return 0;
}


