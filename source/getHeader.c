#include "../headers/getHeader.h"

int way_patrol(int _somander, int _flows ){
	
	char _shift_patroller[sizeof(struct _patrol_set)];
	struct _patrol_set * _patroller;
	int _patrol_report;
	int _patrol_flag;
	char _patrol_sig[10];
	
	_patrol_flag = SET;
	_patrol_report = recv(_somander,_shift_patroller,sizeof(struct _patrol_set),0);
	
	if(_patrol_report != sizeof(struct _patrol_set)){
		error_handling("Patrol recv(1) error");
	}
	
	_patroller = (struct _patrol_set *)_shift_patroller;
	
	while(_patroller->_patrol_sequence != _flows){
			if(_flows == 0)
				_patroller->_patrol_sequence = 0;
			else
				_patroller->_patrol_sequence = _flows-1;
			_patrol_report = write(_somander,(const char*)_patroller,sizeof(struct _patrol_set));
			
			if(_patrol_report != sizeof(struct _patrol_set)){
				error_handling("Patrol write(1) error");
			}
			
			_patrol_report = recv(_somander,_shift_patroller,sizeof(struct _patrol_set),0);
			
			if(_patrol_report != sizeof(struct _patrol_set)){
				error_handling("Patrol recv(2) error");
			}
			_patroller = (struct _patrol_set *)_shift_patroller;
		}
	if(_flows < 2){
		_patroller->_patrol_sequence = _flows+1;
		_patrol_report = write(_somander,(const char*)_patroller,sizeof(struct _patrol_set));
		
		if(_patrol_report != sizeof(struct _patrol_set)){
				error_handling("Patrol write(2) error");
			}
	}
	
	if(_patrol_flag != FALSE){
		_patrol_flag = TRUE;
	}
	
	return _patrol_flag;
}

void loot_data(struct inner_file_data *_ifd,int _client_port){
	int _datas;
	char _tmp_box[sizeof(struct file_box)];
	char _name[50];
	struct file_box *_file_box;
	
	_datas = recv(_client_port,_tmp_box,sizeof(struct file_box),0);
	_file_box = (struct file_box *)_tmp_box;
	
	if(_datas != sizeof(struct file_box)){
		error_handling("Loot recv error");
	}
	
	memcpy(_ifd->_file_data.client_port,_file_box->client_port,sizeof(_ifd->_file_data.client_port));
	memcpy(_ifd->_file_data.filename,_file_box->filename,sizeof(_ifd->_file_data.filename));

	mkdir(_ifd->_file_data.client_port,0755);
	
	sprintf(_name,"./%s/%s%c",_ifd->_file_data.client_port,_ifd->_file_data.filename,'\0');
	
	memcpy(_ifd->_file_data.filename,_name,sizeof(_name));
	_ifd->_file_data.filesize = _file_box->filesize;
}