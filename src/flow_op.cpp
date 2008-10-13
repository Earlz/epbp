/*
<Copyright Header>
Copyright (c) 2007 - 2008 Jordan "Earlz/hckr83" Earls  
<http://www.Earlz.biz.tm>
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
   
THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED 
WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

This file is part of the EPBP project
</Copyright Header>
*/

/**This file contains all the opcodes related to flow control.**/

#include <epbp.h>




void OpcodeProcessor::jmp_immwc(){
	//int16_t ad=*(int16_t*)&op_data[cl+1];
	
}


void OpcodeProcessor::jmp_immdc(){
	uint32_t ad=*(uint32_t*)&ops[cl+1];
	
	cl=ad;
	cout << "cl="<<hex<<cl<<endl;
	cl--; //compensate for the increment at end of Cycle
}
	
void OpcodeProcessor::jit_immdc(){
	if(tr==1){
		cl=*(uint32_t*)&ops[cl+1];
		cl--;
	}else{
		cl+=4;
	}
}
void OpcodeProcessor::jif_immdc(){
	
	if(tr==0){
		cl=*(uint32_t*)&ops[cl+1];
		cl--;
	}else{
		cl+=4;
	}	
}


void OpcodeProcessor::call_immdc(){
	cl++;
	//cout <<"t"<<endl;
	PushCS(cl+4);
	cl=*(uint32_t*)&ops[cl];
	cl--;
}


void OpcodeProcessor::ret(){
	cl=PopCS();
	cl--;
}











