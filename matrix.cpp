#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <functional>
#include <string>
#include <stdexcept>
#include <stdio.h>
#include <omp.h>

using namespace std;

void get_matrix_size_from_cin(int& number);
int parse_int_from_string(const string& input);
void init_matrix(const int& size, int** A);
void print_matrix(const int& size, int** matrix);

default_random_engine generator;
uniform_int_distribution<int> distribution(-100, 100);

int main()
{
    int i, j, k;
    int size;

    cout << "number of threads is in range [1, " << omp_get_max_threads() << "]" << endl << 
        "let\'s use max number of threads" << endl << endl;

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

    print_matrix(size, A);
    cout << endl;
    print_matrix(size, B);




    // #pragma omp parallel for    \
    // shared(A, B, C)             \
    // private(i, j, k)
    // for (i = 0; i < size; i++)
    // {
    //     for (j = 0; j < size; j++)
    //     {
    //         C[i][j] = 0;
    //         for (k = 0; k < size; k++)
    //         {
    //             C[i][j] += A[i][k] * B[k][j];
    //         }
    //     }
    // }





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
    // auto dice = bind(distribution, generator);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            A[i][j] = distribution(generator);

            // A[i][j] = dice() + dice() + dice();
        }
    }
}

void print_matrix(const int& size, int** matrix)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << setw(5) << matrix[i][j] << ' ';
        }

        cout << endl;
    }
}
