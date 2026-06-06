.data
_str_true:  .asciiz "true"
_str_false: .asciiz "false"

.text


# Function: Master
_Master:
    addi $sp, $sp, -28
    sw   $ra, 24($sp)
    sw   $fp, 20($sp)
    move $fp, $sp

    # array int arr[5] at fp+0
    li $t0, 10
    li $t1, 0
    sll $t1, $t1, 2
    addi $t2, $fp, 0
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    li $t0, 20
    li $t1, 1
    sll $t1, $t1, 2
    addi $t2, $fp, 0
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    li $t0, 30
    li $t1, 2
    sll $t1, $t1, 2
    addi $t2, $fp, 0
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    li $t0, 40
    li $t1, 3
    sll $t1, $t1, 2
    addi $t2, $fp, 0
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    li $t0, 50
    li $t1, 4
    sll $t1, $t1, 2
    addi $t2, $fp, 0
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    li $t0, 0
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
    li $t0, 1
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
    li $t0, 2
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
    li $t0, 3
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
    li $t0, 4
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

    # Epilogue
    lw   $ra, 24($sp)
    lw   $fp, 20($sp)
    addi $sp, $sp, 28
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
