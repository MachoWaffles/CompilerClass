.data
_str_true:  .asciiz "true"
_str_false: .asciiz "false"

.text


# Function: Master
_Master:
    addi $sp, $sp, -20
    sw   $ra, 16($sp)
    sw   $fp, 12($sp)
    move $fp, $sp

    # int i
    li $t0, 0
    sw $t0, 0($fp)

_for_start_0:
    lw $t0, 0($fp)
    li $t1, 5
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_0
    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 0($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 0($fp)
    j _for_start_0
_for_end_0:

    # int i
    li $t0, 0
    sw $t0, 0($fp)

_for_start_1:
    lw $t0, 0($fp)
    li $t1, 10
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_1
    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 0($fp)
    li $t1, 2
    add $t0, $t0, $t1
    sw $t0, 0($fp)
    j _for_start_1
_for_end_1:

    # int i
    li $t0, 5
    sw $t0, 0($fp)

_for_start_2:
    lw $t0, 0($fp)
    li $t1, 0
    slt $t0, $t0, $t1
    xori $t0, $t0, 1
    beq $t0, $zero, _for_end_2
    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 0($fp)
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 0($fp)
    j _for_start_2
_for_end_2:


    # Epilogue
    lw   $ra, 16($sp)
    lw   $fp, 12($sp)
    addi $sp, $sp, 20
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
