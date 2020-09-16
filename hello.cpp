#include <iostream>
#include <cstdio>
#include <omp.h>

using namespace std;

int main()
{
    int threads;
    int my_id;

    threads = omp_get_max_threads();
    cout << "max number of threads is " << threads << 
        ", let\'s use it" << endl << endl;

    omp_set_num_threads(threads);

    #pragma omp parallel    \
    private(threads, my_id)
    {
        threads = omp_get_num_threads();
        my_id = omp_get_thread_num();
        printf("number of threads = (%02d), hello from (%02d)\n", threads, my_id);
    }

    return 0;
}
