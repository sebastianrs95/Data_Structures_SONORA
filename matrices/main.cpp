#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include "matrix.h"
#include "linear.h"

using namespace std;
void printMenu();
void printSubMenu(int option);



int main ()
{
    cout << endl << endl << "\t\t\tMATRIX OPERATIONS" << endl << endl << endl;
    printMenu();

    int option;
    cout << endl << endl << "Option: ";
    cin >> option;

    printSubMenu(option);

    /*
    double * mat, * bVec;
    int m, n, mVec, nVec;
    mat = readMatrixFromFile("sel.txt", m, n);
    bVec = readMatrixFromFile("selBVec.txt", mVec, nVec);


    //changeRows(mat, mat+2*n, n, n);

    printMatrix(mat, m, n);
    cout << endl;
    printMatrix(bVec, nVec, mVec);


    cout << endl << endl;

    reduce(mat, bVec, n);
    cout << endl << endl;
    printMatrix(mat, m, n);
    cout << endl;
    printMatrix(bVec, nVec, mVec);



    */
    return 0;
}

void printMenu()
{

    cout << "\t1. " << "Matrix addition" << endl;
    cout << "\t2. " << "Matrix subtraction" << endl;
    cout << "\t3. " << "Matrix multiplication" << endl;
    cout << "\t4. " << "Scalar times a matrix" << endl;
    cout << "\t5. " << "Solve SEL"<< endl;
    cout << "\t6. " << "Inverse of a matrix" << endl;
    cout << "\t7. " << "Norm of a vector" << endl;
}

