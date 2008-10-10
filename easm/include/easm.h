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



#ifndef EASM_H
#define EASM_H

#include <iostream>
#include <regex.h>
#include <string>

using namespace std;

static const uint32_t REGEX_MAX=64; //maximum number of regular expressions per match(by default)



/**Regular Expression Syntax Rules**/
static const string label_decl_re_pattern="_[a-zA-Z0-9_]*: "; //label declaration
static const string label_re_pattern="_[a-zA-Z0-9_]* "; //label usage(as a variable)
static const string register_re_pattern="\s?(?=,)?r[0-9]{1,3}(?=,)?[^[A-Za-z0-9_]"; //register usage







class RegEx{
	regex_t re;
	regmatch_t ma;
	string *matches;
	uint32_t matches_limit;
	bool no_match;
	
	public:
	RegEx(string pattern,int cflags=REG_EXTENDED);
	~RegEx();
	string operator[](uint32_t) const;
	int32_t match(string test,uint32_t max=REGEX_MAX,int flags=0); //returns number of matches
	void free(); //This will free memory from the last match.
	uint32_t number_matches();
};























#endif

