;**************************************************
;
; OMTools
;
; This simple library provides initialization code for
; the stack as well as helper functions for different kinds
; of tasks such as math.
;
; Uses the three registers r23, r24 and r25 for its subroutines.
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

.DEF OMTools_X = r23
.DEF OMTools_Y = r24
.DEF OMTools_Z = r25

rjmp Main							; Jumping to Main.

;**************************************************
; Square
; This function uses the register 23 which is defined
; as OMTools_X and squares the value within it then
; stores the result back in OMTools_X
;
; @param OMTools_X - Value to square.
;**************************************************
OMTools_Square:
	mul OMTools_X, OMTools_X		; Square OMTools_X
	mov OMTools_X, r0				; Move the result back into OMTools_X
	
	clr r0							; Clear the result from the multiplication from r0.
	clr r1							; Clear the result from the multiplication from r1.
	
	ret