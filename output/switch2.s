.globl g
g:
addiu $sp,$sp,-84
sw $fp,80($sp)
sw $31,80($sp)
sw $fp,76($sp)
move $fp,$sp
sw $4,84($fp)
nop
li $2,0
sw $2,8($fp)
lw $8,84($fp)
nop 
li $9,0
bne $9,$8,$L2
li $2,1
sw $2,8($fp)
b $L1
nop
$L2:
li $9,2
bne $9,$8,$L3
li $2,2
sw $2,8($fp)
$L3:
li $9,1
bne $9,$8,$L4
lw $9,8($fp)
nop 
li $10,1
li $10,1
addu $2,$9,$10
sw $2,8($fp)
b $L1
nop
$L4:
lw $9,84($fp)
nop 
li $10,1
li $10,1
addu $2,$9,$10
sw $2,8($fp)
$L1:
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

