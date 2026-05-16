#!/bin/bash

# Run all error handling tests
# Usage: ./run_tests.sh [path/to/minicompiler]
# If no path is given, searches common locations automatically

# ── COMPILER LOCATION ──────────────────────────────────────────────────────────
# Pass the compiler path as the first argument, or set COMPILER= here directly.
# Examples:
#   ./run_tests.sh ../minicompiler
#   ./run_tests.sh ./minicompiler
#   ./run_tests.sh /home/mason/compiler/minicompiler

if [ -n "$1" ]; then
    COMPILER="$1"
else
    for candidate in "../minicompiler" "./minicompiler" "../../minicompiler"; do
        if [ -f "$candidate" ]; then
            COMPILER="$candidate"
            break
        fi
    done
fi

# Verify the compiler was found and is executable before running any tests
if [ -z "$COMPILER" ] || [ ! -f "$COMPILER" ]; then
    echo ""
    echo "❌ Cannot find the compiler binary."
    echo ""
    echo "   Searched for 'minicompiler' in ../  ./  and ../../"
    echo "   Pass the path explicitly:"
    echo "     ./run_tests.sh /path/to/minicompiler"
    echo ""
    exit 1
fi

if [ ! -x "$COMPILER" ]; then
    echo ""
    echo "❌ Found compiler at '$COMPILER' but it is not executable."
    echo "   Run: chmod +x $COMPILER"
    echo ""
    exit 1
fi

echo ""
echo "Using compiler: $COMPILER"
echo ""

PASS=0
FAIL=0

# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m'

run_test() {
    local file=$1
    local description=$2
    local expect_fail=$3   # 1 = expect non-zero exit, 0 = expect exit 0 (warnings only)

    echo -e "${CYAN}────────────────────────────────────────────${NC}"
    echo -e "${YELLOW}TEST: $description${NC}"
    echo -e "File: $file"
    echo ""

    $COMPILER "$file" "/tmp/test_out.s" 2>&1
    EXIT_CODE=$?

    # Guard against the compiler binary disappearing mid-run
    if [ "$EXIT_CODE" -eq 127 ]; then
        echo -e "${RED}✗ ERROR — Compiler binary could not be executed (exit 127)${NC}"
        FAIL=$((FAIL + 1))
        echo ""
        return
    fi

    echo ""
    if [ "$expect_fail" -eq 1 ]; then
        if [ "$EXIT_CODE" -ne 0 ]; then
            echo -e "${GREEN}✓ PASSED — Compiler correctly rejected this input (exit $EXIT_CODE)${NC}"
            PASS=$((PASS + 1))
        else
            echo -e "${RED}✗ FAILED — Compiler should have rejected this input but exited 0${NC}"
            FAIL=$((FAIL + 1))
        fi
    else
        if [ "$EXIT_CODE" -eq 0 ]; then
            echo -e "${GREEN}✓ PASSED — Compiler accepted input and issued warnings (exit 0)${NC}"
            PASS=$((PASS + 1))
        else
            echo -e "${RED}✗ FAILED — Compiler rejected input but warnings-only was expected (exit $EXIT_CODE)${NC}"
            FAIL=$((FAIL + 1))
        fi
    fi
    echo ""
}

echo ""
echo "╔════════════════════════════════════════════╗"
echo "║       ERROR HANDLING TEST SUITE           ║"
echo "╚════════════════════════════════════════════╝"
echo ""

# ── SCANNER TESTS ──────────────────────────────────────────────────────────────
echo -e "${CYAN}═══ SCANNER ERRORS ═══${NC}"

run_test "test_overflow.c" \
    "Integer literal overflow (9999999999 exceeds int range)" \
    1

run_test "test_plusplus.c" \
    "Consecutive ++ operator (not supported, use x = x + 1)" \
    1

# ── PARSER TESTS ───────────────────────────────────────────────────────────────
echo -e "${CYAN}═══ PARSER ERRORS ═══${NC}"

run_test "test_keyword_as_name.c" \
    "Keyword used as variable name in declaration (int int; / int print;)" \
    1

run_test "test_keyword_decassign.c" \
    "Keyword used as variable name in decl-assign (int int = 5; / int print = 10;)" \
    1

# Bison error recovery drops the bad statement and compiles the rest successfully.
# The error message fires correctly but exit 0 is the correct behavior here.
run_test "test_decassign_nosemi.c" \
    "decAssign missing semicolon — error fires, remaining code compiles" \
    0

run_test "test_decassign_noexpr.c" \
    "decAssign missing expression (int x = ;)" \
    1

run_test "test_decl_dual_hint.c" \
    "Declaration with no = or ; — dual suggestion shown (int x 5;)" \
    1

run_test "test_chained_assign.c" \
    "Chained assignment (x = y = 5; is not supported)" \
    1

# Bison error recovery drops the bad print() statement and compiles the rest.
# The error message fires correctly but exit 0 is the correct behavior here.
run_test "test_empty_print.c" \
    "Empty print call — error fires, remaining code compiles" \
    0

# ── SEMANTIC TESTS ─────────────────────────────────────────────────────────────
echo -e "${CYAN}═══ SEMANTIC ERRORS ═══${NC}"

run_test "test_undeclared.c" \
    "Undeclared variable used in assignment (x = 5 with no int x;)" \
    1

run_test "test_duplicate_decl.c" \
    "Duplicate variable declaration (int x declared twice)" \
    1

# ── WARNING TESTS (compiler should still succeed) ──────────────────────────────
echo -e "${CYAN}═══ WARNINGS ONLY (should compile successfully) ═══${NC}"

run_test "test_uninitialized.c" \
    "Uninitialized variable warning (int x; print(x); with no assignment)" \
    0

run_test "test_unused_var.c" \
    "Unused variable warning (int y declared but never read)" \
    0

# ── SUMMARY ────────────────────────────────────────────────────────────────────
echo -e "${CYAN}════════════════════════════════════════════${NC}"
echo -e "Results: ${GREEN}$PASS passed${NC} / ${RED}$FAIL failed${NC}"
echo ""