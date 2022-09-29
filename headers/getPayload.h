#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#define __PAYLOAD_DATA__

#ifndef __HEADER_DATA__
#include "/home/windows/Project_A/headers/getHeader.h"
#endif 

#define MAXBUFS 1000

struct _header_data{
	unsigned long seq_num;	
	unsigned long bufsize;
	unsigned long crc32;	
	char message[5];
	char buffer[MAXBUFS];	
} __attribute__((packed));

struct inner_header_data{
	struct _header_data _head_data;
	unsigned long fragment;
	unsigned int cnt;
	unsigned int compare_value;
}__attribute__((packed));

void salvage_data(struct inner_header_data * _ihd , char* main_buffer, int _clnt_sock, int key );
void _set_message(struct inner_header_data * _ihd_message,char _msg[4]);
void data_setter(struct inner_header_data * _ihd_setter,struct inner_file_data * _ifd_setter);
void _ihd_send(struct inner_header_data * _send_data, int _clnt_sock_send);
void _ihd_recv(struct inner_header_data * _recv_data,int _clnt_sock_recv);
void _ihd_extract(struct inner_header_data * _extract_data, char* _target_buffer);
void _ihd_seq_check(struct inner_header_data * _bucket_data, char* _dummy_buf);
void _ind_bfclear(struct inner_header_data * _clear_data);
