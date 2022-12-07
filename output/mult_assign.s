.globl f
f:
addiu $sp,$sp,-84
sw $fp,80($sp)
sw $31,80($sp)
sw $fp,76($sp)
move $fp,$sp
nop
li $2,5
sw $2,8($fp)
li $2,10
lw $8,8($fp)
mult $2,$8
mflo $2
sw $2,8($fp)
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

