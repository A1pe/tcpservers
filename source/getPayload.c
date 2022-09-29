#include "../headers/getPayload.h"

void salvage_data(struct inner_header_data * _ihd , char* _main_buffer, int _clnt_sock, int _key){
	
	_ihd_recv(_ihd,_clnt_sock);
	if(_key==1){
		_set_message(_ihd,"INGS");
	}
	else if(_key==2){
		_set_message(_ihd,"DONE");
	}
	_ihd_seq_check(_ihd,_main_buffer);
	
	_ihd_send(_ihd,_clnt_sock);
	
}
void _set_message(struct inner_header_data * _ihd_message,char _msg[4]){
	
	sprintf(_ihd_message->_head_data.message,"%s",_msg);
	
}
void data_setter(struct inner_header_data * _ihd_setter,struct inner_file_data * _ifd_setter){
	
	int _div_vals;
	_ihd_setter.sequences = 0;
	_ihd_setter->fragment = 0;
	_ihd_setter->cnt = 0;
	_div_vals = _ifd_setter->_file_data.filesize%MAXBUFS;
	_ihd_setter->compare_value = _ifd_setter->_file_data.filesize/MAXBUFS;
	
	if(_div_vals >= 0){
		_ihd_setter->compare_value++;
	}
	
}
void _ihd_send(struct inner_header_data * _send_data,int _clnt_sock_send){
	
	struct _header_data* _tmp_data;
	
	_tmp_data = &(_send_data->_head_data);
	
	write(_clnt_sock_send,(const char*)_tmp_data,sizeof(struct _header_data));
}
void _ihd_recv(struct inner_header_data * _recv_data,int _clnt_sock_recv){
	
	char _tmp_buf_recv[sizeof(struct _header_data)];
	struct inner_header_data  _temp_recv;
	char tempbuffer[MAXBUFS*2];
	int _tmp_value,_tmp_bufvals;
	
	_tmp_value = recv(_clnt_sock_recv,_tmp_buf_recv,sizeof(struct _header_data),0);
	_tmp_value = _tmp_value - 17;
	_temp_recv._head_data = *(struct _header_data *)_tmp_buf_recv;
	
	while(_tmp_value < _temp_recv._head_data.bufsize){
		memset(tempbuffer,0,sizeof(char)*MAXBUFS*2);
		_tmp_bufvals = recv(_clnt_sock_recv,tempbuffer,sizeof(char)*MAXBUFS*2,0);
		_tmp_value = _tmp_value + _tmp_bufvals;
		strcat(_temp_recv._head_data.buffer,tempbuffer);
	}
	
	_recv_data->_head_data = (_temp_recv._head_data);

}
void _ihd_extract(struct inner_header_data * _extract_data, char* _target_buffer){
	
	//// buffer extract
	
	sprintf(_target_buffer,"%s%s%c",_target_buffer,_extract_data->_head_data.buffer,'\0');
	
	_ind_bfclear(_extract_data);
	
}
void _ihd_seq_check(struct inner_header_data * _bucket_data, char* _dummy_buf){
	
	// 상대가 보낸 시퀸스 값이 내가 생각한 시퀸스 값과 같다면?
	// 
	
	unsigned long now_seq;
	unsigned long next_seq;
	unsigned long prev_seq;
	
	
	now_seq = _bucket_data.sequences;
	next_seq = now_seq + 1;
	prev_seq = now_seq - 1;
	
	switch(_bucket_data._head_data.seq_num){
		case now_seq:
			_bucket_data->_head_data.seq_num = next_seq;
			_bucket_data->cnt++;
			_bucket_data->fragment = _bucket_data->fragment + _bucket_data->_head_data.bufsize;
			_ihd_extract(_bucket_data,_dummy_buf);
			break;
		case next_seq:
			_bucket_data->_head_data.seq_num = now_seq;
			_ind_bfclear(_bucket_data);
			break;
		case prev_seq:
			_bucket_data->_head_data.seq_num = prev_seq;
			_ind_bfclear(_bucket_data);
			break;
		default:
			_ind_bfclear(_bucket_data);
			break;
	}
	
}
void _ind_bfclear(struct inner_header_data * _clear_data){
	
	//// buffer clear
	
	memset(_clear_data->_head_data.buffer,0,MAXBUFS);
	_clear_data->_head_data.bufsize = 0;

}