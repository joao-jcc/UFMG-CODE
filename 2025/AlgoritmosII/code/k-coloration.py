from collections import deque

def is_2_colorable(graph):
    """
    Verifica se um grafo é 2-colorível (bipartido) usando BFS.
    Retorna True e a coloração se for 2-colorível, False e None caso contrário.
    As cores são 0 e 1.
    """
    max_vertex_id = -1
    if graph:
        max_vertex_id = max(graph.keys())
        for neighbors in graph.values():
            if neighbors:
                max_vertex_id = max(max_vertex_id, max(neighbors))
    
    num_effective_vertices = max_vertex_id + 1 if max_vertex_id != -1 else 0
    colors = [-1] * num_effective_vertices

    for start_node in range(num_effective_vertices):
        if colors[start_node] == -1 and (start_node in graph or any(start_node in adj_list for adj_list in graph.values())):
            
            queue = deque()
            queue.append(start_node)
            colors[start_node] = 0

            while queue:
                u = queue.popleft()

                for v in graph.get(u, []):
                    if 0 <= v < num_effective_vertices: # Check if neighbor is within bounds
                        if colors[v] == -1:
                            colors[v] = 1 - colors[u]
                            queue.append(v)
                        elif colors[v] == colors[u]:
                            return False, None
                    else:
                        # Handle case where neighbor ID is out of expected bounds
                        # This might indicate a malformed graph input or need for different graph representation
                        pass
    return True, colors

def is_3_colorable(graph):
    """
    Verifica se um grafo é 3-colorível usando um algoritmo de backtracking.
    Retorna True e a coloração se for 3-colorível, False e None caso contrário.
    As cores são 0, 1 e 2.
    """
    max_vertex_id = -1
    if graph:
        max_vertex_id = max(graph.keys())
        for neighbors in graph.values():
            if neighbors:
                max_vertex_id = max(max_vertex_id, max(neighbors))
    
    if max_vertex_id == -1:
        return True, {}

    num_effective_vertices = max_vertex_id + 1
    colors = [-1] * num_effective_vertices
    num_colors_available = 3

    def solve_3_coloring(vertex_id):
        if vertex_id == num_effective_vertices:
            return True

        # Skip vertices that are not actual nodes in the graph (e.g., if max_vertex_id is large but graph is sparse)
        if vertex_id not in graph and not any(vertex_id in adj_list for adj_list in graph.values()):
             return solve_3_coloring(vertex_id + 1)
            
        for color in range(num_colors_available):
            is_safe = True
            for neighbor in graph.get(vertex_id, []):
                if 0 <= neighbor < num_effective_vertices and colors[neighbor] == color:
                    is_safe = False
                    break
            
            if is_safe:
                colors[vertex_id] = color
                if solve_3_coloring(vertex_id + 1):
                    return True
                colors[vertex_id] = -1 # Backtrack
        
        return False

    if solve_3_coloring(0):
        final_coloring = {i: colors[i] for i in range(num_effective_vertices) if colors[i] != -1}
        return True, final_coloring
    else:
        return False, None

# O grafo G do seu exemplo, remapeado para indexação de 0 a 5
graph_G_remapped = {
    0: [1, 3],
    1: [0, 2, 4],
    2: [1, 5],
    3: [0, 4],
    4: [1, 3, 5],
    5: [2, 4]
}

print("--- Testando o Grafo G (remapeado) ---")

# Teste de 2-Coloração
is_2_colorable_G, colors_2_G = is_2_colorable(graph_G_remapped)
if is_2_colorable_G:
    print(f"O grafo G É 2-colorível. Coloração: {colors_2_G}")
else:
    print("O grafo G NÃO é 2-colorível.")

print("\n") # Adiciona uma linha em branco para melhor leitura

# Teste de 3-Coloração
is_3_colorable_G, colors_3_G = is_3_colorable(graph_G_remapped)
if is_3_colorable_G:
    # Mapear cores de volta para os IDs originais para facilitar a leitura
    # (Opcional, mas útil para o usuário)
    original_colors_3_G = {i+1: colors_3_G[i] for i in range(len(colors_3_G))}
    print(f"O grafo G É 3-colorível. Coloração (com vértices originais 1-6): {original_colors_3_G}")
else:
    print("O grafo G NÃO é 3-colorível.")