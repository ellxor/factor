#include <stdio.h>

// bithacks
inline long abs(long v) { return (v + (v >> 63)) ^ (v >> 63); }
inline long clz(long v) { return __builtin_clzll(v); }
inline long ctz(long v) { return __builtin_ctzll(v); }
inline long log(long v) { return 64 - clz(v); }

// binary gcd algorithm
inline long gcd(long u, long v) {
  unsigned long shift;
  if (u == 0) return v;
  if (v == 0) return u;

  shift = ctz(u | v);
  u >>= ctz(u);
  do {
      v >>= ctz(v);
      if (u > v) {
          long t = v;
          v = u;
          u = t;
      }
      v = v - u;
  } while (v);
  return u << shift;
}

// pollard rho algorithm
inline long pollardRho(long n) {
  long i, factor;
  long x = 2, y = 2, z = 1;

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


inline long factor(long n) {
  long i, l;

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
    long n, f, i, z;

    sscanf(argv[index], "%ld ", &n);
    printf("%ld: ", n);

    z = ctz(n);
    n >>= z;

    for (i = 0; i < z; ++i) {
      printf("2 ");
    }

    while (n > 1) {
      f = factor(n);
      n /= f;

      if (f > n && n > 1) {
        long t = f;
        f = n;
        n = t;
      }

      printf("%ld ", f);
    }

    printf("\n");
  }

  return 0;
}
