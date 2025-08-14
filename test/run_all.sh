#!/bin/bash

echo "=============================="
echo "🧪 Iniciando todos os testes..."
echo "=============================="

pass=0
fail=0

run_test() {
	script=$1
	echo ""
	echo "▶️ Executando: $script"
	if bash "$script"; then
		((pass++))
	else
		((fail++))
	fi
}

run_test ./test_one_philo.sh
run_test ./test_basic.sh
run_test ./test_eat_limit.sh
run_test ./test_valgrind.sh
run_test ./test_helgrind.sh

echo ""
echo "=============================="
echo "✅ Testes finalizados"
echo "✅ Passaram: $pass"
echo "❌ Falharam: $fail"
echo "=============================="

if [ $fail -eq 0 ]; then
	exit 0
else
	exit 1
fi
