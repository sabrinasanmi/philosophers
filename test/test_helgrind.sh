#!/bin/bash

LOGFILE="helgrind_log.txt"

echo "🔍 Testando com Helgrind (vazamentos de memória)..."
valgrind --tool=helgrind --error-exitcode=1 ../philo/philo 5 800 200 200 > "$LOGFILE" 2>&1

if [ $? -eq 0 ]; then
    GREEN='\033[1;32m'
    NC='\033[0m'
    echo -e "${GREEN}[OK]${NC} Nenhum vazamento de memória detectado pelo Helgrind."
    #rm -f "$LOGFILE"
    exit 0
else
    echo "[FAIL] Vazamentos de memória detectados pelo Helgrind! Veja detalhes em $LOGFILE:"
    cat "$LOGFILE"
    exit 1
fi
