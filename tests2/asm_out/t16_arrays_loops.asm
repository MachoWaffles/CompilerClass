.data
_str_true:  .asciiz "true"
_str_false: .asciiz "false"

.text


# Function: Master
_Master:
    addi $sp, $sp, -44
    sw   $ra, 40($sp)
    sw   $fp, 36($sp)
    move $fp, $sp

    # array int arr[5] at fp+0
    # int i
    li $t0, 0
    sw $t0, 20($fp)

_for_start_0:
    lw $t0, 20($fp)
    li $t1, 5
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_0
    lw $t0, 20($fp)
    lw $t1, 20($fp)
    mul $t0, $t0, $t1
    lw $t1, 20($fp)
    sll $t1, $t1, 2
    addi $t2, $fp, 0
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    lw $t0, 20($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($fp)
    j _for_start_0
_for_end_0:

    # int i
    li $t0, 0
    sw $t0, 20($fp)

_for_start_1:
    lw $t0, 20($fp)
    li $t1, 5
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_1
    lw $t0, 20($fp)
    sll $t0, $t0, 2
    addi $t1, $fp, 0
    add  $t1, $t1, $t0
    lw   $t1, 0($t1)
    move $a0, $t1
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 20($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($fp)
    j _for_start_1
_for_end_1:

    # int sum
    li $t0, 0
    sw $t0, 24($fp)
    # int j
    li $t0, 0
    sw $t0, 28($fp)

_while_start_2:
    lw $t0, 28($fp)
    li $t1, 5
    slt $t0, $t0, $t1
    beq $t0, $zero, _while_end_2
    lw $t0, 24($fp)
    lw $t1, 28($fp)
    sll $t1, $t1, 2
    addi $t2, $fp, 0
    add  $t2, $t2, $t1
    lw   $t2, 0($t2)
    add $t0, $t0, $t2
    sw $t0, 24($fp)
    lw $t0, 28($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 28($fp)
    j _while_start_2
_while_end_2:

    lw $t0, 24($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall

    # Epilogue
    lw   $ra, 40($sp)
    lw   $fp, 36($sp)
    addi $sp, $sp, 44
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
