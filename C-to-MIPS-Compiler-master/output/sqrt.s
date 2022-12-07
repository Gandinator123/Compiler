.globl bsqrt
bsqrt:
addiu $sp,$sp,-84
sw $fp,80($sp)
sw $31,80($sp)
sw $fp,76($sp)
move $fp,$sp
sw $4,84($fp)
sw $5,88($fp)
sw $6,92($fp)
nop
b $L2
nop
$L2:
lw $9,84($fp)
nop 
lw $10,88($fp)
nop 
lw $10,88($fp)
nop 
addu $8,$9,$10
li $9,1
li $9,1
srlv $2,$8,$9
sw $2,8($fp)
lw $8,8($fp)
nop 
lw $9,8($fp)
nop 
lw $9,8($fp)
nop 
mult $8,$9
nop
mflo $2
nop
sw $2,12($fp)
lw $8,12($fp)
nop 
lw $9,92($fp)
nop 
lw $9,92($fp)
nop 
slt $2,$9,$8
xori $2,$2,0x1
andi $2,$2,0x00ff
beq $2,$0,$L3
nop
lw $2,8($fp)
nop 
sw $2,84($fp)
$L3:
lw $2,8($fp)
nop 
sw $2,88($fp)
$L1:
lw $9,84($fp)
nop 
li $10,1
li $10,1
addu $8,$9,$10
lw $9,88($fp)
nop 
lw $9,88($fp)
nop 
lw $10,84($fp)
nop 
li $11,1
li $11,1
addu $8,$10,$11
lw $9,88($fp)
nop 
slt $2,$8,$9
andi $2,$2,0x00ff
bne $2,$0,$L2
nop
lw $9,84($fp)
nop 
lw $10,84($fp)
nop 
lw $10,84($fp)
nop 
mult $9,$10
nop
mflo $8
nop
lw $9,92($fp)
nop 
lw $9,92($fp)
nop 
lw $10,84($fp)
nop 
lw $11,84($fp)
nop 
lw $11,84($fp)
nop 
mult $10,$11
nop
mflo $8
nop
lw $9,92($fp)
nop 
slt $2,$8,$9
andi $2,$2,0x00ff
beq $2,$0,$L4
nop
lw $2,88($fp)
nop 
b $L0
nop
$L4:
lw $2,84($fp)
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

