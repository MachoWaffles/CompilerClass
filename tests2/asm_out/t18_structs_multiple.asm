.data
_str_true:  .asciiz "true"
_str_false: .asciiz "false"

.text


# Function: Master
_Master:
    addi $sp, $sp, -24
    sw   $ra, 20($sp)
    sw   $fp, 16($sp)
    move $fp, $sp

    # struct Vec2 v (local)
    li $t0, 3
    # field assign v.x
    sw   $t0, 0($fp)
    li $t0, 4
    # field assign v.y
    sw   $t0, 4($fp)
    # field access v.x
    lw   $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # field access v.y
    lw   $t0, 4($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # struct Rect r (local)
    li $t0, 100
    # field assign r.width
    sw   $t0, 8($fp)
    li $t0, 200
    # field assign r.height
    sw   $t0, 12($fp)
    # field access r.width
    lw   $t0, 8($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # field access r.height
    lw   $t0, 12($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall

    # Epilogue
    lw   $ra, 20($sp)
    lw   $fp, 16($sp)
    addi $sp, $sp, 24
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
