import os
import random

def gen_kn(ns, folder):
    if not os.path.exists(folder):
        os.makedirs(folder)

    # Gera grafos completos de 2 vértices até ns
    for n in ns:
        grafo = [[j for j in range(n) if j != i] for i in range(n)]
        
        file = os.path.join(folder, f"k{n}.txt")
        
        with open(file, 'w') as f:

            M = n * (n - 1) // 2  # número de arestas de grafo completo
            f.write(f"{n} {M}\n")
            
            for i in range(n):
                for j in grafo[i]:
                   f.write(f"{i} {j} {random.randint(5, 30)}\n")


if __name__ == "__main__":
    gen_kn([i for i in range(10, 21)], "kn")