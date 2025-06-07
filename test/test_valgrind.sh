#!/bin/bash

LOGFILE="valgrind_error.log"

echo "🔍 Testando com Valgrind (vazamentos de memória)..."
valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --error-exitcode=1 ./philo/philo 5 800 200 200 7 > "$LOGFILE" 2>&1

if [ $? -eq 0 ]; then
	GREEN='\033[1;32m'
	NC='\033[0m'
    echo -e "${GREEN}[OK]${NC} Nenhum vazamento de memória detectado pelo Valgrind."
    rm -f "$LOGFILE"
    exit 0
else
    echo "[FAIL] Vazamentos de memória detectados pelo Valgrind! Veja detalhes em $LOGFILE:"
    cat "$LOGFILE"
    exit 1
fi
