#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_LINE_SIZE 1024

FILE *open_file(const char *filename, const char *mode);
void read_and_parse_file(FILE *input_file);
uint32_t little_endian_to_big_endian_32(uint32_t value);

#endif // _COMMON_H
