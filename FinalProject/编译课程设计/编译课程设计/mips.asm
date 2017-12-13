.data
	String1:.asciiz "g_var_int1:"
	String2:.asciiz "g_var_int2:"
	String3:.asciiz "g_var_char1:"
	String4:.asciiz "g_var_char2:"
	String5:.asciiz "------------------------"
	String6:.asciiz "g_var_int_arr:"
	String7:.asciiz "g_var_char_arr:"
	String8:.asciiz "Hello World."
	String9:.asciiz "Welcome to BUAA."
	String10:.asciiz "Excuse Me."
	String11:.asciiz "Sally Go1."
	String12:.asciiz "Sally Go2."
	String13:.asciiz "mmppppooodd"
	String14:.asciiz "Lala"
	String15:.asciiz "DiDi"
	String16:.asciiz "BoBo"
	String17:.asciiz "CoCo"
	String18:.asciiz "smaller than n"
	String19:.asciiz "not smaller than n"
	String20:.asciiz "smaller than n or equal to n"
	String21:.asciiz "bigger than n"
	String22:.asciiz "equal to n"
	String23:.asciiz "not equal to n"
	String24:.asciiz "bigger than n or equal to n"
	String25:.asciiz "smaller than n"
	String26:.asciiz "bigger than n"
	String27:.asciiz "not bigger than n"
	String28:.asciiz "not equal to n"
	String29:.asciiz "equal to n"
	String30:.asciiz "------------------------"
	String31:.asciiz "Fib(1):"
	String32:.asciiz "Fib(2):"
	String33:.asciiz "Fib(8):"
	String34:.asciiz "Please enter the number of items you want to calculate the Fibonacci sequence:"
	String35:.asciiz "the Fib number you want to get is:"
	String36:.asciiz "lalalalala."
	String37:.asciiz "sum is:"
	String38:.asciiz "procedure is Over, Thank you."
