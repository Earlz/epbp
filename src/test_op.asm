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
;dd version (currently 0x0000F001
;dd code segment start
;dd code segment end
;dd data segment start
;dd data segment end
;dd space after data segment to load 
;dd <reserved>
org 0
dd 0x0000F001 
dd code_start
dd code_end
dd data_start
dd data_end
dd 0 ;amount of memory
dd 0 ;reserved



code_start:

mov_r_immd 0,0x11223344
mov_rf_immf 0,12.5
dmp

mov_rf_rf 1,0
mov_r_r 1,0
dmp

mov_r_immd 5,4.231 ;this is intentional
mov_rf_immf 5,0x44332211 ;intentional

mov_rf_r 4,5
mov_r_rf 4,5 ;will exchange values into r and rf #4

dmp

mov_r_immd 0,0xAABBCCDD
mov_r_immd 1,0xDDCCBBAA
mov_rf_immf 0,1.234
mov_rf_immf 1,4.321

push_r 0
push_rf 0
push_r 1
push_rf 1

pop_rf 7
pop_r 7
pop_rf 6
pop_r 6

dmp

mov_r_immd 6,8
mov_rpif_immdf 6,0x9A8A7A6A


dmp



mov_rrf






nop

exit
nop

code_end:

data_start:

db "Hello There Mr. Worldgdb."
data_end:



