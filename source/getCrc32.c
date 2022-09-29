#include "../headers/getCrc32.h"

unsigned long getFileCRC(char* _src_data,unsigned long _src_size) {
	unsigned long CRC = 0;
	unsigned long _tmp_table[256];
	unsigned long _index = _src_size/SIXTEENBIT;
	unsigned long _tmp_idx = _src_size%SIXTEENBIT;
	char _tmp_buf[SIXTEENBIT];
	int _tmp_val;
	
	makeCRCtable(_tmp_table, 0xEDB88320);

	for(_tmp_val=0;_tmp_val<_index;_tmp_val++){
		memset(_tmp_buf,0,SIXTEENBIT);
		memcpy(_tmp_buf,_src_data+(SIXTEENBIT*_tmp_val),SIXTEENBIT);
		CRC = calcCRC(_tmp_buf, SIXTEENBIT, CRC, _tmp_table);
	}
	memset(_tmp_buf,0,SIXTEENBIT);
	memcpy(_tmp_buf,_src_data+(SIXTEENBIT*_tmp_val),_tmp_idx);
	CRC = calcCRC(_tmp_buf, _tmp_idx, CRC, _tmp_table);


	return CRC;
}
 

unsigned long calcCRC(const unsigned char *_mem, signed long _size, unsigned long _CRC, unsigned long *_table) {
	_CRC = ~_CRC;

	while (_size--)
		_CRC = _table[(_CRC ^ *(_mem++)) & 0xFF] ^ (_CRC >> 8);

	return ~_CRC;
}


void makeCRCtable(unsigned long *__table, unsigned long _id) {
	unsigned long _tmp_v_i, _tmp_v_j, _tmp_v_k;

	for (_tmp_v_i = 0; _tmp_v_i < 256; ++_tmp_v_i) {
		_tmp_v_k = _tmp_v_i;
		for (_tmp_v_j = 0; _tmp_v_j < 8; ++_tmp_v_j) {
			if (_tmp_v_k & 1) _tmp_v_k = (_tmp_v_k >> 1) ^ _id;
			else _tmp_v_k >>= 1;
		}
		__table[_tmp_v_i] = _tmp_v_k;
	}
}