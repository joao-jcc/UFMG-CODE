.data

##### R1 START MODIFIQUE AQUI START #####

#
# Este espaço é para você definir as suas constantes e vetores auxiliares.
#

vetor1: .word 1 2 3 4 #Primeiro vetor
vetor2: .word 1 1 1 1 #Segundo vetor

##### R1 END MODIFIQUE AQUI END #####
      
.text    

        add s0, zero, zero
        la a0, vetor1
        addi a1, zero, 4
        jal ra, media
        addi t0, zero, 2
        bne a0,t0,teste2
        addi s0,s0,1
teste2: la a0, vetor2
        addi a1, zero, 4
        jal ra, media
        addi t0, zero, 1
        bne a0,t0, FIM
        addi s0,s0,1
        beq zero,zero, FIM

##### R2 START MODIFIQUE AQUI START #####

# Esse espaço é para você escrever o código dos procedimentos. 
# Por enquanto eles estão vazios

media:
    add s1, zero, zero     # Inicializa o acumulador da soma
    add s2, zero, a1       # Salva o tamanho do vetor em s2
loop_media:
    lw t0, 0(a0)           # Carrega o próximo elemento do vetor
    addi a0, a0, 4         # Avança para o próximo elemento
    add s1, s1, t0         # Soma o elemento ao acumulador
    addi s2, s2, -1        # Decrementa o contador
    bnez s2, loop_media    # Verifica se há mais elementos no vetor
    div s1, s1, a1         # Calcula a média dividindo a soma pelo tamanho
    mv a0, s1              # armazena media em a0
    jr ra                  # Retorna para o endereço de retorno
    
variancia:
    la a0, vetor1          # Carrega o endereço inicial do vetor1
    add t1, a0, zero	   # armazena o início do vetor1 em t1
    addi a1, zero, 4       # Tamanho original do vetor em a1
    jal ra, media   	   # Chama a função de média para vetor1
    mv t2, a0              # Salva a média do vetor1 em t2
    la a0, vetor2          # Carrega o endereço inicial do vetor2
    add t3, a0, zero	   # armazena o início do vetor2 em t3
    jal ra, media   	   # Chama a função de média para vetor2
    mv t4, a0              # Salva a média do vetor2 em t4
    add s2, a1, zero	   # Tamanho temporário do vetor em s2
    add s1, zero, zero     # Inicializa o acumulador da covariância

.variancia_loop:
    lw t5, 0(t1)           # Carrega o próximo elemento do vetor1
    lw t6, 0(t3)           # Carrega o próximo elemento do vetor2
    sub t5, t5, t2         # Calcula o desvio do elemento do vetor1 em relação à média do vetor1
    sub t6, t6, t4         # Calcula o desvio do elemento do vetor2 em relação à média do vetor2
    mul t5, t5, t6         # Calcula o produto dos desvios
    add s1, s1, t5         # Acumula o produto dos desvios
    addi t1, t1, 4         # Avança para o próximo elemento do vetor1
    addi t3, t3, 4         # Avança para o próximo elemento do vetor2
    addi s2, s2, -1        # Decrementa o contador
    bnez s2, .variancia_loop   # Verifica se há mais elementos nos vetores		
    addi a1, a1, -1		   # tamanho diminuído em 1 para calcular a covariância
    div s1, s1, a1         # Calcula a covariância dividindo a soma pelo tamanho
    mv a0, s1              # Move o resultado da covariância para a0
    jr ra                  # Retorna para o endereço de retorno


##### R2 END MODIFIQUE AQUI END #####

FIM: add t0, zero, s0
