# Factor Command
This project is a recreation of the [factor command on the linux terminal](https://en.wikipedia.org/wiki/Factor_(Unix)), valid for all 64 bit integers. It reduces input numbers into its [prime factors](https://en.wikipedia.org/wiki/Integer_factorization#Prime_decomposition).

For an integer input n, the program;
- removes all factors of two using bitshifts,
- checks for small prime factors up to log(n)^2,
- uses [Pollard's rho algorithm](https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm) to find a larger factor using [Brent's cycle detection algorithm](https://en.wikipedia.org/wiki/Cycle_detection#Brent.27s_algorithm),
- recurses back to step 2 if the number is not fully factorised,
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

[add to system path]
```
