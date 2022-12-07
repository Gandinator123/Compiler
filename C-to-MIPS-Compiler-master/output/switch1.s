.globl g
g:
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
bne $9,$8,$L2
li $2,10
b $L0
nop
$L2:
li $9,2
bne $9,$8,$L3
li $2,11
b $L0
nop
$L3:
$L1:
$L0:
move $sp,$fp
lw $fp,80($sp)
lw $31,80($sp)
lw $fp,76($sp)
addiu $sp,$sp,84
j $31
nop

