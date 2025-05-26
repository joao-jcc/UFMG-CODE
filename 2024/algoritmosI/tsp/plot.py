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


def plot(data, title="Brute Force", xlabel="X", ylabel="Y", style="seaborn"):
    dots_b = data["brute"]
    dots_r = data["dynamic"]  # Corrigido de "dyanmic" para "dynamic"
    dots_g = data["greedy"]   # Corrigido de "dits_g" para "dots_g"

    # Configuração do estilo do gráfico
    plt.style.use(style)
    
    # Extração dos valores de X e Y
    xs_b, ys_b = zip(*dots_b)
    xs_r, ys_r = zip(*dots_r)
    xs_g, ys_g = zip(*dots_g)

    # Criação do gráfico
    plt.figure(figsize=(10, 6))  # Tamanho do gráfico
    plt.plot(xs_b, ys_b, marker='o', linestyle='-', color='b', label="Brute Force")
    plt.plot(xs_r, ys_r, marker='s', linestyle='--', color='r', label="Dynamic Programming")
    plt.plot(xs_g, ys_g, marker='^', linestyle='-.', color='g', label="Greedy Algorithm")

    # Títulos e rótulos
    plt.title(title, fontsize=16)
    plt.xlabel(xlabel, fontsize=12)
    plt.ylabel(ylabel, fontsize=12)

    # Escala logarítmica no eixo Y
    plt.yscale("log")
    
    # Grade para facilitar a leitura
    plt.grid(True, linestyle='--', alpha=0.7)
    
    # Exibição da legenda
    plt.legend()
    
    # Salvar e mostrar o gráfico
    plt.savefig("exp_comparison_plot.png")
    plt.show()



# Leitura dos dados dos três métodos
dots = {
    "brute": read_results("brute_results.txt"),
    "dynamic": read_results("dynamic_results.txt"),
    "greedy": read_results("greedy_results.txt")
}

# Plotagem das três curvas
plot(dots, title="Comparação de Algoritmos para o TSP", xlabel="Número de Vértices", ylabel="Tempo (ms)")
