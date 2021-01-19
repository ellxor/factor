## factor
This project is a recreation of the [factor command on the linux terminal](https://en.wikipedia.org/wiki/Factor_(Unix)), valid for 32 bit integers. It reduces input numbers into its [prime factors](https://en.wikipedia.org/wiki/Integer_factorization#Prime_decomposition). The average time spent factoring each number is **3.70μs** (see benchmark details below).

**Usage:**
```
factor.exe [list of numbers]
```

**Installation:**
```
git clone https://github.com/llxor/factor.git
cd factor
make -B

[add factor.exe to system path]
```

**Benchmark:**
```
CPU: Intel m3-8100Y (using BMI)
DATA: 100 uniformly distributed ints ∈ (0, 2^31)
```

**Algorithm:**
For an integer input n, the program;
- removes all factors of 2 using bitshifts,
- checks for small prime factors up to log(n)^2,
- checks if n is prime using a deterministic [Miller Rabin](https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test) variant.
- uses [Pollard's rho algorithm](https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm) to find a larger factor using:
    - [Brent's cycle detection algorithm](https://en.wikipedia.org/wiki/Cycle_detection#Brent.27s_algorithm)
    - [Binary GCD algorithm](https://en.wikipedia.org/wiki/Binary_GCD_algorithm),
- recurses previous two steps if the number is not fully factorised,
- and finally, displays the factors to the terminal.
