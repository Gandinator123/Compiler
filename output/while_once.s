.globl f
f:
addiu $sp,$sp,-84
sw $fp,80($sp)
sw $31,80($sp)
sw $fp,76($sp)
move $fp,$sp
nop
li $2,1
sw $2,8($fp)
b $L2
nop
$L2:
li $2,0
sw $2,8($fp)
$L1:
lw $2,8($fp)
nop 
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

