
#include <mpi.h>

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <vector>

int main(int argc, char** argv)
{
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (argc != 2) {
    if (rank == 0) {
      printf("Usage: %s <N>\nwhere <N> is the size of the message to exchange.\n",
	     argv[0]);
    }
    exit(1);
  }
  int N = atoi(argv[1]);

  assert(size == 2);

  std::vector<double> buf_send(N), buf_recv(N);

  if (rank == 0) {
    MPI_Send(buf_send.data(), N, MPI_DOUBLE, 1, 1234, MPI_COMM_WORLD);
    MPI_Recv(buf_recv.data(), N, MPI_DOUBLE, 1, 1234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  } else if (rank == 1) {
    MPI_Send(buf_send.data(), N, MPI_DOUBLE, 0, 1234, MPI_COMM_WORLD);
    MPI_Recv(buf_recv.data(), N, MPI_DOUBLE, 0, 1234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  MPI_Finalize();
  return 0;
}
