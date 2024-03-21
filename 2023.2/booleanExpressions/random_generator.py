import numpy as np
import sys

MAX_SIZE = int(4.5e2)

def gerar_expressao_logica(n):
  """
  Gera uma expressão lógica de n variáveis, a partir de uma tabela verdade aleatória.

  Args:
    n: Número de variáveis.

  Returns:
    Uma string com a expressão lógica.
  """

  # Gerar a tabela verdade
  tabela_verdade = np.random.randint(2, size=(min(2**n, MAX_SIZE), n+1))

  # Gerar a expressão lógica
  expressao = ""
  cnt = 0
  for i in range(min(2**n, MAX_SIZE)):
    if tabela_verdade[i][n] == 0 or len(expressao) >= 1e6:
      continue

    for j in range(n):
      if j == n - 1:
        if tabela_verdade[i][j] == 1:
          expressao += f'{j}'
        else:
          expressao += f'~ {j}'
      else:
        if tabela_verdade[i][j] == 1:
          expressao += f'{j} & '
        else:
          expressao += f'~ {j} & '

    expressao += " | "
    
  return expressao

def gerar_valoracao_aleatoria(n):
  """
  Gera uma valoração aleatória de n variáveis.

  Args:
    n: Número de variáveis.

  Returns:
    Uma string com a valoração aleatória.
  """

  valoracao = ""
  for i in range(n):
    valoracao += str(np.random.randint(2))
  return valoracao

def gerar_valoracao_quantificada_aleatoria(n):
  """
  Gera uma valoração aleatória de n variáveis.

  Args:
    n: Número de variáveis.

  Returns:
    Uma string com a valoração aleatória.
  """

  quants = 0
  valoracao = ""
  for i in range(n):
    val = np.random.randint(4)
    if val == 0 or val == 1:
      valoracao += str(np.random.randint(2))
    elif quants < 5:
      if val == 2:
        quants += 1
        valoracao += "e"
      else:
        quants += 1
        valoracao += "a"
    else:
      valoracao += str(np.random.randint(2))

  return valoracao

def main():
  """
  Função principal.
  """

  # Receber o número de variáveis da linha de comando
  n = int(sys.argv[1])

  op = int(sys.argv[2])

  # Gerar a expressão lógica
  expressao = gerar_expressao_logica(n)

  # Gerar a valoração aleatória
  if op == 0:
    valoracao = gerar_valoracao_aleatoria(n)
  elif op == 1:
    valoracao = gerar_valoracao_quantificada_aleatoria(n)

  # Imprimir os resultados
  print(f'"{expressao[:-2].strip()}"')
  print(valoracao)

if __name__ == "__main__":
  main()
