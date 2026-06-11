.data
_str_true:  .asciiz "true"
_str_false: .asciiz "false"
_g_gIntA: .word 0
_g_gIntB: .word 0
_g_gSeed: .word 0
_g_gStep: .word 0
_g_gPi: .word 0
_g_gLetter: .word 0
_g_gTrue: .word 0
_g_gFalse: .word 0

.text


# Function: addTwo
_addTwo:
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
# End _addTwo

# Function: mul
_mul:
    addi $sp, $sp, -16
    sw   $ra, 12($sp)
    sw   $fp, 8($sp)
    move $fp, $sp

    sw $a0, 0($fp)   # param 'a'
    sw $a1, 4($fp)   # param 'b'
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    mul $t0, $t0, $t1
    move $v0, $t0

    # Epilogue
    lw   $ra, 12($sp)
    lw   $fp, 8($sp)
    addi $sp, $sp, 16
    jr   $ra
# End _mul

# Function: maxOf
_maxOf:
    addi $sp, $sp, -16
    sw   $ra, 12($sp)
    sw   $fp, 8($sp)
    move $fp, $sp

    sw $a0, 0($fp)   # param 'a'
    sw $a1, 4($fp)   # param 'b'
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    slt $t0, $t1, $t0
    beq $t0, $zero, _if_end_0
    lw $t0, 0($fp)
    move $v0, $t0
    j _if_else_0
_if_end_0:

    lw $t0, 4($fp)
    move $v0, $t0
_if_else_0:


    # Epilogue
    lw   $ra, 12($sp)
    lw   $fp, 8($sp)
    addi $sp, $sp, 16
    jr   $ra
# End _maxOf

# Function: fact
_fact:
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $fp, 4($sp)
    move $fp, $sp

    sw $a0, 0($fp)   # param 'n'
    lw $t0, 0($fp)
    li $t1, 1
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _if_end_1
    li $t0, 1
    move $v0, $t0
_if_end_1:

    lw $t0, 0($fp)
    lw $t1, 0($fp)
    li $t2, 1
    sub $t1, $t1, $t2
    move $a0, $t1
    jal _fact
    move $t1, $v0
    mul $t0, $t0, $t1
    move $v0, $t0

    # Epilogue
    lw   $ra, 8($sp)
    lw   $fp, 4($sp)
    addi $sp, $sp, 12
    jr   $ra
# End _fact

# Function: halfOf
_halfOf:
    addi $sp, $sp, -16
    sw   $ra, 12($sp)
    sw   $fp, 8($sp)
    move $fp, $sp

    sw $a0, 0($fp)   # param 'n'
    # float f
    lw $t0, 0($fp)
    sw $t0, 4($fp)
    lw $t0, 4($fp)
    li $t1, 2
    mtc1 $t0, $f0
    mtc1 $t1, $f2
    cvt.s.w $f2, $f2
    div.s $f0, $f0, $f2
    mfc1 $t0, $f0
    move $v0, $t0

    # Epilogue
    lw   $ra, 12($sp)
    lw   $fp, 8($sp)
    addi $sp, $sp, 16
    jr   $ra
# End _halfOf

# Function: getZ
_getZ:
    addi $sp, $sp, -8
    sw   $ra, 4($sp)
    sw   $fp, 0($sp)
    move $fp, $sp

    li $t0, 90
    move $v0, $t0

    # Epilogue
    lw   $ra, 4($sp)
    lw   $fp, 0($sp)
    addi $sp, $sp, 8
    jr   $ra
# End _getZ

# Function: isPos
_isPos:
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $fp, 4($sp)
    move $fp, $sp

    sw $a0, 0($fp)   # param 'n'
    lw $t0, 0($fp)
    li $t1, 0
    slt $t0, $t1, $t0
    beq $t0, $zero, _if_end_2
    li $t0, 1
    move $v0, $t0
    j _if_else_2
_if_end_2:

    li $t0, 0
    move $v0, $t0
_if_else_2:


    # Epilogue
    lw   $ra, 8($sp)
    lw   $fp, 4($sp)
    addi $sp, $sp, 12
    jr   $ra
# End _isPos

# Function: printVal
_printVal:
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $fp, 4($sp)
    move $fp, $sp

    sw $a0, 0($fp)   # param 'v'
    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall

    # Epilogue
    lw   $ra, 8($sp)
    lw   $fp, 4($sp)
    addi $sp, $sp, 12
    jr   $ra
# End _printVal

# Function: doNothing
_doNothing:
    addi $sp, $sp, -8
    sw   $ra, 4($sp)
    sw   $fp, 0($sp)
    move $fp, $sp


    # Epilogue
    lw   $ra, 4($sp)
    lw   $fp, 0($sp)
    addi $sp, $sp, 8
    jr   $ra
# End _doNothing

