#!/usr/bin/env python3

import binmark
import getopt
import sys

MODE_BINARY = 0
MODE_C = 1
MODE_HEXSTREAM = 2

def write_hex(c, output_file):
    val = "%2.2x" % c
    output_file.write(val.encode())

def write_raw(c, output_file):
    output_file.write(c)

def usage():
    print("Usage: binmark_tool.py [options] file...")
    print("Options")
    print("  -b  Binary output format (default)")
    print("  -x  Hexadecimal text stream")
    exit(-1)


def main():
    mode = MODE_BINARY

    # Parse Switches
    opts, args = getopt.getopt(sys.argv[1:], 'bcx')
    for o, a in opts:
        if o == '-b':
            mode = MODE_BINARY
        elif o == '-x':
            mode = MODE_HEXSTREAM
        else:
            usage()

    if len(sys.argv) < 1:
        print("No filename given")
        usage()

    with open(sys.argv[1+len(opts)], "rb") as f:
        input_buffer = f.read()

    output_buffer = binmark.binmark_to_binary(input_buffer)

    if mode == MODE_BINARY:
        sys.stdout.buffer.write(output_buffer)

    elif mode == MODE_HEXSTREAM:
        for val in output_buffer:
            write_hex(val, sys.stdout.buffer)

    return 0

main()
