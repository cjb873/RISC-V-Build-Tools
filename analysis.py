#!/usr/bin/env python3

from sys import argv
from subprocess import run 
from re import search
from math import ceil


OBJDUMP = "/usr/local/riscv/bin/riscv32-unknown-elf-objdump"
DUMP_FILE = "dump"


def right_line(line: str) -> bool:
    header = search("<.*>:$", line)
    
    if ("file format" not in line) and ("Disassembly" not in line) and \
       (header is None) and (not line.isspace()):
        return True

    return False

def get_data_section(program: str, section: str) -> int:
    length = 0
    num_zeroes = 0
    prev_zero = False

    run(OBJDUMP + " -D " + program + " -j " + section + " -z >" + DUMP_FILE, \
        shell=True)

    

    with open(DUMP_FILE, "r") as dump_file:
        for line in dump_file:
            if right_line(line):
                line = line.split(":")[1]
                line = line.split("\t")[1]
                line = line.strip()
                if len(line) <= 4:
                    length = length + 0.5 
                    if "0000" in line:
                        if not prev_zero:
                            prev_zero = True
                        else:
                            prev_zero = False
                            num_zeroes = num_zeroes + 1
                    else:
                        prev_zero = False
                elif len(line) == 8:
                    length = length + 1

    return int(ceil(length)), int(ceil(num_zeroes))

def get_text_section(program: str) -> int:
    length = 0
    
    run(OBJDUMP + " -D " + program + " -j .text -z >" + DUMP_FILE, shell=True)
    
    with open(DUMP_FILE, "r") as dump_file:
        for line in dump_file:
            length = line.split(":")[0]


    return int(length, 16) / 4 + 1 
            

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
    data_length, data_zeroes = get_data_section(bin_file, ".data")
    sdata_length, sdata_zeroes = get_data_section(bin_file, ".sdata")
    rodata_length, rodata_zeroes = get_data_section(bin_file, ".rodata")
    

    print("The length of .data including zeroes is " + str(data_length) + ".")
    print("There are " + str(data_zeroes) + " zeroes in .data.\n\n")
    print("The length of .sdata including zeroes is " + str(sdata_length) + ".")
    print("There are " + str(sdata_zeroes) + " zeroes in .sdata.\n\n")
    print("The length of .rodata including zeroes is " + str(rodata_length) + 
          ".")
    print("There are " + str(rodata_zeroes) + " zeroes in .rodata.\n\n")
    print("The length of .text section is " + str(prog_length) + \
          " instructions.\n\n")
    
    clean_up()


if __name__ == "__main__":
    main()
