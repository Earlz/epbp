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
	file.open(name);
	if(!file){
		EpbpException(BAD_FILENAME);
	}
	uint32_t header[6];
			
	file.read((char*)&header,6*4);
	version=header[0];
	code_start=header[1];
	code_size=header[2]-code_start;
	data_start=header[3];
	data_size=header[4]-data_start;
	extra_space=header[5];
	cout << "EPBP File Properties: "<< endl;
	cout << "code start:   0x" << hex << code_start <<endl;
	cout << "code size:    0x" << hex << code_size << endl;
	cout << "data start:   0x" << hex << data_start << endl;
	cout << "data size:    0x" << hex << data_size <<endl;
	cout << "heap size:    0x" << hex << extra_space << endl;
}

EPBPFile::~EPBPFile(){
	file.close();
}







