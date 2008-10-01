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

;;Macros;;

%macro mov_r_immd 2
	db 0x10
	db %1
	dd %2
%endmacro

%macro mov_rf_immf 2
db 0x10
db (%1)+128
dd %2
%endmacro

%macro mov_r_r 2
db 0x11
db %1
db %2
%endmacro

%macro mov_rf_r 2
db 0x11
db %1+128
db %2
%endmacro

%macro mov_r_rf 2
db 0x11
db %1
db %2+128
%endmacro
%macro mov_rf_rf 2
db 0x11
db %1+128
db %2+128
%endmacro



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

;start code
db 0x00 ;nop
db 0x00 ;nop

db 0x10 ;mov /
db 1 ;r1,
dd 0x1FF1FF1A ;<<

db 0xff ;dmp

db 0 ;nop

db 0x10 ;mov /
db 2+128 ;rf2
dd 3.15 ;<<

db 0xff ;dmp

db 0x11 ;mov /
db 3 ;r3
db 1 ;r1 

db 0xff ;dmp

db 0x11 ;mov /
db 4+128 ;rf4
db 2+128 ;rf2

db 0xff ;dmp

db 0x10 ;mov /
db 6 ;r6
dd 0x11223344 ;<<

db 0xFF ;dmp

db 0x11 ;mov /
db 0+128 ;rf0
db 6 ;r6

db 0x11 ;mov /
db 0 ;r0
db 0+128 ;rf0


db 0xFF ;dmp


db 0x10 ;mov/
db 0 ;r0
dd 4.83 ;<<

db 0x11 ;mov/
db 0+128 ;rf0
db 0 ;r0

db 0xFF ;dmp




db 0xFE ;exit
db 0x00 ;nop

code_end:

data_start:

db "Hello There Mr. Worldgdb."
data_end:



