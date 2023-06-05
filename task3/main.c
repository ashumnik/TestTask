#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "message.h"
#include "logger.h"
#include "common.h"

const char *input_file_name = "data_in.txt";
const char *output_file_name = "data_out.txt";
FILE *output_file;

uint32_t little_endian_to_big_endian_32(uint32_t value)
{
    return ((value & 0x000000FF) << 24) |
           ((value & 0x0000FF00) << 8) |
           ((value & 0x00FF0000) >> 8) |
           ((value & 0xFF000000) >> 24);
}

FILE *open_file(const char *filename, const char *mode) 
{
    FILE *file;
    file = fopen(filename, mode);
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open the file.\n");
        exit(EXIT_FAILURE);
    }
    return file;
}

void read_and_parse_file(FILE *input_file)
{
    message *msg;
    const char *mess_str = "mess=";
    const char *mask_str = "mask=";
    char line[MAX_LINE_SIZE];
    uint32_t mask = 0;

    msg = msg_init();

    while (fgets(line, MAX_LINE_SIZE, input_file) != NULL)
    {
        if (strncmp(line, mess_str, strlen(mess_str)) == 0)
        {
            uint8_t *mess_ptr;
            
            if (msg->counted_len != 0)
            {
                log_warning(output_file, "Message without mask\n");
                continue;
            }

            mess_ptr = (uint8_t *)(strstr(line, mess_str) + strlen(mess_str));
            msg->counted_len = strlen((const char *)mess_ptr) - 1;

            if (msg->counted_len < MIN_MSG_SIZE || msg->counted_len > MAX_MSG_SIZE)
            {
                log_warning(output_file, "Message has wrong size\n");
                msg->counted_len = 0;
                continue;
            }

            parse_msg(msg, mess_ptr);
        }
        else if (strncmp(line, mask_str, strlen(mask_str)) == 0)
        {
            char *mask_ptr;

            if (msg->counted_len == 0)
            {
                log_warning(output_file, "Mask without message\n");
                continue;
            }

            mask_ptr = strstr(line, mask_str) + strlen(mask_str);
            mask = little_endian_to_big_endian_32(*(uint32_t *)mask_ptr);

            msg->counted_crc32 = crc32_count(msg_dataf(msg), DATA_SIZE);
            print_msg(msg, INITIAL_MSG);

            add_padding(msg);
            apply_mask(msg->data, msg->payload_len + DATA_SIZE, mask);
            msg->counted_crc32 = crc32_count(msg_dataf(msg), DATA_SIZE);
            print_msg(msg, MODIFIED_MSG);

            msg->counted_len = 0;
        }
        else
        {
            continue;
        }
    }

    msg_free(msg);
}

int main()
{
    FILE *input_file;
    input_file = open_file(input_file_name, "r");
    output_file = open_file(output_file_name, "a");

    read_and_parse_file(input_file);

    fclose(input_file);
    fclose(output_file);

    return 0;
}
