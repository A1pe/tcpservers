#include "../headers/getSocks.h"

void get_socket(int _sockarry[2],char* _ports){
	
	struct sockaddr_in _serv_adr,_clnt_adr;
	socklen_t _clnt_adr_sz;

	_sockarry[0] = socket(PF_INET, SOCK_STREAM, 0);
	if(_sockarry[0] == -1)
		error_handling("socket() error!");
	
	memset(&_serv_adr, 0, sizeof(_serv_adr));
	_serv_adr.sin_family=AF_INET;
	_serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	_serv_adr.sin_port=htons(atoi(_ports));
	
	if(bind(_sockarry[0],(struct sockaddr*)&_serv_adr, sizeof(_serv_adr)) == -1)
		error_handling("bind() error!");
	
	if(listen(_sockarry[0],5) == -1)
		error_handling("listen() error!");
	
	_clnt_adr_sz = sizeof(_clnt_adr);
	_sockarry[1] = accept(_sockarry[0],(struct sockaddr*)&_clnt_adr, (socklen_t*)&_clnt_adr_sz);
}