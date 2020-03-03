
#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <cassert>
#include <iostream>
#include <vector>

//#define BOUNDS_CHECK

class vector
{
public:
  vector(int n);
  vector(std::initializer_list<double> l);

  int size() const { return data_.size(); }

  bool operator==(const vector& o) const
  {
    if (o.size() != size()) {
      return false;
    }

    for (int i = 0; i < size(); i++) {
      if ((*this)(i) != o(i)) {
	return false;
      }
    }
    return true;
  }

  bool operator!=(const vector& o) const
  {
    return !(*this == o);
  }
  
  double operator()(int i) const
  {
#ifdef BOUNDS_CHECK
    assert(i >= 0 && i < size());
#endif
    return data_[i];
  }

  double& operator()(int i)
  {
#ifdef BOUNDS_CHECK
    assert(i >= 0 && i < size());
#endif
    return data_[i];
  }

private:
  std::vector<double> data_;
};

std::ostream& operator<<(std::ostream& of, const vector& v);

class matrix
{
public:
  matrix(int m, int n);
  matrix(std::initializer_list<std::initializer_list<double>> l);

  int n_rows() const { return m_; }
  int n_cols() const { return n_; }

  double operator()(int i, int j) const
  {
#ifdef BOUNDS_CHECK
    assert(i >= 0 && i < m_);
    assert(j >= 0 && j < n_);
#endif
    return data_[i * n_ + j];
  }

  double& operator()(int i, int j)
  {
#ifdef BOUNDS_CHECK
    assert(i >= 0 && i < m_);
    assert(j >= 0 && j < n_);
#endif
    return data_[i * n_ + j];
  }

  void print() const;

private:
  std::vector<double> data_;
  int m_, n_;
};

double dot(const vector& x, const vector& y);
vector operator+(const vector& x, const vector& y);
vector operator*(const matrix& A, const vector& x);

// ----------------------------------------------------------------------

#include <stdio.h>

#define HERE                                                                   \
  fprintf(stderr, "HERE at %s:%d (%s)\n", __FILE__, __LINE__, __FUNCTION__)

#endif
