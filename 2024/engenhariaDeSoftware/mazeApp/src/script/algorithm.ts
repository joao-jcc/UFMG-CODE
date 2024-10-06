import {Maze, MazeCells} from './maze.js'

// Funções auxiliares
export function unHash(index: number, width: number): [number, number] {
    const row: number = Math.floor(index / width);
    const col: number = index % width;
    return [row, col];
}

export function Hash(row: number, col: number, width: number): number {
    return row * width + col;
}



function neighbors(position: [number, number], width: number, height: number): [number, number][] {
    const [x, y] = position;
    const neighborPositions: [number, number][] = [];

    const deltas = [
        [0, -1],  // esquerda
        [0, 1],   // direita
        [-1, 0],  // em cima
        [1, 0]    // em baixo
    ];

    for (const [dx, dy] of deltas) {
        const newX = x + dx;
        const newY = y + dy;

        // limites
        if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
            neighborPositions.push([newX, newY]);
        }
    }

    return neighborPositions;
}


export function DFS(maze: Maze): void {
    let array = maze.array;
    let start = maze.start;
    let end = maze.end;

    let stack = [start]; // Initialize stack with the start node
    let state: MazeCells[][] = Array(array.length)
        .fill(MazeCells.NONE)
        .map(() => Array(array[0].length).fill(MazeCells.NONE));

    let parents: ([number, number] | null)[][] = Array(array.length)
        .fill(null)
        .map(() => Array(array[0].length).fill(null)); // Initialize 2D array for parents

    parents[start[0]][start[1]] = null; // Start node has no parent
    state[start[0]][start[1]] = MazeCells.FRONTIER; // Mark start node as frontier

    while (stack.length > 0) {
        let current_node = stack.pop();

        const [x, y] = current_node;

        // Mark the current node as explored
        state[x][y] = MazeCells.EXPLORED;

        // If the end node is reached, print the solution
        if (x === end[0] && y === end[1]) {
            console.log("Solution was found");
            return;
        }

        // Expand the node (get neighbors)
        let neighborsList = neighbors(current_node, array[0].length, array.length);
        for (let [x, y] of neighborsList) {
            if (array[x][y] == MazeCells.EMPTY && state[x][y] == MazeCells.NONE) {
                stack.push([x, y]);
                parents[x][y] = current_node; // Set the parent of the neighbor
                state[x][y] = MazeCells.FRONTIER; // Mark the neighbor as part of the frontier
            }
        }
    }

    console.log("No solution found");
}

