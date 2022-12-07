.globl f
f:
addiu $sp,$sp,-84
sw $fp,80($sp)
sw $31,80($sp)
sw $fp,76($sp)
move $fp,$sp
nop
li $2,20
sw $2,8($fp)
b $L2
nop
$L2:
lw $8,8($fp)
nop 
li $9,1
li $9,1
subu $2,$8,$9
sw $2,8($fp)
$L1:
lw $8,8($fp)
nop 
li $9,10
li $9,10
lw $8,8($fp)
nop 
li $9,10
slt $2,$9,$8
andi $2,$2,0x00ff
bne $2,$0,$L2
nop
lw $2,8($fp)
nop 
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

