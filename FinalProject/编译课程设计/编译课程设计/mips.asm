.data
	String1:.asciiz " "
	String2:.asciiz "="
	String3:.asciiz "ERROR:Divided by ZERO. "
	String4:.asciiz "Undefined operation:"
	String5:.asciiz "Please select one from set {+,-,*,/}. "
	String6:.asciiz "Please input a smaller one:"
	String7:.asciiz "True"
	String8:.asciiz "False"
	String9:.asciiz "Wrong number:"
	String10:.asciiz "    "
.globl main
.text
fact:
sw $k0 0($sp)
sw $k1 4($sp)
sw $t4 8($sp)
sw $t5 12($sp)
sw $t6 16($sp)
sw $t7 20($sp)
sw $t8 24($sp)
sw $t9 28($sp)
addiu $sp $sp 32
sw $fp 4($sp)
move $fp $sp
sw $ra 0($fp)
addiu $sp $fp 8
lw $v1 268501144($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 0
move $k0 $sp
move $k1 $0 
addiu $k1 $0 5
li $t1 0
move $t4 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t4
subu $t1 $t1 $t2
move $t5 $t1
move $a1 $t5
bne $a1 $0 Label1
li $v0 1
sw $v0 268501140($0)
move $sp $fp
lw $t9 -4($sp)
lw $t8 -8($sp)
lw $t7 -12($sp)
lw $t6 -16($sp)
lw $t5 -20($sp)
lw $t4 -24($sp)
lw $k1 -28($sp)
lw $k0 -32($sp)
addiu $sp $sp -32
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
j Label2
Label1:
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
move $t6 $t1
move $a2 $t6
sw $a2 268501144($0)
jal fact
lw $t1 268501140($0)
move $t7 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t7
mult $t1 $t2
mflo $t1
move $t8 $t1
move $v0 $t8
sw $v0 268501140($0)
move $sp $fp
lw $t9 -4($sp)
lw $t8 -8($sp)
lw $t7 -12($sp)
lw $t6 -16($sp)
lw $t5 -20($sp)
lw $t4 -24($sp)
lw $k1 -28($sp)
lw $k0 -32($sp)
addiu $sp $sp -32
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
Label2:
move $sp $fp
lw $t9 -4($sp)
lw $t8 -8($sp)
lw $t7 -12($sp)
lw $t6 -16($sp)
lw $t5 -20($sp)
lw $t4 -24($sp)
lw $k1 -28($sp)
lw $k0 -32($sp)
addiu $sp $sp -32
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
isletter:
sw $k0 0($sp)
sw $k1 4($sp)
sw $t4 8($sp)
sw $t5 12($sp)
sw $t6 16($sp)
sw $t7 20($sp)
sw $t8 24($sp)
sw $t9 28($sp)
addiu $sp $sp 32
sw $fp 4($sp)
move $fp $sp
sw $ra 0($fp)
addiu $sp $fp 8
lw $v1 268501144($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 0
move $k0 $sp
move $k1 $0 
addiu $sp $sp 16
addiu $k1 $0 10
li $t1 95
move $t4 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t4
subu $t1 $t1 $t2
move $t5 $t1
move $a1 $t5
bne $a1 $0 Label3
li $v0 1
sw $v0 268501140($0)
move $sp $fp
lw $t9 -4($sp)
lw $t8 -8($sp)
lw $t7 -12($sp)
lw $t6 -16($sp)
lw $t5 -20($sp)
lw $t4 -24($sp)
lw $k1 -28($sp)
lw $k0 -32($sp)
addiu $sp $sp -32
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
j Label4
Label3:
li $t1 97
move $t6 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t6
subu $t1 $t1 $t2
move $t7 $t1
move $a1 $t7
bltz $a1 Label5
li $t1 122
move $t8 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t8
subu $t1 $t1 $t2
move $t9 $t1
move $a1 $t9
bgtz $a1 Label7
li $v0 1
sw $v0 268501140($0)
move $sp $fp
lw $t9 -4($sp)
lw $t8 -8($sp)
lw $t7 -12($sp)
lw $t6 -16($sp)
lw $t5 -20($sp)
lw $t4 -24($sp)
lw $k1 -28($sp)
lw $k0 -32($sp)
addiu $sp $sp -32
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
j Label8
Label7:
li $v0 0
sw $v0 268501140($0)
move $sp $fp
lw $t9 -4($sp)
lw $t8 -8($sp)
lw $t7 -12($sp)
lw $t6 -16($sp)
lw $t5 -20($sp)
lw $t4 -24($sp)
lw $k1 -28($sp)
lw $k0 -32($sp)
addiu $sp $sp -32
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
Label8:
j Label6
Label5:
move $t0 $k0
addiu $t0 $t0 0
li $t1 65
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 4
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 0
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 4
lw $a1 0($a1)
bltz $a1 Label9
move $t0 $k0
addiu $t0 $t0 8
li $t1 90
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 12
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 8
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 12
lw $a1 0($a1)
bgtz $a1 Label11
li $v0 1
sw $v0 268501140($0)
move $sp $fp
lw $t9 -4($sp)
lw $t8 -8($sp)
lw $t7 -12($sp)
lw $t6 -16($sp)
lw $t5 -20($sp)
lw $t4 -24($sp)
lw $k1 -28($sp)
lw $k0 -32($sp)
addiu $sp $sp -32
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
j Label12
Label11:
Label12:
j Label10
Label9:
Label10:
Label6:
Label4:
li $v0 0
sw $v0 268501140($0)
move $sp $fp
lw $t9 -4($sp)
lw $t8 -8($sp)
lw $t7 -12($sp)
lw $t6 -16($sp)
lw $t5 -20($sp)
lw $t4 -24($sp)
lw $k1 -28($sp)
lw $k0 -32($sp)
addiu $sp $sp -32
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
move $sp $fp
lw $t9 -4($sp)
lw $t8 -8($sp)
lw $t7 -12($sp)
lw $t6 -16($sp)
lw $t5 -20($sp)
lw $t4 -24($sp)
lw $k1 -28($sp)
lw $k0 -32($sp)
addiu $sp $sp -32
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
choose_pivot:
sw $k0 0($sp)
sw $k1 4($sp)
sw $t4 8($sp)
sw $t5 12($sp)
sw $t6 16($sp)
sw $t7 20($sp)
sw $t8 24($sp)
sw $t9 28($sp)
addiu $sp $sp 32
sw $fp 4($sp)
move $fp $sp
sw $ra 0($fp)
addiu $sp $fp 8
lw $v1 268501144($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268501148($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 0
move $k0 $sp
move $k1 $0 
addiu $k1 $0 2
addiu $t1 $fp 8
lw $t1 0($t1)
addiu $t2 $fp 12
lw $t2 0($t2)
addu $t1 $t1 $t2
move $t4 $t1
move $t1 $t4
li $t2 2
div $t1 $t2
mflo $t1
move $t5 $t1
move $v0 $t5
sw $v0 268501140($0)
move $sp $fp
lw $t9 -4($sp)
lw $t8 -8($sp)
lw $t7 -12($sp)
lw $t6 -16($sp)
lw $t5 -20($sp)
lw $t4 -24($sp)
lw $k1 -28($sp)
lw $k0 -32($sp)
addiu $sp $sp -32
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
move $sp $fp
lw $t9 -4($sp)
lw $t8 -8($sp)
lw $t7 -12($sp)
lw $t6 -16($sp)
lw $t5 -20($sp)
lw $t4 -24($sp)
lw $k1 -28($sp)
lw $k0 -32($sp)
addiu $sp $sp -32
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
printlist:
sw $k0 0($sp)
sw $k1 4($sp)
sw $t4 8($sp)
sw $t5 12($sp)
sw $t6 16($sp)
sw $t7 20($sp)
sw $t8 24($sp)
sw $t9 28($sp)
addiu $sp $sp 32
sw $fp 4($sp)
move $fp $sp
sw $ra 0($fp)
addiu $sp $fp 8
lw $v1 268501144($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 4
move $k0 $sp
move $k1 $0 
addiu $k1 $0 3
addiu $t0 $fp 12
li $t1 0
sw $t1 0($t0)
Label13:
addiu $t1 $fp 12
lw $t1 0($t1)
addiu $t2 $fp 8
lw $t2 0($t2)
subu $t1 $t1 $t2
move $t4 $t1
move $a1 $t4
bgez $a1 Label14
la $a0 String1
li $v0 4
syscall
li $t1 268501244
addiu $t2 $fp 12
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
move $t5 $t1
move $a0 $t5
li $v0 1
syscall
# com printf T2
li $a0 10
li $v0 11
syscall
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
move $t6 $t1
addiu $t0 $fp 12
move $t1 $t6
sw $t1 0($t0)
j Label13
Label14:
move $sp $fp
lw $t9 -4($sp)
lw $t8 -8($sp)
lw $t7 -12($sp)
lw $t6 -16($sp)
lw $t5 -20($sp)
lw $t4 -24($sp)
lw $k1 -28($sp)
lw $k0 -32($sp)
addiu $sp $sp -32
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
quicksort:
sw $k0 0($sp)
sw $k1 4($sp)
sw $t4 8($sp)
sw $t5 12($sp)
sw $t6 16($sp)
sw $t7 20($sp)
sw $t8 24($sp)
sw $t9 28($sp)
addiu $sp $sp 32
sw $fp 4($sp)
move $fp $sp
sw $ra 0($fp)
addiu $sp $fp 8
lw $v1 268501144($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268501148($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 20
move $k0 $sp
move $k1 $0 
addiu $sp $sp 40
addiu $k1 $0 16
addiu $a2 $fp 8
lw $a2 0($a2)
sw $a2 268501144($0)
addiu $a2 $fp 12
lw $a2 0($a2)
sw $a2 268501148($0)
jal choose_pivot
lw $t1 268501140($0)
move $t4 $t1
li $t1 268501244
move $t2 $t4
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
move $t5 $t1
addiu $t0 $fp 16
move $t1 $t5
sw $t1 0($t0)
addiu $t0 $fp 20
addiu $t1 $fp 8
lw $t1 0($t1)
sw $t1 0($t0)
addiu $t0 $fp 24
addiu $t1 $fp 12
lw $t1 0($t1)
sw $t1 0($t0)
Label15:
addiu $t1 $fp 20
lw $t1 0($t1)
addiu $t2 $fp 24
lw $t2 0($t2)
subu $t1 $t1 $t2
move $t6 $t1
move $a1 $t6
bgtz $a1 Label16
Label17:
li $t1 268501244
addiu $t2 $fp 24
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
move $t7 $t1
addiu $t1 $fp 16
lw $t1 0($t1)
move $t2 $t7
subu $t1 $t1 $t2
move $t8 $t1
move $a1 $t8
bgez $a1 Label18
addiu $t1 $fp 24
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
move $t9 $t1
addiu $t0 $fp 24
move $t1 $t9
sw $t1 0($t0)
j Label17
Label18:
Label19:
move $t0 $k0
addiu $t0 $t0 0
li $t1 268501244
addiu $t2 $fp 20
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 4
addiu $t1 $fp 16
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 0
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 4
lw $a1 0($a1)
blez $a1 Label20
move $t0 $k0
addiu $t0 $t0 8
addiu $t1 $fp 20
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 20
move $t1 $k0
addiu $t1 $t1 8
lw $t1 0($t1)
sw $t1 0($t0)
j Label19
Label20:
move $t0 $k0
addiu $t0 $t0 12
addiu $t1 $fp 20
lw $t1 0($t1)
addiu $t2 $fp 24
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 12
lw $a1 0($a1)
bgtz $a1 Label21
move $t0 $k0
addiu $t0 $t0 16
li $t1 268501244
addiu $t2 $fp 20
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
addiu $t0 $fp 32
move $t1 $k0
addiu $t1 $t1 16
lw $t1 0($t1)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 20
li $t1 268501244
addiu $t2 $fp 24
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
li $t0 268501244
addiu $t1 $fp 20
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
move $t1 $k0
addiu $t1 $t1 20
lw $t1 0($t1)
sw $t1 0($t0)
li $t0 268501244
addiu $t1 $fp 24
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
addiu $t1 $fp 32
lw $t1 0($t1)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 24
addiu $t1 $fp 20
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 20
move $t1 $k0
addiu $t1 $t1 24
lw $t1 0($t1)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 28
addiu $t1 $fp 24
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 24
move $t1 $k0
addiu $t1 $t1 28
lw $t1 0($t1)
sw $t1 0($t0)
j Label22
Label21:
Label22:
j Label15
Label16:
move $t0 $k0
addiu $t0 $t0 32
addiu $t1 $fp 20
lw $t1 0($t1)
addiu $t2 $fp 12
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 32
lw $a1 0($a1)
bgez $a1 Label23
addiu $a2 $fp 20
lw $a2 0($a2)
sw $a2 268501144($0)
addiu $a2 $fp 12
lw $a2 0($a2)
sw $a2 268501148($0)
jal quicksort
j Label24
Label23:
Label24:
move $t0 $k0
addiu $t0 $t0 36
addiu $t1 $fp 8
lw $t1 0($t1)
addiu $t2 $fp 24
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 36
lw $a1 0($a1)
bgez $a1 Label25
addiu $a2 $fp 8
lw $a2 0($a2)
sw $a2 268501144($0)
addiu $a2 $fp 24
lw $a2 0($a2)
sw $a2 268501148($0)
jal quicksort
j Label26
Label25:
Label26:
move $sp $fp
lw $t9 -4($sp)
lw $t8 -8($sp)
lw $t7 -12($sp)
lw $t6 -16($sp)
lw $t5 -20($sp)
lw $t4 -24($sp)
lw $k1 -28($sp)
lw $k0 -32($sp)
addiu $sp $sp -32
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
exprcheck:
sw $k0 0($sp)
sw $k1 4($sp)
sw $t4 8($sp)
sw $t5 12($sp)
sw $t6 16($sp)
sw $t7 20($sp)
sw $t8 24($sp)
sw $t9 28($sp)
addiu $sp $sp 32
sw $fp 4($sp)
move $fp $sp
sw $ra 0($fp)
addiu $sp $fp 8
addiu $sp $sp 20
move $k0 $sp
move $k1 $0 
addiu $sp $sp 16
addiu $k1 $0 10
li $v0 5
syscall
addiu $a3 $fp 8
sw $v0 0($a3)
li $v0 12
syscall
addiu $a3 $fp 24
sw $v0 0($a3)
li $v0 5
syscall
addiu $a3 $fp 12
sw $v0 0($a3)
addiu $a0 $fp 8
lw $a0 0($a0)
li $v0 1
syscall
# com printf G27a
li $a0 10
li $v0 11
syscall
addiu $a0 $fp 24
lw $a0 0($a0)
li $v0 11
syscall
# com printf G31op
li $a0 10
li $v0 11
syscall
addiu $a0 $fp 12
lw $a0 0($a0)
li $v0 1
syscall
# com printf G28b
li $a0 10
li $v0 11
syscall
la $a0 String2
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
addiu $t0 $fp 20
li $t1 1
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 0
addiu $t1 $fp 24
lw $t1 0($t1)
li $t2 43
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 0
lw $a1 0($a1)
beq $a1 $0 Label28
move $t0 $k0
addiu $t0 $t0 4
addiu $t1 $fp 24
lw $t1 0($t1)
li $t2 45
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 4
lw $a1 0($a1)
beq $a1 $0 Label29
move $t0 $k0
addiu $t0 $t0 8
addiu $t1 $fp 24
lw $t1 0($t1)
li $t2 42
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 8
lw $a1 0($a1)
beq $a1 $0 Label30
move $t0 $k0
addiu $t0 $t0 12
addiu $t1 $fp 24
lw $t1 0($t1)
li $t2 47
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 12
lw $a1 0($a1)
beq $a1 $0 Label31
j Label27
Label28:
addiu $t1 $fp 8
lw $t1 0($t1)
addiu $t2 $fp 12
lw $t2 0($t2)
addu $t1 $t1 $t2
move $t4 $t1
addiu $t0 $fp 16
move $t1 $t4
sw $t1 0($t0)
addiu $a0 $fp 16
lw $a0 0($a0)
li $v0 1
syscall
# com printf G29res
li $a0 10
li $v0 11
syscall
addiu $t0 $fp 20
li $t1 0
sw $t1 0($t0)
j Label27
Label29:
addiu $t1 $fp 8
lw $t1 0($t1)
addiu $t2 $fp 12
lw $t2 0($t2)
subu $t1 $t1 $t2
move $t5 $t1
addiu $t0 $fp 16
move $t1 $t5
sw $t1 0($t0)
addiu $a0 $fp 16
lw $a0 0($a0)
li $v0 1
syscall
# com printf G29res
li $a0 10
li $v0 11
syscall
addiu $t0 $fp 20
li $t1 0
sw $t1 0($t0)
j Label27
Label30:
addiu $t1 $fp 8
lw $t1 0($t1)
addiu $t2 $fp 12
lw $t2 0($t2)
mult $t1 $t2
mflo $t1
move $t6 $t1
addiu $t0 $fp 16
move $t1 $t6
sw $t1 0($t0)
addiu $a0 $fp 16
lw $a0 0($a0)
li $v0 1
syscall
# com printf G29res
li $a0 10
li $v0 11
syscall
addiu $t0 $fp 20
li $t1 0
sw $t1 0($t0)
j Label27
Label31:
addiu $t0 $fp 20
li $t1 0
sw $t1 0($t0)
li $t1 0
move $t7 $t1
addiu $t1 $fp 12
lw $t1 0($t1)
move $t2 $t7
subu $t1 $t1 $t2
move $t8 $t1
move $a1 $t8
bne $a1 $0 Label32
la $a0 String3
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label33
Label32:
addiu $t1 $fp 8
lw $t1 0($t1)
addiu $t2 $fp 12
lw $t2 0($t2)
div $t1 $t2
mflo $t1
move $t9 $t1
addiu $t0 $fp 16
move $t1 $t9
sw $t1 0($t0)
addiu $a0 $fp 16
lw $a0 0($a0)
li $v0 1
syscall
# com printf G29res
li $a0 10
li $v0 11
syscall
Label33:
j Label27
Label27:
addiu $a1 $fp 20
lw $a1 0($a1)
beq $a1 $0 Label35
la $a0 String4
li $v0 4
syscall
addiu $a0 $fp 24
lw $a0 0($a0)
li $v0 11
syscall
# com printf G31op
li $a0 10
li $v0 11
syscall
la $a0 String5
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label36
Label35:
Label36:
move $sp $fp
lw $t9 -4($sp)
lw $t8 -8($sp)
lw $t7 -12($sp)
lw $t6 -16($sp)
lw $t5 -20($sp)
lw $t4 -24($sp)
lw $k1 -28($sp)
lw $k0 -32($sp)
addiu $sp $sp -32
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
arraychek:
sw $k0 0($sp)
sw $k1 4($sp)
sw $t4 8($sp)
sw $t5 12($sp)
sw $t6 16($sp)
sw $t7 20($sp)
sw $t8 24($sp)
sw $t9 28($sp)
addiu $sp $sp 32
sw $fp 4($sp)
move $fp $sp
sw $ra 0($fp)
addiu $sp $fp 8
addiu $sp $sp 4
move $k0 $sp
move $k1 $0 
addiu $sp $sp 32
addiu $k1 $0 14
addiu $t0 $fp 8
li $t1 0
sw $t1 0($t0)
Label37:
li $t1 10
move $t4 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t4
subu $t1 $t1 $t2
move $t5 $t1
move $a1 $t5
bgez $a1 Label38
li $t1 10
addiu $t2 $fp 8
lw $t2 0($t2)
subu $t1 $t1 $t2
move $t6 $t1
li $t0 268501244
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
move $t1 $t6
sw $t1 0($t0)
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
move $t7 $t1
addiu $t0 $fp 8
move $t1 $t7
sw $t1 0($t0)
j Label37
Label38:
li $t0 268501244
li $t1 1
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 16
sw $t1 0($t0)
li $t0 268501244
li $t1 2
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 3
sw $t1 0($t0)
li $t0 268501244
li $t1 3
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 -8
sw $t1 0($t0)
li $t0 268501244
li $t1 4
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 40
sw $t1 0($t0)
li $t0 268501244
li $t1 5
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 -1
sw $t1 0($t0)
li $t0 268501244
li $t1 6
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 2
sw $t1 0($t0)
li $t0 268501244
li $t1 7
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 -10
sw $t1 0($t0)
addiu $t0 $fp 8
li $t1 1
sw $t1 0($t0)
li $t1 0
move $t8 $t1
li $t1 1
move $t9 $t1
move $t0 $k0
addiu $t0 $t0 0
li $t1 1
sw $t1 0($t0)
move $a2 $t9
sw $a2 268501144($0)
move $a2 $k0
addiu $a2 $a2 0
lw $a2 0($a2)
sw $a2 268501148($0)
jal choose_pivot
move $t0 $k0
addiu $t0 $t0 4
lw $t1 268501140($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 8
move $t1 $k0
addiu $t1 $t1 4
lw $t1 0($t1)
addiu $t2 $fp 8
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a2 $t8
sw $a2 268501144($0)
move $a2 $k0
addiu $a2 $a2 8
lw $a2 0($a2)
sw $a2 268501148($0)
jal choose_pivot
move $t0 $k0
addiu $t0 $t0 12
lw $t1 268501140($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 16
li $t1 9
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 20
li $t1 9
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 16
lw $a2 0($a2)
sw $a2 268501144($0)
move $a2 $k0
addiu $a2 $a2 20
lw $a2 0($a2)
sw $a2 268501148($0)
jal choose_pivot
move $t0 $k0
addiu $t0 $t0 24
lw $t1 268501140($0)
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 12
lw $a2 0($a2)
sw $a2 268501144($0)
move $a2 $k0
addiu $a2 $a2 24
lw $a2 0($a2)
sw $a2 268501148($0)
jal quicksort
move $t0 $k0
addiu $t0 $t0 28
li $t1 10
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 28
lw $a2 0($a2)
sw $a2 268501144($0)
jal printlist
move $sp $fp
lw $t9 -4($sp)
lw $t8 -8($sp)
lw $t7 -12($sp)
lw $t6 -16($sp)
lw $t5 -20($sp)
lw $t4 -24($sp)
lw $k1 -28($sp)
lw $k0 -32($sp)
addiu $sp $sp -32
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
recurcheck:
sw $k0 0($sp)
sw $k1 4($sp)
sw $t4 8($sp)
sw $t5 12($sp)
sw $t6 16($sp)
sw $t7 20($sp)
sw $t8 24($sp)
sw $t9 28($sp)
addiu $sp $sp 32
sw $fp 4($sp)
move $fp $sp
sw $ra 0($fp)
addiu $sp $fp 8
addiu $sp $sp 4
move $k0 $sp
move $k1 $0 
addiu $k1 $0 3
li $v0 5
syscall
addiu $a3 $fp 8
sw $v0 0($a3)
Label39:
li $t1 13
move $t4 $t1
move $t1 $t4
addiu $t2 $fp 8
lw $t2 0($t2)
subu $t1 $t1 $t2
move $t5 $t1
move $a1 $t5
bgtz $a1 Label40
la $a0 String6
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
li $v0 5
syscall
addiu $a3 $fp 8
sw $v0 0($a3)
j Label39
Label40:
addiu $a2 $fp 8
lw $a2 0($a2)
sw $a2 268501144($0)
jal fact
lw $t1 268501140($0)
move $t6 $t1
move $a0 $t6
li $v0 1
syscall
# com printf T3
li $a0 10
li $v0 11
syscall
move $sp $fp
lw $t9 -4($sp)
lw $t8 -8($sp)
lw $t7 -12($sp)
lw $t6 -16($sp)
lw $t5 -20($sp)
lw $t4 -24($sp)
lw $k1 -28($sp)
lw $k0 -32($sp)
addiu $sp $sp -32
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
lettercheck:
sw $k0 0($sp)
sw $k1 4($sp)
sw $t4 8($sp)
sw $t5 12($sp)
sw $t6 16($sp)
sw $t7 20($sp)
sw $t8 24($sp)
sw $t9 28($sp)
addiu $sp $sp 32
sw $fp 4($sp)
move $fp $sp
sw $ra 0($fp)
addiu $sp $fp 8
addiu $sp $sp 4
move $k0 $sp
move $k1 $0 
addiu $k1 $0 1
li $v0 12
syscall
addiu $a3 $fp 8
sw $v0 0($a3)
addiu $a2 $fp 8
lw $a2 0($a2)
sw $a2 268501144($0)
jal isletter
lw $t1 268501140($0)
move $t4 $t1
move $a1 $t4
beq $a1 $0 Label41
la $a0 String7
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label42
Label41:
la $a0 String8
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
Label42:
move $sp $fp
lw $t9 -4($sp)
lw $t8 -8($sp)
lw $t7 -12($sp)
lw $t6 -16($sp)
lw $t5 -20($sp)
lw $t4 -24($sp)
lw $k1 -28($sp)
lw $k0 -32($sp)
addiu $sp $sp -32
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
main:
li $fp 268501288
addiu $sp $fp 8
addiu $sp $sp 4
move $k0 $sp
move $k1 $0 
addiu $sp $sp 20
addiu $k1 $0 11
li $v0 5
syscall
addiu $a3 $fp 8
sw $v0 0($a3)
Label43:
li $t1 0
move $t4 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t4
subu $t1 $t1 $t2
move $t5 $t1
move $a1 $t5
beq $a1 $0 Label44
addiu $t1 $fp 8
lw $t1 0($t1)
move $t6 $t1
move $t1 $t6
li $t2 4
mult $t1 $t2
mflo $t1
move $t7 $t1
move $t1 $t7
li $t2 4
div $t1 $t2
mflo $t1
move $t8 $t1
move $t1 $t8
li $t2 19
addu $t1 $t1 $t2
move $t9 $t1
move $t0 $k0
addiu $t0 $t0 0
move $t1 $t9
li $t2 19
subu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 4
move $t1 $k0
addiu $t1 $t1 0
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 4
lw $a1 0($a1)
beq $a1 $0 Label46
move $t0 $k0
addiu $t0 $t0 8
move $t1 $k0
addiu $t1 $t1 0
lw $t1 0($t1)
li $t2 2
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 8
lw $a1 0($a1)
beq $a1 $0 Label47
move $t0 $k0
addiu $t0 $t0 12
move $t1 $k0
addiu $t1 $t1 0
lw $t1 0($t1)
li $t2 3
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 12
lw $a1 0($a1)
beq $a1 $0 Label48
move $t0 $k0
addiu $t0 $t0 16
move $t1 $k0
addiu $t1 $t1 0
lw $t1 0($t1)
li $t2 4
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 16
lw $a1 0($a1)
beq $a1 $0 Label49
la $a0 String9
li $v0 4
syscall
addiu $a0 $fp 8
lw $a0 0($a0)
li $v0 1
syscall
# com printf G40choice
li $a0 10
li $v0 11
syscall
j Label45
Label46:
jal exprcheck
j Label45
Label47:
jal arraychek
j Label45
Label48:
jal recurcheck
j Label45
Label49:
jal lettercheck
j Label45
Label45:
la $a0 String10
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
li $v0 5
syscall
addiu $a3 $fp 8
sw $v0 0($a3)
j Label43
Label44:
#accomplish generate mips code.
