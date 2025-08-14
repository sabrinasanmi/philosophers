#!/bin/bash

echo "🧪 Teste com 5 filósofos e limite de 7 refeições..."

# Executa o programa e salva toda a saída em philo_output_eat_limit.txt
../philo/philo 5 800 200 200 7 > philo_output_eat_limit.txt 2>&1

# Pega a última linha do log
output=$(tail -1 philo_output_eat_limit.txt)

# Verifica se algum filósofo morreu
if echo "$output" | grep -q -v "died"; then
    GREEN='\033[1;32m'
    NC='\033[0m'
    echo -e "${GREEN}[OK]${NC} Todos comeram e finalizaram normalmente."
else
    echo "[FAIL] Filósofo morreu ou comportamento inesperado."
fi

# Mostra onde está o log completo
echo "📄 Log completo salvo em philo_output_eat_limit.txt"
