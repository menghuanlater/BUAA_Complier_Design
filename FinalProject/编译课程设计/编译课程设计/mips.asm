.data
	String1:.asciiz "int1:"
	String2:.asciiz "int2:"
	String3:.asciiz "int3:"
	String4:.asciiz "int4:"
	String5:.asciiz "char1:"
	String6:.asciiz "char2:"
	String7:.asciiz "char3:"
	String8:.asciiz "char4:"
	String9:.asciiz "gInt1:"
	String10:.asciiz "gInt4:"
	String11:.asciiz "gCh1:"
	String12:.asciiz "gCh4:"
	String13:.asciiz "gInt2[]:"
	String14:.asciiz "gInt3[]:"
	String15:.asciiz "gInt5[]:"
	String16:.asciiz "gCh2[3]:"
	String17:.asciiz "gCh2[6]:"
	String18:.asciiz "gCh3[3]:"
	String19:.asciiz "gCh3[6]:"
	String20:.asciiz "gCh5[3]:"
	String21:.asciiz "gCh5[6]:"
	String22:.asciiz "The factorial number must >= 0 ."
	String23:.asciiz "The Fibonaci number must >=1."
	String24:.asciiz "xxx:"
	String25:.asciiz "yyy:"
	String26:.asciiz "Over,Ok!"
