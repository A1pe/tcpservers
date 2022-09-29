#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define __SOCKET_DATA__

void get_socket(int _sockarry[2],char* _ports);

extern void error_handling(char * message);