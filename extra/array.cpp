#include <iostream>
#include <iomanip>
#include <omp.h>

// compile: g++ +.cpp -fopenmp

using namespace std;

int main() {
    int i = 0;
    int N = 100000;
    double a[N];
    double b[N];

    double time_1, time_2;

    for (i = 0; i < N; i++) {
        a[i] = i + 1;
    }



    b[0] = a[0];
    b[N - 1] = a[N - 1];



    cout << "max threads number: " << omp_get_max_threads() << endl;

    omp_set_num_threads(8);



    time_1 = omp_get_wtime();

    #pragma omp parallel for    \
    private(i)
    for (i = 2; i < N; i++) {
        if (i == 2 && omp_get_thread_num() == 0) {
            cout << "now threads num: " << omp_get_num_threads() << endl;
        }
        b[i - 1] = (a[i - 2] * a[i - 1] * a[i]) / 3;
    }

    time_2 = omp_get_wtime();

    cout << "time spent: " << fixed << setprecision(7) << time_2 - time_1 << " sec" << endl;
    cout.unsetf(ios::fixed | ios::scientific);
    cout.precision(6);



    // for (i = 0; i < N; i++) {
    //     cout << b[i] << endl;
    // }

    return 0;
}