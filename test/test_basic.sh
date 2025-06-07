#!/bin/bash

echo "🧪 Teste básico com 5 filósofos..."
output=$(./philo/philo 5 800 200 200 2 | grep "died")

if [ -z "$output" ]; then
	GREEN='\033[1;32m'
	NC='\033[0m'
	echo -e "${GREEN}[OK]${NC} Nenhum filósofo morreu, comportamento esperado."
else
	echo "[FAIL] Um ou mais filósofos morreram."
fi