# Function: Master
_Master:
    addi $sp, $sp, -620
    sw   $ra, 616($sp)
    sw   $fp, 612($sp)
    move $fp, $sp

    la  $t0, _g_gIntA
    lw  $t0, 0($t0)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    la  $t0, _g_gIntB
    lw  $t0, 0($t0)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    la  $t0, _g_gSeed
    lw  $t0, 0($t0)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    la  $t0, _g_gStep
    lw  $t0, 0($t0)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    la  $t0, _g_gPi
    lw  $t0, 0($t0)
    mtc1 $t0, $f12
    li   $v0, 2
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    la  $t0, _g_gLetter
    lw  $t0, 0($t0)
    move $a0, $t0
    li   $v0, 11
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    la  $t0, _g_gTrue
    lw  $t0, 0($t0)
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
    la  $t0, _g_gFalse
    lw  $t0, 0($t0)
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
    # int a
    li $t0, 10
    sw $t0, 0($fp)
    # int b
    li $t0, 5
    sw $t0, 4($fp)
    # int r_add
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    add $t0, $t0, $t1
    sw $t0, 8($fp)
    lw $t0, 8($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int r_sub
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    sub $t0, $t0, $t1
    sw $t0, 12($fp)
    lw $t0, 12($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int r_mul
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    mul $t0, $t0, $t1
    sw $t0, 16($fp)
    lw $t0, 16($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int r_div
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    div $t0, $t1
    mflo $t0
    sw $t0, 20($fp)
    lw $t0, 20($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int r_prec
    li $t0, 2
    li $t1, 2
    li $t2, 2
    mul $t1, $t1, $t2
    add $t0, $t0, $t1
    sw $t0, 24($fp)
    lw $t0, 24($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int r_paren
    li $t0, 2
    li $t1, 2
    add $t0, $t0, $t1
    li $t1, 2
    mul $t0, $t0, $t1
    sw $t0, 28($fp)
    lw $t0, 28($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int r_ltr
    li $t0, 20
    li $t1, 3
    sub $t0, $t0, $t1
    li $t1, 2
    sub $t0, $t0, $t1
    sw $t0, 32($fp)
    lw $t0, 32($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int r_idiv
    li $t0, 7
    li $t1, 2
    div $t0, $t1
    mflo $t0
    sw $t0, 36($fp)
    lw $t0, 36($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int negOne
    li $t0, 0
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 40($fp)
    lw $t0, 40($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # float f1
    # float literal 5 (IEEE bits 0x40A00000)
    li $t0, 1084227584
    sw $t0, 44($fp)
    # float f2
    # float literal 2 (IEEE bits 0x40000000)
    li $t0, 1073741824
    sw $t0, 48($fp)
    # float f_div
    lw $t0, 44($fp)
    lw $t1, 48($fp)
    mtc1 $t0, $f0
    mtc1 $t1, $f2
    div.s $f0, $f0, $f2
    mfc1 $t0, $f0
    sw $t0, 52($fp)
    lw $t0, 52($fp)
    mtc1 $t0, $f12
    li   $v0, 2
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # float f_add
    lw $t0, 44($fp)
    lw $t1, 48($fp)
    mtc1 $t0, $f0
    mtc1 $t1, $f2
    add.s $f0, $f0, $f2
    mfc1 $t0, $f0
    sw $t0, 56($fp)
    lw $t0, 56($fp)
    mtc1 $t0, $f12
    li   $v0, 2
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # float f_mul
    lw $t0, 44($fp)
    lw $t1, 48($fp)
    mtc1 $t0, $f0
    mtc1 $t1, $f2
    mul.s $f0, $f0, $f2
    mfc1 $t0, $f0
    sw $t0, 60($fp)
    lw $t0, 60($fp)
    mtc1 $t0, $f12
    li   $v0, 2
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # float f_sub
    lw $t0, 44($fp)
    lw $t1, 48($fp)
    mtc1 $t0, $f0
    mtc1 $t1, $f2
    sub.s $f0, $f0, $f2
    mfc1 $t0, $f0
    sw $t0, 64($fp)
    lw $t0, 64($fp)
    mtc1 $t0, $f12
    li   $v0, 2
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # float f_wide
    li $t0, 10
    sw $t0, 68($fp)
    lw $t0, 68($fp)
    mtc1 $t0, $f12
    li   $v0, 2
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # float f_mix
    lw $t0, 44($fp)
    li $t1, 3
    mtc1 $t0, $f0
    mtc1 $t1, $f2
    cvt.s.w $f2, $f2
    add.s $f0, $f0, $f2
    mfc1 $t0, $f0
    sw $t0, 72($fp)
    lw $t0, 72($fp)
    mtc1 $t0, $f12
    li   $v0, 2
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # bool cmp_lt
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    slt $t0, $t0, $t1
    sw $t0, 76($fp)
    lw $t0, 76($fp)
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
    # bool cmp_gt
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    slt $t0, $t1, $t0
    sw $t0, 80($fp)
    lw $t0, 80($fp)
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
    # bool cmp_le
    lw $t0, 4($fp)
    li $t1, 5
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    sw $t0, 84($fp)
    lw $t0, 84($fp)
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
    # bool cmp_ge
    lw $t0, 4($fp)
    li $t1, 6
    slt $t0, $t0, $t1
    xori $t0, $t0, 1
    sw $t0, 88($fp)
    lw $t0, 88($fp)
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
    # bool cmp_eq
    lw $t0, 0($fp)
    li $t1, 10
    xor  $t0, $t0, $t1
    sltiu $t0, $t0, 1
    sw $t0, 92($fp)
    lw $t0, 92($fp)
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
    # bool cmp_ne
    lw $t0, 0($fp)
    li $t1, 10
    xor  $t0, $t0, $t1
    sltu $t0, $zero, $t0
    sw $t0, 96($fp)
    lw $t0, 96($fp)
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
    # char c_nl
    li $t0, 10
    sw $t0, 100($fp)
    # char c_tab
    li $t0, 9
    sw $t0, 104($fp)
    # char c_bs
    li $t0, 92
    sw $t0, 108($fp)
    # char c_A
    li $t0, 65
    sw $t0, 112($fp)
    lw $t0, 100($fp)
    move $a0, $t0
    li   $v0, 11
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 104($fp)
    move $a0, $t0
    li   $v0, 11
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 108($fp)
    move $a0, $t0
    li   $v0, 11
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 112($fp)
    move $a0, $t0
    li   $v0, 11
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # bool bt
    li $t0, 1
    sw $t0, 116($fp)
    # bool bf
    li $t0, 0
    sw $t0, 120($fp)
    lw $t0, 116($fp)
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
    lw $t0, 120($fp)
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
    # int s_add
    li $t0, 13
    move $a0, $t0
    li $t1, 17
    move $a1, $t1
    jal _addTwo
    move $t0, $v0
    sw $t0, 124($fp)
    lw $t0, 124($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int s_mul
    li $t0, 6
    move $a0, $t0
    li $t1, 7
    move $a1, $t1
    jal _mul
    move $t0, $v0
    sw $t0, 128($fp)
    lw $t0, 128($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int s_max1
    li $t0, 3
    move $a0, $t0
    li $t1, 9
    move $a1, $t1
    jal _maxOf
    move $t0, $v0
    sw $t0, 132($fp)
    lw $t0, 132($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int s_max2
    li $t0, 9
    move $a0, $t0
    li $t1, 3
    move $a1, $t1
    jal _maxOf
    move $t0, $v0
    sw $t0, 136($fp)
    lw $t0, 136($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    li $t0, 999
    move $a0, $t0
    jal _printVal
    move $t0, $v0
    # bool p_pos
    li $t0, 5
    move $a0, $t0
    jal _isPos
    move $t0, $v0
    sw $t0, 140($fp)
    lw $t0, 140($fp)
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
    # bool p_neg
    lw $t0, 40($fp)
    move $a0, $t0
    jal _isPos
    move $t0, $v0
    sw $t0, 144($fp)
    lw $t0, 144($fp)
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
    # float hf
    li $t0, 5
    move $a0, $t0
    jal _halfOf
    move $t0, $v0
    sw $t0, 148($fp)
    lw $t0, 148($fp)
    mtc1 $t0, $f12
    li   $v0, 2
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # char zc
    jal _getZ
    move $t0, $v0
    sw $t0, 152($fp)
    lw $t0, 152($fp)
    move $a0, $t0
    li   $v0, 11
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    jal _doNothing
    move $t0, $v0
    # int fw
    li $t0, 10
    move $a0, $t0
    jal _lateHelper
    move $t0, $v0
    sw $t0, 156($fp)
    lw $t0, 156($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int fac5
    li $t0, 5
    move $a0, $t0
    jal _fact
    move $t0, $v0
    sw $t0, 160($fp)
    lw $t0, 160($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int fac0
    li $t0, 0
    move $a0, $t0
    jal _fact
    move $t0, $v0
    sw $t0, 164($fp)
    lw $t0, 164($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # array int nums[5] at fp+168
    li $t0, 10
    li $t1, 0
    sll $t1, $t1, 2
    addi $t2, $fp, 168
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    li $t0, 20
    li $t1, 1
    sll $t1, $t1, 2
    addi $t2, $fp, 168
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    li $t0, 30
    li $t1, 2
    sll $t1, $t1, 2
    addi $t2, $fp, 168
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    li $t0, 40
    li $t1, 3
    sll $t1, $t1, 2
    addi $t2, $fp, 168
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    li $t0, 50
    li $t1, 4
    sll $t1, $t1, 2
    addi $t2, $fp, 168
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    li $t0, 0
    sll $t0, $t0, 2
    addi $t1, $fp, 168
    add  $t1, $t1, $t0
    lw   $t1, 0($t1)
    move $a0, $t1
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    li $t0, 1
    sll $t0, $t0, 2
    addi $t1, $fp, 168
    add  $t1, $t1, $t0
    lw   $t1, 0($t1)
    move $a0, $t1
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    li $t0, 2
    sll $t0, $t0, 2
    addi $t1, $fp, 168
    add  $t1, $t1, $t0
    lw   $t1, 0($t1)
    move $a0, $t1
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    li $t0, 3
    sll $t0, $t0, 2
    addi $t1, $fp, 168
    add  $t1, $t1, $t0
    lw   $t1, 0($t1)
    move $a0, $t1
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    li $t0, 4
    sll $t0, $t0, 2
    addi $t1, $fp, 168
    add  $t1, $t1, $t0
    lw   $t1, 0($t1)
    move $a0, $t1
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int arr_sum
    li $t0, 0
    sw $t0, 188($fp)
    # int arr_i
    li $t0, 0
    sw $t0, 192($fp)

_while_start_3:
    lw $t0, 192($fp)
    li $t1, 5
    slt $t0, $t0, $t1
    beq $t0, $zero, _while_end_3
    lw $t0, 188($fp)
    lw $t1, 192($fp)
    sll $t1, $t1, 2
    addi $t2, $fp, 168
    add  $t2, $t2, $t1
    lw   $t2, 0($t2)
    add $t0, $t0, $t2
    sw $t0, 188($fp)
    lw $t0, 192($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 192($fp)
    j _while_start_3
_while_end_3:

    lw $t0, 188($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int dbl
    li $t0, 2
    sll $t0, $t0, 2
    addi $t1, $fp, 168
    add  $t1, $t1, $t0
    lw   $t1, 0($t1)
    li $t0, 2
    mul $t1, $t1, $t0
    sw $t1, 196($fp)
    lw $t0, 196($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int pair
    li $t0, 1
    sll $t0, $t0, 2
    addi $t1, $fp, 168
    add  $t1, $t1, $t0
    lw   $t1, 0($t1)
    li $t0, 3
    sll $t0, $t0, 2
    addi $t2, $fp, 168
    add  $t2, $t2, $t0
    lw   $t2, 0($t2)
    add $t1, $t1, $t2
    sw $t1, 200($fp)
    lw $t0, 200($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # array float farr[3] at fp+204
    # float literal 1.5 (IEEE bits 0x3FC00000)
    li $t0, 1069547520
    li $t1, 0
    sll $t1, $t1, 2
    addi $t2, $fp, 204
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    # float literal 2.5 (IEEE bits 0x40200000)
    li $t0, 1075838976
    li $t1, 1
    sll $t1, $t1, 2
    addi $t2, $fp, 204
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    # float literal 3.5 (IEEE bits 0x40600000)
    li $t0, 1080033280
    li $t1, 2
    sll $t1, $t1, 2
    addi $t2, $fp, 204
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    li $t0, 0
    sll $t0, $t0, 2
    addi $t1, $fp, 204
    add  $t1, $t1, $t0
    lw   $t1, 0($t1)
    move $a0, $t1
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    li $t0, 1
    sll $t0, $t0, 2
    addi $t1, $fp, 204
    add  $t1, $t1, $t0
    lw   $t1, 0($t1)
    move $a0, $t1
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    li $t0, 2
    sll $t0, $t0, 2
    addi $t1, $fp, 204
    add  $t1, $t1, $t0
    lw   $t1, 0($t1)
    move $a0, $t1
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # array bool barr[2] at fp+216
    li $t0, 1
    li $t1, 0
    sll $t1, $t1, 2
    addi $t2, $fp, 216
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    li $t0, 0
    li $t1, 1
    sll $t1, $t1, 2
    addi $t2, $fp, 216
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    li $t0, 0
    sll $t0, $t0, 2
    addi $t1, $fp, 216
    add  $t1, $t1, $t0
    lw   $t1, 0($t1)
    move $a0, $t1
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    li $t0, 1
    sll $t0, $t0, 2
    addi $t1, $fp, 216
    add  $t1, $t1, $t0
    lw   $t1, 0($t1)
    move $a0, $t1
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # array char carr[3] at fp+224
    li $t0, 67
    li $t1, 0
    sll $t1, $t1, 2
    addi $t2, $fp, 224
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    li $t0, 83
    li $t1, 1
    sll $t1, $t1, 2
    addi $t2, $fp, 224
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    li $t0, 84
    li $t1, 2
    sll $t1, $t1, 2
    addi $t2, $fp, 224
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    li $t0, 0
    sll $t0, $t0, 2
    addi $t1, $fp, 224
    add  $t1, $t1, $t0
    lw   $t1, 0($t1)
    move $a0, $t1
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    li $t0, 1
    sll $t0, $t0, 2
    addi $t1, $fp, 224
    add  $t1, $t1, $t0
    lw   $t1, 0($t1)
    move $a0, $t1
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    li $t0, 2
    sll $t0, $t0, 2
    addi $t1, $fp, 224
    add  $t1, $t1, $t0
    lw   $t1, 0($t1)
    move $a0, $t1
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # array int sq[5] at fp+236
    # int i
    li $t0, 0
    sw $t0, 256($fp)

_for_start_4:
    lw $t0, 256($fp)
    li $t1, 5
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_4
    lw $t0, 256($fp)
    lw $t1, 256($fp)
    mul $t0, $t0, $t1
    lw $t1, 256($fp)
    sll $t1, $t1, 2
    addi $t2, $fp, 236
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    lw $t0, 256($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 256($fp)
    j _for_start_4
_for_end_4:

    # int i
    li $t0, 0
    sw $t0, 256($fp)

_for_start_5:
    lw $t0, 256($fp)
    li $t1, 5
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_5
    lw $t0, 256($fp)
    sll $t0, $t0, 2
    addi $t1, $fp, 236
    add  $t1, $t1, $t0
    lw   $t1, 0($t1)
    move $a0, $t1
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 256($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 256($fp)
    j _for_start_5
_for_end_5:

    # array int fcall_arr[3] at fp+260
    li $t0, 1
    move $a0, $t0
    li $t1, 2
    move $a1, $t1
    jal _addTwo
    move $t0, $v0
    li $t1, 0
    sll $t1, $t1, 2
    addi $t2, $fp, 260
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    li $t0, 3
    move $a0, $t0
    li $t1, 4
    move $a1, $t1
    jal _mul
    move $t0, $v0
    li $t1, 1
    sll $t1, $t1, 2
    addi $t2, $fp, 260
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    li $t0, 10
    move $a0, $t0
    li $t1, 20
    move $a1, $t1
    jal _addTwo
    move $t0, $v0
    li $t1, 2
    sll $t1, $t1, 2
    addi $t2, $fp, 260
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    li $t0, 0
    sll $t0, $t0, 2
    addi $t1, $fp, 260
    add  $t1, $t1, $t0
    lw   $t1, 0($t1)
    move $a0, $t1
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    li $t0, 1
    sll $t0, $t0, 2
    addi $t1, $fp, 260
    add  $t1, $t1, $t0
    lw   $t1, 0($t1)
    move $a0, $t1
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    li $t0, 2
    sll $t0, $t0, 2
    addi $t1, $fp, 260
    add  $t1, $t1, $t0
    lw   $t1, 0($t1)
    move $a0, $t1
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # array int big[10] at fp+272
    # int i
    li $t0, 0
    sw $t0, 256($fp)

_for_start_6:
    lw $t0, 256($fp)
    li $t1, 10
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_6
    lw $t0, 256($fp)
    li $t1, 3
    mul $t0, $t0, $t1
    lw $t1, 256($fp)
    sll $t1, $t1, 2
    addi $t2, $fp, 272
    add  $t2, $t2, $t1
    sw   $t0, 0($t2)
    lw $t0, 256($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 256($fp)
    j _for_start_6
_for_end_6:

    # int big_sum
    li $t0, 0
    sw $t0, 312($fp)
    # int i
    li $t0, 0
    sw $t0, 256($fp)

_for_start_7:
    lw $t0, 256($fp)
    li $t1, 10
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_7
    lw $t0, 312($fp)
    lw $t1, 256($fp)
    sll $t1, $t1, 2
    addi $t2, $fp, 272
    add  $t2, $t2, $t1
    lw   $t2, 0($t2)
    add $t0, $t0, $t2
    sw $t0, 312($fp)
    lw $t0, 256($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 256($fp)
    j _for_start_7
_for_end_7:

    lw $t0, 312($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # struct Point p (local)
    li $t0, 10
    # field assign p.x
    sw   $t0, 316($fp)
    li $t0, 20
    # field assign p.y
    sw   $t0, 320($fp)
    # field access p.x
    lw   $t0, 316($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # field access p.y
    lw   $t0, 320($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int pt_sum
    # field access p.x
    lw   $t0, 316($fp)
    # field access p.y
    lw   $t1, 320($fp)
    add $t0, $t0, $t1
    sw $t0, 324($fp)
    lw $t0, 324($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # struct Rect r (local)
    li $t0, 100
    # field assign r.width
    sw   $t0, 328($fp)
    li $t0, 200
    # field assign r.height
    sw   $t0, 332($fp)
    # field access r.width
    lw   $t0, 328($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # field access r.height
    lw   $t0, 332($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int area
    # field access r.width
    lw   $t0, 328($fp)
    # field access r.height
    lw   $t1, 332($fp)
    mul $t0, $t0, $t1
    sw $t0, 336($fp)
    lw $t0, 336($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int farg
    # field access p.x
    lw   $t0, 316($fp)
    move $a0, $t0
    # field access p.y
    lw   $t1, 320($fp)
    move $a1, $t1
    jal _addTwo
    move $t0, $v0
    sw $t0, 340($fp)
    lw $t0, 340($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # field access p.y
    lw   $t0, 320($fp)
    li $t1, 5
    add $t0, $t0, $t1
    # field assign p.x
    sw   $t0, 316($fp)
    # field access p.x
    lw   $t0, 316($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # struct Point lp (local)
    li $t0, 0
    # field assign lp.x
    sw   $t0, 344($fp)
    li $t0, 5
    # field assign lp.y
    sw   $t0, 348($fp)

_while_start_8:
    # field access lp.x
    lw   $t0, 344($fp)
    # field access lp.y
    lw   $t1, 348($fp)
    slt $t0, $t0, $t1
    beq $t0, $zero, _while_end_8
    # field access lp.x
    lw   $t0, 344($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # field access lp.x
    lw   $t0, 344($fp)
    li $t1, 1
    add $t0, $t0, $t1
    # field assign lp.x
    sw   $t0, 344($fp)
    j _while_start_8
_while_end_8:

    # struct Point fp (local)
    li $t0, 0
    # field assign fp.x
    sw   $t0, 352($fp)
    li $t0, 10
    # field assign fp.y
    sw   $t0, 356($fp)
    # int i
    li $t0, 0
    sw $t0, 256($fp)

_for_start_9:
    lw $t0, 256($fp)
    li $t1, 4
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_9
    # field access fp.x
    lw   $t0, 352($fp)
    # field access fp.y
    lw   $t1, 356($fp)
    add $t0, $t0, $t1
    # field assign fp.x
    sw   $t0, 352($fp)
    lw $t0, 256($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 256($fp)
    j _for_start_9
_for_end_9:

    # field access fp.x
    lw   $t0, 352($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # struct Point sp (local)
    li $t0, 2
    # field assign sp.x
    sw   $t0, 360($fp)
    li $t0, 0
    # field assign sp.y
    sw   $t0, 364($fp)
    # int wi
    li $t0, 1
    sw $t0, 368($fp)

_while_start_10:
    lw $t0, 368($fp)
    li $t1, 5
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _while_end_10
    lw $t0, 368($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 368($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 368($fp)
    j _while_start_10
_while_end_10:

    # int acc
    li $t0, 0
    sw $t0, 372($fp)
    # int wj
    li $t0, 1
    sw $t0, 376($fp)

_while_start_11:
    lw $t0, 376($fp)
    li $t1, 5
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _while_end_11
    lw $t0, 372($fp)
    lw $t1, 376($fp)
    add $t0, $t0, $t1
    sw $t0, 372($fp)
    lw $t0, 376($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 376($fp)
    j _while_start_11
_while_end_11:

    lw $t0, 372($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int wk
    li $t0, 10
    sw $t0, 380($fp)

_while_start_12:
    lw $t0, 380($fp)
    li $t1, 10
    xor  $t0, $t0, $t1
    sltiu $t0, $t0, 1
    beq $t0, $zero, _while_end_12
    lw $t0, 380($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 380($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 380($fp)
    j _while_start_12
_while_end_12:

    # int wm
    li $t0, 3
    sw $t0, 384($fp)

_while_start_13:
    lw $t0, 384($fp)
    li $t1, 0
    xor  $t0, $t0, $t1
    sltu $t0, $zero, $t0
    beq $t0, $zero, _while_end_13
    lw $t0, 384($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 384($fp)
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 384($fp)
    j _while_start_13
_while_end_13:

    # int wn
    li $t0, 3
    sw $t0, 388($fp)

_while_start_14:
    lw $t0, 388($fp)
    li $t1, 1
    slt $t0, $t0, $t1
    xori $t0, $t0, 1
    beq $t0, $zero, _while_end_14
    lw $t0, 388($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 388($fp)
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 388($fp)
    j _while_start_14
_while_end_14:

    # int wo
    li $t0, 1
    sw $t0, 392($fp)

_while_start_15:
    lw $t0, 392($fp)
    li $t1, 3
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _while_end_15
    lw $t0, 392($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 392($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 392($fp)
    j _while_start_15
_while_end_15:

    # int ni
    li $t0, 1
    sw $t0, 396($fp)

_while_start_16:
    lw $t0, 396($fp)
    li $t1, 3
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _while_end_16
    # int nj
    li $t0, 1
    sw $t0, 400($fp)

_while_start_17:
    lw $t0, 400($fp)
    li $t1, 3
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _while_end_17
    lw $t0, 400($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 400($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 400($fp)
    j _while_start_17
_while_end_17:

    lw $t0, 396($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 396($fp)
    j _while_start_16
_while_end_16:

    # int wi2
    li $t0, 1
    sw $t0, 404($fp)

_while_start_18:
    lw $t0, 404($fp)
    li $t1, 6
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _while_end_18
    lw $t0, 404($fp)
    li $t1, 3
    xor  $t0, $t0, $t1
    sltiu $t0, $t0, 1
    beq $t0, $zero, _if_end_19
    li $t0, 300
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
_if_end_19:

    lw $t0, 404($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 404($fp)
    j _while_start_18
_while_end_18:

    # bool running
    li $t0, 1
    sw $t0, 408($fp)
    # int cnt
    li $t0, 0
    sw $t0, 412($fp)

_while_start_20:
    lw $t0, 408($fp)
    li $t1, 1
    xor  $t0, $t0, $t1
    sltiu $t0, $t0, 1
    beq $t0, $zero, _while_end_20
    lw $t0, 412($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 412($fp)
    lw $t0, 412($fp)
    li $t1, 3
    xor  $t0, $t0, $t1
    sltiu $t0, $t0, 1
    beq $t0, $zero, _if_end_21
    li $t0, 0
    sw $t0, 408($fp)
_if_end_21:

    j _while_start_20
_while_end_20:

    lw $t0, 412($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int never
    li $t0, 0
    sw $t0, 416($fp)

_while_start_22:
    lw $t0, 416($fp)
    li $t1, 999
    slt $t0, $t1, $t0
    beq $t0, $zero, _while_end_22
    j _while_start_22
_while_end_22:

    # int i
    li $t0, 0
    sw $t0, 256($fp)

_for_start_23:
    lw $t0, 256($fp)
    li $t1, 5
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_23
    lw $t0, 256($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 256($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 256($fp)
    j _for_start_23
_for_end_23:

    # int i
    li $t0, 10
    sw $t0, 256($fp)

_for_start_24:
    lw $t0, 256($fp)
    li $t1, 30
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _for_end_24
    lw $t0, 256($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 256($fp)
    li $t1, 10
    add $t0, $t0, $t1
    sw $t0, 256($fp)
    j _for_start_24
_for_end_24:

    # int even_sum
    li $t0, 0
    sw $t0, 420($fp)
    # int i
    li $t0, 0
    sw $t0, 256($fp)

_for_start_25:
    lw $t0, 256($fp)
    li $t1, 6
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_25
    lw $t0, 256($fp)
    li $t1, 2
    xor  $t0, $t0, $t1
    sltiu $t0, $t0, 1
    beq $t0, $zero, _if_end_26
    lw $t0, 420($fp)
    lw $t1, 256($fp)
    add $t0, $t0, $t1
    sw $t0, 420($fp)
_if_end_26:

    lw $t0, 256($fp)
    li $t1, 4
    xor  $t0, $t0, $t1
    sltiu $t0, $t0, 1
    beq $t0, $zero, _if_end_27
    lw $t0, 420($fp)
    lw $t1, 256($fp)
    add $t0, $t0, $t1
    sw $t0, 420($fp)
_if_end_27:

    lw $t0, 256($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 256($fp)
    j _for_start_25
_for_end_25:

    lw $t0, 420($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int i
    li $t0, 1
    sw $t0, 256($fp)

_for_start_28:
    lw $t0, 256($fp)
    li $t1, 2
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _for_end_28
    # int j
    li $t0, 1
    sw $t0, 424($fp)

_for_start_29:
    lw $t0, 424($fp)
    li $t1, 2
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _for_end_29
    # int prod
    lw $t0, 256($fp)
    lw $t1, 424($fp)
    mul $t0, $t0, $t1
    sw $t0, 428($fp)
    lw $t0, 428($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 424($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 424($fp)
    j _for_start_29
_for_end_29:

    lw $t0, 256($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 256($fp)
    j _for_start_28
_for_end_28:

    # int lsum1
    li $t0, 0
    sw $t0, 432($fp)
    # int i
    li $t0, 0
    sw $t0, 256($fp)

_for_start_30:
    lw $t0, 256($fp)
    li $t1, 5
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_30
    lw $t0, 432($fp)
    lw $t1, 256($fp)
    add $t0, $t0, $t1
    sw $t0, 432($fp)
    lw $t0, 256($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 256($fp)
    j _for_start_30
_for_end_30:

    lw $t0, 432($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int lsum2
    li $t0, 0
    sw $t0, 436($fp)
    # int i
    li $t0, 0
    sw $t0, 256($fp)

_for_start_31:
    lw $t0, 256($fp)
    li $t1, 5
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_31
    lw $t0, 436($fp)
    lw $t1, 256($fp)
    li $t2, 2
    mul $t1, $t1, $t2
    add $t0, $t0, $t1
    sw $t0, 436($fp)
    lw $t0, 256($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 256($fp)
    j _for_start_31
_for_end_31:

    lw $t0, 436($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int call_acc
    li $t0, 0
    sw $t0, 440($fp)
    # int i
    li $t0, 1
    sw $t0, 256($fp)

_for_start_32:
    lw $t0, 256($fp)
    li $t1, 4
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _for_end_32
    lw $t0, 440($fp)
    lw $t1, 256($fp)
    move $a0, $t1
    lw $t2, 256($fp)
    move $a1, $t2
    jal _addTwo
    move $t1, $v0
    add $t0, $t0, $t1
    sw $t0, 440($fp)
    lw $t0, 256($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 256($fp)
    j _for_start_32
_for_end_32:

    lw $t0, 440($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int i
    li $t0, 0
    sw $t0, 256($fp)

_for_start_33:
    lw $t0, 256($fp)
    li $t1, 0
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_33
    lw $t0, 256($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 256($fp)
    j _for_start_33
_for_end_33:

    # int iv
    li $t0, 5
    sw $t0, 444($fp)
    lw $t0, 444($fp)
    li $t1, 0
    slt $t0, $t1, $t0
    beq $t0, $zero, _if_end_34
    li $t0, 10
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
_if_end_34:

    lw $t0, 444($fp)
    li $t1, 100
    slt $t0, $t1, $t0
    beq $t0, $zero, _if_end_35
    li $t0, 9999
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
_if_end_35:

    lw $t0, 444($fp)
    li $t1, 5
    xor  $t0, $t0, $t1
    sltiu $t0, $t0, 1
    beq $t0, $zero, _if_end_36
    li $t0, 20
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    j _if_else_36
_if_end_36:

    li $t0, 21
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
_if_else_36:

    lw $t0, 444($fp)
    li $t1, 99
    xor  $t0, $t0, $t1
    sltiu $t0, $t0, 1
    beq $t0, $zero, _if_end_37
    li $t0, 99
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    j _if_else_37
_if_end_37:

    li $t0, 30
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
_if_else_37:

    # int grade
    li $t0, 75
    sw $t0, 448($fp)
    lw $t0, 448($fp)
    li $t1, 90
    slt $t0, $t0, $t1
    xori $t0, $t0, 1
    beq $t0, $zero, _if_end_38
    li $t0, 4
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    j _if_else_38
_if_end_38:

    lw $t0, 448($fp)
    li $t1, 80
    slt $t0, $t0, $t1
    xori $t0, $t0, 1
    beq $t0, $zero, _if_end_39
    li $t0, 3
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    j _if_else_39
_if_end_39:

    lw $t0, 448($fp)
    li $t1, 70
    slt $t0, $t0, $t1
    xori $t0, $t0, 1
    beq $t0, $zero, _if_end_40
    li $t0, 2
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    j _if_else_40
_if_end_40:

    li $t0, 1
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
_if_else_40:

_if_else_39:

_if_else_38:

    li $t0, 0
    beq $t0, $zero, _if_end_41
    j _if_else_41
_if_end_41:

    li $t0, 888
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
_if_else_41:

    li $t0, 1
    beq $t0, $zero, _if_end_42
    li $t0, 777
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    j _if_else_42
_if_end_42:

_if_else_42:

    # int ev_acc
    li $t0, 0
    sw $t0, 452($fp)
    # int i
    li $t0, 0
    sw $t0, 256($fp)

_for_start_43:
    lw $t0, 256($fp)
    li $t1, 10
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_43
    lw $t0, 256($fp)
    li $t1, 2
    xor  $t0, $t0, $t1
    sltiu $t0, $t0, 1
    beq $t0, $zero, _if_end_44
    lw $t0, 452($fp)
    lw $t1, 256($fp)
    add $t0, $t0, $t1
    sw $t0, 452($fp)
_if_end_44:

    lw $t0, 256($fp)
    li $t1, 4
    xor  $t0, $t0, $t1
    sltiu $t0, $t0, 1
    beq $t0, $zero, _if_end_45
    lw $t0, 452($fp)
    lw $t1, 256($fp)
    add $t0, $t0, $t1
    sw $t0, 452($fp)
_if_end_45:

    lw $t0, 256($fp)
    li $t1, 6
    xor  $t0, $t0, $t1
    sltiu $t0, $t0, 1
    beq $t0, $zero, _if_end_46
    lw $t0, 452($fp)
    lw $t1, 256($fp)
    add $t0, $t0, $t1
    sw $t0, 452($fp)
_if_end_46:

    lw $t0, 256($fp)
    li $t1, 8
    xor  $t0, $t0, $t1
    sltiu $t0, $t0, 1
    beq $t0, $zero, _if_end_47
    lw $t0, 452($fp)
    lw $t1, 256($fp)
    add $t0, $t0, $t1
    sw $t0, 452($fp)
_if_end_47:

    lw $t0, 256($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 256($fp)
    j _for_start_43
_for_end_43:

    lw $t0, 452($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    li $t0, 1
    beq $t0, $zero, _if_end_48
    # int wb
    li $t0, 1
    sw $t0, 456($fp)

_while_start_49:
    lw $t0, 456($fp)
    li $t1, 3
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _while_end_49
    lw $t0, 456($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 456($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 456($fp)
    j _while_start_49
_while_end_49:

_if_end_48:

    # int sv
    li $t0, 2
    sw $t0, 460($fp)
    # int sv2
    li $t0, 99
    sw $t0, 464($fp)
    # int sw3
    li $t0, 1
    move $a0, $t0
    li $t1, 1
    move $a1, $t1
    jal _addTwo
    move $t0, $v0
    sw $t0, 468($fp)
    # bool bsw
    li $t0, 1
    sw $t0, 472($fp)
    # int sv4
    li $t0, 3
    sw $t0, 476($fp)
    # int swi
    li $t0, 1
    sw $t0, 480($fp)

_while_start_50:
    lw $t0, 480($fp)
    li $t1, 3
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _while_end_50
    lw $t0, 480($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 480($fp)
    j _while_start_50
_while_end_50:

    # int sv5
    li $t0, 5
    sw $t0, 484($fp)
    lw $t0, 484($fp)
    li $t1, 0
    slt $t0, $t1, $t0
    beq $t0, $zero, _if_end_51
_if_end_51:

    # int outer_sw
    li $t0, 1
    sw $t0, 488($fp)
    # int inner_sw
    li $t0, 2
    sw $t0, 492($fp)
    # int max_int
    li $t0, 2147483647
    sw $t0, 496($fp)
    lw $t0, 496($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int zero
    li $t0, 0
    sw $t0, 500($fp)
    lw $t0, 500($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int neg42
    li $t0, 0
    li $t1, 42
    sub $t0, $t0, $t1
    sw $t0, 504($fp)
    lw $t0, 504($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int chain
    li $t0, 1
    move $a0, $t0
    li $t1, 2
    move $a1, $t1
    jal _addTwo
    move $t0, $v0
    move $a0, $t0
    li $t1, 3
    move $a0, $t1
    li $t2, 4
    move $a1, $t2
    jal _addTwo
    move $t1, $v0
    move $a1, $t1
    jal _addTwo
    move $t0, $v0
    sw $t0, 508($fp)
    lw $t0, 508($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int cbase
    li $t0, 5
    sw $t0, 512($fp)
    # bool cc1
    lw $t0, 512($fp)
    li $t1, 5
    xor  $t0, $t0, $t1
    sltiu $t0, $t0, 1
    sw $t0, 516($fp)
    # bool cc2
    lw $t0, 512($fp)
    li $t1, 5
    xor  $t0, $t0, $t1
    sltu $t0, $zero, $t0
    sw $t0, 520($fp)
    # bool cc3
    lw $t0, 512($fp)
    li $t1, 6
    slt $t0, $t0, $t1
    sw $t0, 524($fp)
    # bool cc4
    lw $t0, 512($fp)
    li $t1, 4
    slt $t0, $t1, $t0
    sw $t0, 528($fp)
    # bool cc5
    lw $t0, 512($fp)
    li $t1, 5
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    sw $t0, 532($fp)
    # bool cc6
    lw $t0, 512($fp)
    li $t1, 5
    slt $t0, $t0, $t1
    xori $t0, $t0, 1
    sw $t0, 536($fp)
    lw $t0, 516($fp)
    bne  $t0, $zero, _print_true_12
    la   $a0, _str_false
    j    _print_bool_done_12
_print_true_12:
    la   $a0, _str_true
_print_bool_done_12:
    li   $v0, 4
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 520($fp)
    bne  $t0, $zero, _print_true_13
    la   $a0, _str_false
    j    _print_bool_done_13
_print_true_13:
    la   $a0, _str_true
_print_bool_done_13:
    li   $v0, 4
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 524($fp)
    bne  $t0, $zero, _print_true_14
    la   $a0, _str_false
    j    _print_bool_done_14
_print_true_14:
    la   $a0, _str_true
_print_bool_done_14:
    li   $v0, 4
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 528($fp)
    bne  $t0, $zero, _print_true_15
    la   $a0, _str_false
    j    _print_bool_done_15
_print_true_15:
    la   $a0, _str_true
_print_bool_done_15:
    li   $v0, 4
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 532($fp)
    bne  $t0, $zero, _print_true_16
    la   $a0, _str_false
    j    _print_bool_done_16
_print_true_16:
    la   $a0, _str_true
_print_bool_done_16:
    li   $v0, 4
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 536($fp)
    bne  $t0, $zero, _print_true_17
    la   $a0, _str_false
    j    _print_bool_done_17
_print_true_17:
    la   $a0, _str_true
_print_bool_done_17:
    li   $v0, 4
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # float ftest
    # float literal 3.14 (IEEE bits 0x4048F5C3)
    li $t0, 1078523331
    sw $t0, 540($fp)
    # bool fgt
    lw $t0, 540($fp)
    # float literal 3 (IEEE bits 0x40400000)
    li $t1, 1077936128
    mtc1 $t0, $f0
    mtc1 $t1, $f2
    c.lt.s $f2, $f0
    li $t0, 0
    bc1f _fcmp_end_18
    li $t0, 1
_fcmp_end_18:
    sw $t0, 544($fp)
    # bool flt
    lw $t0, 540($fp)
    # float literal 3 (IEEE bits 0x40400000)
    li $t1, 1077936128
    mtc1 $t0, $f0
    mtc1 $t1, $f2
    c.lt.s $f0, $f2
    li $t0, 0
    bc1f _fcmp_end_19
    li $t0, 1
_fcmp_end_19:
    sw $t0, 548($fp)
    lw $t0, 544($fp)
    bne  $t0, $zero, _print_true_20
    la   $a0, _str_false
    j    _print_bool_done_20
_print_true_20:
    la   $a0, _str_true
_print_bool_done_20:
    li   $v0, 4
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 548($fp)
    bne  $t0, $zero, _print_true_21
    la   $a0, _str_false
    j    _print_bool_done_21
_print_true_21:
    la   $a0, _str_true
_print_bool_done_21:
    li   $v0, 4
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    la  $t0, _g_gIntA
    lw  $t0, 0($t0)
    li $t1, 50
    add $t0, $t0, $t1
    la  $t1, _g_gIntA
    sw  $t0, 0($t1)
    la  $t0, _g_gIntA
    lw  $t0, 0($t0)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    la  $t0, _g_gSeed
    lw  $t0, 0($t0)
    move $a0, $t0
    li $t1, 3
    move $a1, $t1
    jal _addTwo
    move $t0, $v0
    la  $t1, _g_gSeed
    sw  $t0, 0($t1)
    la  $t0, _g_gSeed
    lw  $t0, 0($t0)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # int comment_var
    li $t0, 42
    sw $t0, 552($fp)
    lw $t0, 552($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # Declare int uninit_warn at offset 556
    # int rec_chain
    li $t0, 3
    move $a0, $t0
    jal _fact
    move $t0, $v0
    move $a0, $t0
    li $t1, 4
    move $a0, $t1
    jal _fact
    move $t1, $v0
    move $a1, $t1
    jal _maxOf
    move $t0, $v0
    sw $t0, 560($fp)
    lw $t0, 560($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall

    # Epilogue
    lw   $ra, 616($sp)
    lw   $fp, 612($sp)
    addi $sp, $sp, 620
    jr   $ra
# End _Master

# Function: lateHelper
_lateHelper:
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $fp, 4($sp)
    move $fp, $sp

    sw $a0, 0($fp)   # param 'x'
    lw $t0, 0($fp)
    li $t1, 2
    mul $t0, $t0, $t1
    move $v0, $t0

    # Epilogue
    lw   $ra, 8($sp)
    lw   $fp, 4($sp)
    addi $sp, $sp, 12
    jr   $ra
# End _lateHelper

.globl main
main:
    addi $sp, $sp, -8
    sw   $ra, 4($sp)

    # int gIntA
    li $t0, 100
    la  $t1, _g_gIntA
    sw  $t0, 0($t1)
    # int gIntB
    li $t0, 200
    la  $t1, _g_gIntB
    sw  $t0, 0($t1)
    # int gSeed
    li $t0, 7
    la  $t1, _g_gSeed
    sw  $t0, 0($t1)
    # int gStep
    li $t0, 3
    la  $t1, _g_gStep
    sw  $t0, 0($t1)
    # float gPi
    # float literal 3.14 (IEEE bits 0x4048F5C3)
    li $t0, 1078523331
    la  $t1, _g_gPi
    sw  $t0, 0($t1)
    # char gLetter
    li $t0, 65
    la  $t1, _g_gLetter
    sw  $t0, 0($t1)
    # bool gTrue
    li $t0, 1
    la  $t1, _g_gTrue
    sw  $t0, 0($t1)
    # bool gFalse
    li $t0, 0
    la  $t1, _g_gFalse
    sw  $t0, 0($t1)

    jal _Master

    lw   $ra, 4($sp)
    addi $sp, $sp, 8
    li   $v0, 10
    syscall
