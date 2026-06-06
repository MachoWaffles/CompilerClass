.data
_str_true:  .asciiz "true"
_str_false: .asciiz "false"

.text


# Function: addInts
_addInts:
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
# End _addInts

# Function: printValue
_printValue:
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
# End _printValue

# Function: Master
_Master:
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $fp, 4($sp)
    move $fp, $sp

    # int s
    li $t0, 3
    move $a0, $t0
    li $t1, 4
    move $a1, $t1
    jal _addInts
    move $t0, $v0
    sw $t0, 0($fp)
    lw $t0, 0($fp)
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    li $t0, 42
    move $a0, $t0
    jal _printValue
    move $t0, $v0

    # Epilogue
    lw   $ra, 8($sp)
    lw   $fp, 4($sp)
    addi $sp, $sp, 12
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
