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

/**This file contains all of the opcodes related to comparing two values 
and modifying the TR register**/

#include <epbp.h>


void OpcodeProcessor::cls_rrf_rrf(){
	cl++;
	
	bool is_floatl=op_data[cl]&0x80;
	bool is_floatr=op_data[cl+1]&0x80;
	
	if((is_floatl^is_floatr)==0){ //matching registers
		if(is_floatr){ //float register
			tr=rf[op_data[cl]]<rf[op_data[cl+1]];
		}else{ //int register
			tr=r[op_data[cl]]<r[op_data[cl+1]];
		}
	}else{ //different regs
		if(is_floatl==1){ //lvalue is float, rvalue is int
			tr=rf[op_data[cl]]<*(float32_t*)&r[op_data[cl+1]];;
			
		}else{ //left is int and right is float
			tr=r[op_data[cl]]<*(uint32_t*)&rf[op_data[cl+1]];
		}
	}
	cl++;
		
}

void OpcodeProcessor::cle_rrf_rrf(){
	cl++;
	
	bool is_floatl=op_data[cl]&0x80;
	bool is_floatr=op_data[cl+1]&0x80;
	
	if((is_floatl^is_floatr)==0){ //matching registers
		if(is_floatr){ //float register
			tr=rf[op_data[cl]]<=rf[op_data[cl+1]];
		}else{ //int register
			tr=r[op_data[cl]]<=r[op_data[cl+1]];
		}
	}else{ //different regs
		if(is_floatl==1){ //lvalue is float, rvalue is int
			tr=rf[op_data[cl]]<=*(float32_t*)&r[op_data[cl+1]];;
			
		}else{ //left is int and right is float
			tr=r[op_data[cl]]<=*(uint32_t*)&rf[op_data[cl+1]];
		}
	}
	cl++;
		
}

void OpcodeProcessor::cgt_rrf_rrf(){
	cl++;
	
	bool is_floatl=op_data[cl]&0x80;
	bool is_floatr=op_data[cl+1]&0x80;
	
	if((is_floatl^is_floatr)==0){ //matching registers
		if(is_floatr){ //float register
			tr=rf[op_data[cl]]>rf[op_data[cl+1]];
		}else{ //int register
			tr=r[op_data[cl]]>r[op_data[cl+1]];
		}
	}else{ //different regs
		if(is_floatl==1){ //lvalue is float, rvalue is int
			tr=rf[op_data[cl]]>*(float32_t*)&r[op_data[cl+1]];;
			
		}else{ //left is int and right is float
			tr=r[op_data[cl]]>*(uint32_t*)&rf[op_data[cl+1]];
		}
	}
	cl++;
		
}

void OpcodeProcessor::cge_rrf_rrf(){
	cl++;
	
	bool is_floatl=op_data[cl]&0x80;
	bool is_floatr=op_data[cl+1]&0x80;
	
	if((is_floatl^is_floatr)==0){ //matching registers
		if(is_floatr){ //float register
			tr=rf[op_data[cl]]>=rf[op_data[cl+1]];
		}else{ //int register
			tr=r[op_data[cl]]>=r[op_data[cl+1]];
		}
	}else{ //different regs
		if(is_floatl==1){ //lvalue is float, rvalue is int
			tr=rf[op_data[cl]]>=*(float32_t*)&r[op_data[cl+1]];;
			
		}else{ //left is int and right is float
			tr=r[op_data[cl]]>=*(uint32_t*)&rf[op_data[cl+1]];
		}
	}
	cl++;
		
}

void OpcodeProcessor::cne_rrf_rrf(){
	cl++;
	
	bool is_floatl=op_data[cl]&0x80;
	bool is_floatr=op_data[cl+1]&0x80;
	
	if((is_floatl^is_floatr)==0){ //matching registers
		if(is_floatr){ //float register
			tr=rf[op_data[cl]]!=rf[op_data[cl+1]];
		}else{ //int register
			tr=r[op_data[cl]]!=r[op_data[cl+1]];
		}
	}else{ //different regs
		if(is_floatl==1){ //lvalue is float, rvalue is int
			tr=rf[op_data[cl]]!=*(float32_t*)&r[op_data[cl+1]];;
			
		}else{ //left is int and right is float
			tr=r[op_data[cl]]!=*(uint32_t*)&rf[op_data[cl+1]];
		}
	}
	cl++;
		
}

void OpcodeProcessor::ceq_rrf_rrf(){
	cl++;
	
	bool is_floatl=op_data[cl]&0x80;
	bool is_floatr=op_data[cl+1]&0x80;
	
	if((is_floatl^is_floatr)==0){ //matching registers
		if(is_floatr){ //float register
			tr=rf[op_data[cl]]==rf[op_data[cl+1]];
		}else{ //int register
			tr=r[op_data[cl]]==r[op_data[cl+1]];
		}
	}else{ //different regs
		if(is_floatl==1){ //lvalue is float, rvalue is int
			tr=rf[op_data[cl]]==*(float32_t*)&r[op_data[cl+1]];;
			
		}else{ //left is int and right is float
			tr=r[op_data[cl]]==*(uint32_t*)&rf[op_data[cl+1]];
		}
	}
	cl++;
		
}














