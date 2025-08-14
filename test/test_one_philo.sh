#!/bin/bash

echo "🧪 Teste com 1 filósofo (deve morrer)..."
raw_output=$(../philo/philo 1 800 200 200)

died_output=$(echo "$raw_output" | grep "died")

echo "$raw_output"

if [ -n "$died_output" ]; then
	GREEN='\033[1;32m'
	NC='\033[0m'
	echo -e "${GREEN}[OK]${NC} Filósofo morreu como esperado."
else
	echo "[FAIL] Nenhuma morte detectada — comportamento incorreto."
fi
