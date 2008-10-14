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
#include <epbp_float.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

//config
static const uint32_t CALLSTACK_SIZE=512;


static const uint32_t MEMORY_FAULT=1;
static const uint32_t COMPILETIME_DATA_OVERFLOW=2;
static const uint32_t NOT_IMPLEMENTED=3;
static const uint32_t BAD_BANK_ALIGNMENT=4;
static const uint32_t CALLSTACK_OVERFLOW=5;
static const uint32_t CALLSTACK_UNDERFLOW=6;
static const uint32_t BAD_FILENAME=7;
static const uint32_t CL_OVERRUN=8;
static const uint32_t MANUAL_EXIT=9;
static const uint32_t BAD_OPCODE=10;
static const uint32_t BAD_COMPARISON=11;


static const uint8_t COMPARE_EQ=0; //equal to
static const uint8_t COMPARE_NT=1; //not equal
static const uint8_t COMPARE_GE=2; //greater or equal
static const uint8_t COMPARE_LE=3; //less or equal
static const uint8_t COMPARE_GT=4; //greater than
static const uint8_t COMPARE_LT=5; //less than



class OpcodeProcessor;

extern OpcodeProcessor cpu;


#define option_bit(x) \
	((x&0x80)>0)
#define to_float(x) \
	(*(float32_t*)&x)
#define to_int(x) \
	(*(uint32_t*)&x)




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
	friend class FloatRegisterClass;
	//friend class FloatIntRegisterClass;
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

class FloatRegisterClass {
	uint32_t bank;
	MemoryClass *mem;
	public:
	FloatRegisterClass(MemoryClass *memory);
	~FloatRegisterClass();
	float32_t &operator[](uint8_t); //write
	float32_t operator[] (uint8_t) const; //read
	void SetBank(uint32_t loc);
	uint32_t GetBank();
};

extern RegisterClass r;
extern FloatRegisterClass rf;



void EpbpException(uint32_t);

class Dump{
	
	
};

class OpcodeProcessor{
	uint32_t op_cache;
	uint8_t *ops;
	volatile uint32_t cl; //current location
	bool tr; //truth register
	uint32_t sr; //Stack register
/**	uint16_t sr_size; //stack size **-Depricated**/
	uint32_t rx[4]; //Xcall register.
	uint32_t *cs; //The Call Stack.
	uint32_t csl; //location inside the call stack.
	uint32_t code_size;
	protected:
	void PushCS(uint32_t code);
	uint32_t PopCS();
	uint32_t PeekCS();
	uint32_t CheckCodeAddresses(); //This should only be called at initialization to check all call addresses.
	public:
	OpcodeProcessor(void *opcode_data,uint32_t code_size,uint32_t flags=0);
	~OpcodeProcessor();
	void Cycle();
	Dump DumpState();
	void icall(uint32_t address); //equivalent of int, but much more elegant and sophisticated
	
	protected:
	/**See bottom of file for abreviation information on opcodes**/
	void mov_Drf_immd();
	void mov_Fr_Dr();
	void push_Fr();
	void pop_Fr();
	void mov_Ur_Dimmd();
	void jmp_immwc(); //not working
	void jmp_immdc();
	void jif_immdc();
	void jit_immdc();	
	void cxx_Fr_SDr(); //covers a set of cXX based opcodes for comparisons.
	void ret();
	void call_immdc();
	void add_Fr_immd();
	
	
	
	
	void push(uint32_t val); //not opcodes, just helpers
	uint32_t pop();
	
};


class EPBPFile{
	ifstream file;
	uint32_t version;
	uint32_t code_start;
	uint32_t code_size;
	uint32_t data_start;
	uint32_t data_size;
	uint32_t extra_space;
	
	public:
	EPBPFile(char* name);
	~EPBPFile();
	void *LoadCode();
	void *LoadData();
	uint32_t CodeSize();
	uint32_t DataSize();
	
};


extern EPBPFile ebc_file;
extern MemoryClass mem;

