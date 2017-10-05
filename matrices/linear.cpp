#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "linear.h"

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::right;
using std::left;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istringstream;

//**************************************************************************
//**************************************************************************
//**************************************************************************

void interchangeRow( double * p, double * q, int n )
{
    double * p1, * q1;
    double value;
    int i;
    p1 = p;
    q1 = q;
    value = *p1;

    for( i = 0 ; i < n ; i++, p1++, q1++)
    {
        value = *p1;
        *p1 = *q1;
        *q1 = value;
    }
}

//**************************************************************************

void createMatrix( double *& p, int m, int n )
{
    p = new double[m*n];
}

//**************************************************************************

void destroyMatrix( double *& p )
{
    delete [] p;
}

//**************************************************************************

double makePivotOne( double * p, int n )
{
    double * p1;
    int i;
    double value = 0.0;
    p1 = p;
    value = 1.0/(*p1);
    *p1 = 1;
    p1++;
    for( i = 1 ; i < n ; i++, p1++ )
    {
        *p1 = value * (*p1);
    }
    return value;
}

//**************************************************************************

double rowElimination( double * p, double * q, int n )
{
    double * p1, * q1;
    double value;
    int i;
    p1 = p;
    q1 = q;
    value = -(*q1)/(*p1);
    *q1 = 0.0;
    q1++;
    p1++;
    for( i = 1 ; i < n ; i++, q1++, p1++ )
    {
        *q1 += value*(*p1);
    }
    return value;
}

//**************************************************************************

int partialPivot( double * column, int n, int currentRowIndex )
{
    double * currentPivot;
    int greatest, greatestValue;     // row index of greatest value
    int i;
    greatestValue = fabs(*column);
    greatest = currentRowIndex;
    currentPivot = column + n;

    for( i = currentRowIndex + 1; i < n ; i++, currentPivot += n )
    {
        if( fabs(*currentPivot) > greatestValue )
        {
            greatest = i;
            greatestValue = *currentPivot;
        }
    }

    return greatest;

}


//**************************************************************************

void prettyMatrix( double * p, int m, int n )
{
    /*
        Ascii codes
        Top left angle: 218
        Top right angle: 191
        Vertical Bar:   124
        Low left angle: 192
        Low right angle: 217
    */
    double * p1;
    p1 = p;
    cout << char(218);
    for ( int i = 0 ; i < n ; i++ ) cout << setw(9) << " ";
    cout << setw(9) << char(191) << endl;

    for (int i = 0; i < m ; ++i)
    {
        cout << char(124);

        for (int j = 0; j < n; ++j)
        {
            cout << setw(9) << *p1;
            p1++;
        }

        cout << setw(9) << char(124) << endl;
    }

    cout << char(192);
    for ( int i = 0 ; i < n ; i++ ) cout << setw(9) << " ";
    cout << setw(9) << char(217) << endl;
}

//**************************************************************************

void oldReduce( double * p, double * r, int n, int m)
{
    double * p1, * q1, *r1, *r2;
    double value;
    int i, j, pivot;
    p1 = p;
    r1 = r;
    for( i = 0 ; i < n ; i++, p1 += n + 1 )
    {
        pivot = partialPivot(p1, n, i);
        interchangeRow(p1 - i, p + pivot*n, n );
        interchangeRow(r + i, r + pivot, 1 );      // here we just add the pivot because of the b vector being a single vector, and 1 because n = 1
        value = makePivotOne(p1, n-i);
        modifyBVector( r + i, value );
        q1 = p1 + n;
        r1 = r + i;
        r2 = r1 + 1;        // r2 is the row of the b-vector to be "eliminated"
        for( j = 0 ; j < n-1-i ; j++, q1 += n, r2++ ){
            value = rowElimination(p1, q1, n - i);
            elimBVector( r1, r2, value );
        }
    }
}

//**************************************************************************
double * inverseMatrix( double * p, double * q, int n, int m)
{
    double * p1, * q1, *r, *r1;
    double value;
    int i, j, pivot;

    createMatrix(r, n, n);

    p1 = p;
    q1 = q;

    for( i = 0 ; i < n ; i++, p1+=n )
    {
        value = makePivotOne(p1+i, n);
        modifyIdentityRow(q1+i, n, value);
        prettyMatrix(p1, n, n);

        // the downwards elimination loop
        for( j = i+1 ; j < n ; j++ )
        {
            value = rowElimination(p1, p1+j*n, n);
            rowEliminationIdentity(q1, n, value, j);    // send the identity matrix for further modification
        }

        // the upwards elimination loop
        for( j = 0 ; j < i ; j++ )
        {
            value = rowElimination(p1, p1-j*n, n);
            rowEliminationIdentity(q1, n, value, -j);
        }


    }
    cout << "p and q after the function" << endl;
    prettyMatrix(p, n, n);
    prettyMatrix(q, n, n);
}

//**************************************************************************

void rowEliminationIdentity( double * p, int n, double coeff, int indexRow )
{
    // Doesn't need but the coefficient with which to multiply
    // the row in the identity matrix
    double * row, *rowToBeElim;
    rowToBeElim = p + (indexRow)*n;
    row = p;

    for( int i = 0 ; i < n ; i++ )
    {
        *rowToBeElim += (*row) * coeff;
        rowToBeElim++;
        row++;
    }
}

//**************************************************************************

double * resolve( double * p, double * q, int n )
{
    double *p1, *q1, * c;
    double value;
    int i, j;
    c = new double[n];

    copyContentsVector( q, c, n );


    for( i = n - 1 ; i > 0 ; i--)
    {
        //p1 = p + (n - (1+i));
        p1 = p + n*i - 1;
        q1 = q + (n-1);
        value = *(q1 + (n-(1+i)));

        for( j = i ; j < n ; j++, p1--, q1-- )
        {
            value = (*p1) * (*q1);
            *(q1-1) += -value;
            c[i-1] += -value;
        }
    }

    return c;

}


//**************************************************************************

void assignValuesMatrix( double * p, int m, int n )
{
    double * p1;
    int i, j;

    p1 = p;
    for( i = 0 ; i < m ; i++ )
    {
        for( j = 0 ; j < n ; j++, p1++ )
        {
            cout << "Enter [" << i << "][" << j << "]: ";
            cin >> *p1;
        }
    }
}

//**************************************************************************

void assignValuesBVector( double * r, int m )
{
    double * r1;
    r1 = r;

    for( int i = 0 ; i < m ; i++, r1++ )
    {
        cout << "Enter row number " << i << " of the B-vector: ";
        cin >> *r1;
    }
}


//**************************************************************************

void modifyBVector( double * r, double value )
{
    *r = *r * value;
}
//**************************************************************************

void modifyIdentityRow( double * r, int n, double value )
{
    double * r1;
    r1 = r;
    for( int i = 0; i < n ; i++, r1++ )
    {
        *r1 *= value;
    }

}

//**************************************************************************

void elimBVector( double * r, double * r1, double value )
{
    *r1 += value*(*r);
}

void copyContentsVector( double * p, double * q, int n )
{
    double *p1, *q1;
    p1 = p;
    q1 = q;


    for( int i = 0 ; i < n ; i++, ++p1, ++q1 )
    {
        *q1 = *p1;
    }


}
