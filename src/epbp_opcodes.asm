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

;;This file contains macros for the EPBP opcode definitions. Note, these are very machine-level macros.
%xdefine HEADER_SIZE (7*4)


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

%macro nop 0
db 0x00
%endmacro

%macro exit 0
db 0xFE
%endmacro

%macro dmp 0;;Shadows Specific!!
db 0xFF
%endmacro

%macro push_r 1
db 0x12
db %1
%endmacro

%macro push_rf 1
db 0x12
db %1+128
%endmacro

%macro pop_r 1
db 0x13
db %1
%endmacro

%macro pop_rf 1
db 0x13
db %1+128
%endmacro

%macro mov_rpif_immdf 2
db 0x14
db %1
dd %2
%endmacro

%macro invld 0
db 0xBA
%endmacro

%macro jmp_immdc 1
db 0x50
dd %1-HEADER_SIZE ;7*4 is header size
%endmacro

%macro jit_immdc 1
db 0x60
dd %1-HEADER_SIZE
%endmacro

%macro jif_immdc 1
db 0x61
dd %1-HEADER_SIZE
%endmacro

%macro cls_r_r 2
db 0x80
db %1
db %2
%endmacro

%macro cls_rf_rf 2
db 0x80
db %1+128
db %2+128
%endmacro

%macro cls_r_rf 2
db 0x80
db %1
db %2+128
%endmacro

%macro cls_rf_r 2
db 0x80
db %1+128
db %2
%endmacro
;;;;;;
%macro cle_r_r 2
db 0x81
db %1
db %2
%endmacro

%macro cle_rf_rf 2
db 0x81
db %1+128
db %2+128
%endmacro

%macro cle_r_rf 2
db 0x81
db %1
db %2+128
%endmacro

%macro cle_rf_r 2
db 0x81
db %1+128
db %2
%endmacro
;;;;;;
%macro cgt_r_r 2
db 0x82
db %1
db %2
%endmacro

%macro cgt_rf_rf 2
db 0x82
db %1+128
db %2+128
%endmacro

%macro cgt_r_rf 2
db 0x82
db %1
db %2+128
%endmacro

%macro cgt_rf_r 2
db 0x82
db %1+128
db %2
%endmacro
;;;;;;
%macro cge_r_r 2
db 0x83
db %1
db %2
%endmacro

%macro cge_rf_rf 2
db 0x83
db %1+128
db %2+128
%endmacro

%macro cge_r_rf 2
db 0x83
db %1
db %2+128
%endmacro

%macro cge_rf_r 2
db 0x83
db %1+128
db %2
%endmacro
;;;;;;
%macro cne_r_r 2
db 0x84
db %1
db %2
%endmacro

%macro cne_rf_rf 2
db 0x84
db %1+128
db %2+128
%endmacro

%macro cne_r_rf 2
db 0x84
db %1
db %2+128
%endmacro

%macro cne_rf_r 2
db 0x84
db %1+128
db %2
%endmacro
;;;;;;
%macro ceq_r_r 2
db 0x85
db %1
db %2
%endmacro

%macro ceq_rf_rf 2
db 0x85
db %1+128
db %2+128
%endmacro

%macro ceq_r_rf 2
db 0x85
db %1
db %2+128
%endmacro

%macro ceq_rf_r 2
db 0x85
db %1+128
db %2
%endmacro
;;;;;;

%macro call_immdc 1
db 0x20
dd %1-HEADER_SIZE
%endmacro

%macro ret 0
db 0xE0
%endmacro

%macro add_r_immd 2
db 0xB0
db %1
dd %2
%endmacro

%macro add_rf_immf 2
db 0xB0
db %1+128
dd %2
%endmacro









%macro mov_Drf_immd 3
db 0x10
db %2|(%1<<7)
dd %3
%endmacro


%macro mov_Fr_Dr 4
db 0x11
db %2 | (%1 << 7)
db %4 | (%3 << 7)
%endmacro

%macro mov_Ur_Dimmd 3
db 0x12
db %1 | (%2 << 7)
dd %3
%endmacro






