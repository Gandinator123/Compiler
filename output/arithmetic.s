.globl f
f:
addiu $sp,$sp,-84
sw $fp,80($sp)
sw $31,80($sp)
sw $fp,76($sp)
move $fp,$sp
sw $4,84($fp)
nop
lw $8,84($fp)
nop 
li $9,1
li $9,1
li $10,2
sll $9,$9,$10
addu $2,$8,$9
sw $2,84($fp)
lw $2,84($fp)
nop 
lw $2,0($2)
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

