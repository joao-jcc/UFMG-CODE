.data

##### R1 START MODIFIQUE AQUI START #####
#
# Este espaço é para você definir as suas constantes e vetores auxiliares.
#

vetor: .word 1 2 3 4 5 6 7 8 9 10


##### R1 END MODIFIQUE AQUI END #####

.text
        add s0, zero, zero #Quantidade de testes em que seu programa passou
        la a0, vetor
        addi a1, zero, 10
        addi a2, zero, 2
        jal ra, multiplos
        addi t0, zero, 5
        bne a0,t0,teste2
        addi s0,s0,1
teste2: la a0, vetor
        addi a1, zero, 10
        addi a2, zero, 3
        jal ra, multiplos
        addi t0, zero, 3
        bne a0,t0, FIM
        addi s0,s0,1
        beq zero,zero,FIM

##### R2 START MODIFIQUE AQUI START #####
multiplos:
    # Argumentos
    # a0: endereço base do vetor
    # a1: Tamanho do vetor
    # a2: Número para verificar multiplicidade

    li t0, 0    # Inicializa contador de múltiplos
    li t3, 0    # Registrador para contar as iterações do loop

loop:
    # Verifica se chegamos ao final do vetor
    bge t3, a1, end_loop

    # Número corrente no vetor carregado para registrador t1
    lw t1, 0(a0)

    # Verifica se há multilicidade: resto zero
    rem t2, t1, a2
    beq t2, zero, is_multiple

    # Próximo elemento do vetor (32 bits word)
    addi a0, a0, 4 
    addi t3, t3, 1   # Incrementa o contador de iterações
    j loop
     
is_multiple:
    # Incrementa a contagem de múltiplos
    addi t0, t0, 1
    # Próximo elemento do vetor (32 bits word)
    addi a0, a0, 4 
    addi t3, t3, 1   # Incrementa o contador de iterações
    j loop

end_loop:
    # Retorna o valor de contagem de múltiplos
    mv a0, t0
    ret

##### R2 END MODIFIQUE AQUI END #####

FIM: addi t0, s0, 0