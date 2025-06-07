#!/bin/bash

echo "🧪 Teste com 5 filósofos e limite de 7 refeições..."
output=$(./philo/philo 5 800 200 200 7 | tail -1)

if echo "$output" | grep -q -v "died"; then
	GREEN='\033[1;32m'
	NC='\033[0m'
	echo -e "${GREEN}[OK]${NC} Todos comeram e finalizaram normalmente."
else
	echo "[FAIL] Filósofo morreu ou comportamento inesperado."
fi
