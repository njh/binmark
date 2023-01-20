#include <stdio.h>

#ifndef BINMARK_H
#define BINMARK_H

typedef int (*binmark_read_cb)(void* data);
typedef int (*binmark_write_cb)(int c, void* data);

/** Convert binmark to binary using callbacks for reading and writing */
int binmark_cb_to_cb(void* input, void* output, binmark_read_cb read_cb, binmark_write_cb write_cb);

/** Convert binmark to binary using streams for input and output */
int binmark_stream_to_stream(FILE* input, FILE* output);

/** Convert binmark to binary using a filename for input and callback for output */
int binmark_filename_to_cb(const char* filename, void* output, binmark_write_cb write_cb);

/** Convert binmark to binary using a filename for input and stream for output */
int binmark_filename_to_stream(const char* filename, FILE* output);

/** Convert binmark to binary using a filename for input and buffer for output */
int binmark_filename_to_buffer(const char* filename, uint8_t *buffer, size_t buffer_len);

#endif
