.globl f
f:
addiu $sp,$sp,-116
sw $fp,112($sp)
sw $31,112($sp)
sw $fp,108($sp)
move $fp,$sp
nop
li $2,0
sw $2,8($fp)
b $L1
nop
$L2:
nop
nop
lw $8,8($fp)
nop 
sll $8,$8,2
addiu $9,$fp,8
addu $8,$8,$9
lw $2,8($fp)
nop 
sw $2,8($8)
nop
nop
lw $8,8($fp)
nop 
addiu $8,$8,1
sw $8,8($fp)
$L1:
lw $8,8($fp)
nop 
li $9,8
li $9,8
lw $8,8($fp)
nop 
li $9,8
slt $2,$8,$9
andi $2,$2,0x00ff
bne $2,$0,$L2
nop
li $8,4
sll $8,$8,2
addiu $9,$fp,8
addu $8,$9,$8
lw $8,8($8)
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

