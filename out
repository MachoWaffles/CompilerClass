.data

.text


# Function: add
_add:
    addi $sp, $sp, -20
    sw   $ra, 16($sp)
    sw   $fp, 12($sp)
    move $fp, $sp

    sw $a0, 0($fp)   # param 'a'
    sw $a1, 4($fp)   # param 'b'
    # int result
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    add $t0, $t0, $t1
    sw $t0, 8($fp)
    lw $t0, 8($fp)
    move $v0, $t0

    # Epilogue
    lw   $ra, 16($sp)
    lw   $fp, 12($sp)
    addi $sp, $sp, 20
    jr   $ra
# End _add

# Function: scale
_scale:
    addi $sp, $sp, -16
    sw   $ra, 12($sp)
    sw   $fp, 8($sp)
    move $fp, $sp

    sw $a0, 0($fp)   # param 'x'
    # float doubled
    lw $t0, 0($fp)
    lw $t1, 0($fp)
    add $t0, $t0, $t1
    sw $t0, 4($fp)
    lw $t0, 4($fp)
    move $v0, $t0

    # Epilogue
    lw   $ra, 12($sp)
    lw   $fp, 8($sp)
    addi $sp, $sp, 16
    jr   $ra
# End _scale

# Function: describeChar
_describeChar:
    addi $sp, $sp, -20
    sw   $ra, 16($sp)
    sw   $fp, 12($sp)
    move $fp, $sp

    sw $a0, 0($fp)   # param 'c'
    sw $a1, 4($fp)   # param 'loud'
    # char code
    lw $t0, 0($fp)
    sw $t0, 8($fp)
    lw $t0, 8($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall

    # Epilogue
    lw   $ra, 16($sp)
    lw   $fp, 12($sp)
    addi $sp, $sp, 20
    jr   $ra
# End _describeChar

# Function: Master
_Master:
    addi $sp, $sp, -24
    sw   $ra, 20($sp)
    sw   $fp, 16($sp)
    move $fp, $sp

    li $t0, 0
    sw $t0, 0($sp)
    # int sum
    li $t0, 3
    move $a0, $t0
    li $t1, 4
    move $a1, $t1
    jal _add
    move $t0, $v0
    sw $t0, 0($fp)
    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    # float pi
    # float literal 3.14 (IEEE bits 0x4048F5C3)
    li $t0, 1078523331
    sw $t0, 4($fp)
    # bool flag
    li $t0, 1
    sw $t0, 8($fp)
    # char letter
    li $t0, 65
    sw $t0, 12($fp)
    lw $t0, 12($fp)
    move $a0, $t0
    lw $t1, 8($fp)
    move $a1, $t1
    jal _describeChar
    move $t0, $v0

    # Epilogue
    lw   $ra, 20($sp)
    lw   $fp, 16($sp)
    addi $sp, $sp, 24
    jr   $ra
# End _Master

.globl main
main:
    addi $sp, $sp, -400


    jal _Master

    addi $sp, $sp, 400
    li   $v0, 10
    syscall
