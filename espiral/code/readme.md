# Projeto de Mapeamento de Pontos em Espiral

Este projeto implementa um algoritmo simples para mapear um índice (i ≥ 0) de um ponto em uma espiral para coordenadas cartesianas (x, y). Ele fornece dois programas executáveis, `triangular` e `square`, para calcular essas coordenadas.

## Pré-requisitos

Certifique-se de que você tenha o compilador GCC (g++) instalado em seu sistema para a compilação do projeto.

## Compilação do Projeto

Para compilar o projeto, siga as instruções abaixo:

1. Abra um terminal e navegue até o diretório raiz do projeto.

2. Verifique se o projeto possui a seguinte estrutura de diretórios:

    ```
    - src/
    - bin/
    ```

3. Utilize o seguinte comando para compilar o projeto:

    ```bash
    make
    ```

   Isso irá compilar o projeto e gerar os executáveis `bin/triangular` e `bin/square`.

## Execução do Projeto

Para executar os programas compilados, utilize os seguintes comandos:

### Executar o programa `triangular`

```bash
./bin/triangular <point-index>
```

### Executar o programa `square`

```bash
./bin/square <point-index>
```

## Ajuda e Limpeza
### Ajuda
   Para obter ajudar sobre como executar o projeto, utilize o seguinte comando:
   ```bash
   make help
   ```

### Limpeza dos Arquivos Compilados
   Para limpar os executáveis e arquivos compilados:
   ```bash
   make clean
   ```

