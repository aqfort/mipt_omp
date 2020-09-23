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
void algorithm_6(const int& size, int** A, int** B, int** C);   // strassen parallel

int get_2_n_size(int size);
void sum_matrix(const int& size, int** A, int** B, int** C);
void sub_matrix(const int& size, int** A, int** B, int** C);
void mul_matrix(const int& size, int** A, int** B, int** C);
void split(const int& size_half, int** A, int** A_11, int** A_12, int** A_21, int** A_22);
void joint(const int& size_half, int** A, int** A_11, int** A_12, int** A_21, int** A_22);
int** get_mem(const int& size);
void del_mem(const int& size, int** A);

int get_2_n_size_parallel(int size);
void sum_matrix_parallel(const int& size, int** A, int** B, int** C);
void sub_matrix_parallel(const int& size, int** A, int** B, int** C);
void mul_matrix_parallel(const int& size, int** A, int** B, int** C);
void split_parallel(const int& size_half, int** A, int** A_11, int** A_12, int** A_21, int** A_22);
void joint_parallel(const int& size_half, int** A, int** A_11, int** A_12, int** A_21, int** A_22);
int** get_mem_parallel(const int& size);
void del_mem_parallel(const int& size, int** A);

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

    {
        cout << "let\'s look at A and B:" << endl;
        print_matrix(size, A);
        cout << endl;
        print_matrix(size, B);
    }

    cout << endl << "algorithm" << endl;










    reset_matrix(size, C);

    time_1 = omp_get_wtime();
    algorithm_1(size, A, B, C);
    time_2 = omp_get_wtime();

    cout << "\n\nresult:\n\n";

    print_matrix(size, C);

    cout << "dumb algorithm spent:\n" << fixed << setprecision(7) << time_2 - time_1 << " sec" << endl;
    // cout << fixed << setprecision(7) << time_2 - time_1 << endl;
    cout.unsetf(ios::fixed | ios::scientific);
    cout.precision(6);










    // reset_matrix(size, C);

    // time_1 = omp_get_wtime();
    // algorithm_2(size, A, B, C);
    // time_2 = omp_get_wtime();

    // // cout << "\n\nresult:\n\n";

    // // print_matrix(size, C);

    // // cout << "dumb parallel algorithm spent:\n" << fixed << setprecision(7) << time_2 - time_1 << " sec" << endl;
    // cout << fixed << setprecision(7) << time_2 - time_1 << endl;
    // cout.unsetf(ios::fixed | ios::scientific);
    // cout.precision(6);










    // reset_matrix(size, C);

    // time_1 = omp_get_wtime();
    // algorithm_3(size, A, B, C);
    // time_2 = omp_get_wtime();

    // // cout << "\n\nresult:\n\n";

    // // print_matrix(size, C);

    // // cout << "reordered algorithm spent\n" << fixed << setprecision(7) << time_2 - time_1 << " sec" << endl;
    // cout << fixed << setprecision(7) << time_2 - time_1 << endl;
    // cout.unsetf(ios::fixed | ios::scientific);
    // cout.precision(6);










    // reset_matrix(size, C);

    // time_1 = omp_get_wtime();
    // algorithm_4(size, A, B, C);
    // time_2 = omp_get_wtime();

    // // cout << "\n\nresult:\n\n";

    // // print_matrix(size, C);

    // // cout << "reordered parallel algorithm spent:\n" << fixed << setprecision(7) << time_2 - time_1 << " sec" << endl;
    // cout << fixed << setprecision(7) << time_2 - time_1 << endl;
    // cout.unsetf(ios::fixed | ios::scientific);
    // cout.precision(6);










    // reset_matrix(size, C);

    // time_1 = omp_get_wtime();
    // algorithm_5(size, A, B, C);
    // time_2 = omp_get_wtime();
    
    // // cout << "\n\nresult:\n\n";

    // // print_matrix(size, C);

    // // cout << "strassen algorithm spent:\n" << fixed << setprecision(7) << time_2 - time_1 << " sec" << endl;
    // cout << fixed << setprecision(7) << time_2 - time_1 << endl;
    // cout.unsetf(ios::fixed | ios::scientific);
    // cout.precision(6);










    // reset_matrix(size, C);

    // time_1 = omp_get_wtime();
    // algorithm_6(size, A, B, C);
    // time_2 = omp_get_wtime();

    // // cout << "\n\nresult:\n\n";

    // // print_matrix(size, C);

    // // cout << "strassen parallel algorithm spent:\n" << fixed << setprecision(7) << time_2 - time_1 << " sec" << endl;
    // cout << fixed << setprecision(7) << time_2 - time_1 << endl;
    // cout.unsetf(ios::fixed | ios::scientific);
    // cout.precision(6);










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
    if (size < 48) {
        algorithm_3(size, A, B, C);
        return;
    }

    int i, j;

    int size_optimal = get_2_n_size(size);

    int** A_new;
    int** B_new;
    int** C_new;

    A_new = get_mem(size_optimal);
    B_new = get_mem(size_optimal);
    C_new = get_mem(size_optimal);



    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            A_new[i][j] = A[i][j];
            B_new[i][j] = B[i][j];
        }
    }

    for (i = 0; i < size_optimal; i++)
    {
        for (j = size; j < size_optimal; j++)
        {
            A_new[i][j] = 0;
            B_new[i][j] = 0;
            C_new[i][j] = 0;
        }
    }

    for (i = size; i < size_optimal; i++)
    {
        for (j = 0; j < size; j++)
        {
            A_new[i][j] = 0;
            B_new[i][j] = 0;
            C_new[i][j] = 0;
        }
    }



    mul_matrix(size_optimal, A_new, B_new, C_new);



    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            C[i][j] = C_new[i][j];
        }
    }



    del_mem(size_optimal, A_new);
    del_mem(size_optimal, B_new);
    del_mem(size_optimal, C_new);
}

