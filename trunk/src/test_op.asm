;
;<Copyright Header>
;Copyright (c) 2007 - 2008 Jordan "Earlz/hckr83" Earls  <http://www.Earlz.biz.tm>
;All rights reserved.
;
;Redistribution and use in source and binary forms, with or without
;modification, are permitted provided that the following conditions
;are met:
;
;1. Redistributions of source code must retain the above copyright
;   notice, this list of conditions and the following disclaimer.
;2. Redistributions in binary form must reproduce the above copyright
;   notice, this list of conditions and the following disclaimer in the
;   documentation and/or other materials provided with the distribution.
;3. The name of the author may not be used to endorse or promote products
;   derived from this software without specific prior written permission.
;   
;THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
;INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
;AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
;THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
;EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
;PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
;OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
;WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
;OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
;ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

;This file is part of the EPBP project
;</Copyright Header>
;*/

%include "epbp_opcodes.asm" ;include file with opcode definitions





EPBP_header:
;in format of 
;db[4] the three characters 'EPBP'
;dd version of EBC format | version of bytecode. Currently 0x00020001
;dd Code generator ID. (optional, but can be used for optimizations). Shadows is 0x1000F001
;dd code segment start
;dd code segment end
;dd data segment start
;dd data segment end
;dd Heap size(after initial data segment). 
;dd <reserved>
org 0
EBC_header:
db 'E','P','B','P'
dd 0x00020001
dd 0x1000F001
dd code_start
dd code_end
dd data_start
dd data_end
dd 0 ;amount of memory
dd 0 ;reserved

EBC_header_end:
;this gap is ignored, so any extra "hidden" information can be put here
db "Test file for the Shadows EPBP implementation",0

code_start:

mov_Ur_Dimmd 0,0,0xFF00
mov_Ur_Dimmd 2,0,0xFF02

mov_Fr_Dr 0,1,0,2
mov_Fr_Dr 0,3,0,0

mov_Drf_immd 0,2,2.51
mov_Fr_Dr 1,0,0,2

push_Fr 0,0
push_Fr 1,0
pop_Fr 1,6
pop_Fr 0,6

mov_Ur_Dimmd 0,0,12
mov_Ur_Dimmd 2,0,10

mov_Drf_immd 0,0,12.0
mov_Drf_immd 0,2,10.0

cxx_Fr_SDr CGT,1,0,0,2 ;r0,r2

add_Fr_immd 0,0,2 
add_Fr_immd 1,0,2.5


mov_Ur_Dimmd 2,0,0
mov_Ur_Dimmd 3,0,0

xload_Dr_Dr 0,2,0,3

xcall_Dr_Dr 0,2,0,3

xunload_Dr 0,2




dmp

exit


code_end:

data_start:
times 256 dd 0 ;initial register area is cleared with 0s
db "Hello There Mr. Worldgdb."
data_end:



