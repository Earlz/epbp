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



#ifndef PLASM_H
#define PLASM_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


static const uint32_t MAX_LINES=4096;



void PlasmException(uint32_t code);


class Parser{	
	string *str;
	uint32_t line;
	uint32_t limit;
	public:
	Parser(istream &inf);
	void setline(uint32_t num); //tells it to operate on this line of the file.
	string operator[](uint32_t n); //this returns a "word" out of the current string.
	string getline(uint32_t num); //get a whole line, unfiltered.
	
	
	
	
};











/**Intended matching:
Registers: (where it would match the r0 part and only the r0 part)
matches:
mov r0,r0
mov r0 , r0
mov r0,1
mov    r0     ,     r0    

not-matches:
mov r0a,r0b
mov r01234,r01234
mov r0_, r0p





*/























#endif

