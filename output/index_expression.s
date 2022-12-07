.globl f
f:
addiu $sp,$sp,-124
sw $fp,120($sp)
sw $31,120($sp)
sw $fp,116($sp)
move $fp,$sp
nop
li $2,8
sw $2,8($fp)
b $L1
nop
$L2:
nop
nop
lw $10,8($fp)
nop 
li $11,8
li $11,8
subu $8,$10,$11
sll $8,$8,2
addiu $9,$fp,8
addu $8,$8,$9
lw $2,8($fp)
nop 
sw $2,12($8)
nop
nop
lw $8,8($fp)
nop 
addiu $8,$8,1
sw $8,8($fp)
$L1:
lw $8,8($fp)
nop 
li $9,16
li $9,16
lw $8,8($fp)
nop 
li $9,16
slt $2,$8,$9
andi $2,$2,0x00ff
bne $2,$0,$L2
nop
li $2,0
sw $2,16($fp)
li $2,0
sw $2,8($fp)
b $L3
nop
$L4:
nop
nop
lw $8,16($fp)
nop 
lw $12,8($fp)
nop 
li $13,0
li $13,0
subu $10,$12,$13
sll $10,$10,2
addiu $11,$fp,8
addu $10,$11,$10
lw $10,12($10)
nop
move $9,$10
lw $12,8($fp)
nop 
li $13,0
li $13,0
subu $10,$12,$13
sll $10,$10,2
addiu $11,$fp,8
addu $10,$11,$10
lw $10,12($10)
nop
move $9,$10
addu $2,$8,$9
sw $2,16($fp)
nop
nop
lw $8,8($fp)
nop 
addiu $8,$8,1
sw $8,8($fp)
$L3:
lw $8,8($fp)
nop 
li $9,8
li $9,8
lw $8,8($fp)
nop 
li $9,8
slt $2,$8,$9
andi $2,$2,0x00ff
bne $2,$0,$L4
nop
lw $2,16($fp)
nop 
b $L0
nop
$L0:
move $sp,$fp
lw $fp,120($sp)
lw $31,120($sp)
lw $fp,116($sp)
addiu $sp,$sp,124
j $31
nop

