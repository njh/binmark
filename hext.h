
#ifndef HEXT_H
#define HEXT_H

int read_hext(FILE* input, uint8_t *buffer, size_t bufferlen);
int read_hext_file(const char* filename, uint8_t *buffer, size_t bufferlen);

#endif
