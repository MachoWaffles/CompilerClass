.data

.text


# Function: Master
_Master:
    addi $sp, $sp, -20
    sw   $ra, 16($sp)
    sw   $fp, 12($sp)
    move $fp, $sp

    # Declare int x at offset 0
    # Declare int y at offset 4
    li $t0, 10
    sw $t0, 0($fp)
    li $t0, 20
    sw $t0, 4($fp)
    # int z
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
    lw $t0, 8($fp)
    li $t1, 0
    mul $t0, $t0, $t1
    sw $t0, 0($fp)
    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    div $t0, $t1
    mflo $t0
    sw $t0, 4($fp)
    lw $t0, 4($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 0($fp)
    sw $t0, 0($sp)

    # Epilogue
    lw   $ra, 16($sp)
    lw   $fp, 12($sp)
    addi $sp, $sp, 20
    jr   $ra
# End _Master

.globl main
main:
    addi $sp, $sp, -400


    jal _Master

    addi $sp, $sp, 400
    li   $v0, 10
    syscall
