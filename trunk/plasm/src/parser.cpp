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

#include <plasm.h>

Parser::Parser(istream &inf){
	str=new string[MAX_LINES];
	uint32_t i=0;
	for(i=0;i<MAX_LINES;i++){
		if(inf.eof()==1){
			break;
		}
		std::getline(inf,str[i]);
	}
	line=0;
	limit=i;
}

void Parser::setline(uint32_t num){
	if(num>limit){
		PlasmException(0);
	}
	line=num;
}



string Parser::operator[](uint32_t num){
	uint32_t i;
	uint32_t first=str[line].find_first_not_of(" \n\t\r\b");
	if(first==string::npos){
		return "";
	}
	/*if(num==0){
		return str[line].substr(first,str[line].find_first_of(" \n\t\r\b,"));
	}*/
	uint32_t last=first;
	first=0;
	string used=str[line];
	for(i=0;i<=num;i++){
		cout <<"used: "<<used <<endl;
		cout <<"last: "<<last <<endl;
		used=used.erase(0,last+first);
		cout <<"-used: "<<used <<endl;
		last=used.find_first_of(" \n\t\r\b");
		first=used.find_first_not_of(" \n\t\r\b");
		last++;
		if(used[last]==','){ last--;}	
	}
	cout <<"---"<<used.substr(0,last-1)<<"|"<<endl;
		return used.substr(0,last-1);

}


	






