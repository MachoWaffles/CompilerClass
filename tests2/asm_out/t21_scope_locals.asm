.data
_str_true:  .asciiz "true"
_str_false: .asciiz "false"
_g_g: .word 0

.text


# Function: funcA
_funcA:
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $fp, 4($sp)
    move $fp, $sp

    # int x
    li $t0, 1
    sw $t0, 0($fp)
    lw $t0, 0($fp)
    move $v0, $t0

    # Epilogue
    lw   $ra, 8($sp)
    lw   $fp, 4($sp)
    addi $sp, $sp, 12
    jr   $ra
# End _funcA

# Function: funcB
_funcB:
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $fp, 4($sp)
    move $fp, $sp

    # int x
    li $t0, 2
    sw $t0, 0($fp)
    lw $t0, 0($fp)
    move $v0, $t0

    # Epilogue
    lw   $ra, 8($sp)
    lw   $fp, 4($sp)
    addi $sp, $sp, 12
    jr   $ra
# End _funcB

# Function: Master
_Master:
    addi $sp, $sp, -16
    sw   $ra, 12($sp)
    sw   $fp, 8($sp)
    move $fp, $sp

    la  $t0, _g_g
    lw  $t0, 0($t0)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int a
    jal _funcA
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
    jal _funcB
    move $t0, $v0
    sw $t0, 4($fp)
    lw $t0, 4($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    la  $t0, _g_g
    lw  $t0, 0($t0)
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

.globl main
main:
    addi $sp, $sp, -8
    sw   $ra, 4($sp)

    # int g
    li $t0, 100
    la  $t1, _g_g
    sw  $t0, 0($t1)

    jal _Master

    lw   $ra, 4($sp)
    addi $sp, $sp, 8
    li   $v0, 10
    syscall
