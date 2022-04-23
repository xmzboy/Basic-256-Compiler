.686P
.model flat, stdcall

include \masm32\include\masm32rt.inc
include Macros.txt

.data
	G real8 10 dup (0.)
.code
fact PROC n : real8
	fld FP8(2.0)
	fld n
	fcompp
	fstsw ax
	sahf
	jb IFLABEL
	fld n
	push 3f800000h
	fld real4 ptr [esp]
	fsub
	TwoRegisterMacros
	push edx
	push eax
	call fact
	push edx
	push eax
	fld qword ptr [esp]
	fld n
	fmul
	TwoRegisterMacros
	jmp IFLABEL1
IFLABEL:
	push 3f800000h
	fld real4 ptr [esp]
	TwoRegisterMacros
IFLABEL1:
	ret
fact ENDP

main proc
	local n : real8
	local a : real8
	local b : real8
	local m : real8
	local D : real8
	local X1 : real8
	local X2 : real8
	local X : real8
	printf("===========FACTORIAL============")
	printf("\n")
	push 3f800000h
	fld real4 ptr [esp]
	fstp n
startFor111:
	fld FP8(20.0)
	fld n
	fcompp
	fstsw ax
	sahf
	ja endFor111
	fld n
	TwoRegisterMacros
	push edx
	push eax
	call fact
	push edx
	push eax
	printf("%f\n")
	pop eax
	pop eax
	fld1
	fld n
	fadd
	fstp n
	jmp startFor111
endFor111:
	printf("==========QUAD-EQUAT============")
	printf("\n")
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
	jb IFLABEL111
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
	jmp IFLABEL1111
IFLABEL111:
	printf("no real roots")
	printf("\n")
IFLABEL1111:
	printf("=============ARRAY==============")
	printf("\n")
	push 0h
	fld real4 ptr [esp]
	fstp X
startFor111111:
	fld FP8(9.0)
	fld X
	fcompp
	fstsw ax
	sahf
	ja endFor111111
	fld X
	fld X
	fmul
	fld X
	FistpEBX
	fstp G [ ebx * type G]
	fld X
	FistpEBX
	printf("%f\n",G[ ebx * Type G])
	fld1
	fld X
	fadd
	fstp X
	jmp startFor111111
endFor111111:
	inkey
	invoke ExitProcess, 0
main endp
end main