
cmake_minimum_required (VERSION 3.9)

project (MPI_Hello)

# Disable MPI-2 C++ bindings
set(MPI_CXX_SKIP_MPICXX ON)
find_package(MPI)

add_executable(mpi_hello mpi_hello.cxx)
target_link_libraries(mpi_hello PRIVATE MPI::MPI_CXX)

add_executable(mpi_message mpi_message.cxx)
target_link_libraries(mpi_message PRIVATE MPI::MPI_CXX)

add_executable(test_integration test_integration.cxx)


