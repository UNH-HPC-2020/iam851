
cmake_minimum_required (VERSION 3.11)

project(Derivative)

enable_testing()

find_package(MPI REQUIRED)

find_package(xtl QUIET)
if (NOT xtl_FOUND)
  include(FetchContent)
  FetchContent_Declare(xtl
    GIT_REPOSITORY    https://github.com/xtensor-stack/xtl.git
    )
  #FetchContent_MakeAvailable(xtl)
  FetchContent_GetProperties(xtl)
  if (NOT xtl_POPULATED)
    FetchContent_Populate(xtl)
    add_subdirectory(${xtl_SOURCE_DIR} ${xtl_BINARY_DIR} EXCLUDE_FROM_ALL)
  endif()
endif()
  
find_package(xtensor QUIET)
if (NOT xtensor_FOUND)
  include(FetchContent)
  FetchContent_Declare(xtensor
    GIT_REPOSITORY    https://github.com/xtensor-stack/xtensor.git
    )
  #FetchContent_MakeAvailable(xtensor)
  FetchContent_GetProperties(xtensor)
  if (NOT xtensor_POPULATED)
    FetchContent_Populate(xtensor)
    add_subdirectory(${xtensor_SOURCE_DIR} ${xtensor_BINARY_DIR} EXCLUDE_FROM_ALL)
  endif()
endif()
  

add_executable(test_heat_eqn test_heat_eqn.cxx)
target_link_libraries(test_heat_eqn PRIVATE m xtensor MPI::MPI_CXX)

add_executable(heat_eqn_solve heat_eqn_solve.cxx)
target_link_libraries(heat_eqn_solve PRIVATE m xtensor MPI::MPI_CXX)

add_executable(mpi_dl_test mpi_dl_test.cxx)
target_link_libraries(mpi_dl_test PRIVATE MPI::MPI_CXX)
