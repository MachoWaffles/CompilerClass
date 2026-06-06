.data
_str_true:  .asciiz "true"
_str_false: .asciiz "false"

.text


# Function: Master
_Master:
    addi $sp, $sp, -32
    sw   $ra, 28($sp)
    sw   $fp, 24($sp)
    move $fp, $sp

    # int total
    li $t0, 0
    sw $t0, 0($fp)
    # int i
    li $t0, 1
    sw $t0, 4($fp)

_for_start_0:
    lw $t0, 4($fp)
    li $t1, 5
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _for_end_0
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    add $t0, $t0, $t1
    sw $t0, 0($fp)
    lw $t0, 4($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 4($fp)
    j _for_start_0
_for_end_0:

    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int i
    li $t0, 1
    sw $t0, 4($fp)

_for_start_1:
    lw $t0, 4($fp)
    li $t1, 3
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _for_end_1
    # int j
    li $t0, 1
    sw $t0, 8($fp)

_for_start_2:
    lw $t0, 8($fp)
    li $t1, 3
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _for_end_2
    # int p
    lw $t0, 4($fp)
    lw $t1, 8($fp)
    mul $t0, $t0, $t1
    sw $t0, 12($fp)
    lw $t0, 12($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 8($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 8($fp)
    j _for_start_2
_for_end_2:

    lw $t0, 4($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 4($fp)
    j _for_start_1
_for_end_1:

    # int i
    li $t0, 10
    sw $t0, 4($fp)

_for_start_3:
    lw $t0, 4($fp)
    li $t1, 5
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_3
    lw $t0, 4($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 4($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 4($fp)
    j _for_start_3
_for_end_3:

    li $t0, 99
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall

    # Epilogue
    lw   $ra, 28($sp)
    lw   $fp, 24($sp)
    addi $sp, $sp, 32
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
