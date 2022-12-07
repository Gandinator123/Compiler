.globl multiply
multiply:
addiu $sp,$sp,-84
sw $fp,80($sp)
sw $31,80($sp)
sw $fp,76($sp)
move $fp,$sp
sw $4,84($fp)
sw $5,88($fp)
nop
li $2,0
sw $2,8($fp)
lw $8,84($fp)
nop 
li $9,0
li $9,0
lw $8,84($fp)
nop 
li $9,0
slt $2,$8,$9
andi $2,$2,0x00ff
beq $2,$0,$L1
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
lw $4,84($fp)
nop 
subu $4,$0,$4
nop
lw $5,88($fp)
nop 
nop
jal multiply
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
subu $2,$0,$2
b $L0
nop
$L1:
b $L3
nop
$L3:
lw $8,8($fp)
nop 
lw $9,88($fp)
nop 
lw $9,88($fp)
nop 
addu $2,$8,$9
sw $2,8($fp)
lw $2,84($fp)
nop 
addiu $2,$2,-1
sw $2,84($fp)
$L2:
lw $8,84($fp)
nop 
li $9,0
li $9,0
lw $8,84($fp)
nop 
li $9,0
slt $2,$9,$8
andi $2,$2,0x00ff
bne $2,$0,$L3
nop
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

