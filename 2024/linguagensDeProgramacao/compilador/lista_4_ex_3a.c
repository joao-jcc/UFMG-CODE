#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>

int main(void) {
    char* program;
    int (*fnptr)(void);
    int a;

    // Tentar mapear 1000 bytes de memória com permissões de execução, leitura e escrita
    program = mmap(NULL, 1000, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);


    // Verificar se mmap falhou
    if (program == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    // Inserir instruções de máquina (mov eax, 0x1234 e ret)
    program[0] = 0xB8;       // mov eax, 0x1234 (opcode)
    program[1] = 0x34;       // valor 0x1234 em little-endian
    program[2] = 0x12;
    program[3] = 0x00;
    program[4] = 0x00;
    program[5] = 0xC3;       // ret (opcode)

    // Exibir bytes gerados (para debug)
    printf("Generated code:\n");
    for (int i = 0; i < 6; i++) {
        printf("%02X ", (unsigned char)program[i]);
    }
    printf("\n");

    // Executar o código gerado
    fnptr = (int (*)(void)) program;
    a = fnptr();

    // Exibir o resultado
    printf("Result = %X\n", a);

    // Liberar a memória alocada
    munmap(program, 1000);

    return 0;
}
