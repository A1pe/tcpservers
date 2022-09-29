#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


#define DOING 1
#define DONE 2

#ifndef __HEADER_DATA__
#include "/home/windows/Project_A/headers/getHeader.h"
#endif

#ifndef __PAYLOAD_DATA__
#include "/home/windows/Project_A/headers/getPayload.h"
#endif

#ifndef __SOCKET_DATA__
#include "/home/windows/Project_A/headers/getSocks.h"
#endif

#ifndef __CRC32_DATA__
#include "/home/windows/Project_A/headers/getCrc32.h"
#endif

void error_handling(char *message);
