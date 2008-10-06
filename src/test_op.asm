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
ebc_header:
dd 0x0000F001 
dd code_start
dd code_end
dd data_start
dd data_end
dd 0 ;amount of memory
dd 0 ;reserved

ebc_header_end:
;this gap is ignored, so any extra "hidden" information can be put here

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


jmp_immdc label1

invld
invld
invld
invld



label1:
nop
dmp
nop


;label2: ;infinite loop test(success)
;nop
;jmp_immdc label2

;Trivial test of using integers to store floats. This should be true.
mov_rf_immf 0,3.5
mov_r_immd 1,3.5
ceq_rf_r 0,1

jit_immdc _good
jif_immdc _bad
invld

_bad:
mov_r_immd 0,0xBADBAD
jmp_immdc _skip
invld
_good:
mov_r_immd 0,0x13371337
jmp_immdc _skip
invld

_skip:
dmp


call_immdc test_proc

mov_r_immd 11,0x13371337
dmp


mov_r_immd 12,0
mov_r_immd 13,10000000
_loop1:

call_immdc burn_in
add_r_immd 12,1
cls_r_r 12,13
jit_immdc _loop1



dmp




nop

exit
nop




test_proc:
mov_r_immd 10,0x13371337
add_r_immd 10,1
dmp
ret




burn_in:
mov_r_immd 0,0
mov_r_immd 1,0
mov_r_immd 2,0
mov_r_immd 3,0
mov_r_immd 4,0
mov_r_immd 5,0
mov_r_immd 6,0
mov_r_immd 7,0
mov_r_immd 8,0
mov_r_immd 9,0
mov_r_immd 10,0
mov_r_immd 11,0
ret



code_end:

data_start:

db "Hello There Mr. Worldgdb."
data_end:



