#include <iostream>
#include <stdio.h>
#include <omp.h>

using namespace std;

int main()
{
    int i;
    int my_id;

    // cout << "4 threads are used" << endl << endl;

    // omp_set_num_threads(4);

    cout << "let's check how " << endl << 
        "  1) static" << endl << 
        "  2) dynamic 1" << endl << 
        "  3) dynamic 2" << endl << 
        "  4) guided" << endl <<
        "    work" << endl;



    cout << endl << "static" << endl << endl;

    #pragma omp parallel for    \
    private(i, my_id)           \
    schedule(static)
    for (i = 0; i < 32; i++)
    {
        my_id = omp_get_thread_num();
        printf("thread (%02d) --- %02d\n", my_id, i);
    }



    cout << endl << "dynamic 1" << endl << endl;

    #pragma omp parallel for    \
    private(i, my_id)           \
    schedule(dynamic)
    for (i = 0; i < 32; i++)
    {
        my_id = omp_get_thread_num();
        printf("thread (%02d) --- %02d\n", my_id, i);
    }



    cout << endl << "dynamic 2" << endl << endl;

    #pragma omp parallel for    \
    private(i, my_id)           \
    schedule(dynamic, 2)
    for (i = 0; i < 32; i++)
    {
        my_id = omp_get_thread_num();
        printf("thread (%02d) --- %02d\n", my_id, i);
    }



    cout << endl << "guided" << endl << endl;

    #pragma omp parallel for    \
    private(i, my_id)           \
    schedule(guided)
    for (i = 0; i < 32; i++)
    {
        my_id = omp_get_thread_num();
        printf("thread (%02d) --- %02d\n", my_id, i);
    }



    cout << endl << "that\'s all we\'ve got" << endl;

    return 0;
}
