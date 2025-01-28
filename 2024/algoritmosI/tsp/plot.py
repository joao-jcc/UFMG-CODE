import matplotlib.pyplot as plt

def read_results(path):
    dots = []
    with open(path, 'r') as file:
        lines = file.readlines()
        for line in lines:
            clock, label = line.split(' ')
            label = int(label)
            clock = float(clock) / 10**6

            dots.append((label, clock))

    dots = sorted(dots, key=lambda dot : dot[0])
    return dots
import matplotlib.pyplot as plt

def plot(dots, title="Brute Force - 100x", xlabel="X", ylabel="Y", style="seaborn"):
    # Configuração do estilo do gráfico
    plt.style.use(style)
    
    # Extração dos valores de X e Y
    xs = [dot[0] for dot in dots]
    ys = [dot[1] for dot in dots]
    
    # Criação do gráfico
    plt.figure(figsize=(10, 6))  # Tamanho do gráfico
    plt.plot(xs, ys, marker='o', linestyle='-', color='b', label="Dados")
    
    # Títulos e rótulos
    plt.title(title, fontsize=16)
    plt.xlabel(xlabel, fontsize=12)
    plt.ylabel(ylabel, fontsize=12)
    
    # Grade para facilitar a leitura
    plt.grid(True, linestyle='--', alpha=0.7)
    
    # Exibição da legenda
    plt.legend()
    
    plt.savefig("exp_brute_force_repeat_50.png")

# Leitura dos dados e plotagem
dots = read_results("experiment_test_cases_brute_50.txt")
plot(dots, title="Execução do TSP com Brute Force", xlabel="Número de Vértices", ylabel="Tempo (s)")
