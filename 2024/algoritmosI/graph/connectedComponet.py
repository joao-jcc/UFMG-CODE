# identifica a componente conexa do vértice u
def connected(u):
    frontier = [u]
    explored = []

    while len(frontier):
        node = frontier.pop()

        for neigh in grafo[node]:
            if neigh in frontier:
                print(f"Ciclo em {node}, {neigh}")
                continue

            elif neigh not in explored:
                frontier.append(neigh)
        
        explored.append(node)
    

    return explored


if __name__ == "__main__":
    grafo = {
        1: [2, 3],
        2: [1, 3, 4, 5],
        3: [1, 2, 5, 7, 8],
        4: [2, 5],
        5: [2, 3, 4, 6],
        6: [5],
        7: [3, 8],
        8: [3, 7],
        9: [10],
        10: [9],
        11: [12],
        12: [11, 13],
        13: [12]
    }

    explored = connected(4)

    print(sorted(explored))

