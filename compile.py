#!/usr/bin/env python3

from subprocess import run
import sys
from time import time
from math import floor


def parse_argv():
    data_size = "128" 
    seed = str(floor(time()))
    iterations = "10"
    program = "quicksort"
    multiplication = False
    rows, cols = "3", "3"

    for argument in sys.argv:
        if "--data" in argument:
            data_size = argument[7:]
        elif "--seed" in argument:
            seed = argument[7:]
        elif "--iterations" in argument:
            iterations = argument[13:]
        elif "--program" in argument:
            program = argument[10:]
        elif "-m" in argument:
            multiplication = True
        elif "--rows" in argument:
            rows = argument[7:]
        elif "--columns" in argument:
            cols = argument[10:]
    
    return data_size, seed, iterations, program, multiplication, rows, cols


def write_file(data_size, seed, iterations, program, rows, cols):
    print("Writing c file")
    with open(program + ".c", 'w', encoding='utf-8') as outfile:
        if program != "matrix_multiplication" and program != "two_dimensional_convoluton":
            outfile.write("const int DATA_SIZE = " + (data_size) + ";\n")
        else:
            outfile.write("const int MATRIX_1_ROWS = " + rows + ";\n")
            outfile.write("const int MATRIX_1_COLS = " + cols + ";\n")
            outfile.write("const int MATRIX_2_ROWS = " + cols + ";\n")
            outfile.write("const int MATRIX_2_COLS = " + rows + ";\n")
            

        outfile.write("const int SEED = " + (seed) + ";\n")
        outfile.write("const int ITERATIONS = " + (iterations) + ";\n")
        
        with open("templates/" + program + ".c", 'r') as infile:
            for line in infile:
                outfile.write(line)


def compile_program(program, multiplication):

    compiler_str = "/opt/riscv/bin/riscv32-unknown-elf-gcc -Ttext 0x00000000 -nostartfiles -e main -march=rv32i"

    if multiplication:
        compiler_str += "m"
    compiler_str += " -mabi=ilp32 -O0 " 
    print("Compiling with str: " + compiler_str)   
 
    run(compiler_str + program + ".c uart.c intToStr.c -o " + program, shell=True)

    print("Running elf2hex")
    run("./elf2hex --bit-width 32 --input " + program + " --output " + program + ".hex", shell=True)
    print("Cleaning up")
    run("rm " + program + " " + program + ".c", shell=True)


def main():
    data_size, seed, iterations, program, multiplication, rows, cols = parse_argv() 
    
    if program != "matrix_multiplication" and program != "two_dimensional_convolution":
        print("Size: " + data_size)
    else:
        print("Rows: " + rows)
        print("Columns: " + cols)

    print("Seed: " + seed)
    print("Iterations: " + iterations)
    print("Multiplication: " + str(multiplication))
    print("Program: " + program)

    write_file(data_size, seed, iterations, program, rows, cols)
    compile_program(program, multiplication)


if __name__ == "__main__":
    main()
