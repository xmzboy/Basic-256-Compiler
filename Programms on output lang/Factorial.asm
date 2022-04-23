.686P
.model flat, stdcall

include \masm32\include\masm32rt.inc
include Macros.txt

.data
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
	inkey
	invoke ExitProcess, 0
main endp
end main