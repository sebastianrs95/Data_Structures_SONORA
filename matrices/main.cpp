#include <cstdlib>
#include <iostream>
#include "matrix.h"

using namespace std;


int main ()
{
    double * mat, * mat2;
    double * vec;
    int rows = 5;
    int cols = 5;

    vec = makeMatrix(4, 1);
    mat = makeMatrix(rows,cols);
    mat2 = makeMatrix(rows,cols);

    double * pMat, * pMat2, *pVec;

    pMat = mat;
    pMat2 = mat2;

    for( int i = 1 ; i <= rows*cols ; ++i, ++pMat, ++pMat2 )
    {
        *pMat = i;
        *pMat2 = i;
    }

    pVec = vec;
    *pVec = 8;
    *(++pVec) = 4;
    *(++pVec) = 1;
    *(++pVec) = 0;

    double * result;
    result = matMultiplication(mat, mat2, rows, cols);
    //printMatrix( scalarProduct(mat, 3, rows, cols), rows, cols);
    //printMatrix( result, rows, cols );
    printMatrix(vec, 4, 1);

    double * inMatrix = readMatrixFromFile("ex2.txt");

    cout << endl << "inMatrix" << endl;
    printMatrix(inMatrix, 4, 6);

    free(inMatrix);
    free(mat);
    free(mat2);
    free(result);
    free(vec);

    return 0;
}


