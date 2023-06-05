#ifndef _LOGGER_H
#define _LOGGER_H

#include <stdint.h>
#include <stdlib.h>

#define LOG_INFO 1
#define LOG_WARNING 2
#define LOG_ERROR 3

#define log_info(file, ...)                      \
    do                                           \
    {                                            \
        log_msg(file, LOG_INFO, __VA_ARGS__);    \
    } while (0)

#define log_warning(file, ...)                   \
    do                                           \
    {                                            \
        log_msg(file, LOG_WARNING, __VA_ARGS__); \
    } while (0)

#define log_error(file, ...)                     \
    do                                           \
    {                                            \
        log_msg(file, LOG_ERROR, __VA_ARGS__);   \
        exit(EXIT_FAILURE);                      \
    } while (0)

extern FILE *output_file;

void log_msg(FILE *f, int level, const char *format, ...);

#endif // _LOGGER_H