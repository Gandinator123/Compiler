.globl f
f:
addiu $sp,$sp,-84
sw $fp,80($sp)
sw $31,80($sp)
sw $fp,76($sp)
move $fp,$sp
swc1 $f12,84($fp)
swc1 $f14,88($fp)
sw $6,92($fp)
nop
lwc1 $f4,84($fp)
nop 
lwc1 $f8,88($fp)
nop 
lwc1 $f10,92($fp)
nop 
mul.s $f6,$f8,$f10
add.s $f0,$f4,$f6
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

