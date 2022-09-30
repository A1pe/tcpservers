#include "/home/windows/tcp_servers/headers/main.h"

int main(int argc, char *argv[]){

	if(argc != 2){
		printf("Usage : %s <port>\n",argv[0]);
		exit(1);
	}
	unsigned long crcs;
	int socks[2];
	struct inner_file_data ifd;
	struct inner_header_data ihd;
	char* buffer;
	
	////////////////////////header start/////////////////////////
	
	get_socket(socks,argv[1]);
	way_patrol(socks[1], 0);
	way_patrol(socks[1], 2);
	
	/////////////////////// file setting ///////////////////////////

	loot_data(&ifd,socks[1]);
	buffer = (char*)calloc(1,ifd._file_data.filesize+1);
	ifd.file_storage = fopen(ifd.file_path,"wb+");
	data_setter(&ihd,&ifd);
	
	/////////////////////////payload start/////////////////////////
	
	while(ihd.cnt <= ihd.compare_value){
		
		salvage_data(&ihd,buffer,socks[1],DOING);
		printf("%d KB / %d KB\r",ihd.cnt,ihd.compare_value);

	}
	salvage_data(&ihd,buffer,socks[1],DONE);
	printf("%d KB / %d KB\n",ihd.cnt-2,ihd.compare_value);
	
	////////////////////////write data////////////////////////////
	
	
	fwrite(buffer,sizeof(char),ihd.fragment,ifd.file_storage);
	fclose(ifd.file_storage);
	
	/////////////////////// crc 32 check ////////////////////////
 
	crcs = getFileCRC(buffer,ihd.fragment);
	
	if(crcs == ihd._head_data.crc32){
		printf("It's equal the value of server's crc32 and client's crc32\n");
		printf("server's crc32 : %ld\nclient's crc32 : %ld\n",crcs,ihd._head_data.crc32);
	}
	else{
		printf("It isn't equal the value of server's crc32 and client's crc32\n");
		printf("server's crc32 : %ld\nclient's crc32 : %ld\n",crcs,ihd._head_data.crc32);
	}
	
	///////////////////// end program ////////////////////////////
	close(socks[1]);
	close(socks[0]);
	
	return 0;
}

void error_handling(char *message){
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
