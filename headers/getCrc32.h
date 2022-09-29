#include<stdio.h>
#include<string.h>

#define __CRC32_DATA__
#define SIXTEENBIT 32768

unsigned long getFileCRC(char* _src_data,unsigned long _src_size);
unsigned long calcCRC(const unsigned char *_mem, signed long _size, unsigned long _CRC, unsigned long *_table);
void makeCRCtable(unsigned long *__table, unsigned long _id);