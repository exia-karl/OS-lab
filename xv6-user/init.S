	.file	"init.c"
	.option pic
	.option norelax
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align	3
.LC0:
	.string	"testing getcwd...\n"
	.align	3
.LC1:
	.string	"mnt"
	.align	3
.LC2:
	.string	"cwd = %s\n"
	.align	3
.LC3:
	.string	"real=%d utime=%d stime=%d cutime=%d cstime=%d\n"
	.align	3
.LC4:
	.string	"FAIL: no cpu time recorded\n"
	.align	3
.LC5:
	.string	"times test OK\n"
	.section	.text.startup,"ax",@progbits
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-208
	li	a2,0
	li	a1,1
	li	a0,2
	sd	ra,200(sp)
	sd	s0,192(sp)
	sd	s2,176(sp)
	sd	s1,184(sp)
	call	dev@plt
	li	a0,0
	call	dup@plt
	li	a0,0
	call	dup@plt
	lla	a0,.LC0
	call	printf@plt
	lla	a0,.LC1
	call	chdir@plt
	addi	s0,sp,72
	li	a1,100
	mv	a0,s0
	call	getcwd@plt
	mv	a1,s0
	lla	a0,.LC2
	call	printf@plt
	addi	a0,sp,8
	call	times@plt
	li	a5,999424
	mv	s2,a0
	sw	zero,4(sp)
	addi	a5,a5,575
.L2:
	lw	a4,4(sp)
	ble	a4,a5,.L3
	call	fork@plt
	bne	a0,zero,.L4
	li	a5,5001216
	sw	zero,40(sp)
	addi	a5,a5,-1217
.L5:
	lw	a4,40(sp)
	ble	a4,a5,.L6
	li	a0,0
.L9:
	call	exit@plt
.L3:
	lw	a4,4(sp)
	addiw	a4,a4,1
	sw	a4,4(sp)
	j	.L2
.L6:
	lw	a4,40(sp)
	addiw	a4,a4,1
	sw	a4,40(sp)
	j	.L5
.L4:
	li	a0,0
	call	wait@plt
	addi	a0,sp,40
	call	times@plt
	ld	a5,8(sp)
	ld	s0,40(sp)
	ld	s1,48(sp)
	ld	a4,64(sp)
	sub	s0,s0,a5
	ld	a5,16(sp)
	ld	a3,56(sp)
	sext.w	a2,s0
	sub	s1,s1,a5
	ld	a5,32(sp)
	subw	a1,a0,s2
	add	s0,s0,s1
	subw	a5,a4,a5
	ld	a4,24(sp)
	lla	a0,.LC3
	subw	a4,a3,a4
	sext.w	a3,s1
	call	printf@plt
	bgt	s0,zero,.L7
	lla	a0,.LC4
	call	printf@plt
	li	a0,1
	j	.L9
.L7:
	lla	a0,.LC5
	call	printf@plt
	call	shutdown@plt
	ld	ra,200(sp)
	ld	s0,192(sp)
	ld	s1,184(sp)
	ld	s2,176(sp)
	li	a0,0
	addi	sp,sp,208
	jr	ra
	.size	main, .-main
	.globl	argv
	.section	.rodata.str1.8
	.align	3
.LC6:
	.string	"sh"
	.section	.data.rel.local,"aw"
	.align	3
	.type	argv, @object
	.size	argv, 16
argv:
	.dword	.LC6
	.dword	0
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
