#!/usr/bin/env python3

from sys import argv
from subprocess import run 
from re import search
from math import ceil


OBJDUMP = "/usr/local/riscv/bin/riscv32-unknown-elf-objdump"


def right_line(line: str) -> bool:
    header = search("<.*>:$", line)
    
    if ("file format" not in line) and ("Disassembly" not in line) and (header is None) and (not line.isspace()):
        return True

    return False

def get_data_section(program: str) -> int:
    length = 0
    num_zeroes = 0

    run(OBJDUMP + " -D " + program + " -j .data -z > dump", shell=True)

    with open("dump", "r") as dumpfile:
        for line in dumpfile:
            if right_line(line):
                line = line.split(":")[1]
                line = line.split("\t")[1]
                line = line.strip()
                if len(line) == 4:
                    length = length + 0.5
                    if  "0000" in line:
                        num_zeroes = num_zeroes + 0.5
                elif len(line) == 8:
                    length = length + 1

    return int(ceil(length)), int(ceil(num_zeroes))

def get_text_section(program: str) -> int:
    length = 0
    
    run(OBJDUMP + " -D " + program + " -j .text > dump", shell=True)
    
    with open("dump", "r") as dumpfile:
        for line in dumpfile:
            length = line.split(":")[0]


    return int(length, 16) / 4 
            

def get_program():
    program = "quicksort"

    for argument in argv:
        if "-p" in argument:
            program = argument.split("=")[1]
            
    return program



def clean_up():
    run("rm dump", shell=True)


def main():
    bin_file = get_program()
    hex_file = bin_file + ".hex"


    prog_length = get_text_section(bin_file)
    data_length, num_zeroes = get_data_section(bin_file)

    print("The length of .data including zeros is " + str(data_length) + ".")
    print("There are " + str(num_zeroes) + " zeroes.")
    # print("The length of .text section is " + str(prog_length) + " instructions.")

    # clean_up()


if __name__ == "__main__":
    main()