.globl main
.text
fibnaci:
sw $fp 4($sp)
move $fp $sp
sw $ra 0($fp)
addiu $sp $fp 12
lw $v1 268501616($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 0
sw $sp 8($fp)
addiu $sp $sp 28
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
bgtz $a1 Label1
li $v0 1
sw $v0 268501612($0)
move $sp $fp
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
j Label2
Label1:
lw $t0 8($fp)
addiu $t0 $t0 8
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a2 8($fp)
addiu $a2 $a2 8
lw $a2 0($a2)
sw $a2 268501616($0)
jal fibnaci
lw $t0 8($fp)
addiu $t0 $t0 12
lw $t1 268501612($0)
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 16
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 2
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a2 8($fp)
addiu $a2 $a2 16
lw $a2 0($a2)
sw $a2 268501616($0)
jal fibnaci
lw $t0 8($fp)
addiu $t0 $t0 20
lw $t1 268501612($0)
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 24
lw $t1 8($fp)
addiu $t1 $t1 12
lw $t1 0($t1)
lw $t2 8($fp)
addiu $t2 $t2 20
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
lw $v0 8($fp)
addiu $v0 $v0 24
lw $v0 0($v0)
sw $v0 268501612($0)
move $sp $fp
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
Label2:
move $sp $fp
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
printglobalvarvalue:
sw $fp 4($sp)
move $fp $sp
sw $ra 0($fp)
addiu $sp $fp 12
addiu $sp $sp 0
sw $sp 8($fp)
la $a0 String1
li $v0 4
syscall
li $a3 268501716
lw $a0 0($a3)
li $v0 1
syscall
# com printf G4g_var_int1
li $a0 10
li $v0 11
syscall
la $a0 String2
li $v0 4
syscall
li $a3 268501720
lw $a0 0($a3)
li $v0 1
syscall
# com printf G5g_var_int2
li $a0 10
li $v0 11
syscall
la $a0 String3
li $v0 4
syscall
li $a3 268501772
lw $a0 0($a3)
li $v0 11
syscall
# com printf G7g_var_char1
li $a0 10
li $v0 11
syscall
la $a0 String4
li $v0 4
syscall
li $a3 268501776
lw $a0 0($a3)
li $v0 11
syscall
# com printf G8g_var_char2
li $a0 10
li $v0 11
syscall
la $a0 String5
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
move $sp $fp
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
printglobalarrvalue:
sw $fp 4($sp)
move $fp $sp
sw $ra 0($fp)
addiu $sp $fp 12
lw $v1 268501616($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 4
sw $sp 8($fp)
addiu $sp $sp 24
addiu $t0 $fp 16
li $t1 0
sw $t1 0($t0)
la $a0 String6
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
Label3:
lw $t0 8($fp)
addiu $t0 $t0 0
addiu $t1 $fp 16
lw $t1 0($t1)
addiu $t2 $fp 12
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 0
lw $a1 0($a1)
bgez $a1 Label4
lw $t0 8($fp)
addiu $t0 $t0 4
li $t1 268501724
addiu $t2 $fp 16
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
lw $a3 8($fp)
addiu $a3 $a3 4
lw $a0 0($a3)
li $v0 1
syscall
# com printf T2
li $a0 10
li $v0 11
syscall
lw $t0 8($fp)
addiu $t0 $t0 8
addiu $t1 $fp 16
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 16
lw $t1 8($fp)
addiu $t1 $t1 8
lw $t1 0($t1)
sw $t1 0($t0)
j Label3
Label4:
addiu $t0 $fp 16
li $t1 0
sw $t1 0($t0)
la $a0 String7
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
Label5:
lw $t0 8($fp)
addiu $t0 $t0 12
addiu $t1 $fp 16
lw $t1 0($t1)
addiu $t2 $fp 12
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 12
lw $a1 0($a1)
bgez $a1 Label6
lw $t0 8($fp)
addiu $t0 $t0 16
li $t1 268501780
addiu $t2 $fp 16
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
lw $a3 8($fp)
addiu $a3 $a3 16
lw $a0 0($a3)
li $v0 11
syscall
# com printf T5
li $a0 10
li $v0 11
syscall
lw $t0 8($fp)
addiu $t0 $t0 20
addiu $t1 $fp 16
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 16
lw $t1 8($fp)
addiu $t1 $t1 20
lw $t1 0($t1)
sw $t1 0($t0)
j Label5
Label6:
move $sp $fp
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
move $sp $fp
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
testswitchcase:
sw $fp 4($sp)
move $fp $sp
sw $ra 0($fp)
addiu $sp $fp 12
lw $v1 268501616($0)
sw $v1 0($sp)
addiu $sp $sp 4
lw $v1 268501620($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 0
sw $sp 8($fp)
addiu $sp $sp 48
lw $t0 8($fp)
addiu $t0 $t0 4
addiu $t1 $fp 12
lw $t1 0($t1)
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 4
lw $a1 0($a1)
beq $a1 $0 Label8
lw $t0 8($fp)
addiu $t0 $t0 8
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 8
lw $a1 0($a1)
beq $a1 $0 Label9
j Label7
Label8:
la $a0 String8
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
jal printglobalvarvalue
j Label7
Label9:
la $a0 String9
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
lw $t0 8($fp)
addiu $t0 $t0 0
li $t1 3
sw $t1 0($t0)
lw $a2 8($fp)
addiu $a2 $a2 0
lw $a2 0($a2)
sw $a2 268501616($0)
jal printglobalarrvalue
j Label7
Label7:
lw $t0 8($fp)
addiu $t0 $t0 12
addiu $t1 $fp 16
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 12
lw $a1 0($a1)
beq $a1 $0 Label12
lw $t0 8($fp)
addiu $t0 $t0 16
addiu $t1 $fp 16
lw $t1 0($t1)
li $t2 2
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 16
lw $a1 0($a1)
beq $a1 $0 Label13
la $a0 String10
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label11
Label12:
la $a0 String11
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label11
Label13:
la $a0 String12
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label11
Label11:
lw $t0 8($fp)
addiu $t0 $t0 20
addiu $t1 $fp 16
lw $t1 0($t1)
addiu $t2 $fp 12
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 40
lw $t1 8($fp)
addiu $t1 $t1 20
lw $t1 0($t1)
li $t2 3
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 40
lw $a1 0($a1)
beq $a1 $0 Label16
lw $t0 8($fp)
addiu $t0 $t0 44
lw $t1 8($fp)
addiu $t1 $t1 20
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 44
lw $a1 0($a1)
beq $a1 $0 Label21
li $a0 0
li $v0 11
syscall
li $a0 10
li $v0 11
syscall
j Label15
Label16:
lw $t0 8($fp)
addiu $t0 $t0 24
addiu $t1 $fp 12
lw $t1 0($t1)
addiu $t2 $fp 16
lw $t2 0($t2)
mult $t1 $t2
mflo $t1
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 28
lw $t1 8($fp)
addiu $t1 $t1 24
lw $t1 0($t1)
li $t2 3
addu $t1 $t1 $t2
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 32
lw $t1 8($fp)
addiu $t1 $t1 28
lw $t1 0($t1)
li $t2 5
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 32
lw $a1 0($a1)
beq $a1 $0 Label18
lw $t0 8($fp)
addiu $t0 $t0 36
lw $t1 8($fp)
addiu $t1 $t1 28
lw $t1 0($t1)
li $t2 -15
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 36
lw $a1 0($a1)
beq $a1 $0 Label19
la $a0 String13
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label17
Label18:
la $a0 String14
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
la $a0 String15
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label17
Label19:
la $a0 String16
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
la $a0 String17
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label17
Label17:
j Label15
Label21:
jal printglobalvarvalue
j Label15
Label15:
move $sp $fp
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
returnten:
sw $fp 4($sp)
move $fp $sp
sw $ra 0($fp)
addiu $sp $fp 12
lw $v1 268501616($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 0
sw $sp 8($fp)
li $v0 10
sw $v0 268501612($0)
move $sp $fp
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
move $sp $fp
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
returntwo:
sw $fp 4($sp)
move $fp $sp
sw $ra 0($fp)
addiu $sp $fp 12
lw $v1 268501616($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 0
sw $sp 8($fp)
li $v0 2
sw $v0 268501612($0)
move $sp $fp
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
move $sp $fp
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
testifelse:
sw $fp 4($sp)
move $fp $sp
sw $ra 0($fp)
addiu $sp $fp 12
lw $v1 268501616($0)
sw $v1 0($sp)
addiu $sp $sp 4
addiu $sp $sp 0
sw $sp 8($fp)
addiu $sp $sp 48
lw $t0 8($fp)
addiu $t0 $t0 0
li $t1 110
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
bgez $a1 Label23
la $a0 String18
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label24
Label23:
la $a0 String19
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
Label24:
lw $t0 8($fp)
addiu $t0 $t0 8
li $t1 110
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
bgtz $a1 Label25
la $a0 String20
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label26
Label25:
la $a0 String21
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
Label26:
lw $t0 8($fp)
addiu $t0 $t0 16
li $t1 110
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 20
addiu $t1 $fp 12
lw $t1 0($t1)
lw $t2 8($fp)
addiu $t2 $t2 16
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 20
lw $a1 0($a1)
bne $a1 $0 Label27
la $a0 String22
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label28
Label27:
la $a0 String23
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
Label28:
lw $t0 8($fp)
addiu $t0 $t0 24
li $t1 110
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 28
addiu $t1 $fp 12
lw $t1 0($t1)
lw $t2 8($fp)
addiu $t2 $t2 24
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 28
lw $a1 0($a1)
bltz $a1 Label29
la $a0 String24
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label30
Label29:
la $a0 String18
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
Label30:
lw $t0 8($fp)
addiu $t0 $t0 32
li $t1 110
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 36
addiu $t1 $fp 12
lw $t1 0($t1)
lw $t2 8($fp)
addiu $t2 $t2 32
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 36
lw $a1 0($a1)
blez $a1 Label31
la $a0 String21
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label32
Label31:
la $a0 String27
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
Label32:
lw $t0 8($fp)
addiu $t0 $t0 40
li $t1 110
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 44
addiu $t1 $fp 12
lw $t1 0($t1)
lw $t2 8($fp)
addiu $t2 $t2 40
lw $t2 0($t2)
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a1 8($fp)
addiu $a1 $a1 44
lw $a1 0($a1)
beq $a1 $0 Label33
la $a0 String23
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
j Label34
Label33:
la $a0 String22
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
Label34:
la $a0 String5
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
move $sp $fp
lw $ra 0($fp)
lw $fp 4($fp)
jr $ra
main:
li $fp 268501828
addiu $sp $fp 12
addiu $sp $sp 36
sw $sp 8($fp)
addiu $sp $sp 156
li $t0 268501716
li $t1 47
sw $t1 0($t0)
li $t0 268501720
li $t1 1
sw $t1 0($t0)
li $t0 268501772
li $t1 97
sw $t1 0($t0)
li $t0 268501776
li $t1 109
sw $t1 0($t0)
jal printglobalvarvalue
li $t0 268501716
li $t1 46
sw $t1 0($t0)
li $t0 268501720
li $t1 8
sw $t1 0($t0)
jal printglobalvarvalue
addiu $t0 $fp 12
li $t1 0
sw $t1 0($t0)
Label35:
lw $t0 8($fp)
addiu $t0 $t0 0
li $t1 11
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
bgtz $a1 Label36
li $t0 268501724
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
addiu $t1 $fp 12
lw $t1 0($t1)
sw $t1 0($t0)
li $t0 268501780
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 4
mult $t1 $t2
mflo $t1
addu $t0 $t0 $t1
li $t1 120
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 8
addiu $t1 $fp 12
lw $t1 0($t1)
li $t2 1
addu $t1 $t1 $t2
sw $t1 0($t0)
addiu $t0 $fp 12
lw $t1 8($fp)
addiu $t1 $t1 8
lw $t1 0($t1)
sw $t1 0($t0)
j Label35
Label36:
lw $t0 8($fp)
addiu $t0 $t0 12
li $t1 0
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 16
li $t1 268501724
lw $t2 8($fp)
addiu $t2 $t2 12
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 20
lw $t1 8($fp)
addiu $t1 $t1 16
lw $t1 0($t1)
li $t2 3
addu $t1 $t1 $t2
sw $t1 0($t0)
li $t0 268501724
li $t1 3
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
li $t1 12
sw $t1 0($t0)
lw $a2 8($fp)
addiu $a2 $a2 24
lw $a2 0($a2)
sw $a2 268501616($0)
jal printglobalarrvalue
addiu $t0 $fp 16
li $t1 1
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 28
li $t1 2
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 32
li $t1 268501724
lw $t2 8($fp)
addiu $t2 $t2 28
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
addiu $t0 $fp 20
lw $t1 8($fp)
addiu $t1 $t1 32
lw $t1 0($t1)
sw $t1 0($t0)
addiu $a2 $fp 16
lw $a2 0($a2)
sw $a2 268501616($0)
addiu $a2 $fp 20
lw $a2 0($a2)
sw $a2 268501620($0)
jal testswitchcase
lw $t0 8($fp)
addiu $t0 $t0 36
addiu $t1 $fp 16
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 40
addiu $t1 $fp 20
lw $t1 0($t1)
li $t2 1
subu $t1 $t1 $t2
sw $t1 0($t0)
lw $a2 8($fp)
addiu $a2 $a2 36
lw $a2 0($a2)
sw $a2 268501616($0)
lw $a2 8($fp)
addiu $a2 $a2 40
lw $a2 0($a2)
sw $a2 268501620($0)
jal testswitchcase
lw $t0 8($fp)
addiu $t0 $t0 44
li $t1 -3
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 48
addiu $t1 $fp 20
lw $t1 0($t1)
li $t2 4
addu $t1 $t1 $t2
sw $t1 0($t0)
lw $a2 8($fp)
addiu $a2 $a2 44
lw $a2 0($a2)
sw $a2 268501616($0)
lw $a2 8($fp)
addiu $a2 $a2 48
lw $a2 0($a2)
sw $a2 268501620($0)
jal testswitchcase
lw $t0 8($fp)
addiu $t0 $t0 52
li $t1 -2
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 56
addiu $t1 $fp 20
lw $t1 0($t1)
li $t2 3
addu $t1 $t1 $t2
sw $t1 0($t0)
lw $a2 8($fp)
addiu $a2 $a2 52
lw $a2 0($a2)
sw $a2 268501616($0)
lw $a2 8($fp)
addiu $a2 $a2 56
lw $a2 0($a2)
sw $a2 268501620($0)
jal testswitchcase
lw $t0 8($fp)
addiu $t0 $t0 60
li $t1 111
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 64
li $t1 222
sw $t1 0($t0)
lw $a2 8($fp)
addiu $a2 $a2 60
lw $a2 0($a2)
sw $a2 268501616($0)
lw $a2 8($fp)
addiu $a2 $a2 64
lw $a2 0($a2)
sw $a2 268501620($0)
jal testswitchcase
lw $t0 8($fp)
addiu $t0 $t0 68
li $t1 1
sw $t1 0($t0)
lw $a2 8($fp)
addiu $a2 $a2 68
lw $a2 0($a2)
sw $a2 268501616($0)
jal fibnaci
lw $t0 8($fp)
addiu $t0 $t0 72
lw $t1 268501612($0)
sw $t1 0($t0)
addiu $t0 $fp 24
lw $t1 8($fp)
addiu $t1 $t1 72
lw $t1 0($t1)
sw $t1 0($t0)
la $a0 String31
li $v0 4
syscall
addiu $a3 $fp 24
lw $a0 0($a3)
li $v0 1
syscall
# com printf G29myfib
li $a0 10
li $v0 11
syscall
lw $t0 8($fp)
addiu $t0 $t0 76
li $t1 2
sw $t1 0($t0)
lw $a2 8($fp)
addiu $a2 $a2 76
lw $a2 0($a2)
sw $a2 268501616($0)
jal fibnaci
lw $t0 8($fp)
addiu $t0 $t0 80
lw $t1 268501612($0)
sw $t1 0($t0)
addiu $t0 $fp 24
lw $t1 8($fp)
addiu $t1 $t1 80
lw $t1 0($t1)
sw $t1 0($t0)
la $a0 String32
li $v0 4
syscall
addiu $a3 $fp 24
lw $a0 0($a3)
li $v0 1
syscall
# com printf G29myfib
li $a0 10
li $v0 11
syscall
lw $t0 8($fp)
addiu $t0 $t0 84
li $t1 8
sw $t1 0($t0)
lw $a2 8($fp)
addiu $a2 $a2 84
lw $a2 0($a2)
sw $a2 268501616($0)
jal fibnaci
lw $t0 8($fp)
addiu $t0 $t0 88
lw $t1 268501612($0)
sw $t1 0($t0)
addiu $t0 $fp 24
lw $t1 8($fp)
addiu $t1 $t1 88
lw $t1 0($t1)
sw $t1 0($t0)
la $a0 String33
li $v0 4
syscall
addiu $a3 $fp 24
lw $a0 0($a3)
li $v0 1
syscall
# com printf G29myfib
li $a0 10
li $v0 11
syscall
lw $t0 8($fp)
addiu $t0 $t0 92
li $t1 4
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 96
li $t1 268501724
lw $t2 8($fp)
addiu $t2 $t2 92
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 100
li $t1 388
lw $t2 8($fp)
addiu $t2 $t2 96
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 104
li $t1 1
sw $t1 0($t0)
lw $a2 8($fp)
addiu $a2 $a2 104
lw $a2 0($a2)
sw $a2 268501616($0)
jal returntwo
lw $t0 8($fp)
addiu $t0 $t0 108
lw $t1 268501612($0)
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 112
lw $t1 8($fp)
addiu $t1 $t1 100
lw $t1 0($t1)
lw $t2 8($fp)
addiu $t2 $t2 108
lw $t2 0($t2)
div $t1 $t2
mflo $t1
sw $t1 0($t0)
li $t0 268501716
lw $t1 8($fp)
addiu $t1 $t1 112
lw $t1 0($t1)
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 116
li $t1 2
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 120
li $t1 268501724
lw $t2 8($fp)
addiu $t2 $t2 116
lw $t2 0($t2)
li $t3 4
mult $t2 $t3
mflo $t2
addu $t1 $t1 $t2
lw $t1 0($t1)
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 124
li $t1 666
lw $t2 8($fp)
addiu $t2 $t2 120
lw $t2 0($t2)
div $t1 $t2
mflo $t1
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 128
li $t1 2
sw $t1 0($t0)
lw $a2 8($fp)
addiu $a2 $a2 128
lw $a2 0($a2)
sw $a2 268501616($0)
jal returnten
lw $t0 8($fp)
addiu $t0 $t0 132
lw $t1 268501612($0)
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 136
lw $t1 8($fp)
addiu $t1 $t1 124
lw $t1 0($t1)
li $t2 111
div $t1 $t2
mflo $t1
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 140
lw $t1 8($fp)
addiu $t1 $t1 136
lw $t1 0($t1)
lw $t2 8($fp)
addiu $t2 $t2 132
lw $t2 0($t2)
mult $t1 $t2
mflo $t1
sw $t1 0($t0)
li $t0 268501720
lw $t1 8($fp)
addiu $t1 $t1 140
lw $t1 0($t1)
sw $t1 0($t0)
jal printglobalvarvalue
addiu $t0 $fp 32
li $t1 97
sw $t1 0($t0)
addiu $a2 $fp 32
lw $a2 0($a2)
sw $a2 268501616($0)
jal testifelse
addiu $t0 $fp 32
li $t1 110
sw $t1 0($t0)
addiu $a2 $fp 32
lw $a2 0($a2)
sw $a2 268501616($0)
jal testifelse
addiu $t0 $fp 32
li $t1 115
sw $t1 0($t0)
addiu $a2 $fp 32
lw $a2 0($a2)
sw $a2 268501616($0)
jal testifelse
la $a0 String34
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
li $v0 5
syscall
addiu $a3 $fp 28
sw $v0 0($a3)
addiu $a2 $fp 28
lw $a2 0($a2)
sw $a2 268501616($0)
jal fibnaci
lw $t0 8($fp)
addiu $t0 $t0 144
lw $t1 268501612($0)
sw $t1 0($t0)
addiu $t0 $fp 24
lw $t1 8($fp)
addiu $t1 $t1 144
lw $t1 0($t1)
sw $t1 0($t0)
la $a0 String35
li $v0 4
syscall
addiu $a3 $fp 24
lw $a0 0($a3)
li $v0 1
syscall
# com printf G29myfib
li $a0 10
li $v0 11
syscall
la $a0 String36
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
li $v0 5
syscall
addiu $a3 $fp 36
sw $v0 0($a3)
li $v0 5
syscall
addiu $a3 $fp 40
sw $v0 0($a3)
li $v0 5
syscall
addiu $a3 $fp 44
sw $v0 0($a3)
la $a0 String37
li $v0 4
syscall
lw $t0 8($fp)
addiu $t0 $t0 148
addiu $t1 $fp 36
lw $t1 0($t1)
addiu $t2 $fp 40
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
lw $t0 8($fp)
addiu $t0 $t0 152
lw $t1 8($fp)
addiu $t1 $t1 148
lw $t1 0($t1)
addiu $t2 $fp 44
lw $t2 0($t2)
addu $t1 $t1 $t2
sw $t1 0($t0)
lw $a3 8($fp)
addiu $a3 $a3 152
lw $a0 0($a3)
li $v0 1
syscall
# com printf T39
li $a0 10
li $v0 11
syscall
la $a0 String38
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
li $v0 10
syscall
#accomplish generate mips code.
