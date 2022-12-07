.globl f
f:
addiu $sp,$sp,-92
sw $fp,88($sp)
sw $31,88($sp)
sw $fp,84($sp)
move $fp,$sp
nop
li $2,10
sw $2,8($fp)
li $8,20
lw $9,8($fp)
nop 
lw $9,8($fp)
nop 
addu $2,$8,$9
sw $2,12($fp)
lw $2,12($fp)
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

