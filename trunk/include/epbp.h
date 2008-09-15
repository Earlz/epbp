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



#ifndef EPBP_H
#define EPBP_H
#include <stdint.h>

static const uint32_t MEMORY_FAULT=1;


class VirtualMachine{
	uint8_t *memory;
	uint32_t size_memory; //size of memory
	uint32_t regbank;
	public:
	VirtualMachine();
	~VirtualMachine();
	uint32_t ReadDword(uint32_t loc); //memory functions
	uint16_t ReadWord(uint32_t loc);
	uint8_t ReadByte(uint32_t loc);
	void WriteDword(uint32_t loc,uint32_t d);
	void WriteWord(uint32_t loc,uint16_t d);
	void WriteByte(uint32_t loc,uint8_t d);
	
	
	uint32_t r(uint8_t num){ //register
		return (uint32_t)memory[regbank+num];
	}
	//void rb(uint8_t num,uint8_t d){
	//	memory[regbank+num]=d;
	//}
	void rd(uint8_t num,uint32_t d){
		*(uint32_t*)&memory[regbank+num]=d;
	}
	void SetRegisterBank(uint32_t loc); //This must be aligned on 256 byte bound
	uint32_t GetRegisterBank();
	
	
};



void exception(uint32_t);

class Dump{
	
	
};

class OpcodeProcessor{
	uint32_t op_cache;
	uint32_t *op_data;
	uint32_t cl; //current location
	bool tr; //truth register
	
	public:
	OpcodeProcessor(void *opcode_data,uint32_t sz_data,uint32_t flags);
	~OpcodeProcessor();
	void Cycle();
	Dump DumpState();
	void icall(uint32_t address); //equivalent of int, but much more elegant and sophisticated
};

















#endif





