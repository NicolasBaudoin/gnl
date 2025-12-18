#!/bin/bash
# test_gnl.sh - Script tout-en-un

# Couleurs
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

# Compteurs
PASS=0
FAIL=0
TOTAL=0

# Fonction d'affichage
print_test() {
    local result=$1
    local test_name=$2
    ((TOTAL++))

    if [ $result -eq 0 ]; then
        echo -e "${GREEN}✅ PASS${NC}: $test_name"
        ((PASS++))
    else
        echo -e "${RED}❌ FAIL${NC}: $test_name"
        ((FAIL++))
    fi
}

# Header
echo -e "${BLUE}================================${NC}"
echo -e "${BLUE}      GNL TESTER v1.0${NC}"
echo -e "${BLUE}================================${NC}\n"

# ========================================
# COMPILATION
# ========================================
echo -e "${YELLOW}🔨 Compilation...${NC}"

BUFFER_SIZE=42
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=$BUFFER_SIZE \
    get_next_line.c get_next_line_utils.c tests/main.c \
    -o gnl_test 2> compile_errors.txt

if [ $? -ne 0 ]; then
    echo -e "${RED}❌ Compilation FAILED!${NC}"
    cat compile_errors.txt
    rm compile_errors.txt
    exit 1
fi

echo -e "${GREEN}✅ Compilation successful (BUFFER_SIZE=$BUFFER_SIZE)${NC}\n"
rm compile_errors.txt

# Créer dossier de tests
mkdir -p test_files

# ========================================
# TEST 1: Fichier simple (1 ligne)
# ========================================
echo -e "${BLUE}--- Test 1: Single line ---${NC}"
echo "Hello, World!" > test_files/test1.txt

./gnl_test test_files/test1.txt > test_files/output1.txt 2>&1

if grep -q "Hello, World!" test_files/output1.txt && \
   grep -q "Total lines read: 1" test_files/output1.txt; then
    print_test 0 "Single line"
else
    print_test 1 "Single line"
    echo -e "${RED}Expected: 1 line with 'Hello, World!'${NC}"
    echo -e "${RED}Got:${NC}"
    cat test_files/output1.txt
fi

# ========================================
# TEST 2: Multiple lignes
# ========================================
echo -e "\n${BLUE}--- Test 2: Multiple lines ---${NC}"
cat > test_files/test2.txt << EOF
Line 1
Line 2
Line 3
EOF

./gnl_test test_files/test2.txt > test_files/output2.txt 2>&1

if grep -q "Total lines read: 3" test_files/output2.txt; then
    print_test 0 "Multiple lines (3 lines)"
else
    print_test 1 "Multiple lines (3 lines)"
    cat test_files/output2.txt
fi

# ========================================
# TEST 3: Fichier vide
# ========================================
echo -e "\n${BLUE}--- Test 3: Empty file ---${NC}"
touch test_files/test3.txt

./gnl_test test_files/test3.txt > test_files/output3.txt 2>&1

if grep -q "Total lines read: 0" test_files/output3.txt; then
    print_test 0 "Empty file"
else
    print_test 1 "Empty file"
    cat test_files/output3.txt
fi

# ========================================
# TEST 4: Ligne très longue (> BUFFER_SIZE)
# ========================================
echo -e "\n${BLUE}--- Test 4: Long line ---${NC}"
python3 -c "print('A' * 10000)" > test_files/test4.txt

./gnl_test test_files/test4.txt > test_files/output4.txt 2>&1

LINE_COUNT=$(grep -o "Total lines read: [0-9]*" test_files/output4.txt | grep -o "[0-9]*")
if [ "$LINE_COUNT" = "1" ]; then
    print_test 0 "Long line (10000 chars)"
else
    print_test 1 "Long line (10000 chars) - Got $LINE_COUNT lines instead of 1"
fi

# ========================================
# TEST 5: Pas de \n à la fin
# ========================================
echo -e "\n${BLUE}--- Test 5: No newline at EOF ---${NC}"
echo -n "No newline at end" > test_files/test5.txt

./gnl_test test_files/test5.txt > test_files/output5.txt 2>&1

if grep -q "No newline at end" test_files/output5.txt && \
   grep -q "Total lines read: 1" test_files/output5.txt; then
    print_test 0 "No newline at EOF"
else
    print_test 1 "No newline at EOF"
    cat test_files/output5.txt
fi

# ========================================
# TEST 6: Lignes vides
# ========================================
echo -e "\n${BLUE}--- Test 6: Empty lines ---${NC}"
cat > test_files/test6.txt << EOF
Line 1

Line 3
EOF

./gnl_test test_files/test6.txt > test_files/output6.txt 2>&1

if grep -q "Total lines read: 3" test_files/output6.txt; then
    print_test 0 "Empty lines in file"
