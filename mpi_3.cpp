#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>
 
int l = 1;
int m = 5;
int N = 10;

int main(int argc, char *argv[])
{
    int world_rank, size;

    int *a;
    int *h;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    a = new int[N];
    
    for (int i=0; i<N; i++){
        a[i] = (l+i+world_rank)%(m-l) + l;
    }
    
    h = new int[m+1];
    for (int i=0; i<=m; i++){
        h[i] = 0;
    }
     for (int i=0; i<N; i++){
        h[a[i]]++;
     }

     for (int i=l; i<=m; i++){
         printf("rank %d: h[%d]=%d\n", world_rank, i, h[i]);
     }

    int *total;
    if (world_rank == 0){
        total = new int[m+1];
    }

    MPI_Reduce(h, total, m+1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0){
        for (int i=l; i<=m; i++){
            printf("h[%d] = %d\n", i, total[i]);
        }
    }

    MPI_Finalize();

}