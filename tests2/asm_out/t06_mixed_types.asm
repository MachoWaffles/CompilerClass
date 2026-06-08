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

    # int i
    li $t0, 7
    sw $t0, 0($fp)
    # float f
    # float literal 2.71 (IEEE bits 0x402D70A4)
    li $t0, 1076719780
    sw $t0, 4($fp)
    # bool b
    li $t0, 1
    sw $t0, 8($fp)
    # char c
    li $t0, 65
    sw $t0, 12($fp)
    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 4($fp)
    mtc1 $t0, $f12
    li   $v0, 2
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
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
    lw $t0, 12($fp)
    move $a0, $t0
    li   $v0, 11
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
