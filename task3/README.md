# Task3 CRC32

## Comments:

1)	It is assumed that the information about the message and about the mask in data_in.txt it is written in separate lines. The message is written without spaces, in a solid line. For example:
```
mess=[message]
mask=[mask]
```
2)	Initial message length is the actual length of the message, not what is stored in the message, in the length field.
3)	Since there are two formulations in the task “data field” and “data bytes”, and also due to the fact that it is assumed that the size of the package may vary, since the length may or may not be a multiple of 4, and also the condition says to count crc32 only for the data field, it was concluded that the part of the package that can change size is the payload. The task was solved based on that “data field” is data, and “data bytes” is payload + data.
4)	The memory for storing all messages is allocated once and overwritten, I considered it more optimal than allocating memory for a message every time.
5)	Parsed messages are not stored in memory after processing (for example, in the list structure), since this is not necessary for this task.
6)	I don't understand the presence of the length field, because it can store a maximum value of 255 bytes, and the length of the message on the task assumes a size of 516 bytes.
