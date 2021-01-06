# Factor Command
This project is a recreation of the [factor command on the linux terminal](https://en.wikipedia.org/wiki/Factor_(Unix)), valid for all 64 bit integers. It reduces input numbers into its [prime factors](https://en.wikipedia.org/wiki/Integer_factorization#Prime_decomposition).

For an integer input n, the program;
- removes all factors of 2 using bitshifts,
- checks for small prime factors up to log(n)^3,
- checks if n is prime using a deterministic [Miller Rabin](https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test) variant.
- uses [Pollard's rho algorithm](https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm) to find a larger factor using:
    - [Brent's cycle detection algorithm](https://en.wikipedia.org/wiki/Cycle_detection#Brent.27s_algorithm)
    - [Binary GCD algorithm](https://en.wikipedia.org/wiki/Binary_GCD_algorithm),
- recurses previous two steps if the number is not fully factorised,
- sorts the full list of factors using [insertion sort](https://en.wikipedia.org/wiki/Insertion_sort),
- and finally, displays the factors to the terminal.

**Usage**:
```
factor.exe [list of numbers]
```

**Installation**:
```
git clone https://github.com/llxor/factor
cd factor
make -B

[add factor.exe to system path]
```

**Benchmarks:**
Benchmarks were recorded using the linux `time` command, using 10 random numbers in the range (1,2**63).

- unix factor:  `0.00s user 0.00s system 79% cpu 0.005 total`
- llxor factor: `0.01s user 0.00s system 97% cpu 0.009 total`
