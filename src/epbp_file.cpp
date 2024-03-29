/*
<Copyright Header>
Copyright (c) 2007 - 2008 Jordan "Earlz/hckr83" Earls  <http://www.Earlz.biz.tm>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.
   
THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

This file is part of the EPBP project
</Copyright Header>
*/

#include <epbp.h>
#include <string>

EPBPFile::EPBPFile(char* name){
	file.open(name,ios::binary);
	if(!file){
		EpbpException(BAD_FILENAME);
	}
	uint32_t header[6];
			
	file.read((char*)&header,8*4);
	int i=0;
	EPBP_=header[i];
	if(EPBP_!=0x50425045){ //hex for 'EPBP'
		EpbpException(INVALID_EBC_FILE);
	}
	i++;
	version=header[i];
	if(version!=EBC_VERSION){
		EpbpException(OUTDATED_IMPLEMENTATION);
	}
	i++;
	generator=header[i];
	i++;
	code_start=header[i];
	i++;
	code_size=header[i]-code_start;
	i++;
	data_start=header[i];
	i++;
	data_size=header[i]-data_start;
	i++;
	extra_space=header[i];
	cout << "EBC File:        "<<name << endl;
	cout << "--EBC Format Details--" << endl;
	cout << "version num:      0x" << hex << version << endl;
	cout << "generator:        0x" << hex << generator << endl;
	cout << "code start :      0x" << hex << code_start <<endl;
	cout << "code size:        0x" << hex << code_size << endl;
	cout << "data start:       0x" << hex << data_start << endl;
	cout << "data size:        0x" << hex << data_size <<endl;
	cout << "heap size:        0x" << hex << extra_space << endl;
}

EPBPFile::~EPBPFile(){
	file.close();
}


void *EPBPFile::LoadCode(){
	void *tmp;
	tmp=new uint8_t[code_size];
	file.seekg(code_start,ios::beg);
	file.read((char*)tmp,(int)code_size);
	cout << hex << *(int*)tmp << endl;
	return tmp;
}


void *EPBPFile::LoadData(){
	void *tmp;
	tmp=new uint8_t[data_size];
	file.seekg(data_start,ios::beg);
	file.read((char*)tmp,(int)data_size);
	return tmp;
}


uint32_t EPBPFile::DataSize(){
	return data_size;
}

uint32_t EPBPFile::CodeSize(){
	return code_size;
}


