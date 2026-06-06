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

    # float pi
    # float literal 3.14 (IEEE bits 0x4048F5C3)
    li $t0, 1078523331
    sw $t0, 0($fp)
    lw $t0, 0($fp)
    mtc1 $t0, $f12
    li   $v0, 2
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # float two_pi
    lw $t0, 0($fp)
    lw $t1, 0($fp)
    mtc1 $t0, $f0
    mtc1 $t1, $f2
    add.s $f0, $f0, $f2
    mfc1 $t0, $f0
    sw $t0, 4($fp)
    lw $t0, 4($fp)
    mtc1 $t0, $f12
    li   $v0, 2
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # Declare float x at offset 8
    # float literal 1.5 (IEEE bits 0x3FC00000)
    li $t0, 1069547520
    sw $t0, 8($fp)
    # float y
    # float literal 2.5 (IEEE bits 0x40200000)
    li $t0, 1075838976
    sw $t0, 12($fp)
    # float z
    lw $t0, 8($fp)
    lw $t1, 12($fp)
    mtc1 $t0, $f0
    mtc1 $t1, $f2
    add.s $f0, $f0, $f2
    mfc1 $t0, $f0
    sw $t0, 16($fp)
    lw $t0, 16($fp)
    mtc1 $t0, $f12
    li   $v0, 2
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
