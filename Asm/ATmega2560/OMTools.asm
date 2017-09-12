;**************************************************
;
; OMTools
;
; This simple library provides initialization code for
; the stack as well as helper functions for different kinds
; of tasks such as math.
;
; Oskar Mendel
; 09/12/2017

;**************************************************
; STACK INITIALIZATION
;**************************************************
ldi r16, HIGH(RAMEND)				; r16 = High part of RAMEND address. 
out SPH, r16						; SPH = High part of RAMEND address.
ldi r16, LOW(RAMEND)				; r16 = Low part of RAMEND address.
out SPL, r16						; SPL = Low Part of RAMEND address.

rjmp Main							; Jumping to Main.