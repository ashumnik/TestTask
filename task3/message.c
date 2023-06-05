#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "message.h"
#include "logger.h"
#include "common.h"

message *msg_init()
{
    message *msg;

    msg = calloc(1, sizeof(message));
    if (msg == NULL)
    {
        log_error(output_file, "Memory allocation error\n");
    }

    msg->data = calloc(MAX_MSG_SIZE, sizeof(uint8_t));
    if (msg->data == NULL)
    {
        log_error(output_file, "Memory allocation error\n");
    }
    
    return msg;
}

void msg_free(message *msg)
{
    free(msg->data);
    free(msg);
}

void parse_msg(message *msg, uint8_t *const mess_ptr)
{
    uint8_t *crc32_ptr = mess_ptr + msg->counted_len - sizeof(uint32_t) - 1;
    uint8_t *data_ptr = crc32_ptr - DATA_SIZE;
    msg->payload_len = data_ptr - mess_ptr - 2;

    msg->type = mess_ptr[0];
    msg->length = mess_ptr[1];
    msg->crc32 = little_endian_to_big_endian_32(*((uint32_t *)crc32_ptr));
    memcpy(msg->data, mess_ptr + 2, DATA_SIZE + msg->payload_len);
}

uint32_t crc32_count(uint8_t *const data, const uint32_t len)
{
    uint32_t crc = INIT_VAL;
    
    for (size_t i = 0; i < len; i++) 
    {
        crc ^= data[i];
        for (size_t j = 0; j < 8; j++) 
        {
            if (crc & 1) 
                crc = (crc >> 1) ^ POLYNOME;
            else 
                crc >>= 1;
        }
    }
    return crc;
}

void apply_mask(uint8_t *data, const uint32_t len, const uint32_t mask)
{ 
    for (size_t i = 0; i < len; i += 4) 
    {
        if (i % 8 == 0) 
        {
            uint32_t tetrad = data[i] << 24 | data[i + 1] << 16 | data[i + 2] << 8 | data[i + 3];
            tetrad ^= mask;
            data[i] = tetrad >> 24;
            data[i + 1] = tetrad >> 16;
            data[i + 2] = tetrad >> 8;
            data[i + 3] = tetrad;
        }
    }
}

void add_padding(message *msg)
{
    int len = DATA_SIZE + msg->payload_len;
    if (len % 4 != 0)
    {
        uint32_t padding_len = 4 - (len % 4);
        memset(msg->data + len, 0, padding_len);
        msg->counted_len += padding_len;
        msg->payload_len += padding_len;
    }
}
