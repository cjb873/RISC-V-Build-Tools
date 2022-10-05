#!/usr/bin/env python3

from subprocess import run
import sys
from time import time
from math import floor


COMPILER = "/usr/local/riscv32/bin/riscv32-unknown-elf-gcc"
ARGUMENTS = " -T script.ld -nostartfiles -O0 -mabi=ilp32 -march=rv32i" 

def parse_argv():
    data_size = "128" 
    seed = str(floor(time()))
    iterations = "10"
    program = "quicksort"
    multiplication = False
    rows, cols = "3", "3"
    keep_binary = False 

    for argument in sys.argv:
        if "--data" in argument:
            data_size = argument.split("=")[1]
        elif "--seed" in argument:
            seed = argument.split("=")[1]
        elif "--iterations" in argument:
            iterations = argument.split("=")[1]
        elif "--program" in argument:
            program = argument.split("=")[1]
        elif "-m" in argument:
            multiplication = True
        elif "--rows" in argument:
            rows = argument.split("=")[1]
        elif "--columns" in argument:
            cols = argument.split("=")[1]
        elif "-k" in argument:
            keep_binary = True

    return data_size, seed, iterations, program, multiplication, rows, cols, \
           keep_binary


def write_file(data_size, seed, iterations, program, rows, cols):
    print("Writing c file")
    with open(program + ".c", 'w', encoding='utf-8') as outfile:
        if program != "matrix_multiplication" and \
           program != "two_dimension_convolution":
            outfile.write("const int DATA_SIZE = " + (data_size) + ";\n")
        else:
            outfile.write("const int MATRIX_ROWS = " + rows + ";\n")
            outfile.write("const int MATRIX_COLS = " + cols + ";\n")
            

        outfile.write("const int SEED = " + (seed) + ";\n")
        outfile.write("const int ITERATIONS = " + (iterations) + ";\n")
        
        with open("templates/" + program + ".c", 'r') as infile:
            for line in infile:
                outfile.write(line)


def compile_program(program, multiplication, keep_binary):

    compiler_str = COMPILER + ARGUMENTS

    if multiplication:
        compiler_str += "m"
    
    compiler_str += " "
    print("Compiling with str: " + compiler_str)   
 
    run(compiler_str + program + ".c -o " + program, shell=True)

    print("Running elf2hex")
    run("./elf2hex --bit-width 32 --input " + program + " --output " + \
        program + ".hex", shell=True)
    print("Cleaning up")
    if not keep_binary:
        run("rm " + program, shell=True)
    run("rm " + program + ".c", shell=True)


def main():
    data_size, seed, iterations, program, multiplication, rows, cols, \
    keep_binary = parse_argv() 
   
    print(program)

    if program != "matrix_multiplication" and \
       program != "two_dimension_convolution":
        print("Size: " + data_size)
    else:
        print("Rows: " + rows)
        print("Columns: " + cols)

    print("Seed: " + seed)
    print("Iterations: " + iterations)
    print("Multiplication: " + str(multiplication))
    print("Keep Binary: " + str(keep_binary))
    print("Program: " + program)

    write_file(data_size, seed, iterations, program, rows, cols)
    compile_program(program, multiplication, keep_binary)


if __name__ == "__main__":
    main()
