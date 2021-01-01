#import <stdio.h>
#import <string.h>

// bithacks
inline long abs(long v) { return (v + (v >> 63)) ^ (v >> 63); }
inline long clz(long v) { return __builtin_clzll(v); }
inline long ctz(long v) { return __builtin_ctzll(v); }
inline long log(long v) { return 64 - clz(v); }

// binary gcd algorithm
long gcd(long u, long v) {
  unsigned long shift;
  if (u == 0)
    return v;
  if (v == 0)
    return u;

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

typedef __int128_t int128;

long powmod(long base, long exp, long mod) {
  long res = 1;

  while (exp != 0) {
    long k = (exp & 1) ? base : 1;
    res = (int128) res * k % mod;
    base = (int128) base * base % mod;
    exp >>= 1;
  }

  return res;
}

int check_composite(long n, long a, long d, int s) {
  long x = powmod(a, d, n);

  if (x == 1 || x == n - 1) {
    return 0;
  }

  for (int r = 1; r < s; r++) {
    x = (int128) x * x % n;
    if (x == n - 1) {
      return 0;
    }
  }

  return 1;
}

const long primes[] = {2,3,5,7,11,13,17,19,23,29,31,37};
const int primec = sizeof primes / sizeof primes[0];

// deterministic mille rabin primality test
int miller_rabin(long n) {
  int r = ctz(n - 1);
  long d = (n - 1) >> r;

  for (int i = 0; i < primec; i++) {
    if (check_composite(n, primes[i], d, r)) {
      return 0;
    }
  }

  return 1;
}

// pollard rho algorithm
long pollard_rho(long n) {
  if (miller_rabin(n)) {
    return n;
  }

  long i, factor;
  long x = 2, y = 2, z = 1;

  while (z) {
    y = x;
    for (i = 0; i < z; ++i) {
      x = (x * x + 1) % n;
      if ((factor = gcd(abs(x - y), n)) > 1) {
        return factor;
      }
    }
    z <<= 1;
  }

  return n;
}

// insertion sort
void sort(int len, long arr[len]) {
  for (int i = 1, j; i < len; i++) {
    long x = arr[i];
    for (j = i - 1; j >= 0 && arr[j] > x; j--) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = x;
  }
}

int main(int argc, char **argv) {
  for (int index = 1; index < argc; ++index) {
    long n;
    sscanf(argv[index], "%ld", &n);

    // check valid input
    char buffer[100];
    sprintf(buffer, "%ld", n);

    if (strcmp(buffer, argv[index]) != 0) {
      printf("`%s` is not a valid 64-bit base-10 integer\n");
      continue;
    }

    printf("%ld: ", n);

    // check input is >= 1
    if (n < 1) {
      printf("input must be > 0\n");
      continue;
    }

    // remove trivial factors of 2
    int z = ctz(n);
    n >>= z;

    for (int i = 0; i < z; ++i) {
      printf("2 ");
    }

    // remove trivial factors up to log(n)**2
    int l = log(n);
    for (long f = 3; f < l * l; f += 2) {
      while (n % f == 0) {
        n /= f;
        printf("%ld ", f);
        l = log(n);
      }
    }

    // find all other factors
    long factors[100];
    int len = 0;

    while (n != 1) {
      long f = pollard_rho(n);
      n /= f;
      factors[len++] = f;
    }

    // display factors in ascending order
    sort(len, factors);

    for (int i = 0; i < len; i++) {
      printf("%ld ", factors[i]);
    }

    printf("\n");
  }

  return 0;
}
