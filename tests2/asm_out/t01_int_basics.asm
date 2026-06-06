.data
_str_true:  .asciiz "true"
_str_false: .asciiz "false"

.text


# Function: Master
_Master:
    addi $sp, $sp, -36
    sw   $ra, 32($sp)
    sw   $fp, 28($sp)
    move $fp, $sp

    # Declare int a at offset 0
    li $t0, 5
    sw $t0, 0($fp)
    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int b
    li $t0, 3
    sw $t0, 4($fp)
    lw $t0, 4($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int sum
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    add $t0, $t0, $t1
    sw $t0, 8($fp)
    lw $t0, 8($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int diff
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    sub $t0, $t0, $t1
    sw $t0, 12($fp)
    lw $t0, 12($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int prod
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    mul $t0, $t0, $t1
    sw $t0, 16($fp)
    lw $t0, 16($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int quot
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    div $t0, $t1
    mflo $t0
    sw $t0, 20($fp)
    lw $t0, 20($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int compound
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    add $t0, $t0, $t1
    li $t1, 2
    mul $t0, $t0, $t1
    sw $t0, 24($fp)
    lw $t0, 24($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall

    # Epilogue
    lw   $ra, 32($sp)
    lw   $fp, 28($sp)
    addi $sp, $sp, 36
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
