#!/bin/bash
# run_tests.sh — CST-405 minicompiler test runner (compile + SPIM runtime)
# Usage: ./tests2/run_tests.sh  (from project root)

COMPILER="./minicompiler"
DIR="./tests2"
ASM="./tests2/asm_out"
mkdir -p "$ASM"

GREEN='\033[0;32m'; RED='\033[0;31m'; YELLOW='\033[1;33m'
CYAN='\033[0;36m'; BOLD='\033[1m'; RESET='\033[0m'

pass=0; fail=0; epass=0; efail=0

# Expected SPIM output for each valid test (space-separated tokens)
declare -A EXPECTED
EXPECTED[t01_int_basics]="5 3 8 2 15 1 16"
EXPECTED[t02_float_basics]="3.14000010 6.28000021 4.00000000"
EXPECTED[t03_bool_basics]="true false true false"
EXPECTED[t04_char_basics]="A B C"
EXPECTED[t05_comparison_ops]="true false false true true false true false true false true false"
EXPECTED[t06_mixed_types]="7 2.71000004 true A"
EXPECTED[t07_while_basic]="0 1 2 3 4 10 8 6 4 2"
EXPECTED[t08_while_accumulator]="55 1 2 3 1 2 3"
EXPECTED[t09_for_basic]="0 1 2 3 4 0 2 4 6 8 5 4 3 2 1 0"
EXPECTED[t10_for_advanced]="15 1 2 3 2 4 6 3 6 9 99"
EXPECTED[t11_functions_basic]="7 42"
EXPECTED[t12_functions_multiparams]="10 6"
EXPECTED[t13_forward_ref]="8 15"
EXPECTED[t14_global_vars]="0 10 20 30"
EXPECTED[t15_arrays_basic]="10 20 30 40 50"
EXPECTED[t16_arrays_loops]="0 1 4 9 16 30"
EXPECTED[t17_structs_basic]="10 20 30"
EXPECTED[t18_structs_multiple]="3 4 100 200"
EXPECTED[t19_structs_in_functions]="5 12 17"
EXPECTED[t20_comments]="42"
EXPECTED[t21_scope_locals]="100 1 2 100"
EXPECTED[t22_arrays_and_functions]="0 2 4 6 8 20"
EXPECTED[t23_integration]="5 10 true A 15 0 1 2 3 4 55 7"

echo ""
echo -e "${BOLD}══════════════════════════════════════════════════════════${RESET}"
echo -e "${BOLD}   CST-405 Minicompiler — Full Test Suite (+ SPIM)        ${RESET}"
echo -e "${BOLD}══════════════════════════════════════════════════════════${RESET}"
echo ""
echo -e "${CYAN}── Valid Programs ──────────────────────────────────────────${RESET}"
echo ""

for cm in "$DIR"/t*.cm; do
    name=$(basename "$cm" .cm)
    asm="$ASM/${name}.asm"

    # Step 1: compile
    compile_out=$("$COMPILER" "$cm" "$asm" 2>&1)
    compile_ok=$?
    sem_errs=$(echo "$compile_out" | grep -c "SEMANTIC ERROR\|✗ Semantic")

    if [ $compile_ok -ne 0 ] || [ $sem_errs -gt 0 ]; then
        echo -e "  ${RED}✗ FAIL${RESET}  $name  ${RED}(compile error)${RESET}"
        echo "$compile_out" | grep -iE "error|✗" | head -2 | sed 's/^/         /'
        fail=$((fail+1))
        continue
    fi

    # Step 2: run through SPIM
    spim_out=$(spim -file "$asm" 2>&1 | grep -v "^SPIM\|^Copyright\|^All Rights\|^See\|^Loaded")
    runtime_errs=$(echo "$spim_out" | grep -c "Exception\|fault")
    actual=$(echo "$spim_out" | tr '\n' ' ' | xargs)
    expected="${EXPECTED[$name]}"

    if [ $runtime_errs -gt 0 ]; then
        echo -e "  ${RED}✗ FAIL${RESET}  $name  ${RED}(runtime error)${RESET}"
        echo "$spim_out" | grep "Exception" | head -2 | sed 's/^/         /'
        fail=$((fail+1))
    elif [ "$actual" = "$expected" ]; then
        echo -e "  ${GREEN}✓ PASS${RESET}  $name"
        pass=$((pass+1))
    else
        echo -e "  ${RED}✗ FAIL${RESET}  $name  ${RED}(wrong output)${RESET}"
        echo -e "         expected: $expected"
        echo -e "         actual:   $actual"
        fail=$((fail+1))
    fi
done

echo ""
echo -e "${CYAN}── Error Programs (must be rejected by semantic analysis) ──${RESET}"
echo ""

for cm in "$DIR"/err*.cm; do
    name=$(basename "$cm" .cm)
    out=$("$COMPILER" "$cm" "$ASM/${name}.asm" 2>&1)
    errs=$(echo "$out" | grep -c "SEMANTIC ERROR\|✗ Semantic\|No 'Master'\|not defined\|not declared")
    if [ $errs -gt 0 ]; then
        echo -e "  ${GREEN}✓ PASS${RESET}  $name  ${YELLOW}(correctly rejected)${RESET}"
        epass=$((epass+1))
    else
        echo -e "  ${RED}✗ FAIL${RESET}  $name  ${RED}(should have been rejected)${RESET}"
        efail=$((efail+1))
    fi
done

total_pass=$((pass+epass)); total_fail=$((fail+efail)); total=$((total_pass+total_fail))
echo ""
echo -e "${BOLD}══════════════════════════════════════════════════════════${RESET}"
echo -e "  Valid:   ${GREEN}$pass passed${RESET} / $(ls "$DIR"/t*.cm | wc -l)"
echo -e "  Errors:  ${GREEN}$epass passed${RESET} / $(ls "$DIR"/err*.cm | wc -l)"
echo -e "  Total:   ${BOLD}$total_pass / $total${RESET}"
if [ $total_fail -eq 0 ]; then
    echo -e "\n  ${GREEN}${BOLD}All tests passed!${RESET}"
else
    echo -e "\n  ${RED}${BOLD}$total_fail test(s) failed.${RESET}"
fi
echo -e "${BOLD}══════════════════════════════════════════════════════════${RESET}"
echo ""
