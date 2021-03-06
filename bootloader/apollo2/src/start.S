/*
 *  armboot - Startup Code for OMP2420/ARM1136 CPU-core
 *
 *  Copyright (c) 2004	Texas Instruments <r-woodruff2@ti.com>
 *
 *  Copyright (c) 2001	Marius Gr�ger <mag@sysgo.de>
 *  Copyright (c) 2002	Alex Z�pke <azu@sysgo.de>
 *  Copyright (c) 2002	Gary Jennejohn <garyj@denx.de>
 *  Copyright (c) 2003	Richard Woodruff <r-woodruff2@ti.com>
 *  Copyright (c) 2003	Kshitij <kshitij@ti.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
#include "configs/imapx800.h"
.globl _start
_start: b	reset
#ifdef CONFIG_PRELOADER
	ldr	pc, _asic
	ldr	pc, _asic
	ldr	pc, _asic
	ldr	pc, _asic
	ldr	pc, _asic
	ldr	pc, _asic
	ldr	pc, _asic

.globl _asic
_asic:
	.word	do_hang
	.word	0x12345678
	.word	0x12345678
	.word	0x12345678
	.word	0x12345678
	.word	0x12345678
	.word	0x12345678
	.word	0x12345678	/* now 16*4=64 */
#else
	ldr	pc, _undefined_instruction
	ldr	pc, _software_interrupt
	ldr	pc, _prefetch_abort
	ldr	pc, _data_abort
	ldr	pc, _not_used
	ldr	pc, _irq
	ldr	pc, _fiq

_undefined_instruction: .word undefined_instruction
_software_interrupt:	.word software_interrupt
_prefetch_abort:	.word prefetch_abort
_data_abort:		.word data_abort
_not_used:		.word not_used
_irq:			.word irq
_fiq:			.word fiq
_pad:			.word 0x12345678 /* now 16*4=64 */
#endif	/* CONFIG_PRELOADER */
.global _end_vect
_end_vect:

	.balignl 16,0xdeadbeef
/*
 *************************************************************************
 *
 * Startup Code (reset vector)
 *
 * do important init only if we don't start from memory!
 * setup Memory and board specific bits prior to relocation.
 * relocate armboot to ram
 * setup stack
 *
 *************************************************************************
 */

_TEXT_BASE:
	.word TEXT_BASE

.globl _armboot_start
_armboot_start:
	.word _start

/*
 * These are defined in the board-specific linker script.
 */
.globl _bss_start
_bss_start:
	.word __bss_start

.globl _bss_end
_bss_end:
	.word _end

.globl IROM_UBOOT_SIZE
IROM_UBOOT_SIZE:
	.word 0x800c000

#ifdef CONFIG_USE_IRQ
/* IRQ stack memory (calculated at run-time) */
.globl IRQ_STACK_START
IRQ_STACK_START:
	.word	0x0badc0de

/* IRQ stack memory (calculated at run-time) */
.globl FIQ_STACK_START
FIQ_STACK_START:
	.word 0x0badc0de
#endif

/*
 * the actual reset code
 */

reset:
	/*
	 * set the cpu to SVC32 mode
	 */
	mrs	r0,cpsr
	bic	r0,r0,#0x1f
	orr	r0,r0,#0xd3
	msr	cpsr,r0
    
	/* the mask ROM code should have PLL and others stable */
//#ifndef CONFIG_SKIP_LOWLEVEL_INIT
//#if	defined(CONFIG_PRELOADER) || !defined(CONFIG_HAVE_PRELOADER)
//#if !defined(CONFIG_MEM_POOL)
    bl  cpu_init_crit
//#endif
//#endif
//#endif

	/* Set up the stack						    */
stack_setup:
#ifdef CONFIG_PRELOADER
	ldr r0, IROM_UBOOT_SIZE
	sub	sp, r0, #0x20		/* leave 32 words for abort-stack   */
#else
	ldr	r0, =CONFIG_SYS_PHY_UBOOT_BASE		/* upper 128 KiB: relocated uboot   */
@	sub	r0, r0, #CONFIG_SYS_MALLOC_LEN /* malloc area			    */
	sub	r0, r0, #CONFIG_SYS_GBL_DATA_SIZE /* bdinfo			    */
#ifdef CONFIG_USE_IRQ
	sub	r0, r0, #(CONFIG_STACKSIZE_IRQ+CONFIG_STACKSIZE_FIQ)
#endif
	sub	sp, r0, #12		/* leave 3 words for abort-stack    */
#endif	/* CONFIG_PRELOADER */


