#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/stat.h>

#define __HEADER_DATA__
#define TRUE 1
#define FALSE -1
#define SET -1

struct file_box{
	char client_port[5];
	char filename[10];	
	unsigned long filesize; 
} __attribute__((packed));

struct inner_file_data{
	struct file_box _file_data;
	char file_path[25];
	FILE* file_storage;
}__attribute__((packed));

struct _patrol_set{
	int _patrol_sequence;
} __attribute__((packed));

int way_patrol(int _somander, int _flows );
void loot_data(struct inner_file_data * _ifd,int _client_port);

extern void error_handling(char * message);

