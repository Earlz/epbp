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


OpcodeProcessor::OpcodeProcessor(void *opcode_data,uint32_t code_sz,uint32_t flags){
	ops=(uint8_t*)opcode_data;
	cl=0;
	tr=false;
	sr=0x1000;
//	sr_size=0xFFF; //4k //--Depricated
	rx[0]=0;
	rx[1]=0;
	rx[2]=0;
	rx[3]=0;
	cs=new uint32_t[CALLSTACK_SIZE];
	csl=0;
	code_size=code_sz;
	cout << "EBC file dump: " << endl;
	for(uint32_t i=0;i<code_size;i++){
		cout << "|"<<hex<<(int)ops[i];
	}
	cout <<endl;
	
	
	
	
}



OpcodeProcessor::~OpcodeProcessor(){
	
	delete []ops;
}


void OpcodeProcessor::Cycle(){
	if(cl>=code_size){
		EpbpException(CL_OVERRUN);
	}
//	cout <<hex << "CL: " << cl << " op_data " << hex<<(int)op_data[cl] << endl;
	switch((uint8_t)ops[cl]){
		case 0x00: //nop
			cout << "nop" << endl;
		break;
		case 0xFE: //exit
			EpbpException(MANUAL_EXIT);
		break;
		case 0x10: 
			mov_Drf_immd();
		break;
		case 0x11:
			mov_Fr_Dr();
		break;
		case 0x12:
			mov_Ur_Dimmd();
		break;
		case 0x30:
			push_Fr();
		break;
		case 0x31:
			pop_Fr();
		break;
		
		
		case 0x14: //mov [r],immd/f
		//	mov_rpif_immdimmf();
		break;
		
		case 0x50: //jmp immdc
			jmp_immdc();
		break;
		case 0x60: //jit immdc
			jit_immdc();
		break;
		case 0x61: //jif immdc
			jif_immdc();
		break;
		case 0x80: //cls rrf rrf
		case 0x81:
		case 0x82:
		case 0x83:
		case 0x84:
		case 0x85:
		cxx_Fr_SDr();
		break;
			
		case 0x20:
			call_immdc();
		break;
		case 0xE0:
			ret();
		break;
		case 0xB0:
			add_Fr_immd();
		break;
		case 0xB1:
			sub_Fr_immd();
		break;
		case 0xB2:
			mul_Fr_immd();
		break;
		case 0xB3:
			div_Fr_immd();
		break;
		case 0xB4:
			mod_Dr_immd();
		break;
		case 0xE8:
			xload_Dr_Dr();
		break;
		case 0xE9:
			xcall_Dr_Dr();
		break;
		case 0xEA:
			xunload_Dr();
		break;
		case 0xEB:
			xerror_Dr();
		break;
		case 0xEC:
			xinfo_Dr_Lr();
		break;
		
		case 0xFF: //this is for debugging: this will dump the first 16 r and rf registers
			int i;
			for(i=0;i<16;i++){
				cout << "r["<<i<<"]=0x"<<hex<<r[i]<<"; ";
				cout << "rf["<<i<<"]="<<rf[i]<<endl;
			}
			cout <<"SR=0x"<<hex<<sr<<endl;
			cout <<"TR="<<tr<<endl;
			cout <<"CL="<<hex<<cl<<endl;
		
		break;
		
		
		default:
		EpbpException(BAD_OPCODE);	
			
	}
	cl++;
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

void OpcodeProcessor::push(uint32_t v){
	mem.dd[(sr*4)]=v;
	sr++;
}

uint32_t OpcodeProcessor::pop(){
	sr--;
	return mem.dd[(sr*4)]; 
}


bool CompareUnsigned(uint32_t x,uint32_t y, uint8_t compare){
	switch(compare){
		case COMPARE_EQ:
			return x==y;
		break;
		case COMPARE_NT:
			return x!=y;
		break;
		case COMPARE_GE:
			return x>=y;
		break;
		case COMPARE_LE:
			return x<=y;
		break;
		case COMPARE_GT:
			return x>y;
		break;
		case COMPARE_LT:
			return x<y;
		break;
		default:
			EpbpException(BAD_COMPARISON);
		break;
		
	}
	return 0; //avoids warnings
	
}

bool CompareSigned(int32_t x,int32_t y, uint8_t compare){
	switch(compare){
		case COMPARE_EQ:
			return x==y;
			break;
		case COMPARE_NT:
			return x!=y;
			break;
		case COMPARE_GE:
			return x>=y;
			break;
		case COMPARE_LE:
			return x<=y;
			break;
		case COMPARE_GT:
			return x>y;
			break;
		case COMPARE_LT:
			return x<y;
			break;
		default:
			EpbpException(BAD_COMPARISON);
			break;
	}
	return 0; //avoids warnings
	
	
}

bool CompareFloat(float32_t x,float32_t y,uint8_t compare){
	switch(compare){
		case COMPARE_EQ:
			return x==y;
			break;
		case COMPARE_NT:
			return x!=y;
			break;
		case COMPARE_GE:
			return x>=y;
			break;
		case COMPARE_LE:
			return x<=y;
			break;
		case COMPARE_GT:
			return x>y;
			break;
		case COMPARE_LT:
			return x<y;
			break;
		default:
			EpbpException(BAD_COMPARISON);
			break;
	}
	
	
	return 0; //avoids warnings
}








