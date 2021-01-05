#import <stdio.h>
#import <string.h>

inline long abs(long v) { return (v + (v >> 63)) ^ (v >> 63); }
inline long clz(long v) { return __builtin_clzll(v); }
inline long ctz(long v) { return __builtin_ctzll(v); }
inline long log(long v) { return 64 - clz(v); }
inline long max(long x, long y) { return x ^ ((x ^ y) & -(x < y)); }
inline long min(long x, long y) { return y ^ ((x ^ y) & -(x < y)); }

long gcd(long u, long v) {
  if (u == 0)
    return v;
  if (v == 0)
    return u;

  long w, shift = ctz(u | v);
  u >>= ctz(u);

  while (v) {
    v >>= ctz(v);
    w = max(u, v);
    u = min(u, v);
    v = w - u;
  }

  return u << shift;
}

typedef __int128_t int128;

long powmod(long base, long exp, long mod) {
  long res = 1;

  while (exp != 0) {
    if (exp & 1)
      res = (int128)res * base % mod;
    base = (int128)base * base % mod;
    exp >>= 1;
  }

  return res;
}

int check_composite(long n, long a, long d, int s) {
  long x = powmod(a, d, n);

  if (x == 1 || x == n - 1)
    return 0;

  for (int r = 1; r < s; r++) {
    x = (int128)x * x % n;
    if (x == n - 1)
      return 0;
  }

  return 1;
}

const long primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
const int primec = sizeof primes / sizeof primes[0];

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

  long x = 2, y = 2, z = 1;

  while (z) {
    y = x;
    for (int i = 0; i < z; ++i) {
      x = (x * x + 1) % n;
      long factor = gcd(abs(x - y), n);
      if (factor > 1)
        return factor;
    }
    z <<= 1;
  }

  return n;
}

void sort(int len, long arr[len]) {
  for (int i = 1, j; i < len; i++) {
    long x = arr[i];
    for (j = i - 1; j >= 0 && arr[j] > x; j--) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = x;
  }
}

int main(int argc, char *argv[argc]) {
  for (int index = 1; index < argc; ++index) {
    long n;
    sscanf(argv[index], "%ld", &n);

    // check valid input
    char buffer[100];
    sprintf(buffer, "%ld", n);

    // remove leading zeros from number
    while (argv[index][0] == '0')
      argv[index]++;

    if (strcmp(buffer, argv[index]) != 0) {
      printf("`%s`: ", argv[index]);

      for (int i = 0; argv[index][i] != 0; i++) {
        char c = argv[index][i];
        if (!('0' <= c && c <= '9')) {
          printf("invalid digit `%c`\n", c);
          goto end;
        }
      }

      printf("overflows 64-bits\n");

    end:
      continue;
    }

    printf("%ld: ", n);

    // check input is >= 1
    if (n < 1) {
      printf("input must be > 0\n");
      continue;
    }

    // skip primes
    if (miller_rabin(n)) {
      printf("%ld\n", n);
      continue;
    }

    // remove trivial factors of 2
    int z = ctz(n);
    n >>= z;

    for (int i = 0; i < z; ++i) {
      printf("2 ");
    }

    // remove trivial factors up to log(n)**3
    int limit = log(n) * log(n) * log(n);

    for (long f = 3; f < limit && n > 1; f += 2) {
      while (n % f == 0) {
        n /= f;
        printf("%ld ", f);

        if (miller_rabin(n)) {
          printf("%ld", n);
          n = 1;
        }
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
