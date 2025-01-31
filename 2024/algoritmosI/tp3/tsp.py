from itertools import permutations

def calculate_path_distance(path, graph):
    distance = 0
    for i in range(len(path) - 1):
        distance += graph[path[i]][path[i + 1]]
    distance += graph[path[-1]][path[0]]  # Retorno ao ponto inicial
    return distance

def tsp_brute_force(graph):
    nodes = list(graph.keys())
    min_distance = float('inf')
    best_path = None
    
    for perm in permutations(nodes):
        current_distance = calculate_path_distance(perm, graph)
        if current_distance < min_distance:
            min_distance = current_distance
            best_path = perm
    
    return best_path, min_distance

# Definição do grafo
nodes = ["Cyberia", "Augmented", "Quasar", "Elysium"]
graph = {
    "Cyberia": {"Augmented": 252, "Quasar": 120, "Elysium": 19},
    "Augmented": {"Cyberia": 252, "Quasar": 117, "Elysium": 27},
    "Quasar": {"Cyberia": 120, "Augmented": 117, "Elysium": 122},
    "Elysium": {"Cyberia": 19, "Augmented": 27, "Quasar": 122}
}

best_path, min_distance = tsp_brute_force(graph)
print("Melhor caminho:", best_path)
print("Menor distância:", min_distance)