#ifndef CONFIG_HAVE_PRELOADER
#ifndef CONFIG_SKIP_RELOCATE_UBOOT
relocate:				/* relocate U-Boot to RAM	    */
	adr	r0, _start		/* r0 <- current position of code   */
	ldr	r1, _TEXT_BASE		/* test if we run from flash or RAM */
	cmp	r0, r1			/* don't reloc during debug	    */
	beq	clear_bss

	ldr	r2, _armboot_start
	ldr	r3, _bss_start
	sub	r2, r3, r2		/* r2 <- size of armboot	    */
	add	r2, r0, r2		/* r2 <- source end address	    */

	/* copy u-boot from NOR to RAM */
copy_loop:
	ldmia	r0!, {r3-r10}		/* copy from source address [r0]    */
	stmia	r1!, {r3-r10}		/* copy to   target address [r1]    */
	cmp	r0, r2			/* until source end addreee [r2]    */
	ble	copy_loop
#endif	/* CONFIG_SKIP_RELOCATE_UBOOT */
#endif


clear_bss:
	ldr	r0, _bss_start		/* find start of bss segment	    */
	ldr	r1, _bss_end		/* stop here			    */
	mov	r2, #0x00000000		/* clear			    */
	b clbss_1

clbss_l:str	r2, [r0]		/* clear loop...		    */
	add	r0, r0, #4
clbss_1:
	cmp	r0, r1
	bne	clbss_l

	ldr	pc, _start_armboot


_start_armboot: .word boot_main

.globl	__invalid_cache
__invalid_cache:
         mov     r0, #0
         mcr     p15, 0, r0, c7, c5, 0   @ invalidate I cache
         mcr     p15, 2, r0, c0, c0, 0
         mrc     p15, 1, r0, c0, c0, 0
 
         ldr     r1, =0x7fff
         and     r2, r1, r0, lsr #13
 
         ldr     r1, =0x3ff
 
         and     r3, r1, r0, lsr #3      @ NumWays - 1
         add     r2, r2, #1              @ NumSets
 
         and     r0, r0, #0x7
         add     r0, r0, #4      @ SetShift
 
         clz     r1, r3          @ WayShift
         add     r4, r3, #1      @ NumWays
 1:      sub     r2, r2, #1      @ NumSets--
         mov     r3, r4          @ Temp = NumWays
 2:      subs    r3, r3, #1      @ Temp--
         mov     r5, r3, lsl r1
         mov     r6, r2, lsl r0
         orr     r5, r5, r6      @ Reg = (Temp<<WayShift)|(NumSets<<SetShift)
         mcr     p15, 0, r5, c7, c6, 2
         bgt     2b
         cmp     r2, #0
         bgt     1b
         dsb
         isb
         mov     pc, lr

#if 1
 .global   _clean_invd_dcache_uboot0 
@void _clean_invd_dcache_uboot0(void);
_clean_invd_dcache_uboot0:
    push    {r4,r5,r6,lr}
    MOV     r2,#0
    MOV     r3,#0x40000000
    MOV     r4,#0x80000000
    MOV     r5,#0xc0000000
    MOVEQ   r6,#0x2000
    MOVNE   r6,#0x4000
clean_invd_loop:
    MCR     p15,0,r2,c7,c14,2  @ invalidate dcache by set / way
    MCR     p15,0,r3,c7,c14,2  @ invalidate dcache by set / way
    MCR     p15,0,r4,c7,c14,2  @ invalidate dcache by set / way
    MCR     p15,0,r5,c7,c14,2  @ invalidate dcache by set / way
    ADD     r2,r2,#0x20
    ADD     r3,r3,#0x20
    ADD     r4,r4,#0x20
    ADD     r5,r5,#0x20
    CMP     r2,r6
    BNE     clean_invd_loop
    DSB
    pop {r4, r5,r6, pc}
#endif
/*
 *************************************************************************
 *
 * CPU_init_critical registers
 *
 * setup important registers
 * setup memory timing
 *
 *************************************************************************
 */
#ifndef CONFIG_PRELOADER
//.extern mmu_table 
.globl __mmu_table
 __mmu_table:
 	.word mmu_table
