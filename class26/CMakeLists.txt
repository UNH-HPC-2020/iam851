
cmake_minimum_required (VERSION 3.11)

project(Class26)

enable_testing()

find_package(MPI REQUIRED)

add_library(params params.c)
target_link_libraries(params PUBLIC MPI::MPI_CXX)

add_executable(mpi_pingpong mpi_pingpong.cxx)
target_link_libraries(mpi_pingpong PRIVATE params)
