
#include <iostream>
#include <omp.h>

// ----------------------------------------------------------------------
// main

int main(int argc, char** argv)
{
  std::cout << "Hi, just starting\n";

#pragma omp parallel
  {
    int thread = omp_get_thread_num();
    int n_threads = omp_get_num_threads();
    std::cout << "Hi, I'm thread " << thread << " of " << n_threads << "\n";
  }

  std::cout << "I'm about to be done.\n";
  return 0;
}
