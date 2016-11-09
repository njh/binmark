/*

  hext: a markup language and tool for describing binary files

  Copyright 2016 Nicholas Humfrey

*/

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "hext.h"



static int8_t ascii_to_hex(char c)
{
    c |= 0x20;

    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'f') {
        return (c - 'a') + 10;
    } else {
        return -1;
    }
}

int read_hext(FILE* input, uint8_t *buffer, size_t bufferlen)
{
    int pos = 0;

    while (pos < bufferlen) {
        int chr = fgetc(input);

        if (chr == EOF) {
            break;

        } else if (isspace(chr) || chr == ':' || chr == '-') {
            // Ignore
            continue;

        } else if (chr == '#') {
            // Ignore the rest of the line
            while (pos < bufferlen) {
                int chr2 = fgetc(input);
                if (chr2 == EOF || chr2 == '\n' || chr2 == '\r')
                    break;
            }

        } else if (isxdigit(chr)) {
            int chr2 = fgetc(input);
            if (chr2 == EOF) {
                break;
            } else if (!isxdigit(chr2)) {
                fprintf(stderr, "Error: got non-hex digit after hex digit: '%c'\n", chr2);
                break;
            }
            buffer[pos++] = (ascii_to_hex(chr) << 4) + ascii_to_hex(chr2);

        } else if (chr == '"') {
            while (pos < bufferlen) {
                int chr2 = fgetc(input);
                if (chr2 == EOF || chr2 == '"') {
                    break;
                } else {
                    buffer[pos++] = chr2;
                }
            }

        } else {
            fprintf(stderr, "Error: unrecognised character in input: '%c'\n", chr);
            break;
        }
    }

    return pos;
}

int read_hext_file(const char* filename, uint8_t *buffer, size_t bufferlen)
{
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return -1;
    }

    int len = read_hext(file, buffer, bufferlen);
    fclose(file);
    return len;
}


#ifdef HEXT_TOOL

enum {
    MODE_BINARY,
    MODE_C,
    MODE_HEXSTREAM
};

void usage()
{
    fprintf(stderr, "Usage: hext [options] file...\n");
    fprintf(stderr, "Options\n");
    fprintf(stderr, "  -b  Binary output format (default)\n");
    fprintf(stderr, "  -c  C data structure format\n");
    fprintf(stderr, "  -x  Hexadecimal text stream\n");
    exit(-1);
}

int main(int argc, char **argv)
{
    uint8_t buffer[1024];
    int len, opt, mode = 0;

    // Parse Switches
    while ((opt = getopt(argc, argv, "bcx")) != -1) {
        switch (opt) {
        case 'b':
            mode = MODE_BINARY;
            break;
        case 'c':
            mode = MODE_C;
            break;
        case 'x':
            mode = MODE_HEXSTREAM;
            break;
        default:
            usage();
            break;
        }
    }

    argc -= optind;
    argv += optind;

    if (argc < 1) {
        fprintf(stderr, "No filename given\n");
        usage();
    }


    // Now read in the file
    len = read_hext_file(argv[0], buffer, sizeof(buffer));
    if (len < 0) {
        return -1;
    }

    if (mode == MODE_BINARY) {
        fwrite(buffer, 1, len, stdout);
    } else if (mode == MODE_HEXSTREAM) {
        int i;
        for (i=0; i<len; i++) {
            fprintf(stdout, "%2.2x", buffer[i]);
        }
    } else if (mode == MODE_C) {
        int i;
        fprintf(stdout, "uint8_t buffer[] = {\n");
        for (i=0; i<len; i++) {
            //printf("%d\n", i%16);
            if (i % 8 == 0) {
                fprintf(stdout, "    ");
            }
            fprintf(stdout, "0x%2.2x", buffer[i]);
            if (i == len - 1) {
                fprintf(stdout, "\n");
            } else {
                fprintf(stdout, ", ");
                if (i % 8 == 7) {
                    fprintf(stdout, "\n");
                }
            }
        }
        fprintf(stdout, "};\n");
    }

    return 0;
}

#endif
