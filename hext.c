/*

  hext: a markup language and tool for binary files
  
  Copyright 2016 Nicholas Humfrey

*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

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
int main(int argc, const char *argv[])
{
    uint8_t buffer[1024];
    
    if (argc != 2) {
        fprintf(stderr, "Usage: hext <filename>\n");
        return -1;
    }
    
    int len = read_hext_file(argv[1], buffer, sizeof(buffer));
    if (len < 0) {
        return -1;
    }
    
    fwrite(buffer, 1, len, stdout);
    
    return 0;
}
#endif
