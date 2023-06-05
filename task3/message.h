#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define DATA_SIZE 252

#define MAX_MSG_SIZE 516
#define MIN_MSG_SIZE 258

#define INITIAL_MSG 0
#define MODIFIED_MSG 1

#define POLYNOME 0x04C11DB7
#define INIT_VAL 0xFFFFFFFF

typedef struct message {
    uint8_t type;
    uint8_t length;
    uint32_t payload_len;
    uint8_t *data;
    uint32_t crc32;
    uint32_t counted_len;
    uint32_t counted_crc32;
} message;

message *msg_init();
void msg_free(message *msg);
void print_msg(message *msg, bool modified);
void parse_msg(message *msg, uint8_t *const mess_ptr);
uint32_t crc32_count(uint8_t *const data, const uint32_t len);
void apply_mask(uint8_t *data, const uint32_t len, const uint32_t mask);
void add_padding(message *msg);

static inline uint8_t *msg_dataf(const message* msg)
{
    return msg->data + msg->payload_len;
}

#endif // _MESSAGE_H