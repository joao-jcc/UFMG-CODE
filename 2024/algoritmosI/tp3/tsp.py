def tsp(graph, i, S):
    if (len(S) == 0):
        # distância da cidade i para a origem 0
        return graph[i][0]

    min_value = None
    for v in S:
        scopy = S.copy(); scopy.remove(v)
        value = tsp(graph, v, scopy) + graph[i][v]

        if min_value is None or min_value > value:
            min_value = value
    
    return min_value




if __name__ == "__main__":
    graph = [
        [0, 16, 11, 6],
        [8, 0, 13, 16],
        [4, 7, 0, 9],
        [5, 12, 2, 0]
    ]

    v = tsp(graph, 0, [1, 2, 3])
    print(v)
