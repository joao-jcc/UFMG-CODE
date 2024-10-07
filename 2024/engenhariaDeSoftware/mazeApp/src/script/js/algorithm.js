import { MazeCells } from './maze.js';
// Funções auxiliares
export function unHash(index, width) {
    const row = Math.floor(index / width);
    const col = index % width;
    return [row, col];
}
export function hash(row, col, width) {
    return row * width + col;
}
function updateMazeCellClass(index, mazeCell) {
    // Select all divs inside the maze-display container
    const mazeDivs = document.querySelectorAll('#maze-display div');
    // Make sure the index is within bounds
    if (index >= 0 && index < mazeDivs.length) {
        const targetCell = mazeDivs[index];
        // Remove any existing second class (for example, keeping only the first one)
        if (targetCell.classList.length >= 2) {
            targetCell.classList.remove(targetCell.classList[1]);
        }
        // Add the new class to update the style of the cell
        targetCell.classList.add(mazeCell.toLowerCase());
    }
    else {
        console.error("Invalid index");
    }
}
function neighbors(index, width, height) {
    const [x, y] = unHash(index, width);
    const neighborPositions = [];
    const deltas = [
        [0, -1], // left
        [0, 1], // right
        [-1, 0], // up
        [1, 0] // down
    ];
    for (const [dx, dy] of deltas) {
        const newX = x + dx;
        const newY = y + dy;
        if (newX >= 0 && newX < height && newY >= 0 && newY < width) {
            neighborPositions.push(hash(newX, newY, width));
        }
    }
    return neighborPositions;
}
export function DFS(maze) {
    let array = maze.array;
    let start = maze.start;
    let end = maze.end;
    let stack = [start];
    let parents = Array(array.length).fill(null);
    while (stack.length > 0) {
        let current_node = stack.pop();
        array[current_node] = MazeCells.EXPLORED;
        if (current_node != start && current_node != end) {
            updateMazeCellClass(current_node, MazeCells.EXPLORED);
        }
        if (current_node == end) {
            console.log("Solution was found!");
            return;
        }
        let neighborsList = neighbors(current_node, maze.width, maze.height);
        for (let index of neighborsList) {
            if (array[index] != MazeCells.EXPLORED && array[index] != MazeCells.FRONTIER) {
                stack.push(index);
                parents[index] = current_node;
                array[index] = MazeCells.FRONTIER;
                if (index != start && index != end) {
                    updateMazeCellClass(index, MazeCells.FRONTIER);
                }
            }
        }
    }
    console.log("No solution found");
}
