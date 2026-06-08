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

    # int a
    li $t0, 3
    move $a0, $t0
    li $t1, 5
    move $a1, $t1
    jal _addTwo
    move $t0, $v0
    sw $t0, 0($fp)
    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int b
    li $t0, 5
    move $a0, $t0
    jal _sumTo
    move $t0, $v0
    sw $t0, 4($fp)
    lw $t0, 4($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall

    # Epilogue
    lw   $ra, 12($sp)
    lw   $fp, 8($sp)
    addi $sp, $sp, 16
    jr   $ra
# End _Master

# Function: addTwo
_addTwo:
    addi $sp, $sp, -16
    sw   $ra, 12($sp)
    sw   $fp, 8($sp)
    move $fp, $sp

    sw $a0, 0($fp)   # param 'x'
    sw $a1, 4($fp)   # param 'y'
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    add $t0, $t0, $t1
    move $v0, $t0

    # Epilogue
    lw   $ra, 12($sp)
    lw   $fp, 8($sp)
    addi $sp, $sp, 16
    jr   $ra
# End _addTwo

# Function: sumTo
_sumTo:
    addi $sp, $sp, -20
    sw   $ra, 16($sp)
    sw   $fp, 12($sp)
    move $fp, $sp

    sw $a0, 0($fp)   # param 'n'
    # int total
    li $t0, 0
    sw $t0, 4($fp)
    # int i
    li $t0, 1
    sw $t0, 8($fp)

_while_start_0:
    lw $t0, 8($fp)
    lw $t1, 0($fp)
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _while_end_0
    lw $t0, 4($fp)
    lw $t1, 8($fp)
    add $t0, $t0, $t1
    sw $t0, 4($fp)
    lw $t0, 8($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 8($fp)
    j _while_start_0
_while_end_0:

    lw $t0, 4($fp)
    move $v0, $t0

    # Epilogue
    lw   $ra, 16($sp)
    lw   $fp, 12($sp)
    addi $sp, $sp, 20
    jr   $ra
# End _sumTo

.globl main
main:
    addi $sp, $sp, -8
    sw   $ra, 4($sp)


    jal _Master

    lw   $ra, 4($sp)
    addi $sp, $sp, 8
    li   $v0, 10
    syscall
