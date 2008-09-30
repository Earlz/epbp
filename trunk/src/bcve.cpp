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
#include <string.h>





//Byte Code Virtual Environment
//This includes register class, memory class, and the xcall mechanism

MemoryClass::MemoryClass(uint32_t isize,void * idata,uint32_t data_size){
	if(data_size>isize){ //What to do if size of initial data is greater than memory size?
		EpbpException(COMPILETIME_DATA_OVERFLOW);
	}
	memory=new uint8_t[isize];
	memcpy(memory,idata,data_size);
	memory_size=isize;
	db.SetMemoryClass(this);
	dw.SetMemoryClass(this);
	dd.SetMemoryClass(this);
	
}

MemoryClass::~MemoryClass(){
	delete []memory;
}

bool MemoryClass::ValidAddressRange_rw(uint32_t start,uint32_t end){
	if(end>start){
		if(end>memory_size){
			return false;
		}else{
			return true;
		}
	}else{
		if(start>memory_size){
			return false;
		}else{
			return true;
		}
	}

}

uint32_t MemoryClass::AllocateMemory(uint32_t size){
	EpbpException(NOT_IMPLEMENTED);
	return 0;
	
}

bool MemoryClass::FreeMemory(uint32_t loc){
	EpbpException(NOT_IMPLEMENTED);
	return 0;
}

uint8_t &MemoryByte::operator[](uint32_t loc){
	if(loc>m->memory_size){
		EpbpException(MEMORY_FAULT);
	}
	return m->memory[loc];
}

uint8_t MemoryByte::operator[](uint32_t loc) const{
	if(loc>m->memory_size){
		EpbpException(MEMORY_FAULT);
	}
	return m->memory[loc];
}


uint16_t &MemoryWord::operator[](uint32_t loc){
	if(loc>(m->memory_size-1)){
		EpbpException(MEMORY_FAULT);
	}
	return (uint16_t&)m->memory[loc];
}

uint16_t MemoryWord::operator[](uint32_t loc) const{
	if(loc>(m->memory_size-1)){
		EpbpException(MEMORY_FAULT);
	}
	return (uint16_t)m->memory[loc];
}

uint32_t &MemoryDword::operator[](uint32_t loc){
	if(loc>(m->memory_size-3)){
		EpbpException(MEMORY_FAULT);
	}
	return (uint32_t&)m->memory[loc];
}

uint32_t MemoryDword::operator[](uint32_t loc) const{
	if(loc>(m->memory_size-3)){
		EpbpException(MEMORY_FAULT);
	}
	return (uint32_t)m->memory[loc];
}


void MemoryByte::SetMemoryClass(MemoryClass *mem){
	m=mem;
}
void MemoryWord::SetMemoryClass(MemoryClass *mem){
	m=mem;
}
void MemoryDword::SetMemoryClass(MemoryClass *mem){
	m=mem;
}



//RegisterClass

RegisterClass::RegisterClass(MemoryClass *memory){
	mem=memory;
	SetBank(0);
}

RegisterClass::~RegisterClass(){
	
}
/*No validity of memory needs to be checked cause this is done automatically*/
uint32_t &RegisterClass::operator[](uint8_t n){
	return (uint32_t&)mem->memory[bank+n*4];
}

uint32_t RegisterClass::operator[](uint8_t n) const{
	return (uint32_t)mem->memory[bank+n*4];
}

void RegisterClass::SetBank(uint32_t loc){
	if((loc&3)!=0){
		EpbpException(BAD_BANK_ALIGNMENT);
	}
	if(mem->ValidAddressRange_rw(loc,loc+(256*4))==false){
		EpbpException(MEMORY_FAULT);
	}
	bank=loc;
}

uint32_t RegisterClass::GetBank(){
	return bank;
}









