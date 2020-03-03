
#include "linear_algebra.h"

#include <stdio.h>
#include <stdlib.h>

void vector_construct(struct vector* v, int n)
{
  v->data = (double*)calloc(n, sizeof(*v->data));
  v->n = n;
}

void vector_destruct(struct vector* v)
{
  free(v->data);
}

void vector_print(const struct vector* v)
{
  printf("{");
  for (int i = 0; i < v->n; i++) {
    printf(" %g", VEC(v, i));
  }
  printf(" }\n");
}
