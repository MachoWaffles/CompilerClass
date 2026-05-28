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

    # Declare float x at offset 0
    # Declare int y at offset 4
    # bool s
    li $t0, 1
    sw $t0, 8($fp)
    # float literal 10 (IEEE bits 0x41200000)
    li $t0, 1092616192
    sw $t0, 0($fp)
    li $t0, 20
    sw $t0, 4($fp)
    # char c
    li $t0, 103
    sw $t0, 12($fp)
    # float z
    lw $t0, 4($fp)
    lw $t1, 0($fp)
    mtc1 $t0, $f0
    cvt.s.w $f0, $f0
    mtc1 $t1, $f2
    div.s $f0, $f0, $f2
    mfc1 $t0, $f0
    li $t1, 10
    mtc1 $t0, $f0
    mtc1 $t1, $f2
    cvt.s.w $f2, $f2
    mul.s $f0, $f0, $f2
    mfc1 $t0, $f0
    # float literal 3 (IEEE bits 0x40400000)
    li $t1, 1077936128
    lw $t2, 4($fp)
    mtc1 $t1, $f0
    mtc1 $t2, $f2
    cvt.s.w $f2, $f2
    mul.s $f0, $f0, $f2
    mfc1 $t1, $f0
    mtc1 $t0, $f0
    mtc1 $t1, $f2
    div.s $f0, $f0, $f2
    mfc1 $t0, $f0
    sw $t0, 16($fp)
    lw $t0, 16($fp)
    mtc1 $t0, $f12
    li   $v0, 2
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 16($fp)
    li $t1, 2
    mtc1 $t0, $f0
    mtc1 $t1, $f2
    cvt.s.w $f2, $f2
    mul.s $f0, $f0, $f2
    mfc1 $t0, $f0
    sw $t0, 0($fp)
    lw $t0, 0($fp)
    mtc1 $t0, $f12
    li   $v0, 2
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 4($fp)
    move $a0, $t0
    li   $v0, 1
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
    lw $t1, 0($fp)
    mtc1 $t0, $f0
    mtc1 $t1, $f2
    add.s $f0, $f0, $f2
    mfc1 $t0, $f0
    mtc1 $t0, $f12
    li   $v0, 2
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 0($fp)
    sw $t0, 0($sp)

    # Epilogue
    lw   $ra, 24($sp)
    lw   $fp, 20($sp)
    addi $sp, $sp, 28
    jr   $ra
# End _Master

.globl main
main:
    addi $sp, $sp, -400


    jal _Master

    addi $sp, $sp, 400
    li   $v0, 10
    syscall
