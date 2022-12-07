.globl f
f:
addiu $sp,$sp,-84
sw $fp,80($sp)
sw $31,80($sp)
sw $fp,76($sp)
move $fp,$sp
nop
sw $8,36($sp)
nop
sw $9,40($sp)
nop
sw $10,44($sp)
nop
sw $11,48($sp)
nop
sw $12,52($sp)
nop
sw $13,56($sp)
nop
sw $14,60($sp)
nop
sw $15,64($sp)
nop
sw $24,68($sp)
nop
sw $25,72($sp)
nop
lui $2,%hi(x)
nop
jal sizeof
nop
lw $8,36($sp)
nop
lw $9,40($sp)
nop
lw $10,44($sp)
nop
lw $11,48($sp)
nop
lw $12,52($sp)
nop
lw $13,56($sp)
nop
lw $14,60($sp)
nop
lw $15,64($sp)
nop
lw $24,68($sp)
nop
lw $25,72($sp)
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

