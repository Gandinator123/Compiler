.globl f
f:
addiu $sp,$sp,-84
sw $fp,80($sp)
sw $31,80($sp)
sw $fp,76($sp)
move $fp,$sp
sw $4,84($fp)
sw $5,88($fp)
nop
lw $8,84($fp)
nop 
lw $9,88($fp)
nop 
lw $9,88($fp)
nop 
slt $2,$9,$8
xori $2,$2,0x1
andi $2,$2,0x00ff
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

