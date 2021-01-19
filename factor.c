#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

inline long clz(long v) { return __builtin_clzll(v); }
inline long ctz(long v) { return __builtin_ctzll(v); }
inline long log(long v) { return 64 - clz(v); }

long gcd(long u, long v) {
  if (u == 0) return v;
  if (v == 0) return u;

  long shift = ctz(u | v);
  u >>= ctz(u);

  while (v) {
    v >>= ctz(v);
    v -= u;
    u += v & -(v < 0);
    v = labs(v);
  }

  return u << shift;
}

typedef __int128_t int128;

long powmod(long base, long exp, long mod) {
  long res = 1;

  while (exp != 0) {
    if (exp & 1) {
      res = (int128)res * base % mod;
    }
    base = (int128)base * base % mod;
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
    x = (int128)x * x % n;
    if (x == n - 1) {
      return 0;
    }
  }

  return 1;
}

const long primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
const int primec = sizeof primes / sizeof primes[0];

int miller_rabin(long n) {
  if (n == 1) {
    return 0;
  }

  int r = ctz(n - 1);
  long d = (n - 1) >> r;

  for (int i = 0; i < primec; i++) {
    if (check_composite(n, primes[i], d, r)) {
      return 0;
    }
  }

  return 1;
}

long pollard_rho(long n) {
  long x = 2;

  for (int z = 1; z != 0; z <<= 1) {
    long y = x;

    for (int i = 0; i < z; ++i) {
      x = ((int128)x * x + 1) % n;
      long factor = gcd(labs(x - y), n);

      if (factor > 1) {
        return factor;
      }
    }
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

long parse(char argv[]) {
  while (argv[0] == '0') {
    argv++;
  }

  char *end = NULL;
  long n = strtol(argv, &end, 10);

  if (*end != '\0') {
    printf("`%s`: invalid digit `%c`\n", argv, *end);
    return -1;
  }

  if (n == LONG_MAX) {
    printf("`%s`: overflows 64 bits\n", argv);
    return -1;
  }

  if (n < 1) {
    printf("%ld:\n", n);
    return -1;
  }

  return n;
}

int factor(long n, long factors[]) {
  int len = 0;

  for (int i = 0; i < ctz(n); i++) {
    factors[len++] = 2;
    n >>= 1;
  }

  if (miller_rabin(n)) {
    factors[len++] = n;
    return len;
  }

  int limit = log(n) * log(n) * log(n);

  for (long f = 3; f <= limit && n > f; f += 2) {
    while (n % f == 0) {
      n /= f;
      factors[len++] = f;

      if (miller_rabin(n)) {
        factors[len++] = n;
        return len;
      }
    }
  }

  while (n != 1) {
    long f = pollard_rho(n);
    factors[len++] = f;
    n /= f;

    if (miller_rabin(n)) {
      factors[len++] = n;
      return len;
    }
  }

  return len;
}

int main(int argc, char *argv[argc]) {
  for (int index = 1; index < argc; ++index) {
    long n = parse(argv[index]);

    if (n == -1) {
      continue;
    }

    long factors[100];
    int len = factor(n, factors);
    sort(len, factors);

    printf("%ld: ", n);
    for (int i = 0; i < len; i++) {
      printf("%ld ", factors[i]);
    }
    printf("\n");
  }

  return 0;
}
