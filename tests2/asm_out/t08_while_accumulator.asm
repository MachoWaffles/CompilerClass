.data
_str_true:  .asciiz "true"
_str_false: .asciiz "false"

.text


# Function: Master
_Master:
    addi $sp, $sp, -24
    sw   $ra, 20($sp)
    sw   $fp, 16($sp)
    move $fp, $sp

    # int sum
    li $t0, 0
    sw $t0, 0($fp)
    # int n
    li $t0, 1
    sw $t0, 4($fp)

_while_start_0:
    lw $t0, 4($fp)
    li $t1, 10
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _while_end_0
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    add $t0, $t0, $t1
    sw $t0, 0($fp)
    lw $t0, 4($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 4($fp)
    j _while_start_0
_while_end_0:

    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int outer
    li $t0, 1
    sw $t0, 8($fp)

_while_start_1:
    lw $t0, 8($fp)
    li $t1, 2
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _while_end_1
    # int inner
    li $t0, 1
    sw $t0, 12($fp)

_while_start_2:
    lw $t0, 12($fp)
    li $t1, 3
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _while_end_2
    lw $t0, 12($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 12($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 12($fp)
    j _while_start_2
_while_end_2:

    lw $t0, 8($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 8($fp)
    j _while_start_1
_while_end_1:


    # Epilogue
    lw   $ra, 20($sp)
    lw   $fp, 16($sp)
    addi $sp, $sp, 24
    jr   $ra
# End _Master

.globl main
main:
    addi $sp, $sp, -8
    sw   $ra, 4($sp)


    jal _Master

    lw   $ra, 4($sp)
    addi $sp, $sp, 8
    li   $v0, 10
    syscall
