.globl f
f:
addiu $sp,$sp,-116
sw $fp,112($sp)
sw $31,112($sp)
sw $fp,108($sp)
move $fp,$sp
nop
li $2,13
sw $2,8($fp)
lw $2,8($fp)
nop 
b $L0
nop
$L0:
move $sp,$fp
lw $fp,112($sp)
lw $31,112($sp)
lw $fp,108($sp)
addiu $sp,$sp,116
j $31
nop

