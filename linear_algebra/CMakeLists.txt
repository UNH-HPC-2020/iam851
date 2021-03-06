
cmake_minimum_required (VERSION 3.11)

project(LinearAlgebra)

enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# If we knew GoogleTest is installed, we can just use the following single line
find_package(GTest)

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
  

add_subdirectory(c) 
add_subdirectory(cxx) 

