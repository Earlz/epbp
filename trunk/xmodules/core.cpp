/*
<Copyright Header>
Copyright (c) 2007 - 2008 Jordan "Earlz/hckr83" Earls  
<http://www.Earlz.biz.tm>
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
   
THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED 
WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

This file is part of the EPBP project
</Copyright Header>
*/

#include <xmod.h>

/**Functions:
init(x) - arguments are not used for this module.


0: testing stuff. (unused)
1: out_error(char *string); this will output the error message in string. If the current device or priveldges do not allow visual output, it may attempt to output things by turning an LED on or a beep or something similar to tell the user an error occured.

2:malloc(int size):(void *free_memory); this will allocate a memory block of 'size' and then place that address in 'free_memory'.

3:free(void *memory): bool error; if all is good, then error will be zero. This frees a block of memory.

4:



*/




XCore::XCore(){
	info.v1=0;
	info.v2=0;
	info.v3=1;
	info.priv=PLEVEL_ALL;
	memcpy(info.name,"xcore",6);
	good_=0;
	xmodule_last_error=0;
}


XCore::~XCore(){
	if(good_==1){
		unload();
	}
}

void XCore::init(uint32_t args){
	cout<<"xcore::init()"<<endl;
	good_=1;

}


void XCore::unload(){
	good_=0;
}

void XCore::Xcall(OpcodeProcessor &cpu,uint32_t func){
	switch(func){
		case 0:
			cout <<"An XCall Function!! w00t!" << endl;
		break;
		case 1: //out_error
			cpu.push(out_error(cpu.pop()));
			
		break;
		
		
	default:
		cerr << "undefined function in xcore: " << func << endl;
	break;
	}
}

uint32_t XCore::out_error(uint32_t str){
	while(mem.db[str]!=0){
		putc(mem.db[str],stdout);
		str++;
	}
	return 0;
}












