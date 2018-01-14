.data
	String7:.asciiz "OVERFLOW! "
	String8:.asciiz "complete number: "
	String9:.asciiz "  "
	String10:.asciiz "---------------------------------------------------------------"
	String11:.asciiz " "
	String12:.asciiz "The total is "
.globl main
.text
complete_num:
sw $k0 0($sp)
sw $k1 4($sp)
sw $t4 8($sp)
sw $t5 12($sp)
sw $t6 16($sp)
sw $t7 20($sp)
sw $t8 24($sp)
sw $t9 28($sp)
sw $s0 32($sp)
sw $s1 36($sp)
sw $s2 40($sp)
sw $s3 44($sp)
sw $s4 48($sp)
sw $s5 52($sp)
sw $s6 56($sp)
sw $s7 60($sp)
addiu $sp $sp 64
sw $fp 4($sp)
move $fp $sp
sw $ra 0($fp)
addiu $sp $fp 8
addiu $sp $sp 4136
move $k0 $sp
move $k1 $0 
addiu $sp $sp 4
addiu $k1 $0 7
li $t1 2
move $s2 $t1
Label1:
li $t1 1024
move $t4 $t1
move $t1 $s2
move $t2 $t4
subu $t1 $t1 $t2
move $t5 $t1
move $a1 $t5
bgez $a1 Label2
li $t1 -1
move $s1 $t1
move $t1 $s2
move $s4 $t1
li $t1 1
move $s0 $t1
Label3:
move $t1 $s0
move $t2 $s2
subu $t1 $t1 $t2
move $t4 $t1
move $a1 $t4
bgez $a1 Label4
move $t1 $s2
move $t2 $s0
div $t1 $t2
mflo $t1
move $t4 $t1
move $t1 $t4
move $t5 $t1
move $t1 $t5
move $t2 $s0
mult $t1 $t2
mflo $t1
move $t6 $t1
move $t1 $t6
move $t7 $t1
move $t1 $t7
move $s6 $t1
move $t1 $s6
move $t2 $s2
subu $t1 $t1 $t2
move $t8 $t1
move $a1 $t8
bne $a1 $0 Label5
move $t1 $s1
li $t2 1
addu $t1 $t1 $t2
move $t4 $t1
move $t1 $t4
move $t5 $t1
move $t1 $t5
move $s1 $t1
move $t1 $s4
move $t2 $s0
subu $t1 $t1 $t2
move $t6 $t1
move $t1 $t6
move $t7 $t1
move $t1 $t7
move $s4 $t1
li $t1 1024
move $t8 $t1
move $t1 $s1
move $t2 $t8
subu $t1 $t1 $t2
move $t9 $t1
move $a1 $t9
bltz $a1 Label7
la $a0 String7
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label8
Label7:
addiu $t0 $fp 8
move $t1 $s1
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
move $t1 $s0
sw $t1 0($t0)
Label8:
j Label6
Label5:
Label6:
move $t1 $s0
li $t2 1
addu $t1 $t1 $t2
move $t4 $t1
move $t1 $t4
move $t5 $t1
move $t1 $t5
move $s0 $t1
j Label3
Label4:
li $t1 0
move $t6 $t1
move $t1 $s4
move $t2 $t6
subu $t1 $t1 $t2
move $t7 $t1
move $a1 $t7
bne $a1 $0 Label9
la $a0 String8
li $v0 4
syscall
addu $a0 $s2 $0
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
li $t1 0
move $s0 $t1
Label11:
move $t1 $s0
move $t2 $s1
subu $t1 $t1 $t2
move $t4 $t1
move $a1 $t4
bgtz $a1 Label12
la $a0 String9
li $v0 4
syscall
addiu $t1 $fp 8
move $t2 $s0
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
move $t4 $t1
move $a0 $t4
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
move $t1 $s0
li $t2 1
addu $t1 $t1 $t2
move $t4 $t1
move $t1 $t4
move $t5 $t1
move $t1 $t5
move $s0 $t1
j Label11
Label12:
la $a0 String9
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label10
Label9:
Label10:
move $t1 $s2
li $t2 1
addu $t1 $t1 $t2
move $t4 $t1
move $t1 $t4
move $t5 $t1
move $t1 $t5
move $s2 $t1
j Label1
Label2:
la $a0 String10
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
addiu $t0 $fp 4132
li $t1 0
sw $t1 0($t0)
li $t1 1
move $s7 $t1
li $t1 2
move $s3 $t1
Label13:
li $t1 1024
move $t6 $t1
move $t1 $s3
move $t2 $t6
subu $t1 $t1 $t2
move $t7 $t1
move $a1 $t7
bgtz $a1 Label14
move $t1 $s3
li $t2 1
subu $t1 $t1 $t2
move $t4 $t1
move $t1 $t4
move $t5 $t1
addiu $t0 $fp 4128
move $t1 $t5
sw $t1 0($t0)
li $t1 2
move $s0 $t1
Label15:
move $t1 $s0
addiu $t2 $fp 4128
lw $t2 0($t2)
subu $t1 $t1 $t2
move $t6 $t1
move $a1 $t6
bgtz $a1 Label16
move $t1 $s3
move $t2 $s0
div $t1 $t2
mflo $t1
move $t4 $t1
move $t1 $t4
move $t5 $t1
move $t1 $t5
move $t2 $s0
mult $t1 $t2
mflo $t1
move $t6 $t1
move $t1 $t6
move $t7 $t1
move $t1 $t7
move $s5 $t1
move $t1 $s5
move $t2 $s3
subu $t1 $t1 $t2
move $t8 $t1
move $a1 $t8
bne $a1 $0 Label17
li $t1 0
move $s7 $t1
j Label18
Label17:
Label18:
move $t1 $s0
li $t2 1
addu $t1 $t1 $t2
move $t4 $t1
move $t1 $t4
move $t5 $t1
move $t1 $t5
move $s0 $t1
j Label15
Label16:
li $t1 1
move $t6 $t1
move $t1 $s7
move $t2 $t6
subu $t1 $t1 $t2
move $t7 $t1
move $a1 $t7
bne $a1 $0 Label19
la $a0 String11
li $v0 4
syscall
addu $a0 $s3 $0
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
addiu $t1 $fp 4132
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
move $t4 $t1
move $t1 $t4
move $t5 $t1
addiu $t0 $fp 4132
move $t1 $t5
sw $t1 0($t0)
addiu $t1 $fp 4132
lw $t1 0($t1)
li $t2 10
div $t1 $t2
mflo $t1
move $t6 $t1
move $t1 $t6
move $t7 $t1
move $t1 $t7
li $t2 10
mult $t1 $t2
mflo $t1
move $t8 $t1
move $t1 $t8
move $t9 $t1
move $t1 $t9
move $s5 $t1
move $t0 $k0
addiu $t0 $t0 0
move $t1 $s5
addiu $t2 $fp 4132
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 0
lw $a1 0($a1)
bne $a1 $0 Label21
la $a0 String9
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label22
Label21:
Label22:
j Label20
Label19:
Label20:
li $t1 1
move $s7 $t1
move $t1 $s3
li $t2 1
addu $t1 $t1 $t2
move $t4 $t1
move $t1 $t4
move $t5 $t1
move $t1 $t5
move $s3 $t1
j Label13
Label14:
la $a0 String12
li $v0 4
syscall
addiu $a0 $fp 4132
lw $a0 0($a0)
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
move $sp $fp
lw $s7 -4($sp)
lw $s6 -8($sp)
lw $s5 -12($sp)
lw $s4 -16($sp)
lw $s3 -20($sp)
lw $s2 -24($sp)
lw $s1 -28($sp)
lw $s0 -32($sp)
lw $t9 -36($sp)
lw $t8 -40($sp)
lw $t7 -44($sp)
lw $t6 -48($sp)
lw $t5 -52($sp)
lw $t4 -56($sp)
lw $k1 -60($sp)
lw $k0 -64($sp)
addiu $sp $sp -64
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
main:
li $fp 268501212
addiu $sp $fp 8
addiu $sp $sp 0
move $k0 $sp
move $k1 $0 
jal complete_num
#accomplish generate mips code.
