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


void OpcodeProcessor::mov_rrf_immdimmf(){
	uint8_t tmp;
	cl+=1;
	tmp=(uint8_t)op_data[cl]; //register;
	cout <<(int) op_data[cl] << endl;
	op_cache=*(uint32_t*)&op_data[cl+1];
	if((tmp&0x80)==0){
		r[tmp]=op_cache;
		cout << "r["<<(int)tmp<<"]=0x"<<hex<<r[tmp]<<endl;
	}else{
		tmp=tmp&0x7F;
		rf[tmp]=*(float32_t*)&op_data[cl+1];
		cout << "rf["<<(int)tmp<<"]="<<(float32_t)rf[tmp]<<endl;
	}
	cl+=4;
}

void OpcodeProcessor::mov_rrf_rrf(){
	cl++;
	bool rx=op_data[cl]&0x80;
	bool ry=op_data[cl+1]&0x80;
	if((rx^ry)==0){ //matching registers
		if(rx!=0){ //float register
			rf[op_data[cl]]=rf[op_data[cl+1]];
		}else{ //int register
			r[op_data[cl]]=r[op_data[cl+1]];
		}
	}else{ //different regs
		if(rx==1){ //target is float and source is int
			uint32_t convi=r[op_data[cl+1]];
			
			rf[op_data[cl]]=*(float32_t*)&convi;
			
		}else{ //target is int and source is float
			float32_t convf=rf[op_data[cl+1]];
			r[op_data[cl]]=*(uint32_t*)&convf;
		}
	}
	
	cl++;
}


void OpcodeProcessor::push_rrf(){
	cl++;
	if((op_data[cl]&0x80)!=0){ //float register
		push(*(uint32_t*)&rf[(op_data[cl]&0x7F)]); //clears off top bit
	}else{
		push(r[op_data[cl]]);
	}
	
}

void OpcodeProcessor::pop_rrf(){
	cl++;
	if((op_data[cl]&0x80)!=0){ //float register
		*(uint32_t*)&rf[(op_data[cl]&0x7F)]=pop();
	}else{
		r[op_data[cl]]=pop();
	}
	
}


void OpcodeProcessor::mov_rpif_immdimmf(){
	cl++;
	/*bool is_float=op_data[cl]&0x80;
	if(is_float){ 
		mem.dd[r[op_data[cl]]]=*(uint32_t*)&op_data[cl+1];
	}else{*/
	///It doesn't matter if it's a float or not, it's just memory.
	mem.dd[r[op_data[cl]]]=*(uint32_t*)&op_data[cl+1];  
	//}
	cl+=4;
}









