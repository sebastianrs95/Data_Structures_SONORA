#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "matrix.h"

using std::cout;
using std::endl;
using std::setw;
using std::right;
using std::left;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istringstream;

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

double * squareMatMult( double * mat, double * mat2, int rows, int cols )
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

double * matMultiplication( double * mat, double * mat2, int m, int n, int k )
{

    double * result, *pMat, *pMat2, *pResult;
    result = (double*) malloc( sizeof(double)*m*k );

    pMat = mat;
    pMat2 = mat2;

    double sum = 0.0;

    for( int i = 0 ; i < k ; ++i )
    {
        pResult = result + i;
        for( int j = 0 ; j < m ; ++j, pResult += k )
        {
            sum = 0.0;
            pMat = mat + j*n;   // move to the next row for each iteration
            pMat2 = mat2 + i;

            for( int l = 0 ; l < n ; ++l, ++pMat, pMat2 += k )
                sum += *(pMat) * (*pMat2);

            *pResult = sum;
        }
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


/*************************************************************************************************************************/

double * readMatrixFromFile( const char * filename, int & rows, int & cols )
{
    ifstream input;
    string line;
    input.open(filename);

    vector<vector<string> > ret;    // make a vector of string vectors that will hold the matrix data in strings

    while( getline(input, line) )
    {
        ret.push_back( split(line, ' ') );
    }

    rows = 0;
    cols = 0;

    bool firstIteration = true;
    vector<double> matData;     // this will hold the strings converted to doubles

    for( vector<vector<string> >::iterator it = ret.begin() ; it != ret.end() ; ++it )
    {
        for( vector<string>::iterator innerIt = it->begin() ; innerIt != it->end() ; innerIt++ )
        {
            if( firstIteration ) cols += 1;
            matData.push_back( string2double(*innerIt) );
        }
        rows += 1;
        firstIteration = false;
    }


    double * newMat, * pNewMat;
    newMat = makeMatrix(rows, cols);

    pNewMat = newMat;
    for( vector<double>::iterator it = matData.begin() ; it != matData.end() ; ++it, ++pNewMat )
    {
        *pNewMat = *it;
    }

    input.close();

    return newMat;
}


/*************************************************************************************************************************/

void changeRows( double * firstRow, double * secondRow, int m, int n )
{
    double *pFirst, *pSecond, aux;

    pFirst = firstRow;
    pSecond = secondRow;

    for( int i = 0 ; i < n ; ++i, ++pFirst, ++pSecond )
    {
        aux = *pFirst;
        *pFirst = *pSecond;
        *pSecond = aux;
    }
}


/*************************************************************************************************************************/

void changeRowsBVec( double * bVec, int position )
{
    double aux = *bVec;
    cout << "position is " << position << endl;
    *bVec = *(bVec + position);
    *(bVec + position) = aux;
}


/*************************************************************************************************************************/

double makePivotOne( double * row, int n )
{
    double *pRow = row;
    double value = 1.0 / (*pRow);
    *pRow = 1;

    ++pRow;
    for( int i = 1;  i < n ; ++i, ++pRow )
    {
        *pRow = value * (*pRow);
    }

    return value;
}


/*************************************************************************************************************************/

double reduceColumn( double * row, double * row2, int n )
{
    double *pRow, *pRow2;
    pRow = row;
    pRow2 = row2;

    double value;
    value = -(*pRow2);
    //*pRow2 = 0;

    //++pRow;
    //++pRow2;
    for( int i = 0 ; i < n ; ++i, ++pRow, ++pRow2 )
    {
        *pRow2 = (*pRow2) + value * (*pRow);
    }

    return value;
}

/*************************************************************************************************************************/

void modifyBVec( double * bVec, double value, int position )
{
    double *pbVec = bVec;
    pbVec += position;
    *pbVec = *pbVec * value;
    cout << "value is: " << value << endl;
}


/*************************************************************************************************************************/

int partialPivot( double * col, int numIt, int n )
{
    double * pCol, greatest;
    pCol = col;

    int greatestIndex = 0;
    greatest = 0;
    for( int i = 0 ; i < numIt ; ++i, pCol += n )
    {
        if( greatest < abs(*pCol) )
        {
            greatest = *pCol;
            greatestIndex = i;
        }
    }

    return greatestIndex + (n-numIt);
}


/*************************************************************************************************************************/

void reduceBVec( double * bVec, double value, int position, int numIteration )
{
    double *pbVec = bVec;
    pbVec += position;
    *pbVec += *(bVec + numIteration) * value;
}


/*************************************************************************************************************************/
void reduce( double * mat, double * bVec, int n )
{
    double *pRow, *pRow2, *pbVec, value;
    pRow = mat;
    pbVec = bVec;

    int pivotIndex;
    for( int i = 0 ; i < n ; ++i, pRow += n+1 )
    {
        pivotIndex = partialPivot(pRow, n-i, n);
        changeRows(mat + i*n, mat + pivotIndex*n, n, n);    // send the beginning of each row
        changeRowsBVec( pbVec, pivotIndex-i );  // minus the i iteration
        value = makePivotOne(pRow, n-i);
        modifyBVec(pbVec, value, i);

        cout << endl << endl << "After pivot in i = " << i << endl;
        printMatrix(mat, n, n);
        cout << endl;
        printMatrix(bVec, n, 1);


        pRow2 = pRow + n;

        for( int j = 0 ; j < n - (i+1) ; ++j, pRow2 += n )
        {
            value = reduceColumn(pRow, pRow2, n-i);
            reduceBVec(pbVec, value, j+i+1, i);    // the j + i + 1 works...
            cout << endl << endl << "After reduce in i = " << i << " and j = " << j << endl;
            printMatrix(mat, n, n);
            cout << endl;
            printMatrix(bVec, n, 1);
        }

    }
}

/*************************************************************************************************************************/


void writeMatrixToFile( double * mat, int rows, int cols, const char * filename )
{
    ofstream outfile;
    outfile.open(filename);

    double * pMat = mat;
    for( int i = 0 ; i < rows ; ++i, ++pMat )
    {
        for( int j = 0 ; j < cols ; ++j )
        {
            outfile << *pMat << ' ';
        }
        outfile << '\n';
    }
    outfile.close();
}

/*************************************************************************************************************************/

double string2double( string str )
{
    double temp = atof(str.c_str());
    return temp;
}


/*************************************************************************************************************************/

vector<string> split( string str, char sep )
{
    vector<string> ret;

    istringstream stm(str);
    string token;
    while( getline(stm, token, sep)) ret.push_back(token);

    return ret;
}

