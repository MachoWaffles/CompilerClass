.data
_str_true:  .asciiz "true"
_str_false: .asciiz "false"

.text


# Function: Test1
_Test1:
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $fp, 4($sp)
    move $fp, $sp

    # int i
    li $t0, 0
    sw $t0, 0($fp)

_for_start_0:
    lw $t0, 0($fp)
    li $t1, 5
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_0
    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 0($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 0($fp)
    j _for_start_0
_for_end_0:


    # Epilogue
    lw   $ra, 8($sp)
    lw   $fp, 4($sp)
    addi $sp, $sp, 12
    jr   $ra
# End _Test1

# Function: Test2
_Test2:
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $fp, 4($sp)
    move $fp, $sp

    # int i
    li $t0, 0
    sw $t0, 0($fp)

_for_start_1:
    lw $t0, 0($fp)
    li $t1, 5
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _for_end_1
    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 0($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 0($fp)
    j _for_start_1
_for_end_1:


    # Epilogue
    lw   $ra, 8($sp)
    lw   $fp, 4($sp)
    addi $sp, $sp, 12
    jr   $ra
# End _Test2

# Function: Test3
_Test3:
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $fp, 4($sp)
    move $fp, $sp

    # int i
    li $t0, 0
    sw $t0, 0($fp)

_for_start_2:
    lw $t0, 0($fp)
    li $t1, 10
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_2
    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 0($fp)
    li $t1, 2
    add $t0, $t0, $t1
    sw $t0, 0($fp)
    j _for_start_2
_for_end_2:


    # Epilogue
    lw   $ra, 8($sp)
    lw   $fp, 4($sp)
    addi $sp, $sp, 12
    jr   $ra
# End _Test3

# Function: Test4
_Test4:
    addi $sp, $sp, -16
    sw   $ra, 12($sp)
    sw   $fp, 8($sp)
    move $fp, $sp

    # int i
    li $t0, 0
    sw $t0, 0($fp)

_for_start_3:
    lw $t0, 0($fp)
    li $t1, 5
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_3
    # int sq
    lw $t0, 0($fp)
    lw $t1, 0($fp)
    mul $t0, $t0, $t1
    sw $t0, 4($fp)
    lw $t0, 4($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 0($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 0($fp)
    j _for_start_3
_for_end_3:


    # Epilogue
    lw   $ra, 12($sp)
    lw   $fp, 8($sp)
    addi $sp, $sp, 16
    jr   $ra
# End _Test4

# Function: Test5
_Test5:
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $fp, 4($sp)
    move $fp, $sp

    # int j
    li $t0, 10
    sw $t0, 0($fp)
    li $t0, 10
    sw $t0, 0($fp)

_for_start_4:
    lw $t0, 0($fp)
    li $t1, 15
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_4
    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 0($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 0($fp)
    j _for_start_4
_for_end_4:


    # Epilogue
    lw   $ra, 8($sp)
    lw   $fp, 4($sp)
    addi $sp, $sp, 12
    jr   $ra
# End _Test5

# Function: Test6
_Test6:
    addi $sp, $sp, -16
    sw   $ra, 12($sp)
    sw   $fp, 8($sp)
    move $fp, $sp

    # int sum
    li $t0, 0
    sw $t0, 0($fp)
    # int i
    li $t0, 1
    sw $t0, 4($fp)

_for_start_5:
    lw $t0, 4($fp)
    li $t1, 5
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _for_end_5
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    add $t0, $t0, $t1
    sw $t0, 0($fp)
    lw $t0, 4($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 4($fp)
    j _for_start_5
_for_end_5:

    lw $t0, 0($fp)
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
# End _Test6

# Function: Test7
_Test7:
    addi $sp, $sp, -20
    sw   $ra, 16($sp)
    sw   $fp, 12($sp)
    move $fp, $sp

    # int i
    li $t0, 1
    sw $t0, 0($fp)

_for_start_6:
    lw $t0, 0($fp)
    li $t1, 3
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _for_end_6
    # int j
    li $t0, 1
    sw $t0, 4($fp)

_for_start_7:
    lw $t0, 4($fp)
    li $t1, 3
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _for_end_7
    # int product
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    mul $t0, $t0, $t1
    sw $t0, 8($fp)
    lw $t0, 8($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 4($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 4($fp)
    j _for_start_7
_for_end_7:

    lw $t0, 0($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 0($fp)
    j _for_start_6
_for_end_6:


    # Epilogue
    lw   $ra, 16($sp)
    lw   $fp, 12($sp)
    addi $sp, $sp, 20
    jr   $ra
# End _Test7

# Function: Test8
_Test8:
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $fp, 4($sp)
    move $fp, $sp

    # int i
    li $t0, 0
    sw $t0, 0($fp)

_for_start_8:
    lw $t0, 0($fp)
    li $t1, 0
    xor  $t0, $t0, $t1
    sltiu $t0, $t0, 1
    beq $t0, $zero, _for_end_8
    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 0($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 0($fp)
    j _for_start_8
_for_end_8:


    # Epilogue
    lw   $ra, 8($sp)
    lw   $fp, 4($sp)
    addi $sp, $sp, 12
    jr   $ra
# End _Test8

# Function: Test9
_Test9:
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $fp, 4($sp)
    move $fp, $sp

    # int i
    li $t0, 0
    sw $t0, 0($fp)

_for_start_9:
    lw $t0, 0($fp)
    li $t1, 5
    xor  $t0, $t0, $t1
    sltu $t0, $zero, $t0
    beq $t0, $zero, _for_end_9
    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 0($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 0($fp)
    j _for_start_9
_for_end_9:


    # Epilogue
    lw   $ra, 8($sp)
    lw   $fp, 4($sp)
    addi $sp, $sp, 12
    jr   $ra
# End _Test9

# Function: Test10
_Test10:
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $fp, 4($sp)
    move $fp, $sp

    # int i
    li $t0, 5
    sw $t0, 0($fp)

_for_start_10:
    lw $t0, 0($fp)
    li $t1, 0
    slt $t0, $t0, $t1
    xori $t0, $t0, 1
    beq $t0, $zero, _for_end_10
    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 0($fp)
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 0($fp)
    j _for_start_10
_for_end_10:


    # Epilogue
    lw   $ra, 8($sp)
    lw   $fp, 4($sp)
    addi $sp, $sp, 12
    jr   $ra
# End _Test10

# Function: Test11
_Test11:
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $fp, 4($sp)
    move $fp, $sp

    # int i
    li $t0, 4
    sw $t0, 0($fp)

_for_start_11:
    lw $t0, 0($fp)
    li $t1, 0
    slt $t0, $t1, $t0
    beq $t0, $zero, _for_end_11
    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 0($fp)
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 0($fp)
    j _for_start_11
_for_end_11:


    # Epilogue
    lw   $ra, 8($sp)
    lw   $fp, 4($sp)
    addi $sp, $sp, 12
    jr   $ra
# End _Test11

# Function: Test12
_Test12:
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $fp, 4($sp)
    move $fp, $sp

    # int i
    li $t0, 10
    sw $t0, 0($fp)

_for_start_12:
    lw $t0, 0($fp)
    li $t1, 5
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_12
    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 0($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 0($fp)
    j _for_start_12
_for_end_12:

    li $t0, 99
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
# End _Test12

# Function: Test13
_Test13:
    addi $sp, $sp, -36
    sw   $ra, 32($sp)
    sw   $fp, 28($sp)
    move $fp, $sp

    # array int arr[5] at fp+0
    # int i
    li $t0, 0
    sw $t0, 20($fp)

_for_start_13:
    lw $t0, 20($fp)
    li $t1, 5
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_13
    lw $t0, 20($fp)
    sll $t0, $t0, 2
    addi $t1, $fp, 0
    add  $t1, $t1, $t0
    lw $t0, 20($fp)
    li $t2, 2
    mul $t0, $t0, $t2
    sw   $t0, 0($t1)
    lw $t0, 20($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($fp)
    j _for_start_13
_for_end_13:

    # int i
    li $t0, 0
    sw $t0, 20($fp)

_for_start_14:
    lw $t0, 20($fp)
    li $t1, 5
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_14
    lw $t0, 20($fp)
    sll $t0, $t0, 2
    addi $t1, $fp, 0
    add  $t1, $t1, $t0
    lw   $t1, 0($t1)
    move $a0, $t1
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 20($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($fp)
    j _for_start_14
_for_end_14:


    # Epilogue
    lw   $ra, 32($sp)
    lw   $fp, 28($sp)
    addi $sp, $sp, 36
    jr   $ra
# End _Test13

# Function: add
_add:
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
# End _add

# Function: Test14
_Test14:
    addi $sp, $sp, -16
    sw   $ra, 12($sp)
    sw   $fp, 8($sp)
    move $fp, $sp

    # int i
    li $t0, 0
    sw $t0, 0($fp)

_for_start_15:
    lw $t0, 0($fp)
    li $t1, 5
    slt $t0, $t0, $t1
    beq $t0, $zero, _for_end_15
    # int result
    lw $t0, 0($fp)
    move $a0, $t0
    li $t1, 10
    move $a1, $t1
    jal _add
    move $t0, $v0
    sw $t0, 4($fp)
    lw $t0, 4($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 0($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 0($fp)
    j _for_start_15
_for_end_15:


    # Epilogue
    lw   $ra, 12($sp)
    lw   $fp, 8($sp)
    addi $sp, $sp, 16
    jr   $ra
# End _Test14

# Function: sumTo
_sumTo:
    addi $sp, $sp, -20
    sw   $ra, 16($sp)
    sw   $fp, 12($sp)
    move $fp, $sp

    sw $a0, 0($fp)   # param 'n'
    # int total
    li $t0, 0
    sw $t0, 4($fp)
    # int i
    li $t0, 1
    sw $t0, 8($fp)

_for_start_16:
    lw $t0, 8($fp)
    lw $t1, 0($fp)
    slt $t0, $t1, $t0
    xori $t0, $t0, 1
    beq $t0, $zero, _for_end_16
    lw $t0, 4($fp)
    lw $t1, 8($fp)
    add $t0, $t0, $t1
    sw $t0, 4($fp)
    lw $t0, 8($fp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 8($fp)
    j _for_start_16
_for_end_16:

    lw $t0, 4($fp)
    move $v0, $t0

    # Epilogue
    lw   $ra, 16($sp)
    lw   $fp, 12($sp)
    addi $sp, $sp, 20
    jr   $ra
# End _sumTo

# Function: Test15
_Test15:
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $fp, 4($sp)
    move $fp, $sp

    # int s
    li $t0, 5
    move $a0, $t0
    jal _sumTo
    move $t0, $v0
    sw $t0, 0($fp)
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
# End _Test15

# Function: Master
_Master:
    addi $sp, $sp, -8
    sw   $ra, 4($sp)
    sw   $fp, 0($sp)
    move $fp, $sp

    jal _Test1
    move $t0, $v0
    jal _Test2
    move $t0, $v0
    jal _Test3
    move $t0, $v0
    jal _Test4
    move $t0, $v0
    jal _Test5
    move $t0, $v0
    jal _Test6
    move $t0, $v0
    jal _Test7
    move $t0, $v0
    jal _Test8
    move $t0, $v0
    jal _Test9
    move $t0, $v0
    jal _Test10
    move $t0, $v0
    jal _Test11
    move $t0, $v0
    jal _Test12
    move $t0, $v0
    jal _Test13
    move $t0, $v0
    jal _Test14
    move $t0, $v0
    jal _Test15
    move $t0, $v0

    # Epilogue
    lw   $ra, 4($sp)
    lw   $fp, 0($sp)
    addi $sp, $sp, 8
    jr   $ra
# End _Master

.globl main
main:
    addi $sp, $sp, -400


    jal _Master

    addi $sp, $sp, 400
    li   $v0, 10
    syscall
