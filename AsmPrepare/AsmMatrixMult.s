	.file	"AsmMatrixMult.cpp"
	.text
	.globl	_Z11ASMmtrxMultiPfS_
	.def	_Z11ASMmtrxMultiPfS_;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z11ASMmtrxMultiPfS_
_Z11ASMmtrxMultiPfS_:
.LFB792:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movq	%r8, 32(%rbp)
/APP
 # 11 "AsmMatrixMult.cpp" 1
	MultMatrixLoop:movups (%r8), %xmm0
	movups 16(%r8), %xmm1
	movups 32(%r8), %xmm2
	movups 48(%r8), %xmm3
	mulps (%rdx), %xmm0
	mulps (%rdx), %xmm1
	mulps (%rdx), %xmm2
	mulps (%rdx), %xmm3
	haddps %xmm1, %xmm0
	haddps %xmm3, %xmm2
	haddps %xmm2, %xmm0
	movups %xmm0, (%rdx)
	add $16, %rdx
	loop MultMatrixLoop
	
 # 0 "" 2
/NO_APP
	nop
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z7ASMmovePfS_
	.def	_Z7ASMmovePfS_;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z7ASMmovePfS_
_Z7ASMmovePfS_:
.LFB793:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$112, %rsp
	.seh_stackalloc	112
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movq	16(%rbp), %rax
	movq	%rax, -112(%rbp)
	movq	-112(%rbp), %rax
	movups	(%rax), %xmm0
	movaps	%xmm0, -16(%rbp)
	movq	24(%rbp), %rax
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rax
	movups	(%rax), %xmm0
	movaps	%xmm0, -32(%rbp)
	movaps	-16(%rbp), %xmm0
	movaps	%xmm0, -80(%rbp)
	movaps	-32(%rbp), %xmm0
	movaps	%xmm0, -96(%rbp)
	movaps	-80(%rbp), %xmm0
	addps	-96(%rbp), %xmm0
	movaps	%xmm0, -16(%rbp)
	movq	16(%rbp), %rax
	movq	%rax, -40(%rbp)
	movaps	-16(%rbp), %xmm0
	movaps	%xmm0, -64(%rbp)
	movaps	-64(%rbp), %xmm0
	movq	-40(%rbp), %rax
	movups	%xmm0, (%rax)
	nop
	nop
	addq	$112, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z11ASMmoveBackPfS_
	.def	_Z11ASMmoveBackPfS_;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z11ASMmoveBackPfS_
_Z11ASMmoveBackPfS_:
.LFB794:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
/APP
 # 52 "AsmMatrixMult.cpp" 1
	movups (%rcx), %xmm0
	subps (%rdx), %xmm0
	movups %xmm0, (%rcx)
	
 # 0 "" 2
/NO_APP
	nop
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z8ASMscalePfS_S_
	.def	_Z8ASMscalePfS_S_;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z8ASMscalePfS_S_
_Z8ASMscalePfS_S_:
.LFB795:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movq	%r8, 32(%rbp)
/APP
 # 62 "AsmMatrixMult.cpp" 1
	movups (%rcx), %xmm0
	subps (%rdx), %xmm0
	mulps (%r8), %xmm0
	addps (%rdx), %xmm0
	movups %xmm0, (%rcx)
	
 # 0 "" 2
/NO_APP
	nop
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z14to_zero_matrixPf
	.def	_Z14to_zero_matrixPf;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z14to_zero_matrixPf
_Z14to_zero_matrixPf:
.LFB796:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movq	%rcx, 16(%rbp)
/APP
 # 74 "AsmMatrixMult.cpp" 1
	subps %xmm4, %xmm4
	movups %xmm4, (%rcx)
	movups %xmm4, 16(%rcx)
	movups %xmm4, 32(%rcx)
	movups %xmm4, 48(%rcx)
	
 # 0 "" 2
/NO_APP
	nop
	popq	%rbp
	ret
	.seh_endproc
	.def	_ZL12to_xy_matrixPff;	.scl	3;	.type	32;	.endef
	.seh_proc	_ZL12to_xy_matrixPff
