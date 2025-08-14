#!/bin/bash

echo "🧪 Teste básico com 5 filósofos..."

# Executa o programa e salva toda a saída em philo_output.txt
../philo/philo 5 800 200 200 2 > philo_output_basic.txt 2>&1

# Verifica se algum filósofo morreu
output=$(grep "died" philo_output.txt)

if [ -z "$output" ]; then
    GREEN='\033[1;32m'
    NC='\033[0m'
    echo -e "${GREEN}[OK]${NC} Nenhum filósofo morreu, comportamento esperado."
else
    echo "[FAIL] Um ou mais filósofos morreram."
fi

# Mostra o log completo salvo
echo "📄 Log completo salvo em philo_output.txt"
