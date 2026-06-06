.data
_str_true:  .asciiz "true"
_str_false: .asciiz "false"
_g_counter: .word 0
_g_step: .word 0

.text


# Function: increment
_increment:
    addi $sp, $sp, -8
    sw   $ra, 4($sp)
    sw   $fp, 0($sp)
    move $fp, $sp

    la  $t0, _g_counter
    lw  $t0, 0($t0)
    la  $t1, _g_step
    lw  $t1, 0($t1)
    add $t0, $t0, $t1
    la  $t1, _g_counter
    sw  $t0, 0($t1)

    # Epilogue
    lw   $ra, 4($sp)
    lw   $fp, 0($sp)
    addi $sp, $sp, 8
    jr   $ra
# End _increment

# Function: Master
_Master:
    addi $sp, $sp, -8
    sw   $ra, 4($sp)
    sw   $fp, 0($sp)
    move $fp, $sp

    li $t0, 0
    la  $t1, _g_counter
    sw  $t0, 0($t1)
    la  $t0, _g_counter
    lw  $t0, 0($t0)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    jal _increment
    move $t0, $v0
    la  $t0, _g_counter
    lw  $t0, 0($t0)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    jal _increment
    move $t0, $v0
    la  $t0, _g_counter
    lw  $t0, 0($t0)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    jal _increment
    move $t0, $v0
    la  $t0, _g_counter
    lw  $t0, 0($t0)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall

    # Epilogue
    lw   $ra, 4($sp)
    lw   $fp, 0($sp)
    addi $sp, $sp, 8
    jr   $ra
# End _Master

.globl main
main:
    addi $sp, $sp, -8
    sw   $ra, 4($sp)

    # int step
    li $t0, 10
    la  $t1, _g_step
    sw  $t0, 0($t1)

    jal _Master

    lw   $ra, 4($sp)
    addi $sp, $sp, 8
    li   $v0, 10
    syscall