_ZL12to_xy_matrixPff:
.LFB797:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movss	%xmm1, 24(%rbp)
	movq	16(%rbp), %rcx
	call	_Z14to_zero_matrixPf
	pxor	%xmm2, %xmm2
	cvtss2sd	24(%rbp), %xmm2
	movq	%xmm2, %rax
	movq	%rax, %xmm0
	call	cos
	cvtsd2ss	%xmm0, %xmm0
	movq	16(%rbp), %rax
	movss	%xmm0, (%rax)
	pxor	%xmm3, %xmm3
	cvtss2sd	24(%rbp), %xmm3
	movq	%xmm3, %rax
	movq	%rax, %xmm0
	call	sin
	movq	16(%rbp), %rax
	addq	$4, %rax
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, (%rax)
	movq	16(%rbp), %rax
	addq	$4, %rax
	movss	(%rax), %xmm0
	movq	16(%rbp), %rax
	addq	$16, %rax
	movss	.LC0(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movss	%xmm0, (%rax)
	movq	16(%rbp), %rax
	leaq	20(%rax), %rdx
	movq	16(%rbp), %rax
	movss	(%rax), %xmm0
	movss	%xmm0, (%rdx)
/APP
 # 91 "AsmMatrixMult.cpp" 1
	fld1
	fsts 40(%rcx)
	fstps 60(%rcx)
	
 # 0 "" 2
/NO_APP
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	_ZL12to_xz_matrixPff;	.scl	3;	.type	32;	.endef
	.seh_proc	_ZL12to_xz_matrixPff
_ZL12to_xz_matrixPff:
.LFB798:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movss	%xmm1, 24(%rbp)
	movq	16(%rbp), %rcx
	call	_Z14to_zero_matrixPf
	pxor	%xmm2, %xmm2
	cvtss2sd	24(%rbp), %xmm2
	movq	%xmm2, %rax
	movq	%rax, %xmm0
	call	cos
	cvtsd2ss	%xmm0, %xmm0
	movq	16(%rbp), %rax
	movss	%xmm0, (%rax)
	pxor	%xmm3, %xmm3
	cvtss2sd	24(%rbp), %xmm3
	movq	%xmm3, %rax
	movq	%rax, %xmm0
	call	sin
	cvtsd2ss	%xmm0, %xmm0
	movq	16(%rbp), %rax
	addq	$8, %rax
	movss	.LC0(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movss	%xmm0, (%rax)
	movq	16(%rbp), %rax
	addq	$8, %rax
	movss	(%rax), %xmm0
	movq	16(%rbp), %rax
	addq	$32, %rax
	movss	.LC0(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movss	%xmm0, (%rax)
	movq	16(%rbp), %rax
	leaq	40(%rax), %rdx
	movq	16(%rbp), %rax
	movss	(%rax), %xmm0
	movss	%xmm0, (%rdx)
/APP
 # 106 "AsmMatrixMult.cpp" 1
	fld1
	fsts 20(%rcx)
	fstps 60(%rcx)
	
 # 0 "" 2
/NO_APP
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	_ZL12to_yz_matrixPff;	.scl	3;	.type	32;	.endef
	.seh_proc	_ZL12to_yz_matrixPff
_ZL12to_yz_matrixPff:
.LFB799:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movss	%xmm1, 24(%rbp)
	movq	16(%rbp), %rcx
	call	_Z14to_zero_matrixPf
	pxor	%xmm2, %xmm2
	cvtss2sd	24(%rbp), %xmm2
	movq	%xmm2, %rax
	movq	%rax, %xmm0
	call	cos
	movq	16(%rbp), %rax
	addq	$20, %rax
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, (%rax)
	pxor	%xmm3, %xmm3
	cvtss2sd	24(%rbp), %xmm3
	movq	%xmm3, %rax
	movq	%rax, %xmm0
	call	sin
	movq	16(%rbp), %rax
	addq	$24, %rax
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, (%rax)
	movq	16(%rbp), %rax
	addq	$24, %rax
	movss	(%rax), %xmm0
	movq	16(%rbp), %rax
	addq	$36, %rax
	movss	.LC0(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movss	%xmm0, (%rax)
	movq	16(%rbp), %rax
	leaq	40(%rax), %rdx
	movq	16(%rbp), %rax
	movss	20(%rax), %xmm0
	movss	%xmm0, (%rdx)
/APP
 # 121 "AsmMatrixMult.cpp" 1
	fld1
	fsts (%rcx)
	fstps 60(%rcx)
	
 # 0 "" 2
/NO_APP
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z15ASMrotateMatrixPfS_S_S_
	.def	_Z15ASMrotateMatrixPfS_S_S_;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z15ASMrotateMatrixPfS_S_S_
_Z15ASMrotateMatrixPfS_S_S_:
.LFB800:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movq	%r8, 32(%rbp)
	movq	%r9, 40(%rbp)
/APP
 # 135 "AsmMatrixMult.cpp" 1
	mov %rcx, %rsi
	movups (%rdx), %xmm5
	movups 48(%rsi), %xmm6
	subps %xmm5, %xmm6
	movups %xmm6, 48(%rsi)
	
 # 0 "" 2
/NO_APP
	movq	32(%rbp), %rax
	movss	(%rax), %xmm0
	movq	40(%rbp), %rax
	movaps	%xmm0, %xmm1
	movq	%rax, %rcx
	call	_ZL12to_xy_matrixPff
	movq	40(%rbp), %rax
	movq	%rax, %r8
	movq	16(%rbp), %rdx
	movl	$4, %ecx
	call	_Z11ASMmtrxMultiPfS_
	movq	32(%rbp), %rax
	addq	$4, %rax
	movss	(%rax), %xmm0
	movq	40(%rbp), %rax
	movaps	%xmm0, %xmm1
	movq	%rax, %rcx
	call	_ZL12to_yz_matrixPff
	movq	40(%rbp), %rax
	movq	%rax, %r8
	movq	16(%rbp), %rdx
	movl	$4, %ecx
	call	_Z11ASMmtrxMultiPfS_
	movq	32(%rbp), %rax
	addq	$8, %rax
	movss	(%rax), %xmm0
	movq	40(%rbp), %rax
	movaps	%xmm0, %xmm1
	movq	%rax, %rcx
	call	_ZL12to_xz_matrixPff
	movq	40(%rbp), %rax
	movq	%rax, %r8
	movq	16(%rbp), %rdx
	movl	$4, %ecx
	call	_Z11ASMmtrxMultiPfS_
/APP
 # 154 "AsmMatrixMult.cpp" 1
	movups 48(%rsi), %xmm6
	addps %xmm5, %xmm6
	movups %xmm6, 48(%rsi)
	
 # 0 "" 2
 # 162 "AsmMatrixMult.cpp" 1
	flds 4(%rsi)
	flds 16(%rsi)
	fstps 4(%rsi)
	fstps 16(%rsi)
	flds 8(%rsi)
	flds 32(%rsi)
	fstps 8(%rsi)
	fstps 32(%rsi)
	flds 12(%rsi)
	flds 48(%rsi)
	fstps 12(%rsi)
	fstps 48(%rsi)
	flds 24(%rsi)
	flds 36(%rsi)
	fstps 24(%rsi)
	fstps 36(%rsi)
	flds 28(%rsi)
	flds 52(%rsi)
	fstps 28(%rsi)
	fstps 52(%rsi)
	flds 44(%rsi)
	flds 56(%rsi)
	fstps 44(%rsi)
	fstps 56(%rsi)
	
 # 0 "" 2
/NO_APP
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 16
.LC0:
	.long	-2147483648
	.long	0
	.long	0
	.long	0
	.ident	"GCC: (Rev5, Built by MSYS2 project) 10.3.0"
	.def	cos;	.scl	2;	.type	32;	.endef
	.def	sin;	.scl	2;	.type	32;	.endef
