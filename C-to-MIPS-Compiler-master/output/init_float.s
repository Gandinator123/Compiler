.globl f
f:
addiu $sp,$sp,-84
sw $fp,80($sp)
sw $31,80($sp)
sw $fp,76($sp)
move $fp,$sp
nop
lui $8,%hi($LC1)
lwc1 $f0,%lo($LC1)($8)
nop
swc1 $f0,8($fp)
$L0:
move $sp,$fp
lw $fp,80($sp)
lw $31,80($sp)
lw $fp,76($sp)
addiu $sp,$sp,84
j $31
nop

$LC1:
.word 1077936128
