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
#include <stdlib.h>

//config
static const uint32_t CALLSTACK_SIZE=512;


static const uint32_t MEMORY_FAULT=1;
static const uint32_t COMPILETIME_DATA_OVERFLOW=2;
static const uint32_t NOT_IMPLEMENTED=3;
static const uint32_t BAD_BANK_ALIGNMENT=4;
static const uint32_t CALLSTACK_OVERFLOW=5;
static const uint32_t CALLSTACK_UNDERFLOW=6;

/** See deprication note in bcve.cpp
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
	bool ValidAddressRange_rw(uint32_t loc_start,uint32_t loc_end);
	
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

**/


class MemoryClass;
class MemoryByte{
	friend class MemoryClass;
	MemoryClass *m;
	void SetMemoryClass(MemoryClass *mem);
	public:

		uint8_t &operator[](uint32_t);
		uint8_t operator[](uint32_t) const;
};

class MemoryWord{
	friend class MemoryClass;
	MemoryClass *m;
	void SetMemoryClass(MemoryClass *mem);
	public:

		uint16_t &operator[](uint32_t);
		uint16_t operator[](uint32_t) const;
};

class MemoryDword{
	friend class MemoryClass;
	MemoryClass *m;
	void SetMemoryClass(MemoryClass *mem);
	public:

		uint32_t &operator[](uint32_t);
		uint32_t operator[](uint32_t) const;
};

class RegisterClass;

class MemoryClass{
	uint8_t *memory;
	uint32_t memory_size; //size of memory
	public:
	MemoryClass(uint32_t initial_size,void *initial_data=NULL,uint32_t data_size=0);
	~MemoryClass();
	bool ValidAddressRange_rw(uint32_t loc_start,uint32_t loc_end);
	uint32_t AllocateMemory(uint32_t size);
	bool FreeMemory(uint32_t loc);
	friend class MemoryByte;
	friend class MemoryWord;
	friend class MemoryDword;
	friend class RegisterClass;
	MemoryByte db;
	MemoryWord dw;
	MemoryDword dd;
	//These genious little classes make it so in code I can easily do memory.db[0]=5; 
	//to set just a byte and not a dword
};


//Conclusion: Registers are always fixed length. Writing just one byte clears the rest of the register
class RegisterClass{
	uint32_t bank;
	MemoryClass *mem;
	
	public:
	RegisterClass(MemoryClass *memory);
	~RegisterClass();
	uint32_t &operator[] (uint8_t); //write to register(return modifyable value)
	uint32_t operator[] (uint8_t) const; //read from register
	void SetBank(uint32_t loc);
	uint32_t GetBank();
};



void exception(uint32_t);

class Dump{
	
	
};

class OpcodeProcessor{
	uint32_t op_cache;
	uint32_t *op_data;
	uint32_t cl; //current location
	bool tr; //truth register
	uint32_t sr; //Stack register
	uint16_t sr_size; //stack size
	uint32_t rx[4]; //Xcall register.
	uint32_t *cs; //The Call Stack.
	uint32_t csl; //location inside the call stack.
	protected:
	void PushCS(uint32_t code);
	uint32_t PopCS();
	uint32_t PeekCS();
	public:
	OpcodeProcessor(void *opcode_data,uint32_t sz_data,uint32_t flags);
	~OpcodeProcessor();
	void Cycle();
	Dump DumpState();
	void icall(uint32_t address); //equivalent of int, but much more elegant and sophisticated
};

















#endif





