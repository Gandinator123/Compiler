.globl f
f:
addiu $sp,$sp,-84
sw $fp,80($sp)
sw $31,80($sp)
sw $fp,76($sp)
move $fp,$sp
nop
li $2,0
sw $2,8($fp)
b $L1
nop
$L2:
nop
nop
li $2,1
b $L0
nop
nop
nop
lw $9,8($fp)
nop 
li $10,1
li $10,1
addu $2,$9,$10
sw $2,8($fp)
$L1:
lw $8,8($fp)
nop 
li $9,0
li $9,0
lw $8,8($fp)
nop 
li $9,0
slt $2,$8,$9
andi $2,$2,0x00ff
bne $2,$0,$L2
nop
li $2,19937
b $L0
nop
$L0:
move $sp,$fp
lw $fp,80($sp)
lw $31,80($sp)
lw $fp,76($sp)
addiu $sp,$sp,84
j $31
nop

