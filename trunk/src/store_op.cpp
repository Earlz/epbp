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


void OpcodeProcessor::mov_Drf_immd(){
	cl++;
	//note option bits are filtered out in the r and rf helper classes.
	if(option_bit(ops[cl])){ //is a displacement
		mem.dd[r[ops[cl]]]=to_int(ops[cl+1]);
	}else{ //is a immediate to float mov
		rf[ops[cl]]=to_float(ops[cl+1]);
	}
	cl+=4;
}

void OpcodeProcessor::mov_Fr_Dr(){
	cl++;
	switch((option_bit(ops[cl])<<1) | option_bit(ops[cl+1])){
		case 0: //not float and not indirect
			r[ops[cl]]=r[ops[cl+1]];
		break;
		case 1: // float not set, indirect set
			r[ops[cl]]=mem.dd[r[ops[cl+1]]];
		break;
		case 2: //float set, not direct
			rf[ops[cl]]=rf[ops[cl+1]];
		break;
		case 3: //float and indirect set
			rf[ops[cl]]=to_float(mem.dd[r[ops[cl+1]]]);
		break;
	}
	cl++;
}

void OpcodeProcessor::mov_Ur_Dimmd(){
	cl++;
	if(option_bit(ops[cl])){
		//immd is pointer
		r[ops[cl]]=mem.dd[to_int(ops[cl+1])];
	}else{
		r[ops[cl]]=to_int(ops[cl+1]);
	}
	cl+=4;
}


void OpcodeProcessor::push_Fr(){
	cl++;
	if(option_bit(ops[cl])){
		//float
		push(to_int(rf[ops[cl]]));
	}else{
		push(r[ops[cl]]);
	}
}

void OpcodeProcessor::pop_Fr(){
	cl++;
	if(option_bit(ops[cl])){
		//float
		to_int(rf[ops[cl]])=pop();
	}else{
		r[ops[cl]]=pop();
	}
}