void printSubMenu( int option )
{
    enum { SUM = 1, SUB, MULT, SCALAR, SEL, INV, NORM };

    double * mat, * mat2, *pMat, *pMat2;
    int rows, cols;

    switch(option)
    {

        case SUM:

            system("cls");
            cout << "Do you want to read the matrices from a file?" << endl;
            cout << "Type 1 for yes, 2 for no: ";
            int option;
            cin >> option;

            // Read from file
            if( option == 1 )
            {
                system("cls");
                cout << "Enter the name of the file holding the first matrix (with extension): ";
                char filename[256];

                scanf("%255s", filename);

                mat = readMatrixFromFile(filename, rows, cols);

                cout << endl << endl << "The matrix read is:" << endl << endl;
                printMatrix(mat, rows, cols);

                cout << endl;
                system("pause");
                system("cls");

                cout << "Enter the name of the file holding the second matrix (with extension): ";
                scanf("%255s", filename);

                mat2 = readMatrixFromFile(filename, rows, cols);
                cout << endl << endl << "The second matrix read is:" << endl << endl;
                printMatrix(mat2, rows, cols);

                cout << endl;
                system("pause");

            }   // end of file reading

            // Read manually or randomly
            if( option == 2 )
            {
                system("cls");
                cout << "Enter the dimensions for the matrices." << endl;
                cout << "Number of rows: ";

                cin >> rows;

                cout << endl << "Number of columns: ";
                cin >> cols;

                system("cls");

                cout << "\t1. Generate two random matrices." << endl;
                cout << "\t2. Enter the matrices data manually." << endl;

                cout << endl << "Select an option: ";
                cin >> option;

                double *pMat, *pMat2;
                mat = (double*) malloc(sizeof(double)*rows*cols);
                mat2 = (double*) malloc(sizeof(double)*rows*cols);

                system("cls");

                // random matrix generation
                if( option == 1 )
                {
                    srand(time(0));

                    pMat = mat;
                    for( int i = 0 ; i < rows*cols ; ++i, ++pMat )
                        *pMat = rand();

                    pMat2 = mat2;
                    for( int i = 0 ; i < rows*cols ; ++i, ++pMat2 )
                        *pMat2 = rand();

                    cout << "The matrices generated are..." << endl;
                    cout << "First matrix: " << endl << endl;

                    printMatrix(mat, rows, cols);

                    cout << endl << endl << endl << "Second matrix: " << endl << endl;

                    printMatrix(mat2, rows, cols);
                    system("pause");
                }   // end of random generation

                // enter manually
                if( option == 2 )
                {
                    cout << "First matrix:" << endl << endl;

                    double entry;
                    pMat = mat;
                    for( int i = 0 ; i < rows ; ++i )
                    {
                        for( int j = 0 ; j < cols ; ++j, ++pMat )
                        {
                            cout << "Entry " << i << ", " << j << ": ";
                            cin >> entry;
                            *pMat = entry;
                            cout << endl;
                        }
                    }

                    cout << "Second matrix: " << endl << endl;
                    pMat2 = mat2;
                    for( int i = 0 ; i < rows ; ++i )
                    {
                        for( int j = 0 ; j < cols ; ++j, ++pMat2 )
                        {
                            cout << "Entry " << i << ", " << j << ": ";
                            cin >> entry;
                            *pMat2 = entry;
                            cout << endl;
                        }
                    }
                }   // end of manual input

            }   // end of not-read-from-file option

            double * result;

            result = sumMatrices(mat, mat2, rows, cols);

            system("cls");
            cout << "The sum of: " << endl << endl;
            printMatrix(mat, rows, cols);

            cout << endl << endl << "+" << endl << endl;
            printMatrix(mat2, rows, cols);

            cout << endl << endl << "is: " << endl << endl << endl;
            printMatrix(result, rows, cols);


            cout << endl;
            system("pause");
            system("cls");

            cout << "Do you want to save the result matrix to a file?" << endl;
            cout << "Type 1 for yes, 2 for no: ";

            cin >> option;
            if( option == 1 )
            {
                system("cls");

                cout << "WARNING: if the file already exists, it will be overwritten." << endl << endl;

                char newFilename[256];
                cout << "Enter the name for the new file: ";
                scanf("%255s", newFilename);
                writeMatrixToFile(result, rows, cols, newFilename);
            }

            free(mat);
            free(mat2);
            free(result);

            break;


        case SUB:

            system("cls");
            cout << "Do you want to read the matrices from a file?" << endl;
            cout << "Type 1 for yes, 2 for no: ";

            cin >> option;

            // Read from file
            if( option == 1 )
            {
                system("cls");
                cout << "Enter the name of the file holding the first matrix (with extension): ";
                char filename[256];

                scanf("%255s", filename);

                mat = readMatrixFromFile(filename, rows, cols);

                cout << endl << endl << "The matrix read is:" << endl << endl;
                printMatrix(mat, rows, cols);

                cout << endl;
                system("pause");
                system("cls");

                cout << "Enter the name of the file holding the second matrix (with extension): ";
                scanf("%255s", filename);

                mat2 = readMatrixFromFile(filename, rows, cols);
                cout << endl << endl << "The second matrix read is:" << endl << endl;
                printMatrix(mat2, rows, cols);

                cout << endl;
                system("pause");

            }   // end of file reading

            // Read manually or randomly
            if( option == 2 )
            {
                system("cls");
                cout << "Enter the dimensions for the matrices." << endl;
                cout << "Number of rows: ";

                cin >> rows;

                cout << endl << "Number of columns: ";
                cin >> cols;

                system("cls");

                cout << "\t1. Generate two random matrices." << endl;
                cout << "\t2. Enter the matrices data manually." << endl;

                cout << endl << "Select an option: ";
                cin >> option;

                mat = (double*) malloc(sizeof(double)*rows*cols);
                mat2 = (double*) malloc(sizeof(double)*rows*cols);

                system("cls");

                // random matrix generation
                if( option == 1 )
                {
                    srand(time(0));

                    pMat = mat;
                    for( int i = 0 ; i < rows*cols ; ++i, ++pMat )
                        *pMat = rand();

                    pMat2 = mat2;
                    for( int i = 0 ; i < rows*cols ; ++i, ++pMat2 )
                        *pMat2 = rand();

                    cout << "The matrices generated are..." << endl;
                    cout << "First matrix: " << endl << endl;

                    printMatrix(mat, rows, cols);

                    cout << endl << endl << endl << "Second matrix: " << endl << endl;

                    printMatrix(mat2, rows, cols);
                    system("pause");
                }   // end of random generation

                // enter manually
                if( option == 2 )
                {
                    cout << "First matrix:" << endl << endl;

                    double entry;
                    pMat = mat;
                    for( int i = 0 ; i < rows ; ++i )
                    {
                        for( int j = 0 ; j < cols ; ++j, ++pMat )
                        {
                            cout << "Entry " << i << ", " << j << ": ";
                            cin >> entry;
                            *pMat = entry;
                            cout << endl;
                        }
                    }

                    cout << "Second matrix: " << endl << endl;
                    pMat2 = mat2;
                    for( int i = 0 ; i < rows ; ++i )
                    {
                        for( int j = 0 ; j < cols ; ++j, ++pMat2 )
                        {
                            cout << "Entry " << i << ", " << j << ": ";
                            cin >> entry;
                            *pMat2 = entry;
                            cout << endl;
                        }
                    }
                }   // end of manual input
            }

            result = subtractMatrices(mat, mat2, rows, cols);

            system("cls");
            cout << "The subtraction of: " << endl << endl;
            printMatrix(mat, rows, cols);

            cout << endl << endl << "-" << endl << endl;
            printMatrix(mat2, rows, cols);

            cout << endl << endl << "is: " << endl << endl << endl;
            printMatrix(result, rows, cols);

            cout << endl;
            system("pause");
            system("cls");

            cout << "Do you want to save the result matrix to a file?" << endl;
            cout << "Type 1 for yes, 2 for no: ";

            cin >> option;
            if( option == 1 )
            {
                system("cls");

                cout << "WARNING: if the file already exists, it will be overwritten." << endl << endl;

                char newFilename[256];
                cout << "Enter the name for the new file: ";
                scanf("%255s", newFilename);
                writeMatrixToFile(result, rows, cols, newFilename);
            }

            free(mat);
            free(mat2);
            free(result);

            break;


        case MULT:

            system("cls");
            cout << "Do you want to read the matrices from a file?" << endl;
            cout << "Type 1 for yes, 2 for no: ";

            cin >> option;

            int m, n, n2, k;

            // Read from file
            if( option == 1 )
            {
                system("cls");
                cout << "Enter the name of the file holding the first matrix (with extension): ";
                char filename[256];

                scanf("%255s", filename);

                mat = readMatrixFromFile(filename, m, n);

                cout << endl << endl << "The matrix read is:" << endl << endl;
                printMatrix(mat, m, n);

                cout << endl;
                system("pause");
                system("cls");

                cout << "Enter the name of the file holding the second matrix (with extension): ";
                scanf("%255s", filename);

                mat2 = readMatrixFromFile(filename, n2, k);
                cout << endl << endl << "The second matrix read is:" << endl << endl;
                printMatrix(mat2, n2, k);

                cout << endl;
                system("pause");

            }   // end of file reading

            // Read manually or randomly
            if( option == 2 )
            {
                system("cls");
                cout << "Enter the dimensions for the first matrix." << endl;
                cout << "Number of rows: ";
                cin >> m;

                cout << endl << "Number of columns for the first matrix (which is also the number of rows for the second): ";
                cin >> n;

                n2 = n; // just a precaution for a further check

                cout << endl << "Number of columns of the second matrix: ";
                cin >> k;

                system("cls");

                cout << "\t1. Generate two random matrices." << endl;
                cout << "\t2. Enter the matrices data manually." << endl;

                cout << endl << "Select an option: ";
                cin >> option;

                mat = (double*) malloc(sizeof(double)*m*n);
                mat2 = (double*) malloc(sizeof(double)*n*k);

                system("cls");

                // random matrix generation
                if( option == 1 )
                {
                    srand(time(0));

                    pMat = mat;
                    for( int i = 0 ; i < m*n ; ++i, ++pMat )
                        *pMat = rand();

                    pMat2 = mat2;
                    for( int i = 0 ; i < n*k ; ++i, ++pMat2 )
                        *pMat2 = rand();

                    cout << "The matrices generated are..." << endl;
                    cout << "First matrix: " << endl << endl;

                    printMatrix(mat, m, n);

                    cout << endl << endl << endl << "Second matrix: " << endl << endl;

                    printMatrix(mat2, n, k);

                    cout << endl;
                    system("pause");
                }   // end of random generation

                // enter manually
                if( option == 2 )
                {
                    cout << "First matrix:" << endl << endl;

                    double entry;
                    pMat = mat;
                    for( int i = 0 ; i < m ; ++i )
                    {
                        for( int j = 0 ; j < n ; ++j, ++pMat )
                        {
                            cout << "Entry " << i << ", " << j << ": ";
                            cin >> entry;
                            *pMat = entry;
                            cout << endl;
                        }
                    }

                    cout << "Second matrix: " << endl << endl;
                    pMat2 = mat2;
                    for( int i = 0 ; i < n ; ++i )
                    {
                        for( int j = 0 ; j < k ; ++j, ++pMat2 )
                        {
                            cout << "Entry " << i << ", " << j << ": ";
                            cin >> entry;
                            *pMat2 = entry;
                            cout << endl;
                        }
                    }
                }   // end of manual input
            }

            if( n != n2 )
            {
                system("cls");
                cout << "The number of columns of the first matrix must be equal" << endl << "to the number of rows of the second." << endl;
                return;
            }

            result = matMultiplication(mat, mat2, m, n, k);

            system("cls");
            cout << "The multiplication of: " << endl << endl;
            printMatrix(mat, m, n);

            cout << endl << endl << "*" << endl << endl;
            printMatrix(mat2, n, k);

            cout << endl << endl << "is: " << endl << endl << endl;
            printMatrix(result, m, k);

            cout << endl;
            system("pause");
            system("cls");

            cout << "Do you want to save the result matrix to a file?" << endl;
            cout << "Type 1 for yes, 2 for no: ";

            cin >> option;
            if( option == 1 )
            {
                system("cls");

                cout << "WARNING: if the file already exists, it will be overwritten." << endl << endl;

                char newFilename[256];
                cout << "Enter the name for the new file: ";
                scanf("%255s", newFilename);
                writeMatrixToFile(result, m, k, newFilename);
            }

            free(mat);
            free(mat2);
            free(result);
            break;

        case SEL:

            system("cls");

            cout << "Read the matrices from a file? (if not, go back to menu)" << endl;
            cout << "Type 1 for yes, 2 for no: ";

            cin >> option;


            double * bVector, * sel;
            int mVec, nVec;
            // Read from file
            if( option == 1 )
            {
                system("cls");
                cout << "Enter the name of the file holding the first matrix (with extension): ";
                char filename[256];

                scanf("%255s", filename);

                sel = readMatrixFromFile(filename, m, n);

                system("cls");
                cout << "Enter the name of the file holding the bVector (with extension): ";

                scanf("%255s", filename);

                bVector = readMatrixFromFile(filename, mVec, nVec);

                cout << endl << endl << "The matrix read is:" << endl << endl;
                printMatrix(sel, m, n);

                cout << endl << endl << "The B-vector read is:" << endl << endl;
                printMatrix(bVector, nVec, mVec);

                cout << endl;
                system("pause");

            }   // end of file reading

            // Read manually or randomly
            if( option == 2 )
            {
                system("cls");
                cout << "NOTE: for file reading, follow this format:" << endl;
                cout << "Example matrix: " << endl << endl;
                cout << "3 5 7" << endl;
                cout << "5 0 3" << endl;
                cout << "9 7 8" << endl;
                cout << endl << endl << "Enter it like so in the file." << endl;
                system("pause");
                system("cls");

                cout << endl << endl << "\t\t\tMATRIX OPERATIONS" << endl << endl << endl;
                printMenu();

                int option;
                cout << endl << endl << "Option: ";
                cin >> option;

                printSubMenu(option);
            }

            oldReduce(sel, bVector, m, n);
            result = resolve(sel, bVector, n);

            cout << "solution vector" << endl;
            printMatrix(result, nVec, mVec);

            free(mat);
            free(bVector);
            free(result);
            break;

    } // end of switch
}


