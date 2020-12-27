# Factor Command
This project is a recreation of the factor command on the linux terminal, valid for all 64 bit integers. The program checks for trivial factors up to log(n)² and then uses the pollard rho algorithm to find the smallest factor. This script if the factor command is unavaiable, such as on Windows.

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
