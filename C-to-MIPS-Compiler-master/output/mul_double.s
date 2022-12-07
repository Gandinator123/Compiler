.globl f
f:
addiu $sp,$sp,-84
sw $fp,80($sp)
sw $31,80($sp)
sw $fp,76($sp)
move $fp,$sp
swc1 $f12,88($fp)
swc1 $f13,84($fp)
swc1 $f14,100($fp)
swc1 $f15,96($fp)
nop
lwc1 $f4,88($fp)
lwc1 $f5,84($fp)
lwc1 $f6,100($fp)
lwc1 $f7,96($fp)
mul.d $f0,$f4,$f6
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

