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

#ifndef XMOD_H
#define XMOD_H


#include <epbp.h>



//Module Numbers

static const uint32_t XCORE_MODULE=0;


extern uint32_t xmodule_last_error;

class XModule{
	protected:
		string name_;
		struct{
			uint8_t v1,v2,v3;
			uint32_t priv;
			uint8_t name[9];
		}info;
		bool good_;

		uint8_t scratch[9];
	public:
		XModule(){
			good_=0;
			info.v1=0;
			info.v2=0;
			info.v3=0;
			info.priv=0;
			memcpy(info.name,"<blank>",8);
			xmodule_last_error=1;
		}
		~XModule(){}
		bool good(){return good_;}
		uint32_t version(){return (info.v1<<16)|(info.v2<<8)|info.v3;}
		uint32_t privilege(){return info.priv;}
		
		uint8_t *name(){
			memcpy(scratch,info.name,9);
			return scratch;
		}
		
		void Xcall(OpcodeProcessor &cpu,uint32_t func){} //only should work if init called before-hand.
		void init(uint32_t args){} //will initalize the module for Xcall use.
		void unload(){} //should unload any memory currently in use, makes it so Xcall cannot be used. 
		void *get_info(){return (void*)&info;}
};
	
	
	
/**Insert module class definitions here**/

class XCore : public XModule{
	//OpcodeProcessor *c;
	public:
	XCore();
	~XCore();
	void Xcall(OpcodeProcessor &cpu,uint32_t func);
	void init(uint32_t args);
	void unload();	
		
	private:
	uint32_t out_error(uint32_t str);
};









class XList{
	protected:
		XCore module_xcore;
		
	public:
		XList(){}
		bool load(uint32_t num,uint32_t args);
		void call(OpcodeProcessor &this_cpu,uint32_t num,uint32_t func);
		void unload(uint32_t num);
		void *info(uint32_t num);
};


/*
class XArgs{
	OpcodeProcessor *xcpu;
	
	public:
	XArgs(OpcodeProcessor *this_cpu);
	~XArgs();
	uint32_t getstackarg(uint32_t n); //get the nth element from the top of the stack.
	void putstackarg(uint32_t n,uint32_t val); //change the nth stack element located n-top of stack.
	uint32_t getcallarg(uint32_t n); //get the nth call stack element off the top of the stack.
	void putcallarg(uint32_t n,uint32_t val);
	
	
	
};
*/




extern XList xlist;



#endif
