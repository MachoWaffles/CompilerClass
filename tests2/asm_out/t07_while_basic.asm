.data
_str_true:  .asciiz "true"
_str_false: .asciiz "false"

.text


# Function: Master
_Master:
    addi $sp, $sp, -16
    sw   $ra, 12($sp)
    sw   $fp, 8($sp)
    move $fp, $sp

    # int i
    li $t0, 0
    sw $t0, 0($fp)

_while_start_0:
    lw $t0, 0($fp)
    li $t1, 5
    slt $t0, $t0, $t1
    beq $t0, $zero, _while_end_0
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
    j _while_start_0
_while_end_0:

    # int j
    li $t0, 10
    sw $t0, 4($fp)

_while_start_1:
    lw $t0, 4($fp)
    li $t1, 0
    slt $t0, $t1, $t0
    beq $t0, $zero, _while_end_1
    lw $t0, 4($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 4($fp)
    li $t1, 2
    sub $t0, $t0, $t1
    sw $t0, 4($fp)
    j _while_start_1
_while_end_1:


    # Epilogue
    lw   $ra, 12($sp)
    lw   $fp, 8($sp)
    addi $sp, $sp, 16
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
