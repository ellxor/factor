#include <stdio.h>

// bithacks
inline int abs(int v) { return (v + (v >> 31)) ^ (v >> 31); }
inline int clz(v) { return __builtin_clz(v); }
inline int ctz(v) { return __builtin_ctz(v); }
inline int log(v) { return 32 - clz(v); }

// binary gcd algorithm
inline int gcd(int u, int v) {
  unsigned int shift;
  if (u == 0) return v;
  if (v == 0) return u;

  shift = ctz(u | v);
  u >>= ctz(u);
  do {
      v >>= ctz(v);
      if (u > v) {
          int t = v;
          v = u;
          u = t;
      }
      v = v - u;
  } while (v);
  return u << shift;
}

// pollard rho algorithm
inline int pollardRho(int n) {
  int i, factor;
  long int x = 2, y = 2, z = 1;

  while (z) {
    y = x;
    for (i = 0; i < z; ++i) {
      x = (x*x + 1) % n;
      if ((factor = gcd(abs(x - y), n)) > 1) {
        return factor;
      }
    }
    z <<= 1;
  }

  return n;
}


inline int factor(int n) {
  int i, l;

  l = log(n);
  l *= l;

  for (i = 3; i < l; i += 2) {
    if (n % i == 0) {
      return i;
    }
  }

  return pollardRho(n);
}


int main(int argc, char **argv)
{
  for (int index = 1; index < argc; ++index)
  {
    int n, f, i, z;

    sscanf(argv[index], "%d ", &n);

    printf("%d: ", n);

    z = ctz(n);

    for (i = 0; i < z; ++i) {
      printf("2 ");
      n >>=1;
    }

    while (n > 1) {
      f = factor(n);
      n /= f;

      if (f > n && n > 1) {
        int t = f;
        f = n;
        n = t;
      }

      printf("%d ", f);
    }

    printf("\n");
  }

  return 0;
}