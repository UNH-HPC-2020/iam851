
#include <iostream>
#include <mpi.h>

int main(int argc, char** argv)
{
  int rank, size;

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int test = 0;

  if (rank == 0) {
    test = 99;

    for (int r = 1; r < size; r++) {
      MPI_Send(&test, 1, MPI_INT, r, 123, MPI_COMM_WORLD);
    }
  } else {
    MPI_Recv(&test, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  std::cout << "Hi there " << rank << "/" << size << " test = " << test << "\n";

  MPI_Finalize();
  return 0;
}
