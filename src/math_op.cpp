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

/**This file contains all the general math operations, such as adding 
and subtracting**/

#include <epbp.h>


void OpcodeProcessor::add_Fr_immd(){
	cl++;
	if(option_bit(ops[cl])){
		//float
		rf[ops[cl]]+=to_float(ops[cl+1]);
	}else{
		r[ops[cl]]+=to_int(ops[cl+1]);
	}
	cl+=4;
}

void OpcodeProcessor::sub_Fr_immd(){
	cl++;
	if(option_bit(ops[cl])){
		//float
		rf[ops[cl]]-=to_float(ops[cl+1]);
	}else{
		r[ops[cl]]-=to_int(ops[cl+1]);
	}
	cl+=4;
}

void OpcodeProcessor::mul_Fr_immd(){
	cl++;
	if(option_bit(ops[cl])){
		//float
		rf[ops[cl]]*=to_float(ops[cl+1]);
	}else{
		r[ops[cl]]*=to_int(ops[cl+1]);
	}
	cl+=4;
}


void OpcodeProcessor::div_Fr_immd(){
	cl++;
	if(option_bit(ops[cl])){
		//float
		if(to_float(ops[cl+1])==0.0){
			EpbpException(DIVIDE_BY_ZERO);
		}
		rf[ops[cl]]/=to_float(ops[cl+1]);
	}else{
		if(to_int(ops[cl+1])==0){
			EpbpException(DIVIDE_BY_ZERO);
		}
		r[ops[cl]]/=to_int(ops[cl+1]);
	}
	cl+=4;
}


void OpcodeProcessor::mod_Dr_immd(){
	cl++;
	if(option_bit(ops[cl])){
		//indirect
		if(to_int(ops[cl+1])==0.0){
			EpbpException(DIVIDE_BY_ZERO);
		}
		mem.dd[r[ops[cl]]]%=to_int(ops[cl+1]);
	}else{
		if(to_int(ops[cl+1])==0){
			EpbpException(DIVIDE_BY_ZERO);
		}
		r[ops[cl]]%=to_int(ops[cl+1]);
	}
	cl+=4;
}







