#include <stdio.h>
#include <string.h>
#include <mpi.h>
 
int main(int argc, char *argv[])
{
    int world_rank;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int color = world_rank % 4;

    MPI_Comm mod_comm;
    MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &mod_comm);

    int row_rank, row_size;
    MPI_Comm_rank(mod_comm, &row_rank);
    MPI_Comm_size(mod_comm, &row_size);

    printf("WORLD RANK: %d \t ROW RANK/SIZE: %d/%d\n",
	    world_rank, row_rank, row_size);

    MPI_Comm_free(&mod_comm);

    MPI_Finalize();

}