cpu_init_crit:
    /*
	 * flush v4 I/D caches
	 */
	mov	r0, #0
	mcr	p15, 0, r0, c8, c7, 0	/* flush v3/v4 cache */
	mcr	p15, 0, r0, c7, c5, 0	/* flush v4 TLB */

	/*
	 * disable caches and flow prediction
	 */
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, r0, #0x00002000	@ clear bits 13 (--V-)
	bic	r0, r0, #0x00000007	@ clear bits 2:0 (-CAM)
	orr	r0, r0, #0x00000002	@ set bit 1 (--A-) Align
	orr	r0, r0, #0x00001800	@ set bit 12 (Z---) BTB
	mcr	p15, 0, r0, c1, c0, 0

	/*
	 * set cp10, cp11 accsess to enable double precision
	 */
	mrc p15, 0, r0, c1, c0, 2
	orr r0, r0, #0x00f00000
	mcr p15, 0, r0, c1, c0, 2

	/*
	 * Jump to board specific initialization... The Mask ROM will have already initialized
	 * basic memory.  Go here to bump up clock rate and handle wake up conditions.
	 */

#if !(CONFIG_ICACHE_OFF && CONFIG_DCACHE_OFF)
//#if 0 
    mov ip, lr
	ldr r0,__mmu_table
	bl	cache_init		@go setup pll,mux,memory
	mov lr, ip			@ restore link
#endif
	mov	pc, lr		/* back to my caller */

#else

#ifndef CONFIG_SKIP_LOWLEVEL_INIT
#if	defined(CONFIG_PRELOADER) || !defined(CONFIG_HAVE_PRELOADER)
cpu_init_crit:
	/*
	 * flush v4 I/D caches
	 */
	mov	r0, #0
	mcr	p15, 0, r0, c8, c7, 0	/* flush v3/v4 cache */
	mcr	p15, 0, r0, c7, c5, 0	/* flush v4 TLB */

	/*
	 * disable caches and flow prediction
	 */
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, r0, #0x00002000	@ clear bits 13 (--V-)
	bic	r0, r0, #0x00000007	@ clear bits 2:0 (-CAM)
	orr	r0, r0, #0x00000002	@ set bit 1 (--A-) Align
	orr	r0, r0, #0x00001800	@ set bit 12 (Z---) BTB
	mcr	p15, 0, r0, c1, c0, 0

	/*
	 * set cp10, cp11 accsess to enable double precision
	 */
	mrc p15, 0, r0, c1, c0, 2
	orr r0, r0, #0x00f00000
	mcr p15, 0, r0, c1, c0, 2

	/*
	 * Jump to board specific initialization... The Mask ROM will have already initialized
	 * basic memory.  Go here to bump up clock rate and handle wake up conditions.
	 */
	mov	ip, lr		/* persevere link reg across call */
	bl	lowlevel_init	/* go setup pll,mux,memory */
	bl	dram_init	/* go setup pll,mux,memory */
	mov	lr, ip		/* restore link */
	mov	pc, lr		/* back to my caller */
#endif /* CONFIG_PRELOADER || !CONFIG_HAVE_PRELOADER */
#endif /* CONFIG_SKIP_LOWLEVEL_INIT */


#endif



#ifndef CONFIG_PRELOADER
/*
 *************************************************************************
 *
 * Interrupt handling
 *
 *************************************************************************
 */
@
@ IRQ stack frame.
@
#define S_FRAME_SIZE	72

#define S_OLD_R0	68
#define S_PSR		64
#define S_PC		60
#define S_LR		56
#define S_SP		52

#define S_IP		48
#define S_FP		44
#define S_R10		40
#define S_R9		36
#define S_R8		32
#define S_R7		28
#define S_R6		24
#define S_R5		20
#define S_R4		16
#define S_R3		12
#define S_R2		8
#define S_R1		4
#define S_R0		0

#define MODE_SVC 0x13
#define I_BIT	 0x80

