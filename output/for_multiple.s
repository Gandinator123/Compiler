.globl f
f:
addiu $sp,$sp,-92
sw $fp,88($sp)
sw $31,88($sp)
sw $fp,84($sp)
move $fp,$sp
nop
li $2,0
sw $2,12($fp)
li $2,0
sw $2,8($fp)
b $L1
nop
$L2:
nop
nop
lw $8,12($fp)
nop 
li $9,1
li $9,1
subu $2,$8,$9
sw $2,12($fp)
nop
nop
lw $9,8($fp)
nop 
li $10,1
li $10,1
addu $2,$9,$10
sw $2,8($fp)
$L1:
lw $8,8($fp)
nop 
li $9,10
li $9,10
lw $8,8($fp)
nop 
li $9,10
slt $2,$8,$9
andi $2,$2,0x00ff
bne $2,$0,$L2
nop
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