int get_2_n_size(int size)
{
    int result = 1;

    while (result < size)
    {
        result *= 2;
    }

    return result;
}

void sum_matrix(const int& size, int** A, int** B, int** C)
{
    int i, j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void sub_matrix(const int& size, int** A, int** B, int** C)
{
    int i, j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void mul_matrix(const int& size, int** A, int** B, int** C)
{
    if (size < 48)
    {
        algorithm_3(size, A, B, C);
        return;
    }

    int i, j, k;
    int size_half = size / 2;

    if (size < 2)
    {
        C[0][0] = A[0][0] * B[0][0];
    }

    else
    {
        int** A_11;
        int** A_12;
        int** A_21;
        int** A_22;

        int** B_11;
        int** B_12;
        int** B_21;
        int** B_22;

        int** C_11;
        int** C_12;
        int** C_21;
        int** C_22;

        A_11 = get_mem(size_half);
        A_12 = get_mem(size_half);
        A_21 = get_mem(size_half);
        A_22 = get_mem(size_half);

        B_11 = get_mem(size_half);
        B_12 = get_mem(size_half);
        B_21 = get_mem(size_half);
        B_22 = get_mem(size_half);

        C_11 = get_mem(size_half);
        C_12 = get_mem(size_half);
        C_21 = get_mem(size_half);
        C_22 = get_mem(size_half);



        split(size_half, A, A_11, A_12, A_21, A_22);
        split(size_half, B, B_11, B_12, B_21, B_22);
        split(size_half, C, C_11, C_12, C_21, C_22);

        int** P_1;
        int** P_2;
        int** P_3;
        int** P_4;
        int** P_5;
        int** P_6;
        int** P_7;

        P_1 = get_mem(size_half);
        P_2 = get_mem(size_half);
        P_3 = get_mem(size_half);
        P_4 = get_mem(size_half);
        P_5 = get_mem(size_half);
        P_6 = get_mem(size_half);
        P_7 = get_mem(size_half);

        int** temp_1;
        int** temp_2;

        temp_1 = get_mem(size_half);
        temp_2 = get_mem(size_half);

        {
            sum_matrix(size_half, A_11, A_22, temp_1);
            sum_matrix(size_half, B_11, B_22, temp_2);
            mul_matrix(size_half, temp_1, temp_2, P_1);

            sum_matrix(size_half, A_21, A_22, temp_1);
            mul_matrix(size_half, temp_1, B_11, P_2);

            sub_matrix(size_half, B_12, B_22, temp_2);
            mul_matrix(size_half, A_11, temp_2, P_3);

            sub_matrix(size_half, B_21, B_11, temp_2);
            mul_matrix(size_half, A_22, temp_2, P_4);

            sum_matrix(size_half, A_11, A_12, temp_1);
            mul_matrix(size_half, temp_1, B_22, P_5);

            sub_matrix(size_half, A_21, A_11, temp_1);
            sum_matrix(size_half, B_11, B_12, temp_2);
            mul_matrix(size_half, temp_1, temp_2, P_6);

            sub_matrix(size_half, A_12, A_22, temp_1);
            sum_matrix(size_half, B_21, B_22, temp_2);
            mul_matrix(size_half, temp_1, temp_2, P_7);

            

            sum_matrix(size_half, P_1, P_4, temp_1);
            sub_matrix(size_half, temp_1, P_5, temp_2);
            sum_matrix(size_half, temp_2, P_7, C_11);

            sum_matrix(size_half, P_3, P_5, C_12);

            sum_matrix(size_half, P_2, P_4, C_21);

            sub_matrix(size_half, P_1, P_2, temp_1);
            sum_matrix(size_half, temp_1, P_3, temp_2);
            sum_matrix(size_half, temp_2, P_6, C_22);
        }

        del_mem(size_half, temp_1);
        del_mem(size_half, temp_2);

        del_mem(size_half, P_1);
        del_mem(size_half, P_2);
        del_mem(size_half, P_3);
        del_mem(size_half, P_4);
        del_mem(size_half, P_5);
        del_mem(size_half, P_6);
        del_mem(size_half, P_7);

        // joint(size_half, A, A_11, A_12, A_21, A_22);    //
        // joint(size_half, B, B_11, B_12, B_21, B_22);    //
        joint(size_half, C, C_11, C_12, C_21, C_22);



        del_mem(size_half, A_11);
        del_mem(size_half, A_12);
        del_mem(size_half, A_21);
        del_mem(size_half, A_22);

        del_mem(size_half, B_11);
        del_mem(size_half, B_12);
        del_mem(size_half, B_21);
        del_mem(size_half, B_22);

        del_mem(size_half, C_11);
        del_mem(size_half, C_12);
        del_mem(size_half, C_21);
        del_mem(size_half, C_22);
    }   
}

void split(const int& size_half, int** A, int** A_11, int** A_12, int** A_21, int** A_22)
{
    int i, j;

    for (i = 0; i < size_half; i++)
    {
        for (j = 0; j < size_half; j++)
        {
            A_11[i][j] = A[i][j];
            A_12[i][j] = A[i][j + size_half];
            A_21[i][j] = A[i + size_half][j];
            A_22[i][j] = A[i + size_half][j + size_half];
        }
    }
}

void joint(const int& size_half, int** A, int** A_11, int** A_12, int** A_21, int** A_22)
{
    int i, j;

    for (i = 0; i < size_half; i++)
    {
        for (j = 0; j < size_half; j++)
        {
            A[i][j] = A_11[i][j];
            A[i][j + size_half] = A_12[i][j];
            A[i + size_half][j] = A_21[i][j];
            A[i + size_half][j + size_half] = A_22[i][j];
        }
    }
}

int** get_mem(const int& size)
{
    int** A = new int*[size];
    for (int i = 0; i < size; i++)
    {
        A[i] = new int[size];
    }

    return A;
}

void del_mem(const int& size, int** A)
{
    for (int i = 0; i < size; i++)
    {
        delete[] A[i];
    }
    delete[] A;
}


















void algorithm_6(const int& size, int** A, int** B, int** C)
{
    int i, j;

    int size_optimal = get_2_n_size_parallel(size);

    int** A_new;
    int** B_new;
    int** C_new;

    A_new = get_mem_parallel(size_optimal);
    B_new = get_mem_parallel(size_optimal);
    C_new = get_mem_parallel(size_optimal);


    // #pragma omp parallel for            \
    // shared(A, B, A_new, B_new)
    #pragma omp parallel for collapse(2)
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            A_new[i][j] = A[i][j];
            B_new[i][j] = B[i][j];
        }
    }

    // #pragma omp parallel for            \
    // shared(A_new, B_new, C_new)
    #pragma omp parallel for collapse(2)
    for (i = 0; i < size_optimal; i++)
    {
        for (j = size; j < size_optimal; j++)
        {
            A_new[i][j] = 0;
            B_new[i][j] = 0;
            C_new[i][j] = 0;
        }
    }

    // #pragma omp parallel for            \
    // shared(A_new, B_new, C_new)
    #pragma omp parallel for collapse(2)
    for (i = size; i < size_optimal; i++)
    {
        for (j = 0; j < size; j++)
        {
            A_new[i][j] = 0;
            B_new[i][j] = 0;
            C_new[i][j] = 0;
        }
    }



    mul_matrix_parallel(size_optimal, A_new, B_new, C_new);



    // #pragma omp parallel for    \
    // shared(C, C_new)            \
    // private(size, i, j)         \
    // schedule(guided)
    #pragma omp parallel for collapse(2)
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            C[i][j] = C_new[i][j];
        }
    }



    del_mem_parallel(size_optimal, A_new);
    del_mem_parallel(size_optimal, B_new);
    del_mem_parallel(size_optimal, C_new);
}

