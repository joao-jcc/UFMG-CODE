#!/bin/bash

# Caminho para a pasta de trabalho
WORKDIR="$HOME/Desktop/UFMG-CODE/2024/algoritmosI/tp1"

# Caminho para o executável
BIN_DIR="$WORKDIR/bin"

# Caminho para o script Python
PYTHON_SCRIPT="$WORKDIR/correctness.py"

# Navega para o diretório de trabalho
cd "$WORKDIR" || { echo "Erro: Diretório não encontrado"; exit 1; }

# Loop para executar os casos de teste do 01 ao 08
for i in {01..08}; do
    # Execute o programa a partir da pasta bin
    "$BIN_DIR/tp1" < "tests/inputs/testCase0${i}.txt" > "outs/${i}.txt"
    echo "Test case ${i} executed."
done

echo "All test cases executed."

# Executa o script Python para verificação
echo "Executando o script de correção..."
python3 "$PYTHON_SCRIPT"

# echo "All done."