else
    print_test 1 "Empty lines in file"
    cat test_files/output6.txt
fi

# ========================================
# TEST 7: Fichier inexistant
# ========================================
echo -e "\n${BLUE}--- Test 7: Non-existent file ---${NC}"

./gnl_test test_files/nonexistent.txt > test_files/output7.txt 2>&1

if grep -qi "error\|cannot" test_files/output7.txt; then
    print_test 0 "Non-existent file (error handled)"
else
    print_test 1 "Non-existent file (should show error)"
    cat test_files/output7.txt
fi

# ========================================
# TEST 8: FD multiple (bonus)
# ========================================
echo -e "\n${BLUE}--- Test 8: Multiple FD (if bonus) ---${NC}"
echo "File A Line 1" > test_files/testA.txt
echo "File B Line 1" > test_files/testB.txt

# Ce test nécessite un main.c adapté pour tester les FD multiples
# Pour l'instant on le skip
echo -e "${YELLOW}⚠️  SKIP: Requires special main for multiple FD${NC}"

# ========================================
# TEST 9: STDIN (bonus)
# ========================================
echo -e "\n${BLUE}--- Test 9: Reading from STDIN ---${NC}"

echo -e "STDIN Line 1\nSTDIN Line 2" | ./gnl_test /dev/stdin > test_files/output9.txt 2>&1

if grep -q "STDIN Line 1" test_files/output9.txt; then
    print_test 0 "STDIN reading"
else
    print_test 1 "STDIN reading"
    cat test_files/output9.txt
fi

# ========================================
# TEST 10: Très gros fichier (performance)
# ========================================
echo -e "\n${BLUE}--- Test 10: Big file (performance) ---${NC}"
python3 -c "for i in range(100000): print(f'Line {i}')" > test_files/big_file.txt

START=$(date +%s.%N)
./gnl_test test_files/big_file.txt > /dev/null 2>&1
END=$(date +%s.%N)

RUNTIME=$(echo "$END - $START" | bc)
echo -e "  Runtime: ${RUNTIME}s for 100k lines"

if (( $(echo "$RUNTIME < 10" | bc -l) )); then
    print_test 0 "Performance test (< 10s)"
else
    print_test 1 "Performance test (${RUNTIME}s is too slow)"
fi

# ========================================
# VALGRIND TESTS (memory leaks)
# ========================================
if command -v valgrind &> /dev/null; then
    echo -e "\n${BLUE}================================${NC}"
    echo -e "${BLUE}    VALGRIND TESTS (Leaks)${NC}"
    echo -e "${BLUE}================================${NC}\n"

    # Test 1 avec Valgrind
    echo -e "${YELLOW}🔍 Checking leaks on test1.txt...${NC}"
    valgrind --leak-check=full --error-exitcode=42 \
        --log-file=valgrind1.log ./gnl_test test_files/test1.txt > /dev/null 2>&1

    if [ $? -eq 0 ]; then
        print_test 0 "Memory leaks test 1"
    else
        print_test 1 "Memory leaks test 1 (LEAKS DETECTED!)"
        echo -e "${RED}See valgrind1.log for details${NC}"
    fi

    # Test 2 avec Valgrind
    echo -e "${YELLOW}🔍 Checking leaks on test2.txt...${NC}"
    valgrind --leak-check=full --error-exitcode=42 \
        --log-file=valgrind2.log ./gnl_test test_files/test2.txt > /dev/null 2>&1

    if [ $? -eq 0 ]; then
        print_test 0 "Memory leaks test 2"
        rm valgrind1.log valgrind2.log 2>/dev/null
    else
        print_test 1 "Memory leaks test 2 (LEAKS DETECTED!)"
        echo -e "${RED}See valgrind2.log for details${NC}"
    fi
else
    echo -e "\n${YELLOW}⚠️  Valgrind not installed - skipping memory tests${NC}"
fi

# ========================================
# RÉSUMÉ FINAL
# ========================================
echo -e "\n${BLUE}================================${NC}"
echo -e "${BLUE}        FINAL RESULTS${NC}"
echo -e "${BLUE}================================${NC}"
echo -e "  Total tests: $TOTAL"
echo -e "  ${GREEN}✅ PASS: $PASS${NC}"
echo -e "  ${RED}❌ FAIL: $FAIL${NC}"
echo -e "${BLUE}================================${NC}"

# Cleanup
rm -f gnl_test

# Garder test_files pour debug, décommente pour auto-delete:
# rm -rf test_files

# Exit code
if [ $FAIL -eq 0 ]; then
    echo -e "\n${GREEN}🎉 All tests passed! Your GNL is working correctly.${NC}\n"
    exit 0
else
    echo -e "\n${RED}💥 $FAIL test(s) failed. Check the outputs above.${NC}\n"
    exit 1
fi