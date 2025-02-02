import matplotlib.pyplot as plt
import numpy as np

def read_results(path):
    dots = []
    with open(path, 'r') as file:
        lines = file.readlines()[1:]  # Ignorar cabeçalho
        for line in lines:
            parts = line.split('\t')
            label = int(parts[1])  # Número de vértices
            clock = float(parts[2]) / 10**9  # Tempo em segundos
            dots.append((label, clock))
    return sorted(dots, key=lambda dot: dot[0])

def plot(dots1, dots2, dots3, output_path):
    plt.style.use("seaborn")
    plt.figure(figsize=(10, 6))
    
    xs1, ys1 = zip(*dots1)
    xs2, ys2 = zip(*dots2)
    xs3, ys3 = zip(*dots3)
    
    plt.plot(xs1, ys1, marker='o', linestyle='-', color='b', label="Brute Force")
    plt.plot(xs2, ys2, marker='s', linestyle='-', color='r', label="Dynamic Programming")
    plt.plot(xs3, ys3, marker='^', linestyle='-', color='g', label="Greedy")
    
    plt.xscale("linear")
    plt.yscale("log")  # Escala logarítmica no eixo Y
    plt.xlabel("Número de Vértices", fontsize=12)
    plt.ylabel("Tempo (s)", fontsize=12)
    plt.title("Tempo de execução do TSP", fontsize=16)
    
    # Configuração de ticks para maior discriminação
    plt.yticks([10**-3, 10**-2, 10**-1, 10**0, 10**1])
    
    plt.grid(True, which="both", linestyle='--', alpha=0.7)
    plt.legend()
    plt.savefig(output_path)
    plt.close()

def main(input_path1, input_path2, input_path3, output_path):
    dots1 = read_results(input_path1)
    dots2 = read_results(input_path2)
    dots3 = read_results(input_path3)
    plot(dots1, dots2, dots3, output_path)

if __name__ == "__main__":
    main("results_brute.txt", "results_dynamic.txt", "results_greedy.txt", "comparison_tsp.png")
