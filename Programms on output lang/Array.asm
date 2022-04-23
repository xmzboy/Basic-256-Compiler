.686P
.model flat, stdcall

include \masm32\include\masm32rt.inc
include Macros.txt

.data
	G real8 10 dup (0.)
.code

main proc
	local X : real8
	push 0h
	fld real4 ptr [esp]
	fstp X
startFor1:
	fld FP8(9.0)
	fld X
	fcompp
	fstsw ax
	sahf
	ja endFor1
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
	jmp startFor1
endFor1:
	inkey
	invoke ExitProcess, 0
main endp
end main