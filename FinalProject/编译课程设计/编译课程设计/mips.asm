.data
	String1:.asciiz " "
	String2:.asciiz "expre:"
	String3:.asciiz "fibo:"
	String4:.asciiz "gcd:"
	String5:.asciiz "string:!#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"
	String6:.asciiz "Test Not Return"
.globl main
.text
testdefine:
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
addiu $sp $sp 60
move $k0 $sp
move $k1 $0 
li $t0 268501212
li $t1 0
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 97
sw $t1 0($t0)
li $t0 268501212
li $t1 1
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 98
sw $t1 0($t0)
li $t0 268501212
li $t1 2
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 99
sw $t1 0($t0)
li $t0 268501212
li $t1 3
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 100
sw $t1 0($t0)
li $t0 268501212
li $t1 4
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 101
sw $t1 0($t0)
li $t0 268501212
li $t1 5
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 102
sw $t1 0($t0)
li $t0 268501212
li $t1 6
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 103
sw $t1 0($t0)
li $t0 268501212
li $t1 7
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 104
sw $t1 0($t0)
li $t0 268501212
li $t1 8
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 105
sw $t1 0($t0)
li $t0 268501212
li $t1 9
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 106
sw $t1 0($t0)
li $t0 268501212
li $t1 10
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 107
sw $t1 0($t0)
li $t0 268501212
li $t1 11
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 108
sw $t1 0($t0)
li $t0 268501212
li $t1 12
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 109
sw $t1 0($t0)
li $t0 268501212
li $t1 13
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 110
sw $t1 0($t0)
li $t0 268501212
li $t1 14
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 111
sw $t1 0($t0)
li $t0 268501212
li $t1 15
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 112
sw $t1 0($t0)
li $t0 268501212
li $t1 16
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 113
sw $t1 0($t0)
li $t0 268501212
li $t1 17
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 114
sw $t1 0($t0)
li $t0 268501212
li $t1 18
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 115
sw $t1 0($t0)
li $t0 268501212
li $t1 19
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 116
sw $t1 0($t0)
li $t0 268501212
li $t1 20
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 117
sw $t1 0($t0)
li $t0 268501212
li $t1 21
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 118
sw $t1 0($t0)
li $t0 268501212
li $t1 22
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 119
sw $t1 0($t0)
li $t0 268501212
li $t1 23
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 120
sw $t1 0($t0)
li $t0 268501212
li $t1 24
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 121
sw $t1 0($t0)
li $t0 268501212
li $t1 25
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 122
sw $t1 0($t0)
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
fibo:
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
lw $v1 268501076($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 0
move $k0 $sp
move $k1 $0 
addiu $sp $sp 28
addiu $k1 $0 13
li $t1 0
move $t4 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t4
subu $t1 $t1 $t2
move $t5 $t1
move $a1 $t5
bgez $a1 Label1
li $v0 -1
sw $v0 268501072($0)
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
li $t1 0
move $t6 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t6
subu $t1 $t1 $t2
move $t7 $t1
move $a1 $t7
bne $a1 $0 Label3
li $v0 0
sw $v0 268501072($0)
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
li $t1 1
move $t8 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t8
subu $t1 $t1 $t2
move $t9 $t1
move $a1 $t9
bne $a1 $0 Label5
li $v0 1
sw $v0 268501072($0)
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
j Label6
Label5:
move $t0 $k0
addiu $t0 $t0 0
li $t1 10
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
blez $a1 Label7
li $v0 -2
sw $v0 268501072($0)
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
move $t0 $k0
addiu $t0 $t0 8
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 8
lw $a2 0($a2)
sw $a2 268501076($0)
jal fibo
move $t0 $k0
addiu $t0 $t0 12
lw $t1 268501072($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 16
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 2
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 16
lw $a2 0($a2)
sw $a2 268501076($0)
jal fibo
move $t0 $k0
addiu $t0 $t0 20
lw $t1 268501072($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 24
move $t1 $k0
addiu $t1 $t1 12
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 20
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
move $v0 $k0
addiu $v0 $v0 24
lw $v0 0($v0)
sw $v0 268501072($0)
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
Label6:
Label4:
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
printspace:
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
addiu $sp $sp 0
move $k0 $sp
move $k1 $0 
la $a0 String1
li $v0 4
syscall
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
display:
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
lw $v1 268501076($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 8
move $k0 $sp
move $k1 $0 
addiu $sp $sp 4
addiu $k1 $0 7
li $t1 0
move $t4 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t4
subu $t1 $t1 $t2
move $t5 $t1
move $a1 $t5
bgtz $a1 Label9
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
j Label10
Label9:
li $t1 26
move $t6 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t6
subu $t1 $t1 $t2
move $t7 $t1
move $a1 $t7
blez $a1 Label11
addiu $t0 $fp 8
li $t1 26
sw $t1 0($t0)
j Label12
Label11:
addiu $t0 $fp 12
li $t1 0
sw $t1 0($t0)
Label13:
addiu $t1 $fp 12
lw $t1 0($t1)
addiu $t2 $fp 8
lw $t2 0($t2)
subu $t1 $t1 $t2
move $t8 $t1
move $a1 $t8
bgez $a1 Label14
li $t1 268501212
addiu $t2 $fp 12
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
move $t9 $t1
move $a0 $t9
li $v0 11
syscall
# com printf T6
li $a0 10
li $v0 11
syscall
move $t0 $k0
addiu $t0 $t0 0
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 12
move $t1 $k0
addiu $t1 $t1 0
lw $t1 0($t1)
sw $t1 0($t0)
j Label13
Label14:
jal printspace
Label12:
Label10:
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
expre:
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
addiu $sp $sp 12
move $k0 $sp
move $k1 $0 
addiu $k1 $0 5
li $v0 5
syscall
addiu $a3 $fp 8
sw $v0 0($a3)
li $v0 5
syscall
addiu $a3 $fp 12
sw $v0 0($a3)
addiu $t1 $fp 8
lw $t1 0($t1)
addiu $t2 $fp 12
lw $t2 0($t2)
addu $t1 $t1 $t2
move $t4 $t1
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 -2
mult $t1 $t2
mflo $t1
move $t5 $t1
li $t1 0
move $t2 $t5
subu $t1 $t1 $t2
move $t6 $t1
move $t1 $t4
move $t2 $t6
subu $t1 $t1 $t2
move $t7 $t1
move $t1 $t7
move $t8 $t1
addiu $t0 $fp 16
move $t1 $t8
sw $t1 0($t0)
la $a0 String2
li $v0 4
syscall
addiu $a0 $fp 16
lw $a0 0($a0)
li $v0 1
syscall
# com printf G43z
li $a0 10
li $v0 11
syscall
jal printspace
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
mod:
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
lw $v1 268501076($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268501080($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 4
move $k0 $sp
move $k1 $0 
addiu $k1 $0 3
addiu $t1 $fp 8
lw $t1 0($t1)
addiu $t2 $fp 12
lw $t2 0($t2)
div $t1 $t2
mflo $t1
move $t4 $t1
move $t1 $t4
addiu $t2 $fp 12
lw $t2 0($t2)
mult $t1 $t2
mflo $t1
move $t5 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t5
subu $t1 $t1 $t2
move $t6 $t1
addiu $t0 $fp 16
move $t1 $t6
sw $t1 0($t0)
addiu $v0 $fp 16
lw $v0 0($v0)
sw $v0 268501072($0)
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
gcd:
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
lw $v1 268501076($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268501080($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 0
move $k0 $sp
move $k1 $0 
addiu $sp $sp 4
addiu $k1 $0 7
li $t1 0
move $t4 $t1
addiu $t1 $fp 12
lw $t1 0($t1)
move $t2 $t4
subu $t1 $t1 $t2
move $t5 $t1
move $a1 $t5
bne $a1 $0 Label15
li $v0 0
sw $v0 268501072($0)
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
j Label16
Label15:
addiu $a2 $fp 8
lw $a2 0($a2)
sw $a2 268501076($0)
addiu $a2 $fp 12
lw $a2 0($a2)
sw $a2 268501080($0)
jal mod
lw $t1 268501072($0)
move $t6 $t1
li $t1 0
move $t7 $t1
move $t1 $t6
move $t2 $t7
subu $t1 $t1 $t2
move $t8 $t1
move $a1 $t8
bne $a1 $0 Label17
addiu $v0 $fp 12
lw $v0 0($v0)
sw $v0 268501072($0)
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
j Label18
Label17:
addiu $a2 $fp 8
lw $a2 0($a2)
sw $a2 268501076($0)
addiu $a2 $fp 12
lw $a2 0($a2)
sw $a2 268501080($0)
jal mod
lw $t1 268501072($0)
move $t9 $t1
addiu $a2 $fp 12
lw $a2 0($a2)
sw $a2 268501076($0)
move $a2 $t9
sw $a2 268501080($0)
jal gcd
move $t0 $k0
addiu $t0 $t0 0
lw $t1 268501072($0)
sw $t1 0($t0)
move $v0 $k0
addiu $v0 $v0 0
lw $v0 0($v0)
sw $v0 268501072($0)
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
Label18:
Label16:
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
process:
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
addiu $sp $sp 4
addiu $k1 $0 7
li $v0 12
syscall
addiu $a3 $fp 8
sw $v0 0($a3)
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 97
subu $t1 $t1 $t2
move $t6 $t1
move $a1 $t6
beq $a1 $0 Label20
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 98
subu $t1 $t1 $t2
move $t7 $t1
move $a1 $t7
beq $a1 $0 Label21
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 100
subu $t1 $t1 $t2
move $t8 $t1
move $a1 $t8
beq $a1 $0 Label22
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 101
subu $t1 $t1 $t2
move $t9 $t1
move $a1 $t9
beq $a1 $0 Label23
move $t0 $k0
addiu $t0 $t0 0
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 102
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 0
lw $a1 0($a1)
beq $a1 $0 Label24
j Label19
Label20:
jal expre
j Label19
Label21:
li $v0 5
syscall
li $a3 268501176
sw $v0 0($a3)
li $a2 268501176
lw $a2 0($a2)
sw $a2 268501076($0)
jal fibo
lw $t1 268501072($0)
move $t4 $t1
li $t0 268501196
move $t1 $t4
sw $t1 0($t0)
la $a0 String3
li $v0 4
syscall
li $a0 268501196
lw $a0 0($a0)
li $v0 1
syscall
# com printf G11ans
li $a0 10
li $v0 11
syscall
jal printspace
j Label19
Label22:
li $v0 5
syscall
li $a3 268501192
sw $v0 0($a3)
li $a2 268501192
lw $a2 0($a2)
sw $a2 268501076($0)
jal display
j Label19
Label23:
li $v0 5
syscall
li $a3 268501200
sw $v0 0($a3)
li $v0 5
syscall
li $a3 268501204
sw $v0 0($a3)
la $a0 String4
li $v0 4
syscall
li $a2 268501200
lw $a2 0($a2)
sw $a2 268501076($0)
li $a2 268501204
lw $a2 0($a2)
sw $a2 268501080($0)
jal gcd
lw $t1 268501072($0)
move $t5 $t1
move $a0 $t5
li $v0 1
syscall
# com printf T2
li $a0 10
li $v0 11
syscall
jal printspace
j Label19
Label24:
la $a0 String5
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label19
Label19:
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
li $fp 268501316
addiu $sp $fp 8
addiu $sp $sp 8
move $k0 $sp
move $k1 $0 
addiu $k1 $0 2
addiu $t0 $fp 8
li $t1 0
sw $t1 0($t0)
jal testdefine
li $v0 5
syscall
addiu $a3 $fp 12
sw $v0 0($a3)
Label26:
addiu $t1 $fp 8
lw $t1 0($t1)
addiu $t2 $fp 12
lw $t2 0($t2)
subu $t1 $t1 $t2
move $t4 $t1
move $a1 $t4
bgez $a1 Label27
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
move $t5 $t1
addiu $t0 $fp 8
move $t1 $t5
sw $t1 0($t0)
jal process
j Label26
Label27:
li $v0 10
syscall
la $a0 String6
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
#accomplish generate mips code.
