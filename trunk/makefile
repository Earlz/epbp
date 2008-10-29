#<Copyright Header>
#Copyright (c) 2007 - 2008 Jordan "Earlz/hckr83" Earls  <http://www.Earlz.biz.tm>
#All rights reserved.
#
#Redistribution and use in source and binary forms, with or without
#modification, are permitted provided that the following conditions
#are met:
#
#1. Redistributions of source code must retain the above copyright
#   notice, this list of conditions and the following disclaimer.
#2. Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the distribution.
#3. The name of the author may not be used to endorse or promote products
#   derived from this software without specific prior written permission.
#   
#THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
#INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
#AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
#THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
#ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#This file is part of the EPBP project
#</Copyright Header>



_OBJS=objs/main.o objs/opcodes.o objs/bcve.o objs/epbp_file.o\
 objs/store_op.o objs/cmp_op.o objs/math_op.o objs/bitwise_op.o\
 objs/float_op.o objs/sys_op.o objs/flow_op.o objs/xmod.o

CPPFLAGS=-static -static-libgcc -Wall -pedantic -g -I./include
#Note: Right now, O3 does work



default: opcodes modules asm system link

test_op.asm:
	yasm -o bin/test_op.ebc src/test_op.asm

main.cpp:
	g++ $(CPPFLAGS) -c src/main.cpp -o objs/main.o

bcve.cpp:
	g++ $(CPPFLAGS) -c src/bcve.cpp -o objs/bcve.o

opcodes.cpp:
	g++ $(CPPFLAGS) -c src/opcodes.cpp -o objs/opcodes.o

epbp_file.cpp:
	g++ $(CPPFLAGS) -c src/epbp_file.cpp -o objs/epbp_file.o

store_op.cpp:
	g++ $(CPPFLAGS) -c src/store_op.cpp -o objs/store_op.o

cmp_op.cpp:
	g++ $(CPPFLAGS) -c src/cmp_op.cpp -o objs/cmp_op.o

math_op.cpp:
	g++ $(CPPFLAGS) -c src/math_op.cpp -o objs/math_op.o

bitwise_op.cpp:
	g++ $(CPPFLAGS) -c src/bitwise_op.cpp -o objs/bitwise_op.o

float_op.cpp:
	g++ $(CPPFLAGS) -c src/float_op.cpp -o objs/float_op.o

sys_op.cpp:
	g++ $(CPPFLAGS) -c src/sys_op.cpp -o objs/sys_op.o


flow_op.cpp:
	g++ $(CPPFLAGS) -c src/flow_op.cpp -o objs/flow_op.o

xmod.cpp:
	g++ $(CPPFLAGS) -c src/xmod.cpp -o objs/xmod.o




clean:
	rm -f $(_OBJS)
	


_MODULE_OBJS=objs/xmodules/core.o

modules_core.cpp:
	g++ $(CPPFLAGS) -c xmodules/core.cpp -o objs/xmodules/core.o
	







modules: sys_op.cpp xmod.cpp modules_core.cpp


link:
	g++ $(CPPFLAGS) -o bin/epbp $(_OBJS) $(_MODULE_OBJS)
	

	
.PHONY: opcodes modules asm system

#.PHONY does nothing on BSD make? makes GNU make behave more like BSD make..
	
opcodes: opcodes.cpp store_op.cpp cmp_op.cpp bitwise_op.cpp float_op.cpp sys_op.cpp flow_op.cpp math_op.cpp



asm: test_op.asm

system: main.cpp bcve.cpp epbp_file.cpp






#Don't forget to 'make link' !!