.globl main
.text
testalldefine:
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
addiu $sp $sp 260
move $k0 $sp
move $k1 $0 
addiu $sp $sp 120
addiu $k1 $0 36
addiu $t0 $fp 8
li $t1 10
sw $t1 0($t0)
addiu $t0 $fp 92
li $t1 40
sw $t1 0($t0)
addiu $t0 $fp 136
li $t1 48
sw $t1 0($t0)
addiu $t0 $fp 220
li $t1 57
sw $t1 0($t0)
addiu $t0 $fp 264
li $t1 0
sw $t1 0($t0)
Label1:
li $t1 10
addiu $t2 $fp 220
lw $t2 0($t2)
addu $t1 $t1 $t2
move $t4 $t1
move $t1 $t4
li $t2 56
subu $t1 $t1 $t2
move $t5 $t1
move $t1 $t5
li $t2 1
subu $t1 $t1 $t2
move $t6 $t1
addiu $t1 $fp 264
lw $t1 0($t1)
move $t2 $t6
subu $t1 $t1 $t2
move $t7 $t1
move $a1 $t7
bgez $a1 Label2
li $t1 20
addiu $t2 $fp 264
lw $t2 0($t2)
addu $t1 $t1 $t2
move $t8 $t1
addiu $t0 $fp 12
addiu $t1 $fp 264
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
move $t1 $t8
sw $t1 0($t0)
li $t1 30
addiu $t2 $fp 264
lw $t2 0($t2)
addu $t1 $t1 $t2
move $t9 $t1
addiu $t0 $fp 52
addiu $t1 $fp 264
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
move $t1 $t9
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 0
li $t1 50
addiu $t2 $fp 264
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 96
addiu $t1 $fp 264
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
move $t1 $k0
addiu $t1 $t1 0
lw $t1 0($t1)
sw $t1 0($t0)
addiu $t0 $fp 140
addiu $t1 $fp 264
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 97
sw $t1 0($t0)
addiu $t0 $fp 180
addiu $t1 $fp 264
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 98
sw $t1 0($t0)
addiu $t0 $fp 224
addiu $t1 $fp 264
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 99
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 4
addiu $t1 $fp 264
lw $t1 0($t1)
li $t2 56
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 8
move $t1 $k0
addiu $t1 $t1 4
lw $t1 0($t1)
li $t2 55
subu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 264
move $t1 $k0
addiu $t1 $t1 8
lw $t1 0($t1)
sw $t1 0($t0)
j Label1
Label2:
la $a0 String1
li $v0 4
syscall
li $a0 333
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
la $a0 String2
li $v0 4
syscall
li $a0 789
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
la $a0 String3
li $v0 4
syscall
li $a0 -7125
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
la $a0 String4
li $v0 4
syscall
li $a0 -1
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
la $a0 String5
li $v0 4
syscall
li $a0 48
li $v0 11
syscall
li $a0 10
li $v0 11
syscall
la $a0 String6
li $v0 4
syscall
li $a0 45
li $v0 11
syscall
li $a0 10
li $v0 11
syscall
la $a0 String7
li $v0 4
syscall
li $a0 42
li $v0 11
syscall
li $a0 10
li $v0 11
syscall
la $a0 String8
li $v0 4
syscall
li $a0 68
li $v0 11
syscall
li $a0 10
li $v0 11
syscall
la $a0 String9
li $v0 4
syscall
addiu $a0 $fp 8
lw $a0 0($a0)
li $v0 1
syscall
# com printf G33gint1
li $a0 10
li $v0 11
syscall
la $a0 String10
li $v0 4
syscall
addiu $a0 $fp 92
lw $a0 0($a0)
li $v0 1
syscall
# com printf G36gint4
li $a0 10
li $v0 11
syscall
la $a0 String11
li $v0 4
syscall
addiu $a0 $fp 136
lw $a0 0($a0)
li $v0 11
syscall
# com printf G38gch1
li $a0 10
li $v0 11
syscall
la $a0 String12
li $v0 4
syscall
addiu $a0 $fp 220
lw $a0 0($a0)
li $v0 11
syscall
# com printf G41gch4
li $a0 10
li $v0 11
syscall
addiu $t0 $fp 264
li $t1 0
sw $t1 0($t0)
la $a0 String13
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
Label3:
move $t0 $k0
addiu $t0 $t0 12
li $t1 10
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 16
addiu $t1 $fp 264
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 12
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 16
lw $a1 0($a1)
bgez $a1 Label4
move $t0 $k0
addiu $t0 $t0 20
addiu $t1 $fp 264
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 264
move $t1 $k0
addiu $t1 $t1 20
lw $t1 0($t1)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 24
addiu $t1 $fp 264
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 28
addiu $t1 $fp 12
move $t2 $k0
addiu $t2 $t2 24
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
move $a0 $k0
addiu $a0 $a0 28
lw $a0 0($a0)
li $v0 1
syscall
# com printf T14
li $a0 10
li $v0 11
syscall
j Label3
Label4:
addiu $t0 $fp 264
li $t1 0
sw $t1 0($t0)
la $a0 String14
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
Label5:
move $t0 $k0
addiu $t0 $t0 32
li $t1 10
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 36
addiu $t1 $fp 264
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 32
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 36
lw $a1 0($a1)
bgez $a1 Label6
move $t0 $k0
addiu $t0 $t0 40
addiu $t1 $fp 264
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 264
move $t1 $k0
addiu $t1 $t1 40
lw $t1 0($t1)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 44
addiu $t1 $fp 264
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 48
addiu $t1 $fp 52
move $t2 $k0
addiu $t2 $t2 44
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
move $a0 $k0
addiu $a0 $a0 48
lw $a0 0($a0)
li $v0 1
syscall
# com printf T19
li $a0 10
li $v0 11
syscall
j Label5
Label6:
addiu $t0 $fp 264
li $t1 0
sw $t1 0($t0)
la $a0 String15
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
Label7:
move $t0 $k0
addiu $t0 $t0 52
li $t1 10
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 56
addiu $t1 $fp 264
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 52
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 56
lw $a1 0($a1)
bgez $a1 Label8
move $t0 $k0
addiu $t0 $t0 60
addiu $t1 $fp 264
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 264
move $t1 $k0
addiu $t1 $t1 60
lw $t1 0($t1)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 64
addiu $t1 $fp 264
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 68
addiu $t1 $fp 96
move $t2 $k0
addiu $t2 $t2 64
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
move $a0 $k0
addiu $a0 $a0 68
lw $a0 0($a0)
li $v0 1
syscall
# com printf T24
li $a0 10
li $v0 11
syscall
j Label7
Label8:
la $a0 String16
li $v0 4
syscall
move $t0 $k0
addiu $t0 $t0 72
li $t1 3
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 76
addiu $t1 $fp 140
move $t2 $k0
addiu $t2 $t2 72
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
move $a0 $k0
addiu $a0 $a0 76
lw $a0 0($a0)
li $v0 11
syscall
# com printf T26
li $a0 10
li $v0 11
syscall
la $a0 String17
li $v0 4
syscall
move $t0 $k0
addiu $t0 $t0 80
li $t1 6
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 84
addiu $t1 $fp 140
move $t2 $k0
addiu $t2 $t2 80
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
move $a0 $k0
addiu $a0 $a0 84
lw $a0 0($a0)
li $v0 11
syscall
# com printf T28
li $a0 10
li $v0 11
syscall
la $a0 String18
li $v0 4
syscall
move $t0 $k0
addiu $t0 $t0 88
li $t1 3
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 92
addiu $t1 $fp 180
move $t2 $k0
addiu $t2 $t2 88
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
move $a0 $k0
addiu $a0 $a0 92
lw $a0 0($a0)
li $v0 11
syscall
# com printf T30
li $a0 10
li $v0 11
syscall
la $a0 String19
li $v0 4
syscall
move $t0 $k0
addiu $t0 $t0 96
li $t1 6
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 100
addiu $t1 $fp 180
move $t2 $k0
addiu $t2 $t2 96
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
move $a0 $k0
addiu $a0 $a0 100
lw $a0 0($a0)
li $v0 11
syscall
# com printf T32
li $a0 10
li $v0 11
syscall
la $a0 String20
li $v0 4
syscall
move $t0 $k0
addiu $t0 $t0 104
li $t1 3
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 108
addiu $t1 $fp 224
move $t2 $k0
addiu $t2 $t2 104
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
move $a0 $k0
addiu $a0 $a0 108
lw $a0 0($a0)
li $v0 11
syscall
# com printf T34
li $a0 10
li $v0 11
syscall
la $a0 String21
li $v0 4
syscall
move $t0 $k0
addiu $t0 $t0 112
li $t1 6
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 116
addiu $t1 $fp 224
move $t2 $k0
addiu $t2 $t2 112
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
move $a0 $k0
addiu $a0 $a0 116
lw $a0 0($a0)
li $v0 11
syscall
# com printf T36
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
givevaluetoglobalvar:
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
li $t0 268501340
li $t1 100
sw $t1 0($t0)
li $t0 268501424
li $t1 400
sw $t1 0($t0)
li $t0 268501468
li $t1 68
sw $t1 0($t0)
li $t0 268501552
li $t1 70
sw $t1 0($t0)
addiu $t0 $fp 8
li $t1 0
sw $t1 0($t0)
Label9:
li $t1 10
move $t4 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t4
subu $t1 $t1 $t2
move $t5 $t1
move $a1 $t5
bgez $a1 Label10
li $t1 200
addiu $t2 $fp 8
lw $t2 0($t2)
addu $t1 $t1 $t2
move $t6 $t1
li $t0 268501344
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
move $t1 $t6
sw $t1 0($t0)
li $t1 300
addiu $t2 $fp 8
lw $t2 0($t2)
addu $t1 $t1 $t2
move $t7 $t1
li $t0 268501384
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
move $t1 $t7
sw $t1 0($t0)
li $t1 500
addiu $t2 $fp 8
lw $t2 0($t2)
addu $t1 $t1 $t2
move $t8 $t1
li $t0 268501428
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
move $t1 $t8
sw $t1 0($t0)
li $t0 268501472
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 105
sw $t1 0($t0)
li $t0 268501512
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 106
sw $t1 0($t0)
li $t0 268501556
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 107
sw $t1 0($t0)
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 66
addu $t1 $t1 $t2
move $t9 $t1
move $t0 $k0
addiu $t0 $t0 0
move $t1 $t9
li $t2 65
subu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 8
move $t1 $k0
addiu $t1 $t1 0
lw $t1 0($t1)
sw $t1 0($t0)
j Label9
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
calculatefactorial:
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
lw $v1 268501240($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 0
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
bgez $a1 Label11
la $a0 String22
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
li $v0 0
sw $v0 268501236($0)
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
li $t1 0
move $t6 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t6
subu $t1 $t1 $t2
move $t7 $t1
move $a1 $t7
bne $a1 $0 Label13
li $v0 1
sw $v0 268501236($0)
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
j Label14
Label13:
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
move $t8 $t1
move $a2 $t8
sw $a2 268501240($0)
jal calculatefactorial
lw $t1 268501236($0)
move $t9 $t1
move $t0 $k0
addiu $t0 $t0 0
move $t1 $t9
addiu $t2 $fp 8
lw $t2 0($t2)
mult $t1 $t2
mflo $t1
sw $t1 0($t0)
move $v0 $k0
addiu $v0 $v0 0
lw $v0 0($v0)
sw $v0 268501236($0)
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
Label14:
Label12:
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
fibonaci:
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
lw $v1 268501240($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 0
move $k0 $sp
move $k1 $0 
addiu $sp $sp 16
addiu $k1 $0 10
li $t1 2
move $t4 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t4
subu $t1 $t1 $t2
move $t5 $t1
move $a1 $t5
bgtz $a1 Label15
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
move $t6 $t1
li $t1 1
move $t7 $t1
move $t1 $t6
move $t2 $t7
subu $t1 $t1 $t2
move $t8 $t1
move $a1 $t8
bgtz $a1 Label17
la $a0 String23
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
li $v0 0
sw $v0 268501236($0)
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
Label18:
li $v0 1
sw $v0 268501236($0)
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
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
move $t9 $t1
move $a2 $t9
sw $a2 268501240($0)
jal fibonaci
move $t0 $k0
addiu $t0 $t0 0
lw $t1 268501236($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 4
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 2
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 4
lw $a2 0($a2)
sw $a2 268501240($0)
jal fibonaci
move $t0 $k0
addiu $t0 $t0 8
lw $t1 268501236($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 12
move $t1 $k0
addiu $t1 $t1 0
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 8
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
move $v0 $k0
addiu $v0 $v0 12
lw $v0 0($v0)
sw $v0 268501236($0)
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
main:
li $fp 268501596
addiu $sp $fp 8
addiu $sp $sp 88
move $k0 $sp
move $k1 $0 
addiu $k1 $0 6
jal givevaluetoglobalvar
jal testalldefine
li $t1 8
move $t4 $t1
move $a2 $t4
sw $a2 268501240($0)
jal fibonaci
lw $t1 268501236($0)
move $t5 $t1
addiu $t0 $fp 8
move $t1 $t5
sw $t1 0($t0)
li $t1 10
move $t6 $t1
move $a2 $t6
sw $a2 268501240($0)
jal calculatefactorial
lw $t1 268501236($0)
move $t7 $t1
addiu $t0 $fp 12
li $t1 1
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
move $t1 $t7
sw $t1 0($t0)
la $a0 String24
li $v0 4
syscall
addiu $a0 $fp 8
lw $a0 0($a0)
li $v0 1
syscall
# com printf G52givevaluetoglobalvar
li $a0 10
li $v0 11
syscall
la $a0 String25
li $v0 4
syscall
li $t1 1
move $t8 $t1
addiu $t1 $fp 12
move $t2 $t8
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
move $t9 $t1
move $a0 $t9
li $v0 1
syscall
# com printf T6
li $a0 10
li $v0 11
syscall
la $a0 String26
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
li $v0 10
syscall
#accomplish generate mips code.
