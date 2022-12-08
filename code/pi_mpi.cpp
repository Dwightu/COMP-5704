#include <iostream>
#include "mpi.h"

using namespace std;
const int maxn = 1000000000; // The same as pi_openmp

MPI_Status status;
int main(int argc, char *argv[]) {
    int pCnt, pId, slaves, source, dest;
    int cnt, n, offset;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &pId);
    MPI_Comm_size(MPI_COMM_WORLD, &pCnt);

    slaves = pCnt - 1;
    offset = maxn / slaves;
    if(pId == 0) {
        for(dest = 1; dest <= slaves; dest++) {
            MPI_Send(&offset, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
            MPI_Send(&n, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
        }
        cnt = 0;
        for(int i = 1; i <= slaves; i++) {
            source = i;
            MPI_Recv(&offset, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
            MPI_Recv(&n, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
            cnt += n;
        }

        double pi = 4.0 * cnt / maxn;
        cout << "PI is " << pi << endl;
    }

    if(pId > 0) {
        source = 0;
        MPI_Recv(&offset, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&n, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
        n = 0;
        srand(time(NULL));
        for(int i = 0; i < offset; i++) {
            // generates points
            double x = (double)rand() / RAND_MAX;
            double y = (double)rand() / RAND_MAX;
            if(x * x + y * y <= 1)
                n++;
        }
        MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&n, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
