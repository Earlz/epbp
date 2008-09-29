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


/**Variable initialization.**/

char *str="Hello There Mr. Worldgdb."; //temp


MemoryClass mem(0x10000,str,22);
RegisterClass r(&mem);
OpcodeProcessor cpu(LoadFile());
EPBPFile file("bin/test_op.ebc");



/**End Variable Init.**/


void EpbpException(uint32_t code){
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


void *LoadFile(){
	ifstream inf;
	uint8_t *tmp=new uint8_t[(128*1024)]; //128k
	inf.open("bin/test_op.ebc");
	cout << "Loading File" << endl;
	uint32_t i=0;
	while(inf.good()==1){
		tmp[i]=(int)inf.get();
		cout <<hex<< (int)tmp[i] << endl;
		i++;
		
	}
	return tmp;
	
}
	






void bcve_test(uint32_t num){
	uint32_t i;
	cout << "Test Number "<<num << endl;
	cout <<"BEGIN TESTING OUTPUT" << endl;
	cout <<"--------------------" << endl;
	switch(num){
		case 0:
			/**Proves that the db and dw conventions effectively bind 
			data to there specified types.**/
			/**Expected Output:
			Hello There Mr. Worldg
			aello There Mr. Worldg
			aallo There Mr. Worldg
			aaaao There Mr. Worldg
			**/
			for(i=0;i<32;i++){
				cout << mem.db[i];
			}
			cout << endl;
			mem.db[0]='a';
			for(i=0;i<32;i++){
				cout << mem.db[i];
			}
			cout << endl;
			mem.dw[0]='aa';
			for(i=0;i<32;i++){
				cout << mem.db[i];
			}
			cout << endl;
			mem.dd[0]='aaaa';
			for(i=0;i<32;i++){
				cout << mem.db[i];
			}
			cout << endl;
		break;
		
		case 1:
			/**Proves that registers and register banks write properly*/
			/**Expected Output:
			aaaaddddccccMr. Worldg
			**/
			r[0]='aaaa';
			r[1]='bbbb';
			r[2]='cccc';
			r.SetBank(4);
			r[0]='dddd';
			for(i=0;i<32;i++){
				cout << mem.db[i];
			}
			cout << endl;
			break;
		default:
			cout <<"invalid test "<< endl;
		break;
	}
	
	cout << "------------------" << endl;
	cout << "END TESTING OUTPUT" << endl;
	
}





int main(void){
	int i;
	LoadFile();
	cout << "hi there" << endl;
	for(i=0;i<=1;i++){
		bcve_test(i);
	}
	
	cpu.Cycle();
	
	return 0;
}





























