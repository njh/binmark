/*

  C++ wrapper class to load a binmark file into memory

  Copyright 2016 Nicholas Humfrey

*/

#ifndef BINMARK_HH
#define BINMARK_HH

extern "C" {
    #include "binmark.h"
}

class BinmarkFile {
public:
    BinmarkFile(const char* filename) {
        length = binmark_filename_to_buffer(filename, buffer, buffer_size);
        if (length <= 0) {
            fprintf(stderr, "Error: failed to load file: %s\n", filename);
        }
    }

    static const int buffer_size = 2048;
    int length = 0;
    uint8_t buffer[buffer_size];
};

#endif
