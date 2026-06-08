.data
_str_true:  .asciiz "true"
_str_false: .asciiz "false"
_g_globalSeed: .word 0

.text


# Function: addInts
_addInts:
    addi $sp, $sp, -16
    sw   $ra, 12($sp)
    sw   $fp, 8($sp)
    move $fp, $sp

    sw $a0, 0($fp)   # param 'a'
    sw $a1, 4($fp)   # param 'b'
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    add $t0, $t0, $t1
    move $v0, $t0

    # Epilogue
    lw   $ra, 12($sp)
    lw   $fp, 8($sp)
    addi $sp, $sp, 16
    jr   $ra
# End _addInts

# Function: Master
_Master:
    addi $sp, $sp, -40
    sw   $ra, 36($sp)
    sw   $fp, 32($sp)
    move $fp, $sp

    la  $t0, _g_globalSeed
    lw  $t0, 0($t0)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    la  $t0, _g_globalSeed
    lw  $t0, 0($t0)
    li $t1, 5
    add $t0, $t0, $t1
    la  $t1, _g_globalSeed
    sw  $t0, 0($t1)
    la  $t0, _g_globalSeed
    lw  $t0, 0($t0)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # bool flag
    li $t0, 1
    sw $t0, 0($fp)
    lw $t0, 0($fp)
    bne  $t0, $zero, _print_true_0
    la   $a0, _str_false
    j    _print_bool_done_0
_print_true_0:
    la   $a0, _str_true
_print_bool_done_0:
    li   $v0, 4
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # char letter
    li $t0, 65
    sw $t0, 4($fp)
    lw $t0, 4($fp)
    move $a0, $t0
    li   $v0, 11
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int s
    li $t0, 7
    move $a0, $t0
    li $t1, 8
    move $a1, $t1
    jal _addInts
    move $t0, $v0
    sw $t0, 8($fp)
    lw $t0, 8($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int i
    li $t0, 0
    sw $t0, 12($fp)

_for_start_0:
    lw $t0, 12($fp)
    li $t1, 5
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_0
    lw $t0, 12($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 12($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 12($fp)
    j _for_start_0
_for_end_0:

    # int acc
    li $t0, 0
    sw $t0, 16($fp)
    # int k
    li $t0, 1
    sw $t0, 20($fp)

_while_start_1:
    lw $t0, 20($fp)
    li $t1, 10
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _while_end_1
    lw $t0, 16($fp)
    lw $t1, 20($fp)
    add $t0, $t0, $t1
    sw $t0, 16($fp)
    lw $t0, 20($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($fp)
    j _while_start_1
_while_end_1:

    lw $t0, 16($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # struct Counter c (local)
    li $t0, 7
    # field assign c.value
    sw   $t0, 24($fp)
    li $t0, 3
    # field assign c.step
    sw   $t0, 28($fp)
    # field access c.value
    lw   $t0, 24($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall

    # Epilogue
    lw   $ra, 36($sp)
    lw   $fp, 32($sp)
    addi $sp, $sp, 40
    jr   $ra
# End _Master

.globl main
main:
    addi $sp, $sp, -8
    sw   $ra, 4($sp)

    # int globalSeed
    li $t0, 5
    la  $t1, _g_globalSeed
    sw  $t0, 0($t1)

    jal _Master

    lw   $ra, 4($sp)
    addi $sp, $sp, 8
    li   $v0, 10
    syscall
