.data
_str_true:  .asciiz "true"
_str_false: .asciiz "false"

.text


# Function: Master
_Master:
    addi $sp, $sp, -64
    sw   $ra, 60($sp)
    sw   $fp, 56($sp)
    move $fp, $sp

    # int a
    li $t0, 3
    sw $t0, 0($fp)
    # int b
    li $t0, 5
    sw $t0, 4($fp)
    # bool r1
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    slt $t0, $t0, $t1
    sw $t0, 8($fp)
    lw $t0, 8($fp)
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
    # bool r2
    lw $t0, 4($fp)
    lw $t1, 0($fp)
    slt $t0, $t0, $t1
    sw $t0, 12($fp)
    lw $t0, 12($fp)
    bne  $t0, $zero, _print_true_1
    la   $a0, _str_false
    j    _print_bool_done_1
_print_true_1:
    la   $a0, _str_true
_print_bool_done_1:
    li   $v0, 4
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # bool r3
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    slt $t0, $t1, $t0
    sw $t0, 16($fp)
    lw $t0, 16($fp)
    bne  $t0, $zero, _print_true_2
    la   $a0, _str_false
    j    _print_bool_done_2
_print_true_2:
    la   $a0, _str_true
_print_bool_done_2:
    li   $v0, 4
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # bool r4
    lw $t0, 4($fp)
    lw $t1, 0($fp)
    slt $t0, $t1, $t0
    sw $t0, 20($fp)
    lw $t0, 20($fp)
    bne  $t0, $zero, _print_true_3
    la   $a0, _str_false
    j    _print_bool_done_3
_print_true_3:
    la   $a0, _str_true
_print_bool_done_3:
    li   $v0, 4
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # bool r5
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    sw $t0, 24($fp)
    lw $t0, 24($fp)
    bne  $t0, $zero, _print_true_4
    la   $a0, _str_false
    j    _print_bool_done_4
_print_true_4:
    la   $a0, _str_true
_print_bool_done_4:
    li   $v0, 4
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # bool r6
    lw $t0, 4($fp)
    lw $t1, 0($fp)
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    sw $t0, 28($fp)
    lw $t0, 28($fp)
    bne  $t0, $zero, _print_true_5
    la   $a0, _str_false
    j    _print_bool_done_5
_print_true_5:
    la   $a0, _str_true
_print_bool_done_5:
    li   $v0, 4
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # bool r7
    lw $t0, 4($fp)
    lw $t1, 0($fp)
    slt $t0, $t0, $t1
    xori $t0, $t0, 1
    sw $t0, 32($fp)
    lw $t0, 32($fp)
    bne  $t0, $zero, _print_true_6
    la   $a0, _str_false
    j    _print_bool_done_6
_print_true_6:
    la   $a0, _str_true
_print_bool_done_6:
    li   $v0, 4
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # bool r8
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    slt $t0, $t0, $t1
    xori $t0, $t0, 1
    sw $t0, 36($fp)
    lw $t0, 36($fp)
    bne  $t0, $zero, _print_true_7
    la   $a0, _str_false
    j    _print_bool_done_7
_print_true_7:
    la   $a0, _str_true
_print_bool_done_7:
    li   $v0, 4
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # bool r9
    lw $t0, 0($fp)
    lw $t1, 0($fp)
    xor  $t0, $t0, $t1
    sltiu $t0, $t0, 1
    sw $t0, 40($fp)
    lw $t0, 40($fp)
    bne  $t0, $zero, _print_true_8
    la   $a0, _str_false
    j    _print_bool_done_8
_print_true_8:
    la   $a0, _str_true
_print_bool_done_8:
    li   $v0, 4
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # bool r10
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    xor  $t0, $t0, $t1
    sltiu $t0, $t0, 1
    sw $t0, 44($fp)
    lw $t0, 44($fp)
    bne  $t0, $zero, _print_true_9
    la   $a0, _str_false
    j    _print_bool_done_9
_print_true_9:
    la   $a0, _str_true
_print_bool_done_9:
    li   $v0, 4
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # bool r11
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    xor  $t0, $t0, $t1
    sltu $t0, $zero, $t0
    sw $t0, 48($fp)
    lw $t0, 48($fp)
    bne  $t0, $zero, _print_true_10
    la   $a0, _str_false
    j    _print_bool_done_10
_print_true_10:
    la   $a0, _str_true
_print_bool_done_10:
    li   $v0, 4
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # bool r12
    lw $t0, 0($fp)
    lw $t1, 0($fp)
    xor  $t0, $t0, $t1
    sltu $t0, $zero, $t0
    sw $t0, 52($fp)
    lw $t0, 52($fp)
    bne  $t0, $zero, _print_true_11
    la   $a0, _str_false
    j    _print_bool_done_11
_print_true_11:
    la   $a0, _str_true
_print_bool_done_11:
    li   $v0, 4
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall

    # Epilogue
    lw   $ra, 60($sp)
    lw   $fp, 56($sp)
    addi $sp, $sp, 64
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
