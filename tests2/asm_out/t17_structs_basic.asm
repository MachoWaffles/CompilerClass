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

    # struct Point p (local)
    li $t0, 10
    # field assign p.x
    sw   $t0, 0($fp)
    li $t0, 20
    # field assign p.y
    sw   $t0, 4($fp)
    # field access p.x
    lw   $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # field access p.y
    lw   $t0, 4($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int total
    # field access p.x
    lw   $t0, 0($fp)
    # field access p.y
    lw   $t1, 4($fp)
    add $t0, $t0, $t1
    sw $t0, 8($fp)
    lw $t0, 8($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall

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
