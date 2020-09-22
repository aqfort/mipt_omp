#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <functional>
#include <string>
#include <stdexcept>
#include <stdio.h>
#include <omp.h>

// ok, size = 1000

// ijk: 6.2467250000
// ikj: 4.2248852000 --- optimal
// jik: 4.3990838000
// jki: 8.0499976000
// kij: 5.3461839000
// kji: 7.8837998000

using namespace std;

void get_matrix_size_from_cin(int& number);
int parse_int_from_string(const string& input);
void init_matrix(const int& size, int** A);
void print_matrix(const int& size, int** matrix);
void reset_matrix(const int& size, int** matrix);

void algorithm_1(const int& size, int** A, int** B, int** C);   // dumb
void algorithm_2(const int& size, int** A, int** B, int** C);   // parallel
void algorithm_3(const int& size, int** A, int** B, int** C);   // reordered dumb
void algorithm_4(const int& size, int** A, int** B, int** C);   // reordered parallel
void algorithm_5(const int& size, int** A, int** B, int** C);   // strassen

default_random_engine generator;
uniform_int_distribution<int> distribution(-100, 100);
// auto dice = bind(distribution, generator);

int main()
{
    int i, j, k;
    int size;
    double time_1, time_2;

    cout << "number of threads is in range [1, " << omp_get_max_threads() << "]" << endl << 
        "let\'s use max number of threads" << endl <<
        "stopwatch accuracy = " << fixed << setprecision(7) << omp_get_wtick() << " sec" << endl << endl;
    cout.unsetf(ios::fixed | ios::scientific);
    cout.precision(6);

    omp_set_num_threads(omp_get_max_threads());

    get_matrix_size_from_cin(size);

    cout << endl << "ok, size = " << size << endl << endl;

    int** A = new int*[size];
    for (i = 0; i < size; i++)
    {
        A[i] = new int[size];
    }

    int** B = new int*[size];
    for (i = 0; i < size; i++)
    {
        B[i] = new int[size];
    }

    int** C = new int*[size];
    for (i = 0; i < size; i++)
    {
        C[i] = new int[size];
    }

    init_matrix(size, A);
    init_matrix(size, B);

    // {
    //     cout << "let\'s look at A and B:" << endl;
    //     print_matrix(size, A);
    //     cout << endl;
    //     print_matrix(size, B);
    // }

    // cout << endl << "algorithm" << endl;





    reset_matrix(size, C);

    time_1 = omp_get_wtime();
    algorithm_1(size, A, B, C);
    time_2 = omp_get_wtime();

    cout << "dumb algorithm spent " << fixed << setprecision(7) << time_2 - time_1 << endl;
    cout.unsetf(ios::fixed | ios::scientific);
    cout.precision(6);





    reset_matrix(size, C);

    time_1 = omp_get_wtime();
    algorithm_2(size, A, B, C);
    time_2 = omp_get_wtime();

    cout << "dumb parallel algorithm spent " << fixed << setprecision(7) << time_2 - time_1 << endl;
    cout.unsetf(ios::fixed | ios::scientific);
    cout.precision(6);





    reset_matrix(size, C);

    time_1 = omp_get_wtime();
    algorithm_3(size, A, B, C);
    time_2 = omp_get_wtime();

    cout << "reordered algorithm spent " << fixed << setprecision(7) << time_2 - time_1 << endl;
    cout.unsetf(ios::fixed | ios::scientific);
    cout.precision(6);





    reset_matrix(size, C);

    time_1 = omp_get_wtime();
    algorithm_4(size, A, B, C);
    time_2 = omp_get_wtime();

    cout << "reordered parallel algorithm spent " << fixed << setprecision(7) << time_2 - time_1 << endl;
    cout.unsetf(ios::fixed | ios::scientific);
    cout.precision(6);





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

void get_matrix_size_from_cin(int& number)
{
    bool done = false;
    string string_input;

    while (!done)
    {
        cout << "enter size of matrix" << endl;

        getline(cin, string_input);

        try
        {
            number = parse_int_from_string(string_input);

            if (1 <= number)
            {
                done = true;
            }
            else
            {
                cerr << "size of matrix should be natural number" << endl;
            }
            
        }
        catch(const std::exception& e)
        {
            cerr << "enter number in proper format" << endl << 
                e.what() << endl;
        }
    }
}

int parse_int_from_string(const string& string_input)
{
    istringstream string_stream(string_input);
    bool flag = true;

    int data(0);

    while (string_stream.peek() == ' ')
    {
        string_stream.ignore(1);
    }

    flag = flag && (string_stream >> data);

    while (string_stream.peek() == ' ')
    {
        string_stream.ignore(1);
    }

    flag = flag && (string_stream.eof());

    if (!flag)
    {
        throw runtime_error("wrong input format: \"" + string_input + "\"");
    }

    return data;
}

void init_matrix(const int& size, int** A)
{
    int i, j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            A[i][j] = distribution(generator);

            // A[i][j] = dice() + dice() + dice();
        }
    }
}

void print_matrix(const int& size, int** matrix)
{
    int i, j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            cout << setw(5) << matrix[i][j] << ' ';
        }

        cout << endl;
    }
}

void reset_matrix(const int& size, int** matrix)
{
    int i, j;

    #pragma omp parallel for    \
    private(i, j)               \
    shared(matrix)              \
    schedule(guided)
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

void algorithm_1(const int& size, int** A, int** B, int** C)
{
    int i, j, k;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            for (k = 0; k < size; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void algorithm_2(const int& size, int** A, int** B, int** C)
{
    int i, j, k;

    #pragma omp parallel for    \
    shared(A, B, C)             \
    private(i, j, k)
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            for (k = 0; k < size; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void algorithm_3(const int& size, int** A, int** B, int** C)
{
    int i, j, k;

    for (i = 0; i < size; i++)
    {
        for (k = 0; k < size; k++)
        {
            for (j = 0; j < size; j++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void algorithm_4(const int& size, int** A, int** B, int** C)
{
    int i, j, k;

    #pragma omp parallel for    \
    shared(A, B, C)             \
    private(i, j, k)
    for (i = 0; i < size; i++)
    {
        for (k = 0; k < size; k++)
        {
            for (j = 0; j < size; j++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void algorithm_5(const int& size, int** A, int** B, int** C)
{

}