/*
 * use bad_save_user_regs for abort/prefetch/undef/swi ...
 * use irq_save_user_regs / irq_restore_user_regs for IRQ/FIQ handling
 */

	.macro	bad_save_user_regs
	sub	sp, sp, #S_FRAME_SIZE		@ carve out a frame on current user stack
	stmia	sp, {r0 - r12}			@ Save user registers (now in svc mode) r0-r12

	ldr	r2, _armboot_start
	sub	r2, r2, #(CONFIG_SYS_MALLOC_LEN)
	sub	r2, r2, #(CONFIG_SYS_GBL_DATA_SIZE+8)	@ set base 2 words into abort stack
	ldmia	r2, {r2 - r3}			@ get values for "aborted" pc and cpsr (into parm regs)
	add	r0, sp, #S_FRAME_SIZE		@ grab pointer to old stack

	add	r5, sp, #S_SP
	mov	r1, lr
	stmia	r5, {r0 - r3}			@ save sp_SVC, lr_SVC, pc, cpsr
	mov	r0, sp				@ save current stack into r0 (param register)
	.endm

	.macro	irq_save_user_regs
	sub	sp, sp, #S_FRAME_SIZE
	stmia	sp, {r0 - r12}			@ Calling r0-r12
	add	r8, sp, #S_PC			@ !!!! R8 NEEDS to be saved !!!! a reserved stack spot would be good.
	stmdb	r8, {sp, lr}^			@ Calling SP, LR
	str	lr, [r8, #0]			@ Save calling PC
	mrs	r6, spsr
	str	r6, [r8, #4]			@ Save CPSR
	str	r0, [r8, #8]			@ Save OLD_R0
	mov	r0, sp
	.endm

	.macro	irq_restore_user_regs
	ldmia	sp, {r0 - lr}^			@ Calling r0 - lr
	mov	r0, r0
	ldr	lr, [sp, #S_PC]			@ Get PC
	add	sp, sp, #S_FRAME_SIZE
	subs	pc, lr, #4			@ return & move spsr_svc into cpsr
	.endm

	.macro get_bad_stack
	ldr	r13, _armboot_start		@ setup our mode stack (enter in banked mode)
	sub	r13, r13, #(CONFIG_SYS_MALLOC_LEN)	@ move past malloc pool
	sub	r13, r13, #(CONFIG_SYS_GBL_DATA_SIZE+8) @ move to reserved a couple spots for abort stack

	str	lr, [r13]			@ save caller lr in position 0 of saved stack
	mrs	lr, spsr			@ get the spsr
	str	lr, [r13, #4]			@ save spsr in position 1 of saved stack

	mov	r13, #MODE_SVC			@ prepare SVC-Mode
	@ msr	spsr_c, r13
	msr	spsr, r13			@ switch modes, make sure moves will execute
	mov	lr, pc				@ capture return pc
	movs	pc, lr				@ jump to next instruction & switch modes.
	.endm

	.macro get_bad_stack_swi
	sub	r13, r13, #4			@ space on current stack for scratch reg.
	str	r0, [r13]			@ save R0's value.
	ldr	r0, _armboot_start		@ get data regions start
	sub	r0, r0, #(CONFIG_SYS_MALLOC_LEN)	@ move past malloc pool
	sub	r0, r0, #(CONFIG_SYS_GBL_DATA_SIZE+8)	@ move past gbl and a couple spots for abort stack
	str	lr, [r0]			@ save caller lr in position 0 of saved stack
	mrs	r0, spsr			@ get the spsr
	str	lr, [r0, #4]			@ save spsr in position 1 of saved stack
	ldr	r0, [r13]			@ restore r0
	add	r13, r13, #4			@ pop stack entry
	.endm

	.macro get_irq_stack			@ setup IRQ stack
	ldr	sp, IRQ_STACK_START
	.endm

	.macro get_fiq_stack			@ setup FIQ stack
	ldr	sp, FIQ_STACK_START
	.endm
#endif	/* CONFIG_PRELOADER */

/*
 * exception handlers
 */
#ifdef CONFIG_PRELOADER
	.align	5

.globl do_hang
do_hang:
	b	.						/* hang and never return */

#else	/* !CONFIG_PRELOADER */
	.align	5
undefined_instruction:
	get_bad_stack
	bad_save_user_regs
	bl	do_undefined_instruction

	.align	5
software_interrupt:
	get_bad_stack_swi
	bad_save_user_regs
	bl	do_software_interrupt

	.align	5
prefetch_abort:
	get_bad_stack
	bad_save_user_regs
	bl	do_prefetch_abort

	.align	5
data_abort:
	get_bad_stack
	bad_save_user_regs
	bl	do_data_abort

	.align	5
not_used:
	get_bad_stack
	bad_save_user_regs
	bl	do_not_used

#ifdef CONFIG_USE_IRQ

	.align	5
irq:
	get_irq_stack
	irq_save_user_regs
	bl	do_irq
	irq_restore_user_regs

	.align	5
fiq:
	get_fiq_stack
	/* someone ought to write a more effiction fiq_save_user_regs */
	irq_save_user_regs
	bl	do_fiq
	irq_restore_user_regs

#else

	.align	5
irq:
	get_bad_stack
	bad_save_user_regs
	bl	do_irq

	.align	5
fiq:
	get_bad_stack
	bad_save_user_regs
	bl	do_fiq

#endif
	.align 5
.global arm1136_cache_flush
arm1136_cache_flush:
		mcr	p15, 0, r1, c7, c5, 0	@ invalidate I cache
		mov	pc, lr			@ back to caller
#endif	/* CONFIG_PRELOADER */
