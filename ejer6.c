#include "stdio.h"
#include "stdlib.h"
#include "mpi.h"
#include "time.h"

#define NUM_SAMPLES 1000000

int main(int argc, char *argv[]) {
    int ran, tam;
    int cl = 0;
    int cg;
    double pi;
    unsigned int t = time(NULL);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &ran);
    MPI_Comm_size(MPI_COMM_WORLD, &tam);

    for (int i = 0; i < NUM_SAMPLES / tam; i++) {
        double x = (double)rand_r(&t) / RAND_MAX;
        double y = (double)rand_r(&t) / RAND_MAX;

        if (x * x + y * y <= 1.0) {
            cl++;
        }
    }
    MPI_Reduce(&cl, &cg, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (ran == 0) {
        pi = 4.0 * cg / (double)NUM_SAMPLES;
        printf("Valor estimado de pi: %f\n", pi);
    }

    MPI_Finalize();
    return 0;
}