#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>

#include "message.h"
#include "logger.h"
#include "common.h"

void print_msg(message *msg, bool modified)
{
    uint32_t data_len = DATA_SIZE + msg->payload_len;
    if (!modified)
    {
        log_info(output_file, "Type: %d\n", msg->type);
        log_info(output_file, "Initial message length: %d\n", msg->counted_len);
        log_info(output_file, "Initial message data:\n");
        for (size_t i = 0; i < data_len; i++)
            log_info(output_file, "%c", msg->data[i]);
        log_info(output_file, "\n");
        if (msg->counted_crc32 != msg->crc32)
            log_info(output_file, "Initial CRC-32: %d (CRC-32 in message: %d)\n", msg->counted_crc32, msg->crc32);
        else
            log_info(output_file, "Initial CRC-32: %d\n", msg->crc32);
    }
    else
    {
        log_info(output_file, "Modified message length: %d\n", msg->counted_len);
        log_info(output_file, "Modified message data:\n");
        for (size_t i = 0; i < data_len; i++)
            log_info(output_file, "%c", msg->data[i]);
        log_info(output_file, "\n");
        log_info(output_file, "Modified CRC-32: %d\n\n", msg->counted_crc32);
    }
}

void log_msg(FILE *f, int level, const char *format, ...)
{
    va_list va;
    char *l;
    char buffer[MAX_LINE_SIZE];

    switch (level)
    {
    case LOG_INFO:
        l = "";
        break;
    case LOG_WARNING:
        l = "[WARNING] ";
        break;
    case LOG_ERROR:
        l = "[ ERROR ] ";
        break;
    default:
        l = "";
        break;
    }

    va_start(va, format);
    vsnprintf(buffer, MAX_LINE_SIZE, format, va);
    va_end(va);
    fprintf(f, "%s%s", l, buffer);
}