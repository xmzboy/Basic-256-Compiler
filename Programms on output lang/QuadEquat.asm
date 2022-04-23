.686P
.model flat, stdcall

include \masm32\include\masm32rt.inc
include Macros.txt

.data
.code

main proc
	local a : real8
	local b : real8
	local m : real8
	local D : real8
	local X1 : real8
	local X2 : real8
	push 40000000h
	fld real4 ptr [esp]
	fstp a
	push 41100000h
	fld real4 ptr [esp]
	fchs
	fstp b
	push 40800000h
	fld real4 ptr [esp]
	fstp m
	push 0h
	fld real4 ptr [esp]
	fstp D
	fld b
	fld b
	fmul
	push 40800000h
	fld real4 ptr [esp]
	fld a
	fmul
	fld m
	fmul
	fsub
	fstp D
	fld FP8(0.0)
	fld D
	fcompp
	fstsw ax
	sahf
	jb IFLABEL
	fld b
	fchs
	fld D
	fsqrt
	fadd
	push 40000000h
	fld real4 ptr [esp]
	fld a
	fmul
	fdiv
	fstp X1
	fld b
	fchs
	fld D
	fsqrt
	fsub
	push 40000000h
	fld real4 ptr [esp]
	fld a
	fmul
	fdiv
	fstp X2
	fld X1
	TwoRegisterMacros
	push edx
	push eax
	printf("%f\n")
	pop eax
	pop eax
	fld X2
	TwoRegisterMacros
	push edx
	push eax
	printf("%f\n")
	pop eax
	pop eax
	jmp IFLABEL1
IFLABEL:
	printf("none")
	printf("\n")
IFLABEL1:
	inkey
	invoke ExitProcess, 0
main endp
end main