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
	String22:.asciiz "Are you kidding me?\\n"
	String23:.asciiz "The factorial number must >= 0 ."
	String24:.asciiz "The Fibonaci number must >=1."
	String25:.asciiz "complex --- x1:"
	String26:.asciiz "complex --- x2:"
	String27:.asciiz "complex --- x3:"
	String28:.asciiz "complex --- x4:"
	String29:.asciiz "complex --- x5:"
	String30:.asciiz "In If-Else i = 4"
	String31:.asciiz "In If-Else i = 3"
	String32:.asciiz "In If-Else i = 2"
	String33:.asciiz "In If-Else i = 1"
	String34:.asciiz "Test If-Else Over."
	String35:.asciiz "Welcome"
	String36:.asciiz "False"
	String37:.asciiz "True"
	String38:.asciiz "Tiga"
	String39:.asciiz "CoCo"
	String40:.asciiz "Sally"
	String41:.asciiz "TAT_-_"
	String42:.asciiz "My Sniper"
	String43:.asciiz "At test While:"
	String44:.asciiz "many params1:"
	String45:.asciiz "many params2:"
	String46:.asciiz "The All Value Of GGG:"
	String47:.asciiz "Hello Boy, you need to be careful"
	String48:.asciiz "If you input 0 ---> end the procedure"
	String49:.asciiz "If you input 1 ---> we return the number of 1+1"
	String50:.asciiz "If you input 2 ---> we return the number of 2*2"
	String51:.asciiz "If you input others ---> we carry out the next procedure"
	String52:.asciiz "Hey,Input int number to choose:"
	String53:.asciiz "You mean to exit.Ok -_-"
	String54:.asciiz "The result 1+1 is:"
	String55:.asciiz "The result 2*2 is:"
	String56:.asciiz "Next the trip."
	String57:.asciiz "complex expression add --- > x6:"
	String58:.asciiz "Test scanf"
	String59:.asciiz "Test printf character"
	String60:.asciiz "return100:"
	String61:.asciiz "gCh2[1]:"
	String62:.asciiz "const1:"
	String63:.asciiz "const2:"
	String64:.asciiz "multi_layer:"
	String65:.asciiz "Congratulations,you passed all tests."
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
# com printf G34gint1
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
# com printf G37gint4
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
# com printf G39gch1
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
# com printf G42gch4
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
li $t0 268502116
li $t1 100
sw $t1 0($t0)
li $t0 268502200
li $t1 400
sw $t1 0($t0)
li $t0 268502244
li $t1 68
sw $t1 0($t0)
li $t0 268502328
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
li $t0 268502120
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
li $t0 268502160
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
li $t0 268502204
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
move $t1 $t8
sw $t1 0($t0)
li $t0 268502248
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 105
sw $t1 0($t0)
li $t0 268502288
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 106
sw $t1 0($t0)
li $t0 268502332
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
returnadd:
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
lw $v1 268502016($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502020($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502024($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502028($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502032($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502036($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502040($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502044($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502048($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502052($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 4
move $k0 $sp
move $k1 $0 
addiu $sp $sp 12
addiu $k1 $0 9
addiu $t1 $fp 8
lw $t1 0($t1)
addiu $t2 $fp 12
lw $t2 0($t2)
addu $t1 $t1 $t2
move $t4 $t1
move $t1 $t4
addiu $t2 $fp 16
lw $t2 0($t2)
addu $t1 $t1 $t2
move $t5 $t1
move $t1 $t5
addiu $t2 $fp 20
lw $t2 0($t2)
addu $t1 $t1 $t2
move $t6 $t1
move $t1 $t6
addiu $t2 $fp 24
lw $t2 0($t2)
addu $t1 $t1 $t2
move $t7 $t1
move $t1 $t7
addiu $t2 $fp 28
lw $t2 0($t2)
addu $t1 $t1 $t2
move $t8 $t1
move $t1 $t8
addiu $t2 $fp 32
lw $t2 0($t2)
addu $t1 $t1 $t2
move $t9 $t1
move $t0 $k0
addiu $t0 $t0 0
move $t1 $t9
addiu $t2 $fp 36
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 4
move $t1 $k0
addiu $t1 $t1 0
lw $t1 0($t1)
addiu $t2 $fp 40
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 8
move $t1 $k0
addiu $t1 $t1 4
lw $t1 0($t1)
addiu $t2 $fp 44
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 48
move $t1 $k0
addiu $t1 $t1 8
lw $t1 0($t1)
sw $t1 0($t0)
addiu $v0 $fp 48
lw $v0 0($v0)
sw $v0 268502012($0)
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
returnmix:
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
lw $v1 268502016($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502020($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502024($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502028($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502032($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502036($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502040($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502044($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502048($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502052($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 8
move $k0 $sp
move $k1 $0 
addiu $sp $sp 68
addiu $k1 $0 23
addiu $t0 $fp 52
li $t1 0
sw $t1 0($t0)
addiu $t1 $fp 8
lw $t1 0($t1)
addiu $t2 $fp 12
lw $t2 0($t2)
addu $t1 $t1 $t2
move $t4 $t1
move $t1 $t4
addiu $t2 $fp 16
lw $t2 0($t2)
addu $t1 $t1 $t2
move $t5 $t1
move $t1 $t5
addiu $t2 $fp 20
lw $t2 0($t2)
addu $t1 $t1 $t2
move $t6 $t1
move $t1 $t6
addiu $t2 $fp 24
lw $t2 0($t2)
addu $t1 $t1 $t2
move $t7 $t1
addiu $t1 $fp 28
lw $t1 0($t1)
addiu $t2 $fp 32
lw $t2 0($t2)
mult $t1 $t2
mflo $t1
move $t8 $t1
move $t1 $t7
move $t2 $t8
subu $t1 $t1 $t2
move $t9 $t1
move $t0 $k0
addiu $t0 $t0 0
move $t1 $t9
addiu $t2 $fp 36
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 4
move $t1 $k0
addiu $t1 $t1 0
lw $t1 0($t1)
addiu $t2 $fp 40
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 8
addiu $t1 $fp 44
lw $t1 0($t1)
li $t2 2
div $t1 $t2
mflo $t1
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 12
move $t1 $k0
addiu $t1 $t1 4
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 8
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 48
move $t1 $k0
addiu $t1 $t1 12
lw $t1 0($t1)
sw $t1 0($t0)
Label11:
move $t0 $k0
addiu $t0 $t0 16
li $t1 10
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 20
addiu $t1 $fp 52
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 16
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 20
lw $a1 0($a1)
bgez $a1 Label12
move $t0 $k0
addiu $t0 $t0 24
addiu $t1 $fp 52
lw $t1 0($t1)
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 24
lw $a1 0($a1)
beq $a1 $0 Label14
move $t0 $k0
addiu $t0 $t0 28
addiu $t1 $fp 52
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 28
lw $a1 0($a1)
beq $a1 $0 Label15
move $t0 $k0
addiu $t0 $t0 32
addiu $t1 $fp 52
lw $t1 0($t1)
li $t2 2
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 32
lw $a1 0($a1)
beq $a1 $0 Label16
move $t0 $k0
addiu $t0 $t0 36
addiu $t1 $fp 52
lw $t1 0($t1)
li $t2 3
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 36
lw $a1 0($a1)
beq $a1 $0 Label17
move $t0 $k0
addiu $t0 $t0 40
addiu $t1 $fp 52
lw $t1 0($t1)
li $t2 4
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 40
lw $a1 0($a1)
beq $a1 $0 Label18
move $t0 $k0
addiu $t0 $t0 44
addiu $t1 $fp 52
lw $t1 0($t1)
li $t2 5
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 44
lw $a1 0($a1)
beq $a1 $0 Label19
move $t0 $k0
addiu $t0 $t0 48
addiu $t1 $fp 52
lw $t1 0($t1)
li $t2 6
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 48
lw $a1 0($a1)
beq $a1 $0 Label20
move $t0 $k0
addiu $t0 $t0 52
addiu $t1 $fp 52
lw $t1 0($t1)
li $t2 7
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 52
lw $a1 0($a1)
beq $a1 $0 Label21
move $t0 $k0
addiu $t0 $t0 56
addiu $t1 $fp 52
lw $t1 0($t1)
li $t2 8
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 56
lw $a1 0($a1)
beq $a1 $0 Label22
move $t0 $k0
addiu $t0 $t0 60
addiu $t1 $fp 52
lw $t1 0($t1)
li $t2 9
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 60
lw $a1 0($a1)
beq $a1 $0 Label23
la $a0 String22
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label13
Label14:
li $t0 268502372
li $t1 0
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
sw $t1 0($t0)
j Label13
Label15:
li $t0 268502372
li $t1 1
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
addiu $t1 $fp 12
lw $t1 0($t1)
sw $t1 0($t0)
j Label13
Label16:
li $t0 268502372
li $t1 2
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
addiu $t1 $fp 16
lw $t1 0($t1)
sw $t1 0($t0)
j Label13
Label17:
li $t0 268502372
li $t1 3
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
addiu $t1 $fp 20
lw $t1 0($t1)
sw $t1 0($t0)
j Label13
Label18:
li $t0 268502372
li $t1 4
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
addiu $t1 $fp 24
lw $t1 0($t1)
sw $t1 0($t0)
j Label13
Label19:
li $t0 268502372
li $t1 5
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
addiu $t1 $fp 28
lw $t1 0($t1)
sw $t1 0($t0)
j Label13
Label20:
li $t0 268502372
li $t1 6
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
addiu $t1 $fp 32
lw $t1 0($t1)
sw $t1 0($t0)
j Label13
Label21:
li $t0 268502372
li $t1 7
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
addiu $t1 $fp 36
lw $t1 0($t1)
sw $t1 0($t0)
j Label13
Label22:
li $t0 268502372
li $t1 8
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
addiu $t1 $fp 40
lw $t1 0($t1)
sw $t1 0($t0)
j Label13
Label23:
li $t0 268502372
li $t1 9
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
addiu $t1 $fp 44
lw $t1 0($t1)
sw $t1 0($t0)
j Label13
Label13:
move $t0 $k0
addiu $t0 $t0 64
addiu $t1 $fp 52
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 52
move $t1 $k0
addiu $t1 $t1 64
lw $t1 0($t1)
sw $t1 0($t0)
j Label11
Label12:
addiu $v0 $fp 48
lw $v0 0($v0)
sw $v0 268502012($0)
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
mixparam:
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
lw $v1 268502016($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502020($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502024($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502028($0)
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
move $a1 $t4
beq $a1 $0 Label25
li $v0 49
sw $v0 268502012($0)
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
j Label26
Label25:
addiu $t1 $fp 16
lw $t1 0($t1)
addiu $t2 $fp 20
lw $t2 0($t2)
addu $t1 $t1 $t2
move $t5 $t1
move $a1 $t5
beq $a1 $0 Label27
li $v0 50
sw $v0 268502012($0)
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
j Label28
Label27:
li $v0 48
sw $v0 268502012($0)
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
Label28:
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
lw $v1 268502016($0)
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
bgez $a1 Label29
la $a0 String23
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
li $v0 0
sw $v0 268502012($0)
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
j Label30
Label29:
li $t1 0
move $t6 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t6
subu $t1 $t1 $t2
move $t7 $t1
move $a1 $t7
bne $a1 $0 Label31
li $v0 1
sw $v0 268502012($0)
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
j Label32
Label31:
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
move $t8 $t1
move $a2 $t8
sw $a2 268502016($0)
jal calculatefactorial
lw $t1 268502012($0)
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
sw $v0 268502012($0)
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
Label32:
Label30:
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
lw $v1 268502016($0)
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
bgtz $a1 Label33
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
bgtz $a1 Label35
la $a0 String24
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
li $v0 0
sw $v0 268502012($0)
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
j Label36
Label35:
Label36:
li $v0 1
sw $v0 268502012($0)
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
j Label34
Label33:
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
move $t9 $t1
move $a2 $t9
sw $a2 268502016($0)
jal fibonaci
move $t0 $k0
addiu $t0 $t0 0
lw $t1 268502012($0)
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
sw $a2 268502016($0)
jal fibonaci
move $t0 $k0
addiu $t0 $t0 8
lw $t1 268502012($0)
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
sw $v0 268502012($0)
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
Label34:
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
return100:
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
li $v0 100
sw $v0 268502012($0)
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
returnintvalue:
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
addiu $k1 $0 6
li $t1 8
move $t4 $t1
move $a2 $t4
sw $a2 268502016($0)
jal fibonaci
lw $t1 268502012($0)
move $t5 $t1
li $t1 4
move $t6 $t1
move $a2 $t6
sw $a2 268502016($0)
jal calculatefactorial
lw $t1 268502012($0)
move $t7 $t1
li $t1 100
move $t2 $t5
addu $t1 $t1 $t2
move $t8 $t1
move $t1 $t8
move $t2 $t7
addu $t1 $t1 $t2
move $t9 $t1
move $v0 $t9
sw $v0 268502012($0)
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
complexexpression:
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
addiu $sp $sp 332
addiu $k1 $0 89
li $t1 9
move $t4 $t1
move $a2 $t4
sw $a2 268502016($0)
jal fibonaci
lw $t1 268502012($0)
move $t5 $t1
li $t1 7
move $t2 $t5
mult $t1 $t2
mflo $t1
move $t6 $t1
li $t1 7
move $t2 $t6
subu $t1 $t1 $t2
move $t7 $t1
li $t1 5
move $t8 $t1
move $a2 $t8
sw $a2 268502016($0)
jal calculatefactorial
lw $t1 268502012($0)
move $t9 $t1
move $t0 $k0
addiu $t0 $t0 0
move $t1 $t9
li $t2 174
subu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 4
move $t1 $k0
addiu $t1 $t1 0
lw $t1 0($t1)
li $t2 67
addu $t1 $t1 $t2
sw $t1 0($t0)
jal return100
move $t0 $k0
addiu $t0 $t0 8
lw $t1 268502012($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 12
move $t1 $k0
addiu $t1 $t1 8
lw $t1 0($t1)
li $t2 16
subu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 16
move $t1 $k0
addiu $t1 $t1 12
lw $t1 0($t1)
li $t2 12
subu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 20
move $t1 $t7
li $t2 2
div $t1 $t2
mflo $t1
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 24
move $t1 $k0
addiu $t1 $t1 4
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 16
lw $t2 0($t2)
div $t1 $t2
mflo $t1
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 28
move $t1 $k0
addiu $t1 $t1 20
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 24
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 32
move $t1 $k0
addiu $t1 $t1 28
lw $t1 0($t1)
li $t2 -96
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 8
move $t1 $k0
addiu $t1 $t1 32
lw $t1 0($t1)
sw $t1 0($t0)
la $a0 String25
li $v0 4
syscall
addiu $a0 $fp 8
lw $a0 0($a0)
li $v0 1
syscall
# com printf G84x1
li $a0 10
li $v0 11
syscall
move $t0 $k0
addiu $t0 $t0 36
li $t1 7
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 36
lw $a2 0($a2)
sw $a2 268502016($0)
jal fibonaci
move $t0 $k0
addiu $t0 $t0 40
lw $t1 268502012($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 44
li $t1 1
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 44
lw $a2 0($a2)
sw $a2 268502016($0)
jal fibonaci
move $t0 $k0
addiu $t0 $t0 48
lw $t1 268502012($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 52
li $t1 -15
move $t2 $k0
addiu $t2 $t2 40
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 56
move $t1 $k0
addiu $t1 $t1 52
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 48
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 60
move $t1 $k0
addiu $t1 $t1 56
lw $t1 0($t1)
li $t2 2
subu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 64
li $t1 3
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 64
lw $a2 0($a2)
sw $a2 268502016($0)
jal calculatefactorial
move $t0 $k0
addiu $t0 $t0 68
lw $t1 268502012($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 72
li $t1 56
move $t2 $k0
addiu $t2 $t2 60
lw $t2 0($t2)
mult $t1 $t2
mflo $t1
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 76
li $t1 89
move $t2 $k0
addiu $t2 $t2 72
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 80
move $t1 $k0
addiu $t1 $t1 76
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 68
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 84
li $t1 3
move $t2 $k0
addiu $t2 $t2 80
lw $t2 0($t2)
mult $t1 $t2
mflo $t1
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 88
move $t1 $k0
addiu $t1 $t1 84
lw $t1 0($t1)
li $t2 3
subu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 92
li $t1 2
move $t2 $k0
addiu $t2 $t2 88
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 96
move $t1 $k0
addiu $t1 $t1 92
lw $t1 0($t1)
li $t2 4
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 100
li $t1 1
move $t2 $k0
addiu $t2 $t2 96
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 104
move $t1 $k0
addiu $t1 $t1 100
lw $t1 0($t1)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 108
move $t1 $k0
addiu $t1 $t1 104
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 112
li $t1 111
move $t2 $k0
addiu $t2 $t2 108
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 116
move $t1 $k0
addiu $t1 $t1 112
lw $t1 0($t1)
li $t2 2
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 120
li $t1 4
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 120
lw $a2 0($a2)
sw $a2 268502016($0)
jal calculatefactorial
move $t0 $k0
addiu $t0 $t0 124
lw $t1 268502012($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 128
li $t1 6
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 128
lw $a2 0($a2)
sw $a2 268502016($0)
jal fibonaci
move $t0 $k0
addiu $t0 $t0 132
lw $t1 268502012($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 136
move $t1 $k0
addiu $t1 $t1 124
lw $t1 0($t1)
li $t2 4
div $t1 $t2
mflo $t1
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 140
move $t1 $k0
addiu $t1 $t1 136
lw $t1 0($t1)
li $t2 111
mult $t1 $t2
mflo $t1
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 144
move $t1 $k0
addiu $t1 $t1 116
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 140
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 148
move $t1 $k0
addiu $t1 $t1 144
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 132
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 12
move $t1 $k0
addiu $t1 $t1 148
lw $t1 0($t1)
sw $t1 0($t0)
la $a0 String26
li $v0 4
syscall
addiu $a0 $fp 12
lw $a0 0($a0)
li $v0 1
syscall
# com printf G85x2
li $a0 10
li $v0 11
syscall
move $t0 $k0
addiu $t0 $t0 152
li $t1 6
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 152
lw $a2 0($a2)
sw $a2 268502016($0)
jal fibonaci
move $t0 $k0
addiu $t0 $t0 156
lw $t1 268502012($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 160
li $t1 139
move $t2 $k0
addiu $t2 $t2 156
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 164
li $t1 2
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 164
lw $a2 0($a2)
sw $a2 268502016($0)
jal fibonaci
move $t0 $k0
addiu $t0 $t0 168
lw $t1 268502012($0)
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 168
lw $a2 0($a2)
sw $a2 268502016($0)
jal fibonaci
move $t0 $k0
addiu $t0 $t0 172
lw $t1 268502012($0)
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 172
lw $a2 0($a2)
sw $a2 268502016($0)
jal fibonaci
move $t0 $k0
addiu $t0 $t0 176
lw $t1 268502012($0)
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 176
lw $a2 0($a2)
sw $a2 268502016($0)
jal fibonaci
move $t0 $k0
addiu $t0 $t0 180
lw $t1 268502012($0)
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 180
lw $a2 0($a2)
sw $a2 268502016($0)
jal calculatefactorial
move $t0 $k0
addiu $t0 $t0 184
lw $t1 268502012($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 188
move $t1 $k0
addiu $t1 $t1 160
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 184
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 192
move $t1 $k0
addiu $t1 $t1 188
lw $t1 0($t1)
li $t2 9
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 16
move $t1 $k0
addiu $t1 $t1 192
lw $t1 0($t1)
sw $t1 0($t0)
la $a0 String27
li $v0 4
syscall
addiu $a0 $fp 16
lw $a0 0($a0)
li $v0 1
syscall
# com printf G86x3
li $a0 10
li $v0 11
syscall
jal return100
move $t0 $k0
addiu $t0 $t0 196
lw $t1 268502012($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 200
li $t1 3
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 200
lw $a2 0($a2)
sw $a2 268502016($0)
jal fibonaci
move $t0 $k0
addiu $t0 $t0 204
lw $t1 268502012($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 208
li $t1 268502120
move $t2 $k0
addiu $t2 $t2 204
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 212
li $t1 3
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 212
lw $a2 0($a2)
sw $a2 268502016($0)
jal calculatefactorial
move $t0 $k0
addiu $t0 $t0 216
lw $t1 268502012($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 220
li $t1 268502204
move $t2 $k0
addiu $t2 $t2 216
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 224
move $t1 $k0
addiu $t1 $t1 196
lw $t1 0($t1)
li $t2 50
div $t1 $t2
mflo $t1
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 228
li $t1 14
move $t2 $k0
addiu $t2 $t2 224
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 232
move $t1 $k0
addiu $t1 $t1 228
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 208
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 236
move $t1 $k0
addiu $t1 $t1 232
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 220
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 240
move $t1 $k0
addiu $t1 $t1 236
lw $t1 0($t1)
li $t2 5000
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 20
move $t1 $k0
addiu $t1 $t1 240
lw $t1 0($t1)
sw $t1 0($t0)
la $a0 String28
li $v0 4
syscall
addiu $a0 $fp 20
lw $a0 0($a0)
li $v0 1
syscall
# com printf G87x4
li $a0 10
li $v0 11
syscall
move $t0 $k0
addiu $t0 $t0 244
li $t1 5
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 244
lw $a2 0($a2)
sw $a2 268502016($0)
jal calculatefactorial
move $t0 $k0
addiu $t0 $t0 248
lw $t1 268502012($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 252
move $t1 $k0
addiu $t1 $t1 248
lw $t1 0($t1)
li $t2 67
subu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 256
li $t1 4
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 260
li $t1 268502160
move $t2 $k0
addiu $t2 $t2 256
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
jal return100
move $t0 $k0
addiu $t0 $t0 264
lw $t1 268502012($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 268
li $t1 5
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 268
lw $a2 0($a2)
sw $a2 268502016($0)
jal fibonaci
move $t0 $k0
addiu $t0 $t0 272
lw $t1 268502012($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 276
move $t1 $k0
addiu $t1 $t1 252
lw $t1 0($t1)
li $t2 97
mult $t1 $t2
mflo $t1
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 280
move $t1 $k0
addiu $t1 $t1 276
lw $t1 0($t1)
addiu $t2 $fp 8
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 284
move $t1 $k0
addiu $t1 $t1 280
lw $t1 0($t1)
addiu $t2 $fp 16
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 288
move $t1 $k0
addiu $t1 $t1 284
lw $t1 0($t1)
li $t2 4666
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 292
move $t1 $k0
addiu $t1 $t1 288
lw $t1 0($t1)
li $t2 72
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 296
move $t1 $k0
addiu $t1 $t1 292
lw $t1 0($t1)
li $t2 87
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 300
move $t1 $k0
addiu $t1 $t1 296
lw $t1 0($t1)
li $t2 57
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 304
move $t1 $k0
addiu $t1 $t1 300
lw $t1 0($t1)
li $t2 268502244
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 308
move $t1 $k0
addiu $t1 $t1 304
lw $t1 0($t1)
li $t2 5320
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 312
move $t1 $k0
addiu $t1 $t1 308
lw $t1 0($t1)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 316
move $t1 $k0
addiu $t1 $t1 312
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 260
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 320
move $t1 $k0
addiu $t1 $t1 316
lw $t1 0($t1)
li $t2 1000
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 324
move $t1 $k0
addiu $t1 $t1 320
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 264
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 328
move $t1 $k0
addiu $t1 $t1 324
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 272
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 24
move $t1 $k0
addiu $t1 $t1 328
lw $t1 0($t1)
sw $t1 0($t0)
la $a0 String29
li $v0 4
syscall
addiu $a0 $fp 24
lw $a0 0($a0)
li $v0 1
syscall
# com printf G88x5
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
complexif_else:
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
addiu $sp $sp 20
addiu $k1 $0 11
addiu $t0 $fp 8
li $t1 4
sw $t1 0($t0)
Label37:
li $t1 0
move $t4 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t4
subu $t1 $t1 $t2
move $t5 $t1
move $a1 $t5
bltz $a1 Label38
li $t1 4
move $t6 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t6
subu $t1 $t1 $t2
move $t7 $t1
move $a1 $t7
bne $a1 $0 Label39
la $a0 String30
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label40
Label39:
li $t1 3
move $t8 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t8
subu $t1 $t1 $t2
move $t9 $t1
move $a1 $t9
bne $a1 $0 Label41
la $a0 String31
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label42
Label41:
move $t0 $k0
addiu $t0 $t0 0
li $t1 2
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
bne $a1 $0 Label43
la $a0 String32
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label44
Label43:
move $t0 $k0
addiu $t0 $t0 8
li $t1 1
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
bne $a1 $0 Label45
la $a0 String33
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label46
Label45:
la $a0 String34
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
Label46:
Label44:
Label42:
Label40:
move $t0 $k0
addiu $t0 $t0 16
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 8
move $t1 $k0
addiu $t1 $t1 16
lw $t1 0($t1)
sw $t1 0($t0)
j Label37
Label38:
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
complexswitch_case:
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
addiu $sp $sp 28
addiu $k1 $0 13
addiu $t0 $fp 8
li $t1 1
sw $t1 0($t0)
Label47:
li $t1 4
move $t4 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t4
subu $t1 $t1 $t2
move $t5 $t1
move $a1 $t5
bgtz $a1 Label48
move $t0 $k0
addiu $t0 $t0 8
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 8
lw $a1 0($a1)
beq $a1 $0 Label50
move $t0 $k0
addiu $t0 $t0 12
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 2
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 12
lw $a1 0($a1)
beq $a1 $0 Label51
move $t0 $k0
addiu $t0 $t0 16
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 3
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 16
lw $a1 0($a1)
beq $a1 $0 Label54
move $t0 $k0
addiu $t0 $t0 20
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 4
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 20
lw $a1 0($a1)
beq $a1 $0 Label57
j Label49
Label50:
la $a0 String35
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
la $a0 String35
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label49
Label51:
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 2
subu $t1 $t1 $t2
move $t6 $t1
move $a1 $t6
beq $a1 $0 Label52
la $a0 String36
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label53
Label52:
la $a0 String37
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
Label53:
j Label49
Label54:
li $t0 268502116
li $t1 3
sw $t1 0($t0)
Label55:
li $a1 268502116
lw $a1 0($a1)
beq $a1 $0 Label56
la $a0 String38
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
li $t1 268502116
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
move $t7 $t1
li $t0 268502116
move $t1 $t7
sw $t1 0($t0)
j Label55
Label56:
j Label49
Label57:
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
move $t8 $t1
move $t1 $t8
li $t2 2
subu $t1 $t1 $t2
move $t9 $t1
move $a1 $t9
beq $a1 $0 Label59
move $t0 $k0
addiu $t0 $t0 0
move $t1 $t8
li $t2 3
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 0
lw $a1 0($a1)
beq $a1 $0 Label60
move $t0 $k0
addiu $t0 $t0 4
move $t1 $t8
li $t2 4
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 4
lw $a1 0($a1)
beq $a1 $0 Label61
la $a0 String39
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label58
Label59:
la $a0 String40
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label58
Label60:
la $a0 String41
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label58
Label61:
la $a0 String42
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label58
Label58:
j Label49
Label49:
move $t0 $k0
addiu $t0 $t0 24
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 8
move $t1 $k0
addiu $t1 $t1 24
lw $t1 0($t1)
sw $t1 0($t0)
j Label47
Label48:
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
complexwhile:
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
addiu $sp $sp 32
addiu $k1 $0 14
addiu $t0 $fp 8
li $t1 0
sw $t1 0($t0)
Label64:
li $t1 3
move $t4 $t1
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $t4
subu $t1 $t1 $t2
move $t5 $t1
move $a1 $t5
bgez $a1 Label65
addiu $t0 $fp 12
li $t1 0
sw $t1 0($t0)
Label66:
li $t1 3
move $t6 $t1
addiu $t1 $fp 12
lw $t1 0($t1)
move $t2 $t6
subu $t1 $t1 $t2
move $t7 $t1
move $a1 $t7
bgez $a1 Label67
addiu $t0 $fp 16
li $t1 0
sw $t1 0($t0)
Label68:
li $t1 3
move $t8 $t1
addiu $t1 $fp 16
lw $t1 0($t1)
move $t2 $t8
subu $t1 $t1 $t2
move $t9 $t1
move $a1 $t9
bgez $a1 Label69
la $a0 String43
li $v0 4
syscall
move $t0 $k0
addiu $t0 $t0 0
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 9
mult $t1 $t2
mflo $t1
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 4
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 3
mult $t1 $t2
mflo $t1
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 8
move $t1 $k0
addiu $t1 $t1 0
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 4
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 12
move $t1 $k0
addiu $t1 $t1 8
lw $t1 0($t1)
addiu $t2 $fp 16
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 16
move $t1 $k0
addiu $t1 $t1 12
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
sw $t1 0($t0)
move $a0 $k0
addiu $a0 $a0 16
lw $a0 0($a0)
li $v0 1
syscall
# com printf T11
li $a0 10
li $v0 11
syscall
move $t0 $k0
addiu $t0 $t0 20
addiu $t1 $fp 16
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 16
move $t1 $k0
addiu $t1 $t1 20
lw $t1 0($t1)
sw $t1 0($t0)
j Label68
Label69:
move $t0 $k0
addiu $t0 $t0 24
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 12
move $t1 $k0
addiu $t1 $t1 24
lw $t1 0($t1)
sw $t1 0($t0)
j Label66
Label67:
move $t0 $k0
addiu $t0 $t0 28
addiu $t1 $fp 8
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 8
move $t1 $k0
addiu $t1 $t1 28
lw $t1 0($t1)
sw $t1 0($t0)
j Label64
Label65:
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
_multi_layer:
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
lw $v1 268502016($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268502020($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 0
move $k0 $sp
move $k1 $0 
addiu $k1 $0 1
addiu $t1 $fp 8
lw $t1 0($t1)
addiu $t2 $fp 12
lw $t2 0($t2)
addu $t1 $t1 $t2
move $t4 $t1
move $v0 $t4
sw $v0 268502012($0)
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
main:
li $fp 268502412
addiu $sp $fp 8
addiu $sp $sp 120
move $k0 $sp
move $k1 $0 
addiu $sp $sp 168
addiu $k1 $0 48
jal givevaluetoglobalvar
jal testalldefine
la $a0 String44
li $v0 4
syscall
li $t1 1
move $t4 $t1
li $t1 26
move $t5 $t1
li $t1 33
move $t6 $t1
li $t1 445
move $t7 $t1
li $t1 512
move $t8 $t1
li $t1 656
move $t9 $t1
move $t0 $k0
addiu $t0 $t0 0
li $t1 744
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 4
li $t1 834
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 8
li $t1 954
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 12
li $t1 1021
sw $t1 0($t0)
move $a2 $t4
sw $a2 268502016($0)
move $a2 $t5
sw $a2 268502020($0)
move $a2 $t6
sw $a2 268502024($0)
move $a2 $t7
sw $a2 268502028($0)
move $a2 $t8
sw $a2 268502032($0)
move $a2 $t9
sw $a2 268502036($0)
move $a2 $k0
addiu $a2 $a2 0
lw $a2 0($a2)
sw $a2 268502040($0)
move $a2 $k0
addiu $a2 $a2 4
lw $a2 0($a2)
sw $a2 268502044($0)
move $a2 $k0
addiu $a2 $a2 8
lw $a2 0($a2)
sw $a2 268502048($0)
move $a2 $k0
addiu $a2 $a2 12
lw $a2 0($a2)
sw $a2 268502052($0)
jal returnadd
move $t0 $k0
addiu $t0 $t0 16
lw $t1 268502012($0)
sw $t1 0($t0)
move $a0 $k0
addiu $a0 $a0 16
lw $a0 0($a0)
li $v0 1
syscall
# com printf T11
li $a0 10
li $v0 11
syscall
la $a0 String45
li $v0 4
syscall
move $t0 $k0
addiu $t0 $t0 20
li $t1 97
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 24
li $t1 98
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 28
li $t1 99
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 32
li $t1 52
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 36
li $t1 101
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 40
li $t1 43
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 44
li $t1 45
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 48
li $t1 42
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 52
li $t1 47
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 56
li $t1 95
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 20
lw $a2 0($a2)
sw $a2 268502016($0)
move $a2 $k0
addiu $a2 $a2 24
lw $a2 0($a2)
sw $a2 268502020($0)
move $a2 $k0
addiu $a2 $a2 28
lw $a2 0($a2)
sw $a2 268502024($0)
move $a2 $k0
addiu $a2 $a2 32
lw $a2 0($a2)
sw $a2 268502028($0)
move $a2 $k0
addiu $a2 $a2 36
lw $a2 0($a2)
sw $a2 268502032($0)
move $a2 $k0
addiu $a2 $a2 40
lw $a2 0($a2)
sw $a2 268502036($0)
move $a2 $k0
addiu $a2 $a2 44
lw $a2 0($a2)
sw $a2 268502040($0)
move $a2 $k0
addiu $a2 $a2 48
lw $a2 0($a2)
sw $a2 268502044($0)
move $a2 $k0
addiu $a2 $a2 52
lw $a2 0($a2)
sw $a2 268502048($0)
move $a2 $k0
addiu $a2 $a2 56
lw $a2 0($a2)
sw $a2 268502052($0)
jal returnmix
move $t0 $k0
addiu $t0 $t0 60
lw $t1 268502012($0)
sw $t1 0($t0)
move $a0 $k0
addiu $a0 $a0 60
lw $a0 0($a0)
li $v0 1
syscall
# com printf T22
li $a0 10
li $v0 11
syscall
addiu $t0 $fp 100
li $t1 0
sw $t1 0($t0)
la $a0 String46
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
Label70:
move $t0 $k0
addiu $t0 $t0 64
li $t1 10
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 68
addiu $t1 $fp 100
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 64
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 68
lw $a1 0($a1)
bgez $a1 Label71
move $t0 $k0
addiu $t0 $t0 72
li $t1 268502372
addiu $t2 $fp 100
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
move $a0 $k0
addiu $a0 $a0 72
lw $a0 0($a0)
li $v0 11
syscall
# com printf T25
li $a0 10
li $v0 11
syscall
move $t0 $k0
addiu $t0 $t0 76
addiu $t1 $fp 100
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 100
move $t1 $k0
addiu $t1 $t1 76
lw $t1 0($t1)
sw $t1 0($t0)
j Label70
Label71:
la $a0 String47
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
la $a0 String48
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
la $a0 String49
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
la $a0 String50
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
la $a0 String51
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
la $a0 String52
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
li $v0 5
syscall
addiu $a3 $fp 8
sw $v0 0($a3)
move $t0 $k0
addiu $t0 $t0 80
li $t1 0
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 84
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 80
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 84
lw $a1 0($a1)
bne $a1 $0 Label72
la $a0 String53
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
li $v0 10
syscall
j Label73
Label72:
move $t0 $k0
addiu $t0 $t0 88
li $t1 1
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 92
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 88
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 92
lw $a1 0($a1)
bne $a1 $0 Label74
la $a0 String54
li $v0 4
syscall
li $a0 2
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
li $v0 10
syscall
j Label75
Label74:
move $t0 $k0
addiu $t0 $t0 96
li $t1 2
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 100
addiu $t1 $fp 8
lw $t1 0($t1)
move $t2 $k0
addiu $t2 $t2 96
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
move $a1 $k0
addiu $a1 $a1 100
lw $a1 0($a1)
bne $a1 $0 Label76
la $a0 String55
li $v0 4
syscall
li $a0 4
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
li $v0 10
syscall
j Label77
Label76:
la $a0 String56
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
Label77:
Label75:
Label73:
jal complexexpression
la $a0 String57
li $v0 4
syscall
li $a0 4578
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
la $a0 String58
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
li $v0 5
syscall
addiu $a3 $fp 104
sw $v0 0($a3)
li $v0 5
syscall
addiu $a3 $fp 108
sw $v0 0($a3)
li $v0 5
syscall
addiu $a3 $fp 112
sw $v0 0($a3)
la $a0 String1
li $v0 4
syscall
addiu $a0 $fp 104
lw $a0 0($a0)
li $v0 1
syscall
# com printf G107int1
li $a0 10
li $v0 11
syscall
la $a0 String2
li $v0 4
syscall
addiu $a0 $fp 108
lw $a0 0($a0)
li $v0 1
syscall
# com printf G108int2
li $a0 10
li $v0 11
syscall
la $a0 String3
li $v0 4
syscall
addiu $a0 $fp 112
lw $a0 0($a0)
li $v0 1
syscall
# com printf G109int3
li $a0 10
li $v0 11
syscall
li $v0 12
syscall
addiu $a3 $fp 116
sw $v0 0($a3)
li $v0 12
syscall
addiu $a3 $fp 120
sw $v0 0($a3)
li $v0 12
syscall
addiu $a3 $fp 124
sw $v0 0($a3)
la $a0 String5
li $v0 4
syscall
addiu $a0 $fp 116
lw $a0 0($a0)
li $v0 11
syscall
# com printf G110char1
li $a0 10
li $v0 11
syscall
la $a0 String6
li $v0 4
syscall
addiu $a0 $fp 120
lw $a0 0($a0)
li $v0 11
syscall
# com printf G111char2
li $a0 10
li $v0 11
syscall
la $a0 String7
li $v0 4
syscall
addiu $a0 $fp 124
lw $a0 0($a0)
li $v0 11
syscall
# com printf G112char3
li $a0 10
li $v0 11
syscall
li $v0 5
syscall
addiu $a3 $fp 104
sw $v0 0($a3)
li $v0 12
syscall
addiu $a3 $fp 116
sw $v0 0($a3)
li $v0 5
syscall
addiu $a3 $fp 108
sw $v0 0($a3)
li $v0 12
syscall
addiu $a3 $fp 120
sw $v0 0($a3)
li $v0 5
syscall
addiu $a3 $fp 112
sw $v0 0($a3)
li $v0 12
syscall
addiu $a3 $fp 124
sw $v0 0($a3)
la $a0 String1
li $v0 4
syscall
addiu $a0 $fp 104
lw $a0 0($a0)
li $v0 1
syscall
# com printf G107int1
li $a0 10
li $v0 11
syscall
la $a0 String2
li $v0 4
syscall
addiu $a0 $fp 108
lw $a0 0($a0)
li $v0 1
syscall
# com printf G108int2
li $a0 10
li $v0 11
syscall
la $a0 String3
li $v0 4
syscall
addiu $a0 $fp 112
lw $a0 0($a0)
li $v0 1
syscall
# com printf G109int3
li $a0 10
li $v0 11
syscall
la $a0 String5
li $v0 4
syscall
addiu $a0 $fp 116
lw $a0 0($a0)
li $v0 11
syscall
# com printf G110char1
li $a0 10
li $v0 11
syscall
la $a0 String6
li $v0 4
syscall
addiu $a0 $fp 120
lw $a0 0($a0)
li $v0 11
syscall
# com printf G111char2
li $a0 10
li $v0 11
syscall
la $a0 String7
li $v0 4
syscall
addiu $a0 $fp 124
lw $a0 0($a0)
li $v0 11
syscall
# com printf G112char3
li $a0 10
li $v0 11
syscall
la $a0 String59
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
la $a0 String60
li $v0 4
syscall
jal return100
move $t0 $k0
addiu $t0 $t0 104
lw $t1 268502012($0)
sw $t1 0($t0)
move $a0 $k0
addiu $a0 $a0 104
lw $a0 0($a0)
li $v0 11
syscall
# com printf T33
li $a0 10
li $v0 11
syscall
la $a0 String61
li $v0 4
syscall
move $t0 $k0
addiu $t0 $t0 108
li $t1 1
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 112
li $t1 268502248
move $t2 $k0
addiu $t2 $t2 108
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
move $a0 $k0
addiu $a0 $a0 112
lw $a0 0($a0)
li $v0 11
syscall
# com printf T35
li $a0 10
li $v0 11
syscall
la $a0 String11
li $v0 4
syscall
li $a0 268502244
lw $a0 0($a0)
li $v0 11
syscall
# com printf G13gch1
li $a0 10
li $v0 11
syscall
la $a0 String62
li $v0 4
syscall
li $a0 121
li $v0 11
syscall
li $a0 10
li $v0 11
syscall
la $a0 String63
li $v0 4
syscall
li $a0 97
li $v0 11
syscall
li $a0 10
li $v0 11
syscall
la $a0 String64
li $v0 4
syscall
move $t0 $k0
addiu $t0 $t0 116
li $t1 3
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 116
lw $a2 0($a2)
sw $a2 268502016($0)
jal calculatefactorial
move $t0 $k0
addiu $t0 $t0 120
lw $t1 268502012($0)
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 120
lw $a2 0($a2)
sw $a2 268502016($0)
jal fibonaci
move $t0 $k0
addiu $t0 $t0 124
lw $t1 268502012($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 128
li $t1 2333
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 132
li $t1 6763
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 128
lw $a2 0($a2)
sw $a2 268502016($0)
move $a2 $k0
addiu $a2 $a2 132
lw $a2 0($a2)
sw $a2 268502020($0)
jal _multi_layer
move $t0 $k0
addiu $t0 $t0 136
lw $t1 268502012($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 140
li $t1 7
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 140
lw $a2 0($a2)
sw $a2 268502016($0)
jal calculatefactorial
move $t0 $k0
addiu $t0 $t0 144
lw $t1 268502012($0)
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 136
lw $a2 0($a2)
sw $a2 268502016($0)
move $a2 $k0
addiu $a2 $a2 144
lw $a2 0($a2)
sw $a2 268502020($0)
jal _multi_layer
move $t0 $k0
addiu $t0 $t0 148
lw $t1 268502012($0)
sw $t1 0($t0)
move $t0 $k0
addiu $t0 $t0 152
li $t1 8
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 152
lw $a2 0($a2)
sw $a2 268502016($0)
jal fibonaci
move $t0 $k0
addiu $t0 $t0 156
lw $t1 268502012($0)
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 148
lw $a2 0($a2)
sw $a2 268502016($0)
move $a2 $k0
addiu $a2 $a2 156
lw $a2 0($a2)
sw $a2 268502020($0)
jal _multi_layer
move $t0 $k0
addiu $t0 $t0 160
lw $t1 268502012($0)
sw $t1 0($t0)
move $a2 $k0
addiu $a2 $a2 124
lw $a2 0($a2)
sw $a2 268502016($0)
move $a2 $k0
addiu $a2 $a2 160
lw $a2 0($a2)
sw $a2 268502020($0)
jal _multi_layer
move $t0 $k0
addiu $t0 $t0 164
lw $t1 268502012($0)
sw $t1 0($t0)
move $a0 $k0
addiu $a0 $a0 164
lw $a0 0($a0)
li $v0 1
syscall
# com printf T48
li $a0 10
li $v0 11
syscall
jal complexif_else
jal complexwhile
jal complexswitch_case
la $a0 String65
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
li $v0 10
syscall
#accomplish generate mips code.
