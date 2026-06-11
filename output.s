.data
_str_true:  .asciiz "true"
_str_false: .asciiz "false"

.text


# Function: Master
_Master:
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $fp, 4($sp)
    move $fp, $sp

    # int x
    li $t0, 3
    sw $t0, 0($fp)
    lw $t0, 0($fp)
    li $t1, 0
    slt $t0, $t1, $t0
    beq $t0, $zero, _if_end_0

_while_start_1:
    lw $t0, 0($fp)
    li $t1, 0
    slt $t0, $t1, $t0
    beq $t0, $zero, _while_end_1
    lw $t0, 0($fp)
    li $t1, 2
    xor  $t0, $t0, $t1
    sltiu $t0, $t0, 1
    beq $t0, $zero, _if_end_2
    li $t0, 99
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    j _if_else_2
_if_end_2:

    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
_if_else_2:

    lw $t0, 0($fp)
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 0($fp)
    j _while_start_1
_while_end_1:

_if_end_0:


    # Epilogue
    lw   $ra, 8($sp)
    lw   $fp, 4($sp)
    addi $sp, $sp, 12
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
