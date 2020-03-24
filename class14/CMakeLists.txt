
cmake_minimum_required (VERSION 3.11)

project(LinearAlgebra)

enable_testing()

find_package(OpenMP)

# If we knew GoogleTest is installed, we can just use the following single line
find_package(GTest QUIET)

# but if not, we'll fetch it ourselves
if (NOT GTEST_FOUND)
  include(FetchContent)
  FetchContent_Declare(googletest
    GIT_REPOSITORY    https://github.com/google/googletest.git
    GIT_TAG           release-1.8.0
    )
  #FetchContent_MakeAvailable(googletest)
  FetchContent_GetProperties(googletest)
  if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
  endif()
  
  add_library(GTest::GTest INTERFACE IMPORTED)
  target_include_directories(GTest::GTest INTERFACE "${googletest_SOURCE_DIR}/googletest/include")
  target_link_libraries(GTest::GTest INTERFACE gtest)
  
  add_library(GTest::Main INTERFACE IMPORTED)
  target_link_libraries(GTest::Main INTERFACE gtest_main)
endif()

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
  

add_executable(test_integration test_integration.cxx)
if (OpenMP_CXX_FOUND)
  target_link_libraries(test_integration PRIVATE OpenMP::OpenMP_CXX)
endif()

add_executable(test_average test_average.cxx)
target_link_libraries(test_average PRIVATE xtensor)
if (OpenMP_CXX_FOUND)
  target_link_libraries(test_average PRIVATE OpenMP::OpenMP_CXX)
endif()

# This is how we could use OpenMP in C if we wanted to
# if (OpenMP_C_FOUND)
#   target_link_libraries(<target> PRIVATE OpenMP::OpenMP_C)
# endif()

# This is how we could use OpenMP in Fortran if we wanted to
# if (OpenMP_Fortran_FOUND)
#   target_link_libraries(<target> PRIVATE OpenMP::OpenMP_Fortran)
# endif()

if (OpenMP_CXX_FOUND)
  add_executable(test_openmp test_openmp.cxx)
  target_link_libraries(test_openmp PRIVATE OpenMP::OpenMP_CXX)
endif()
