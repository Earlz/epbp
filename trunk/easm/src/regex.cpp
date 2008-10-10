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
#include <easm.h>



RegEx::RegEx(string pattern,int flags){
	int error;
	error=regcomp(&re,pattern.c_str(),flags);
	no_match=1;
	if(error){
		throw;
	}
}


int32_t RegEx::match(string test,uint32_t max,int flags){
	int error;
	uint32_t i;
	no_match=1;
	matches=new string[max];
	error=regexec(&re,(char*)test.c_str(),1,&ma,flags);
	if(error){
		no_match=1;
		matches_limit=0;
		delete []matches;
		return -1;
	}
	
	for(i=0;i<max;i++){
		matches[i]=test.substr(ma.rm_so,ma.rm_eo-ma.rm_so); //copy part of string to matches
		test.erase(ma.rm_so,ma.rm_eo-ma.rm_so); //delete matched part
		error=regexec(&re,test.c_str(),1,&ma,flags);
		if(error){
			break;
		}
		
	}
	/* debug stuff...
	uint32_t j;
	for(j=0;j<=i;j++){
		cout <<matches[j]<<endl;
	}
	
	matches_limit=i;
	cout <<matches_limit<<endl;
	*/
	matches_limit=i;
	no_match=0;
	return i+1;
}


RegEx::~RegEx(){
	delete []matches;
}

string RegEx::operator[](uint32_t n) const{
	if(no_match){return "";}
	if(n>matches_limit){
		return "";
	}else{
		return matches[n];
	}	
	
}

uint32_t RegEx::number_matches(){
	return matches_limit;
}

void RegEx::free(){
	if(no_match==0){
		delete []matches;
		no_match=1;
	}


}
