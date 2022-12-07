.globl fib
fib:
addiu $sp,$sp,-84
sw $fp,80($sp)
sw $31,80($sp)
sw $fp,76($sp)
move $fp,$sp
sw $4,84($fp)
nop
lw $8,84($fp)
nop 
li $9,0
li $9,0
slt $2,$9,$8
xori $2,$2,0x1
andi $2,$2,0x00ff
beq $2,$0,$L1
nop
li $2,0
b $L0
nop
$L1:
lw $8,84($fp)
nop 
li $9,1
li $9,1
lw $8,84($fp)
nop 
li $9,1
xor $2,$8,$9
sltu $2,$2,1
andi $2,$2,0x00ff
beq $2,$0,$L2
nop
li $2,1
b $L0
nop
$L2:
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
lw $8,84($fp)
nop 
li $9,1
li $9,1
subu $4,$8,$9
nop
jal fib
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
move $8,$2
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
lw $9,84($fp)
nop 
li $10,2
li $10,2
subu $4,$9,$10
nop
jal fib
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
move $9,$2
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
lw $10,84($fp)
nop 
li $11,2
li $11,2
subu $4,$10,$11
nop
jal fib
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
addu $2,$8,$9
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

