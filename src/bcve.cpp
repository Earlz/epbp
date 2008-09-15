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






//Byte Code Virtual Environment
//This includes register class, memory class, and the xcall mechanism

/**Decremented --hard to code around the virtual machine object. Solution-> split components
	into individual objects.
**
VirtualMachine::VirtualMachine(){
	memory=new uint8_t[0x10000];
	size_memory=0x10000;
	regbank=0;
	
	
}


VirtualMachine::~VirtualMachine(){
	delete []memory;
	
}


uint8_t VirtualMachine::ReadByte(uint32_t loc){
	if(loc>size_memory){
		exception(MEMORY_FAULT);
	}
	return memory[loc];
}

uint16_t VirtualMachine::ReadWord(uint32_t loc){
	if(loc>(size_memory-1)){
		exception(MEMORY_FAULT);
	}
	return (uint16_t)memory[loc];
}

uint32_t VirtualMachine::ReadDword(uint32_t loc){
	if(loc>(size_memory-3)){
		exception(MEMORY_FAULT);
	}
	return (uint32_t)memory[loc];
}


void VirtualMachine::WriteByte(uint32_t loc,uint8_t d){
	if(loc>(size_memory)){
		exception(MEMORY_FAULT);
	}
	memory[loc]=d;
}

void VirtualMachine::WriteWord(uint32_t loc,uint16_t d){
	if(loc>(size_memory-1)){
		exception(MEMORY_FAULT);
	}
	*(uint16_t*)&memory[loc]=d;
}
void VirtualMachine::WriteDword(uint32_t loc,uint32_t d){
	if(loc>(size_memory-3)){
		exception(MEMORY_FAULT);
	}
	*(uint32_t*)&memory[loc]=d;
}

void VirtualMachine::SetRegisterBank(uint32_t loc){
	if(loc>(size_memory-(256*4)+1)){
		exception(MEMORY_FAULT);
	}
	regbank=loc;
}

uint32_t VirtualMachine::GetRegisterBank(){
	return regbank;
}

*/





