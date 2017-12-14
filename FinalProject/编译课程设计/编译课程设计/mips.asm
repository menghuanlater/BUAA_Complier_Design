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
	String13:.asciiz "gIn2[]:"
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
sw $fp 4($sp)
move $fp $sp
sw $ra 0($fp)
addiu $sp $fp 12
addiu $sp $sp 260
sw $sp 8($fp)
addiu $sp $sp 144
addiu $t0 $fp 12
li $t1 10
sw $t1 0($t0)
addiu $t0 $fp 96
li $t1 40
sw $t1 0($t0)
addiu $t0 $fp 140
li $t1 48
sw $t1 0($t0)
addiu $t0 $fp 224
li $t1 57
sw $t1 0($t0)
addiu $t0 $fp 268
li $t1 0
sw $t1 0($t0)
Label1:
lw $t0 8($fp)
addiu $t0 $t0 0
li $t1 10
addiu $t2 $fp 224
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 4
lw $t1 8($fp)
addiu $t1 $t1 0
lw $t1 0($t1)
li $t2 56
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 8
lw $t1 8($fp)
addiu $t1 $t1 4
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 12
addiu $t1 $fp 268
lw $t1 0($t1)
lw $t2 8($fp)
addiu $t2 $t2 8
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 12
lw $a1 0($a1)
bgez $a1 Label2
lw $t0 8($fp)
addiu $t0 $t0 16
li $t1 20
addiu $t2 $fp 268
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 16
addiu $t1 $fp 268
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
lw $t1 8($fp)
addiu $t1 $t1 16
lw $t1 0($t1)
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 20
li $t1 30
addiu $t2 $fp 268
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 56
addiu $t1 $fp 268
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
lw $t1 8($fp)
addiu $t1 $t1 20
lw $t1 0($t1)
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 24
li $t1 50
addiu $t2 $fp 268
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 100
addiu $t1 $fp 268
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
lw $t1 8($fp)
addiu $t1 $t1 24
lw $t1 0($t1)
sw $t1 0($t0)
addiu $t0 $fp 144
addiu $t1 $fp 268
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 97
sw $t1 0($t0)
addiu $t0 $fp 184
addiu $t1 $fp 268
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 98
sw $t1 0($t0)
addiu $t0 $fp 228
addiu $t1 $fp 268
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 99
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 28
addiu $t1 $fp 268
lw $t1 0($t1)
li $t2 56
addu $t1 $t1 $t2
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 32
lw $t1 8($fp)
addiu $t1 $t1 28
lw $t1 0($t1)
li $t2 55
subu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 268
lw $t1 8($fp)
addiu $t1 $t1 32
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
addiu $a3 $fp 12
lw $a0 0($a3)
li $v0 1
syscall
# com printf G33gint1
li $a0 10
li $v0 11
syscall
la $a0 String10
li $v0 4
syscall
addiu $a3 $fp 96
lw $a0 0($a3)
li $v0 1
syscall
# com printf G36gint4
li $a0 10
li $v0 11
syscall
la $a0 String11
li $v0 4
syscall
addiu $a3 $fp 140
lw $a0 0($a3)
li $v0 11
syscall
# com printf G38gch1
li $a0 10
li $v0 11
syscall
la $a0 String12
li $v0 4
syscall
addiu $a3 $fp 224
lw $a0 0($a3)
li $v0 11
syscall
# com printf G41gch4
li $a0 10
li $v0 11
syscall
addiu $t0 $fp 268
li $t1 0
sw $t1 0($t0)
la $a0 String13
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
Label3:
lw $t0 8($fp)
addiu $t0 $t0 36
li $t1 10
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 40
addiu $t1 $fp 268
lw $t1 0($t1)
lw $t2 8($fp)
addiu $t2 $t2 36
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 40
lw $a1 0($a1)
bgez $a1 Label4
lw $t0 8($fp)
addiu $t0 $t0 44
addiu $t1 $fp 268
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 268
lw $t1 8($fp)
addiu $t1 $t1 44
lw $t1 0($t1)
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 48
addiu $t1 $fp 268
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 52
addiu $t1 $fp 16
lw $t2 8($fp)
addiu $t2 $t2 48
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
lw $a3 8($fp)
addiu $a3 $a3 52
lw $a0 0($a3)
li $v0 1
syscall
# com printf T14
li $a0 10
li $v0 11
syscall
j Label3
Label4:
addiu $t0 $fp 268
li $t1 0
sw $t1 0($t0)
la $a0 String14
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
Label5:
lw $t0 8($fp)
addiu $t0 $t0 56
li $t1 10
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 60
addiu $t1 $fp 268
lw $t1 0($t1)
lw $t2 8($fp)
addiu $t2 $t2 56
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 60
lw $a1 0($a1)
bgez $a1 Label6
lw $t0 8($fp)
addiu $t0 $t0 64
addiu $t1 $fp 268
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 268
lw $t1 8($fp)
addiu $t1 $t1 64
lw $t1 0($t1)
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 68
addiu $t1 $fp 268
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 72
addiu $t1 $fp 56
lw $t2 8($fp)
addiu $t2 $t2 68
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
lw $a3 8($fp)
addiu $a3 $a3 72
lw $a0 0($a3)
li $v0 1
syscall
# com printf T19
li $a0 10
li $v0 11
syscall
j Label5
Label6:
addiu $t0 $fp 268
li $t1 0
sw $t1 0($t0)
la $a0 String15
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
Label7:
lw $t0 8($fp)
addiu $t0 $t0 76
li $t1 10
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 80
addiu $t1 $fp 268
lw $t1 0($t1)
lw $t2 8($fp)
addiu $t2 $t2 76
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 80
lw $a1 0($a1)
bgez $a1 Label8
lw $t0 8($fp)
addiu $t0 $t0 84
addiu $t1 $fp 268
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 268
lw $t1 8($fp)
addiu $t1 $t1 84
lw $t1 0($t1)
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 88
addiu $t1 $fp 268
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 92
addiu $t1 $fp 100
lw $t2 8($fp)
addiu $t2 $t2 88
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
lw $a3 8($fp)
addiu $a3 $a3 92
lw $a0 0($a3)
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
lw $t0 8($fp)
addiu $t0 $t0 96
li $t1 3
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 100
addiu $t1 $fp 144
lw $t2 8($fp)
addiu $t2 $t2 96
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
lw $a3 8($fp)
addiu $a3 $a3 100
lw $a0 0($a3)
li $v0 11
syscall
# com printf T26
li $a0 10
li $v0 11
syscall
la $a0 String17
li $v0 4
syscall
lw $t0 8($fp)
addiu $t0 $t0 104
li $t1 6
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 108
addiu $t1 $fp 144
lw $t2 8($fp)
addiu $t2 $t2 104
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
lw $a3 8($fp)
addiu $a3 $a3 108
lw $a0 0($a3)
li $v0 11
syscall
# com printf T28
li $a0 10
li $v0 11
syscall
la $a0 String18
li $v0 4
syscall
lw $t0 8($fp)
addiu $t0 $t0 112
li $t1 3
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 116
addiu $t1 $fp 184
lw $t2 8($fp)
addiu $t2 $t2 112
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
lw $a3 8($fp)
addiu $a3 $a3 116
lw $a0 0($a3)
li $v0 11
syscall
# com printf T30
li $a0 10
li $v0 11
syscall
la $a0 String19
li $v0 4
syscall
lw $t0 8($fp)
addiu $t0 $t0 120
li $t1 6
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 124
addiu $t1 $fp 184
lw $t2 8($fp)
addiu $t2 $t2 120
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
lw $a3 8($fp)
addiu $a3 $a3 124
lw $a0 0($a3)
li $v0 11
syscall
# com printf T32
li $a0 10
li $v0 11
syscall
la $a0 String20
li $v0 4
syscall
lw $t0 8($fp)
addiu $t0 $t0 128
li $t1 3
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 132
addiu $t1 $fp 228
lw $t2 8($fp)
addiu $t2 $t2 128
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
lw $a3 8($fp)
addiu $a3 $a3 132
lw $a0 0($a3)
li $v0 11
syscall
# com printf T34
li $a0 10
li $v0 11
syscall
la $a0 String21
li $v0 4
syscall
lw $t0 8($fp)
addiu $t0 $t0 136
li $t1 6
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 140
addiu $t1 $fp 228
lw $t2 8($fp)
addiu $t2 $t2 136
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
lw $a3 8($fp)
addiu $a3 $a3 140
lw $a0 0($a3)
li $v0 11
syscall
# com printf T36
li $a0 10
li $v0 11
syscall
move $sp $fp
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
givevaluetoglobalvar:
sw $fp 4($sp)
move $fp $sp
sw $ra 0($fp)
addiu $sp $fp 12
addiu $sp $sp 4
sw $sp 8($fp)
addiu $sp $sp 28
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
addiu $t0 $fp 12
li $t1 0
sw $t1 0($t0)
Label9:
lw $t0 8($fp)
addiu $t0 $t0 0
li $t1 10
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 4
addiu $t1 $fp 12
lw $t1 0($t1)
lw $t2 8($fp)
addiu $t2 $t2 0
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 4
lw $a1 0($a1)
bgez $a1 Label10
lw $t0 8($fp)
addiu $t0 $t0 8
li $t1 200
addiu $t2 $fp 12
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
li $t0 268501344
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
lw $t1 8($fp)
addiu $t1 $t1 8
lw $t1 0($t1)
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 12
li $t1 300
addiu $t2 $fp 12
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
li $t0 268501384
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
lw $t1 8($fp)
addiu $t1 $t1 12
lw $t1 0($t1)
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 16
li $t1 500
addiu $t2 $fp 12
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
li $t0 268501428
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
lw $t1 8($fp)
addiu $t1 $t1 16
lw $t1 0($t1)
sw $t1 0($t0)
li $t0 268501472
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 105
sw $t1 0($t0)
li $t0 268501512
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 106
sw $t1 0($t0)
li $t0 268501556
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 107
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 20
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 66
addu $t1 $t1 $t2
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 24
lw $t1 8($fp)
addiu $t1 $t1 20
lw $t1 0($t1)
li $t2 65
subu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 12
lw $t1 8($fp)
addiu $t1 $t1 24
lw $t1 0($t1)
sw $t1 0($t0)
j Label9
Label10:
move $sp $fp
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
calculatefactorial:
sw $fp 4($sp)
move $fp $sp
sw $ra 0($fp)
addiu $sp $fp 12
lw $v1 268501240($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 0
sw $sp 8($fp)
addiu $sp $sp 28
lw $t0 8($fp)
addiu $t0 $t0 0
li $t1 0
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 4
addiu $t1 $fp 12
lw $t1 0($t1)
lw $t2 8($fp)
addiu $t2 $t2 0
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 4
lw $a1 0($a1)
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
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
j Label12
Label11:
lw $t0 8($fp)
addiu $t0 $t0 8
li $t1 0
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 12
addiu $t1 $fp 12
lw $t1 0($t1)
lw $t2 8($fp)
addiu $t2 $t2 8
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 12
lw $a1 0($a1)
bne $a1 $0 Label13
li $v0 1
sw $v0 268501236($0)
move $sp $fp
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
j Label14
Label13:
lw $t0 8($fp)
addiu $t0 $t0 16
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a2 8($fp)
addiu $a2 $a2 16
lw $a2 0($a2)
sw $a2 268501240($0)
jal calculatefactorial
lw $t0 8($fp)
addiu $t0 $t0 20
lw $t1 268501236($0)
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 24
lw $t1 8($fp)
addiu $t1 $t1 20
lw $t1 0($t1)
addiu $t2 $fp 12
lw $t2 0($t2)
mult $t1 $t2
mflo $t1
sw $t1 0($t0)
lw $v0 8($fp)
addiu $v0 $v0 24
lw $v0 0($v0)
sw $v0 268501236($0)
move $sp $fp
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
Label14:
Label12:
move $sp $fp
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
fibonaci:
sw $fp 4($sp)
move $fp $sp
sw $ra 0($fp)
addiu $sp $fp 12
lw $v1 268501240($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 0
sw $sp 8($fp)
addiu $sp $sp 40
lw $t0 8($fp)
addiu $t0 $t0 0
li $t1 2
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 4
addiu $t1 $fp 12
lw $t1 0($t1)
lw $t2 8($fp)
addiu $t2 $t2 0
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 4
lw $a1 0($a1)
bgtz $a1 Label15
lw $t0 8($fp)
addiu $t0 $t0 8
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 12
li $t1 1
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 16
lw $t1 8($fp)
addiu $t1 $t1 8
lw $t1 0($t1)
lw $t2 8($fp)
addiu $t2 $t2 12
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 16
lw $a1 0($a1)
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
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
j Label18
Label17:
Label18:
li $v0 1
sw $v0 268501236($0)
move $sp $fp
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
j Label16
Label15:
lw $t0 8($fp)
addiu $t0 $t0 20
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a2 8($fp)
addiu $a2 $a2 20
lw $a2 0($a2)
sw $a2 268501240($0)
jal fibonaci
lw $t0 8($fp)
addiu $t0 $t0 24
lw $t1 268501236($0)
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 28
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 2
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a2 8($fp)
addiu $a2 $a2 28
lw $a2 0($a2)
sw $a2 268501240($0)
jal fibonaci
lw $t0 8($fp)
addiu $t0 $t0 32
lw $t1 268501236($0)
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 36
lw $t1 8($fp)
addiu $t1 $t1 24
lw $t1 0($t1)
lw $t2 8($fp)
addiu $t2 $t2 32
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
lw $v0 8($fp)
addiu $v0 $v0 36
lw $v0 0($v0)
sw $v0 268501236($0)
move $sp $fp
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
Label16:
move $sp $fp
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
main:
li $fp 268501596
addiu $sp $fp 12
addiu $sp $sp 88
sw $sp 8($fp)
addiu $sp $sp 24
jal givevaluetoglobalvar
jal testalldefine
lw $t0 8($fp)
addiu $t0 $t0 0
li $t1 8
sw $t1 0($t0)
lw $a2 8($fp)
addiu $a2 $a2 0
lw $a2 0($a2)
sw $a2 268501240($0)
jal fibonaci
lw $t0 8($fp)
addiu $t0 $t0 4
lw $t1 268501236($0)
sw $t1 0($t0)
addiu $t0 $fp 12
lw $t1 8($fp)
addiu $t1 $t1 4
lw $t1 0($t1)
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 8
li $t1 10
sw $t1 0($t0)
lw $a2 8($fp)
addiu $a2 $a2 8
lw $a2 0($a2)
sw $a2 268501240($0)
jal calculatefactorial
lw $t0 8($fp)
addiu $t0 $t0 12
lw $t1 268501236($0)
sw $t1 0($t0)
addiu $t0 $fp 16
li $t1 1
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
lw $t1 8($fp)
addiu $t1 $t1 12
lw $t1 0($t1)
sw $t1 0($t0)
la $a0 String24
li $v0 4
syscall
addiu $a3 $fp 12
lw $a0 0($a3)
li $v0 1
syscall
# com printf G52givevaluetoglobalvar
li $a0 10
li $v0 11
syscall
la $a0 String25
li $v0 4
syscall
lw $t0 8($fp)
addiu $t0 $t0 16
li $t1 1
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 20
addiu $t1 $fp 16
lw $t2 8($fp)
addiu $t2 $t2 16
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
lw $a3 8($fp)
addiu $a3 $a3 20
lw $a0 0($a3)
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
