#include "Extensions.h"

void Extensions::swap(int a, int b)
{
  int c = a;
  a = b;
  b = c;
}

/*
int Extensions::max(int a, int b)
{
  if (a > b)
  {
    return a;
  }
  return b;
}

int Extensions::min(int a, int b)
{
  if (a < b)
  {
    return a;
  }
  return b;
}
*/

int Extensions::crossProduct(int ax, int ay, int bx, int by)
{
  return ax * by - bx * ay;
}