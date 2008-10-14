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



EPBPFile ebc_file("bin/test_op.ebc");
MemoryClass mem(0x10000,ebc_file.LoadData(),ebc_file.DataSize());
RegisterClass r(&mem);
FloatRegisterClass rf(&mem);
OpcodeProcessor cpu(ebc_file.LoadCode(),ebc_file.CodeSize());





/**End Variable Init.**/


void EpbpException(uint32_t code){
	switch(code){
		case MEMORY_FAULT:
			cout << ">>>Exception: Code: MEMORY_FAULT"<< endl;
			cout << ">>>Invalid memory was dereferenced. "<<endl;
			exit(1);
		break;
		case CL_OVERRUN:
			cout << ">>>EXCEPTION: CL_OVERRUN" << endl;
			cout << ">>>The CL program counter has overflowed out of code memory." << endl;
			exit(1);
			break;
		case MANUAL_EXIT:
			cout << ">>>EXCEPTION: MANUAL_EXIT" << endl;
			cout << ">>>The Program has requested to manually exit." << endl;
			cout << ">>>(This is not always an error)" << endl;
			exit(0);
			break;
		case BAD_OPCODE:
			cout <<">>>EXCEPTION: BAD_OPCODE" << endl;
			cout <<">>>An unimplemented or invalid opcode attempted to be executed" <<endl;
			exit(1);
			break;
			
		default:
			cout <<">>>Exception: UNKNOWN_EXCEPTION"<<endl;
			cout <<">>>This exception is not yet implemented. "<<endl;
			exit(2);
		break;
	}
	
}



	












int main(void){

	cout << "-------------------------------" << endl;
	cout << "--Shadows EPBP Implementation--" << endl;
	cout << "--<http://epbp.earlz.biz.tm>---" << endl;
	cout << "-------------------------------" << endl;	
	cout << endl <<">>>Beginning CPU emulation>>>" <<endl;
	for(;;){
		cpu.Cycle();
	}
	

	return 0;
}





























