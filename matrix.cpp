#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <stdio.h>
#include <omp.h>

using namespace std;



int main()
{
    int i, j, k;
    int size;
    ifstream input("input.txt");

    cout << "number of threads is in range [1, " << omp_get_max_threads() << "]" << endl;
    cout << "let\'s use max number of threads" << endl << endl;

    omp_set_num_threads(omp_get_max_threads());

    input >> size;

    cout << "size = " << size << endl << endl;

    double** A = new double*[size];
    for (i = 0; i < size; i++)
    {
        A[i] = new double[size];
    }

    double** B = new double*[size];
    for (i = 0; i < size; i++)
    {
        B[i] = new double[size];
    }

    double** C = new double*[size];
    for (i = 0; i < size; i++)
    {
        C[i] = new double[size];
    }





    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            input >> A[i][j];
        }
    }

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            input >> B[i][j];
        }
    }

    #pragma omp parallel for    \
    shared(A, B, C)             \
    private(i, j, k)
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            C[i][j] = 0;
            for (k = 0; k < size; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    cout << "A * B = " << endl << endl;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            cout << setw(5) << C[i][j] << ' ';
        }

        cout << endl;
    }
    





    for (i = 0; i < size; i++)
    {
        delete[] A[i];
    }
    delete[] A;

    for (i = 0; i < size; i++)
    {
        delete[] B[i];
    }
    delete[] B;

    for (i = 0; i < size; i++)
    {
        delete[] C[i];
    }
    delete[] C;

    return 0;
}