extern OpcodeProcessor cpu;


bool CompareUnsigned(uint32_t x,uint32_t y, uint8_t compare);
bool CompareSigned(int32_t x,int32_t y, uint8_t compare);
bool CompareFloat(float32_t x,float32_t y, uint8_t compare);






#endif


/**Opcode Legend:


***New Encoding with Option Bits***
r means register, rf means float register.
immd means immediate dword/dword float/pointer constant
immp is immediate pointer(only)
--//a prefix of f means float only, i means integer only, p means pointer only.

if r has no prefix, it is assumed integer only.
F means float option bit. If this is prefixed then the first bit will determine if the operation is float based.
I means index option bit. If this is prefixed before a memory operand, then it will determine if the displacement is multiplied or added.
D means direct option bit. If this is prefixed before a register or immediate(in some cases) then this means it can be referenced as a direct value(no dereference) or an indirect value(treated as a pointer)
L means lock option bit. This is for locking the address bus. Not currently used.
S means sign option bit. This determines if the operand should be treated as a signed value. This only affects integer values. This is used in comparisons and for sign extending.
U means unallocated option bit. If an option bit is later used such as on an immediate, it will actual go into this U option bit. This is only for naming purposes. 
B means byte. Note, this can only be used with indirect addressing. if set, then the address holds a byte, else holds a dword(the default and assumed type)
W means word. This can only be used with indirect addressing. If set, the address holds a word, else holds a dword.
Z means byte-word flipping of size. If set, then the address holds a byte, else it holds a word.

If D is encoded in the opcode, then B or W or Z can also be an option to choose how big the memory addressed operand is.
This can be done in a pop like this pop_D_Br which would be pop (byte/dword) [rx]


Code address options:
immdc is immediate dword code address
immbc is byte code address
immwc is word code address

In order for code address option bits to be used, one bit must be left off of the code address. For this reason, they will not commonly be used and instead encoded directly into the instruction.

R means relative address. If set, the code address will be added to the CL, rather than setting the CL absolutely.




For any instruction where an option bit can ambigously be assumed, to unambigously specify them, they should be placed as a seperate operand. For the inversion of an option bit, it should be prefixed with an X.
Such for a cgt where it is signed only(and thus int only)
cgt_XF_Dr_immd.


So this is what a few instructions mean.
Note, float registers can not be used as a pointer.

mov_Fr_Dr
mov float register/integer register, float register/[integer register]

mov_Ur_Dimmd
mov integer register, immediate dword/[immediate pointer]

cgt_Fr_SDr
if float option:
cgt float register, float register/[integer register]
else
cgt integer register, integer register ;if Sign bit set, compared as signed values, else compared unsigned.
endif


cgtS_Ur_Dimmd (This is a complex example)
Since the S is encoded directly into the instruction, it is always a signed comparison.
Because there is a bit directly in the opcode, this instruction will take up two opcodes.
one for the signed option bit version, and the other for the unsigned option bit version.
so it goes like this,
if S bit
cgt(signed) integer register, immdiate dword/[immediate pointer]
else
cgt(unsigned) integer register, immediate dword/[immediate pointer]

cgt_XF_Dr_immd:
This instruction is integer only(not float) so,
cgt integer register/[integer register], immediate dword
Note this is equivalent(by assumption) to cgt_Dr_immd. The long unassumed version should be used only where the definition of an opcode can be ambiguous.
such as
cgt_Ur_Bimmp
With this, it may be unclear as to if the comparison is signed or unsigned. Signing is assumed unsigned, but if both signed and unsigned instructions exist, this causes a problem.
So, if both instructions exist, they should be as follows
cgt_XS_Ur_Bimmp (unsigned)
cgt_S_Ur_Bimmp (signed) note, the byte of immp is also sign extended. If it should not be sign extended and assumed to be unsigned(although I don't think I will support signed-unsigned comparisons, I'll show it just for example) it will be:
cgt_S_Ur_XS_Bimmp








**/

