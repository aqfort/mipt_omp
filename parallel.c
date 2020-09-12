#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel

    {
        printf("hello\n");
    }

    return 0;
}
