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


;**************************************************
; OMTools REGISTER DEFINITIONS
;**************************************************
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

;**************************************************
; Square root
; This function uses the fact that the sum of odd 
; numbers create square numbers. Values like 11 that
; doesn't have an integer as its square root will be
; truncated.
;
; Example:
;	1         = 1^2 = 1
;	1 + 3     = 2^2 = 4
;	1 + 3 + 5 = 3^2 = 9 
;
; @param OMTools_X - Value to take the square root of.
;**************************************************
OMTools_Squareroot:
	ldi OMTools_Y, 1				; Used for sum.

	OMTools_SquarerootLoop:
		sub OMTools_X, OMTools_Y	; Subtract the square with our current sum.
		brcs OMTools_SquarerootDone ; If carry flag got set by subtraction we are done.
		inc r0						; Increment counter.
		subi OMTools_Y, -2			; Get next odd number.
		rjmp OMTools_SquarerootLoop

	OMTools_SquarerootDone:
		mov OMTools_X, r0			; Move counter result to OMTools_X

		clr OMTools_Y				; Clear the helper registers.
		clr r0

		ret

;**************************************************
; Divide two single byte number.
; This function performs division using repeated
; subtraction, as long as the dividend is greater
; than the divisor we subtract the divisor from the
; dividend.
;
; @param OMTools_X - Value for the dividend.
; @param OMTools_Y - Value for the divisor.
;
; @returns OMTools_Z - Result of OMTools_X / OMTools_Y.
;**************************************************
OMTools_Div8:
	ldi OMTools_Z, 0			; Used as a counter

	OMTools_Div8Loop:
	sub OMTools_X, OMTools_Y	; Sumtract dividend with divisor.
	brcs OMTools_Div8Done		; Branch if OMTools_X < OMTools_Y.
	inc OMTools_Z				; Increment counter.
	rjmp OMTools_Div8Loop

	OMTools_Div8Done:

	clr OMTools_X				; Clear the used registers.
	clr OMTools_Y

	ret

;**************************************************
; Delay milliseconds.
; Uses OMTools_Y and OMTools_Z as variables for delaying
; by milliseconds.  
;
; Example:
;	OMTools_Y = 10
;	OMTools_Z = 100
;
; @param OMTools_Y -
; @param OMTools_Z -
;**************************************************
OMTools_WaitMilliseconds:
	L1: 
	dec OMTools_Z
	brne L1
	dec OMTools_Y
	brne L1

	ret