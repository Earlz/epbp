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


//Opcode Parser
#include <epbp.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;


OpcodeProcessor::OpcodeProcessor(void *opcode_data,uint32_t flags){
	op_data=(uint32_t*)opcode_data;
	cl=0;
	tr=false;
	sr=0x1000;
	sr_size=0xFFF; //4k
	rx[0]=0;
	rx[1]=0;
	rx[2]=0;
	rx[3]=0;
	cs=new uint32_t[CALLSTACK_SIZE];
	csl=0;
	
	
	
	
}



OpcodeProcessor::~OpcodeProcessor(){
	
	delete []op_data;
}


void OpcodeProcessor::Cycle(){
	switch((uint8_t)op_data[cl]){
		case 0x00: //nop
			cout << "nop" << endl;
		break;
		
		
		
		
		
		
	}
}


void OpcodeProcessor::PushCS(uint32_t code){
	if(csl>=CALLSTACK_SIZE){
		EpbpException(CALLSTACK_OVERFLOW);
	}
	cs[csl]=code;
	csl++;
}

uint32_t OpcodeProcessor::PopCS(){
	if(csl==0){
		EpbpException(CALLSTACK_UNDERFLOW);
	}
	csl--;
	return cs[csl]; //decrement csl first then return the value.
}

uint32_t OpcodeProcessor::PeekCS(){
	if(csl==0){
		EpbpException(CALLSTACK_UNDERFLOW);
	}
	return cs[(csl-1)];
}