int get_2_n_size_parallel(int size)
{
    int result = 1;

    while (result < size)
    {
        result *= 2;
    }

    return result;
}

void sum_matrix_parallel(const int& size, int** A, int** B, int** C)
{
    int i, j;

    // #pragma omp parallel for    \
    // shared(A, B, C)             \
    // private(size, i, j)         \
    // schedule(guided)
    // #pragma omp parallel for collapse(2)
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void sub_matrix_parallel(const int& size, int** A, int** B, int** C)
{
    int i, j;

    // #pragma omp parallel for    \
    // shared(A, B, C)             \
    // private(size, i, j)         \
    // schedule(guided)
    // #pragma omp parallel for collapse(2)
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void mul_matrix_parallel(const int& size, int** A, int** B, int** C)
{
    int i, j, k;
    int size_half = size / 2;

    if (size < 48)
    {
        algorithm_3(size, A, B, C);
        return;
    }

    else
    {
        int** A_11;
        int** A_12;
        int** A_21;
        int** A_22;

        int** B_11;
        int** B_12;
        int** B_21;
        int** B_22;

        int** C_11;
        int** C_12;
        int** C_21;
        int** C_22;

        // #pragma omp sections
        {
            // #pragma omp section
            {
                A_11 = get_mem_parallel(size_half);
                A_12 = get_mem_parallel(size_half);
                A_21 = get_mem_parallel(size_half);
                A_22 = get_mem_parallel(size_half);
            }

            // #pragma omp section
            {
                B_11 = get_mem_parallel(size_half);
                B_12 = get_mem_parallel(size_half);
                B_21 = get_mem_parallel(size_half);
                B_22 = get_mem_parallel(size_half);
            }

            // #pragma omp section
            {
                C_11 = get_mem_parallel(size_half);
                C_12 = get_mem_parallel(size_half);
                C_21 = get_mem_parallel(size_half);
                C_22 = get_mem_parallel(size_half);
            }
        }



        split_parallel(size_half, A, A_11, A_12, A_21, A_22);
        split_parallel(size_half, B, B_11, B_12, B_21, B_22);
        split_parallel(size_half, C, C_11, C_12, C_21, C_22);

        int** P_1;
        int** P_2;
        int** P_3;
        int** P_4;
        int** P_5;
        int** P_6;
        int** P_7;

        // #pragma omp sections
        {
            // #pragma omp section
            P_1 = get_mem_parallel(size_half);
            // #pragma omp section
            P_2 = get_mem_parallel(size_half);
            // #pragma omp section
            P_3 = get_mem_parallel(size_half);
            // #pragma omp section
            P_4 = get_mem_parallel(size_half);
            // #pragma omp section
            P_5 = get_mem_parallel(size_half);
            // #pragma omp section
            P_6 = get_mem_parallel(size_half);
            // #pragma omp section
            P_7 = get_mem_parallel(size_half);
        }

        int** temp_1;
        int** temp_2;

        temp_1 = get_mem_parallel(size_half);
        temp_2 = get_mem_parallel(size_half);

        {
        
            sum_matrix_parallel(size_half, A_11, A_22, temp_1);
            sum_matrix_parallel(size_half, B_11, B_22, temp_2);
            mul_matrix_parallel(size_half, temp_1, temp_2, P_1);
    
            sum_matrix_parallel(size_half, A_21, A_22, temp_1);
            mul_matrix_parallel(size_half, temp_1, B_11, P_2);

            sub_matrix_parallel(size_half, B_12, B_22, temp_1);
            mul_matrix_parallel(size_half, A_11, temp_1, P_3);
    
            sub_matrix_parallel(size_half, B_21, B_11, temp_1);
            mul_matrix_parallel(size_half, A_22, temp_1, P_4);

            sum_matrix_parallel(size_half, A_11, A_12, temp_1);
            mul_matrix_parallel(size_half, temp_1, B_22, P_5);

            sub_matrix_parallel(size_half, A_21, A_11, temp_1);
            sum_matrix_parallel(size_half, B_11, B_12, temp_2);
            mul_matrix_parallel(size_half, temp_1, temp_2, P_6);

            sub_matrix_parallel(size_half, A_12, A_22, temp_1);
            sum_matrix_parallel(size_half, B_21, B_22, temp_2);
            mul_matrix_parallel(size_half, temp_1, temp_2, P_7);

                
            
            sum_matrix_parallel(size_half, P_1, P_4, temp_1);
            sub_matrix_parallel(size_half, temp_1, P_5, temp_2);
            sum_matrix_parallel(size_half, temp_2, P_7, C_11);

            sum_matrix_parallel(size_half, P_3, P_5, C_12);

            sum_matrix_parallel(size_half, P_2, P_4, C_21);
    
            sub_matrix_parallel(size_half, P_1, P_2, temp_1);
            sum_matrix_parallel(size_half, temp_1, P_3, temp_2);
            sum_matrix_parallel(size_half, temp_2, P_6, C_22);
        }


        del_mem_parallel(size_half, temp_1);
        del_mem_parallel(size_half, temp_2);

        // #pragma omp sections
        {
            // #pragma omp section
            del_mem_parallel(size_half, P_1);
            // #pragma omp section
            del_mem_parallel(size_half, P_2);
            // #pragma omp section
            del_mem_parallel(size_half, P_3);
            // #pragma omp section
            del_mem_parallel(size_half, P_4);
            // #pragma omp section
            del_mem_parallel(size_half, P_5);
            // #pragma omp section
            del_mem_parallel(size_half, P_6);
            // #pragma omp section
            del_mem_parallel(size_half, P_7);
        }

        joint_parallel(size_half, C, C_11, C_12, C_21, C_22);



        // #pragma omp sections
        {
            // #pragma omp section
            {
                del_mem_parallel(size_half, A_11);
                del_mem_parallel(size_half, A_12);
                del_mem_parallel(size_half, A_21);
                del_mem_parallel(size_half, A_22);
            }

            // #pragma omp section
            {
                del_mem_parallel(size_half, B_11);
                del_mem_parallel(size_half, B_12);
                del_mem_parallel(size_half, B_21);
                del_mem_parallel(size_half, B_22);
            }

            // #pragma omp section
            {
                del_mem_parallel(size_half, C_11);
                del_mem_parallel(size_half, C_12);
                del_mem_parallel(size_half, C_21);
                del_mem_parallel(size_half, C_22);
            }
        }
    }   
}

void split_parallel(const int& size_half, int** A, int** A_11, int** A_12, int** A_21, int** A_22)
{
    int i, j;

    // #pragma omp parallel for collapse(2)
    for (i = 0; i < size_half; i++)
    {
        for (j = 0; j < size_half; j++)
        {
            A_11[i][j] = A[i][j];
            A_12[i][j] = A[i][j + size_half];
            A_21[i][j] = A[i + size_half][j];
            A_22[i][j] = A[i + size_half][j + size_half];
        }
    }
}

void joint_parallel(const int& size_half, int** A, int** A_11, int** A_12, int** A_21, int** A_22)
{
    int i, j;

    // #pragma omp parallel for collapse(2)
    for (i = 0; i < size_half; i++)
    {
        for (j = 0; j < size_half; j++)
        {
            A[i][j] = A_11[i][j];
            A[i][j + size_half] = A_12[i][j];
            A[i + size_half][j] = A_21[i][j];
            A[i + size_half][j + size_half] = A_22[i][j];
        }
    }
}

int** get_mem_parallel(const int& size)
{
    int** A = new int*[size];
    int i;

    for (i = 0; i < size; i++)
    {
        A[i] = new int[size];
    }

    return A;
}

void del_mem_parallel(const int& size, int** A)
{
    int i;

    for (i = 0; i < size; i++)
    {
        delete[] A[i];
    }
    delete[] A;
}
