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

    # bool t
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
    # bool f
    li $t0, 0
    sw $t0, 4($fp)
    lw $t0, 4($fp)
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
    # Declare bool t2 at offset 8
    li $t0, 1
    sw $t0, 8($fp)
    lw $t0, 8($fp)
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
    # Declare bool f2 at offset 12
    li $t0, 0
    sw $t0, 12($fp)
    lw $t0, 12($fp)
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
