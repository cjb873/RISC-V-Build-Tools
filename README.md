# RISCV Build Tools
These command line tools are intended to help compile benchmarks for a bare-metal RISC-V system. 
The analysis tool looks at the binary to find the length of the different sections in the binary.

# Compilation
An example compilation command looks like:
```
./compile.py --program=matrix_multiplication --iterations=10 --rows=3 --columns=3 --keep --multiplication
```
This will compile the matrix multiplication benchmark, ensuring that it does use RISC-V's m extension, with matricies
that are 3x3, run the benchmark with 10 different randomly generated matricies, and it will keep the binary file.

# Analysis
An example analysis command looks like:
```
./analysis.py -p=max
```
This will look at the max benchmark and output simple data concerning the length of sections in its binary.
For this program to work, you must compile with the keep option to ensure that the binary file exists.
