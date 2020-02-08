#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
 
int l = 1;
int m = 5;
int N = 10;

 void histogram(int *a, int *h){
     for (int i=0; i<N; i++){
        h[a[i]]++;
     }
 }

int main(int argc, char *argv[])
{
    int world_rank, size;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    int* a = new int[N];

    srand (time(NULL));
    
    for (int i=0; i<N; i++){
        a[i] = rand()%m + l;
        printf("rank %d: a[%d]=%d\n", world_rank, i, a[i]);
    }
    
    
    int* h = new int[m+1];
    histogram(a,h);

    int *total;
    if (world_rank == 0){
        total = new int[m+1];
    }

    MPI_Reduce(h, total, m+1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0){
        for (int i=l; i<=m; i++){
            printf("h[%d] = %d\n", i, h[i]);
        }
    }


    MPI_Finalize();

}