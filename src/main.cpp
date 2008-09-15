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

#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>
#include <epbp.h>
using namespace std;


uint8_t *opcode_data;


void exception(uint32_t code){
	switch(code){
		case MEMORY_FAULT:
			cout << "Exception: Code: MEMORY_FAULT"<< endl;
			exit(1);
		break;
		default:
			cout <<"Exception: Code: UNKNOWN"<<endl;
			exit(2);
		break;
	}
	
}


void LoadFile(){
	ifstream inf;
	inf.open("bin/test_op.ebc");
	cout << "Loading File" << endl;
	uint32_t i=0;
	while(inf.good()==1){
		opcode_data[i]=(int)inf.get();
		cout <<hex<< (int)opcode_data[i] << endl;
		i++;
		
	}
	
}
	






int main(void){
	opcode_data=new uint8_t[(128*1024)]; //128k for opcode storage
	LoadFile();
	cout << "hi there" << endl;
	return 0;
}





























