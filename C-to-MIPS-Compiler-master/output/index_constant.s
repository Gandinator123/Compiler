.globl f
f:
addiu $sp,$sp,-116
sw $fp,112($sp)
sw $31,112($sp)
sw $fp,108($sp)
move $fp,$sp
nop
li $8,0
sll $8,$8,2
addiu $9,$fp,8
addu $8,$8,$9
li $2,23
sw $2,4($8)
li $8,0
sll $8,$8,2
addiu $9,$fp,8
addu $8,$9,$8
lw $8,4($8)
nop
move $2,$8
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

