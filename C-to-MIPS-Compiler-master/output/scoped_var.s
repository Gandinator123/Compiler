.globl f
f:
addiu $sp,$sp,-92
sw $fp,88($sp)
sw $31,88($sp)
sw $fp,84($sp)
move $fp,$sp
nop
li $2,5678
sw $2,8($fp)
li $2,1234
sw $2,8($fp)
lw $2,8($fp)
nop 
b $L0
nop
$L0:
move $sp,$fp
lw $fp,88($sp)
lw $31,88($sp)
lw $fp,84($sp)
addiu $sp,$sp,92
j $31
nop

