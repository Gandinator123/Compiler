.globl f
f:
addiu $sp,$sp,-92
sw $fp,88($sp)
sw $31,88($sp)
sw $fp,84($sp)
move $fp,$sp
swc1 $f12,92($fp)
sw $5,96($fp)
nop
lui $8,%hi($LC0)
lwc1 $f0,%lo($LC0)($8)
nop
swc1 $f0,8($fp)
li $2,0
sw $2,12($fp)
b $L4
nop
$L4:
lw $2,12($fp)
nop 
addiu $2,$2,1
sw $2,12($fp)
lwc1 $f4,8($fp)
nop 
lwc1 $f6,92($fp)
nop 
mul.s $f0,$f4,$f6
swc1 $f0,8($fp)
$L3:
lw $8,12($fp)
nop 
lw $9,96($fp)
nop 
lw $9,96($fp)
nop 
lw $8,12($fp)
nop 
lw $9,96($fp)
nop 
slt $2,$8,$9
andi $2,$2,0x00ff
bne $2,$0,$L4
nop
lwc1 $f0,8($fp)
nop 
b $L2
nop
$L2:
move $sp,$fp
lw $fp,88($sp)
lw $31,88($sp)
lw $fp,84($sp)
addiu $sp,$sp,92
j $31
nop

$LC0:
.word 1065353216
