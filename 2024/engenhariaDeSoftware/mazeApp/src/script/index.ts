import { Maze, MazeCells } from './maze.js';

// maze: variável global que representa o labirinto
let maze: Maze;


// Helper Functions
function coordinatesIndex(index: number) : [number, number] {
    const row: number = Math.floor(index / maze.width);
    const col: number = index % maze.width;
    return [row, col]
}


// Bind Functions
function bindHandlers(): void {
    const resizeButton = document.getElementById("resize-btn");
    if (resizeButton) {
        resizeButton.addEventListener('click', clickOnResizeButton);
    }

    const resetButton = document.getElementById("reset-btn");
    if (resetButton) {
        resetButton.addEventListener('click', clickOnResetButton);
    }

    // Select all buttons with the class 'btn-build'
    const buildButtons = document.querySelectorAll('.btn-build');
    buildButtons.forEach(button => {
        button.addEventListener('mousedown', buildButtonClick);
    });

    bindMazeEvents();
    // Stop drawing when the mouse leaves the maze diplay
    const mazeDisplay = document.getElementById('maze-display');
    mazeDisplay.addEventListener('mouseleave', (event: MouseEvent) => mazeUpLeave(event));

    document.addEventListener('contextmenu', rightClick);
}


function bindMazeEvents() : void {
    // Select all elements with class 'mazeCells'
    const mazeCells = document.querySelectorAll<HTMLDivElement>('.mazeCell');

    // Add event listeners to all maze cells with index provided by forEach
    mazeCells.forEach((mazeCell, index) => {
        // Start drawing on mousedown
        mazeCell.addEventListener('mousedown', (event: MouseEvent) => mazeCellPressed(event, index));

        // Stop drawing on mouseup
        mazeCell.addEventListener('mouseup', (event: MouseEvent) => mazeUpLeave(event));

        // Draw as the mouse moves over a cell, if buildDrawing is true
        mazeCell.addEventListener('mousemove', (event: MouseEvent) => mazeCellOver(event, index));
    });
}


// Event Handlers
function clickOnResizeButton(): void {
    const wInput = parseInt((document.getElementById("maze-width") as HTMLInputElement).value);
    const hInput = parseInt((document.getElementById("maze-height") as HTMLInputElement).value);

    // Validate inputs
    if (isNaN(wInput) || isNaN(hInput) || wInput < 1 || hInput < 1) {
        alert("Please enter valid dimensions greater than 0.");
        return;
    }

    // Call reset method on maze instance
    maze.resize(wInput, hInput);
    bindMazeEvents();
    document.body.style.cursor = 'auto';
}


function clickOnResetButton(): void {
    maze.reset();
    bindMazeEvents();
    document.body.style.cursor = 'auto';

}


function buildButtonClick(event: MouseEvent): void {
    const buttonId = (event.currentTarget as HTMLElement).id;

    switch (buttonId) {
        case 'btn-wall':
            maze.setBlock(MazeCells.WALL);
            document.body.style.cursor = "url('../../img/wallCursor.png'), auto";
            break;
        case 'btn-empty':
            maze.setBlock(MazeCells.EMPTY);
            document.body.style.cursor = "url('../../img/emptyCursor.png'), auto";
            break;
        case 'btn-start':
            maze.setBlock(MazeCells.START);
            document.body.style.cursor = "url('../../img/startCursor.png'), auto";
            break;
        case 'btn-end':
            maze.setBlock(MazeCells.END);
            document.body.style.cursor = "url('../../img/endCursor.png'), auto";
            break;
        default:
            document.body.style.cursor = 'auto';
            break;
    }

    console.log("buildBlock set to " +  maze.buildBlock);
}


function rightClick(event: MouseEvent) {
    event.preventDefault();
    document.body.style.cursor = 'auto';
    console.log("RightClick: blockBuild set NONE")
    maze.setBlock(MazeCells.NONE);
    maze.buildDrawing = false;
}


function mazeCellPressed(event: MouseEvent, index: number): void {
    if (maze.buildBlock == MazeCells.NONE) {
        console.log("Build Block is NONE; Nothing to draw!");
        return;
    }

    maze.buildDrawing = true;
    // Update the class of the clicked cell to represent a build block
    const targetCell = event.target as HTMLDivElement; 
    if (targetCell.classList.length >= 2) {
        targetCell.classList.remove(targetCell.classList[1]);
    }
    
    // update class html to fit new style
    targetCell.classList.add(maze.buildBlock.toLowerCase()); 

    // Update the maze array to reflect the change
    let [row, col] = coordinatesIndex(index);
    maze.array[row][col] = maze.buildBlock;
}


function mazeUpLeave(event: MouseEvent): void {
    maze.buildDrawing = false;

}


// Function to handle the pressing of a maze cell
function mazeCellOver(event: MouseEvent, index: number): void {
    if (maze.buildBlock == MazeCells.NONE) {
        return;
    }

    // Only continue drawing if buildDrawing is true
    if (!maze.buildDrawing) {
        return;
    }

    // Update the class of the cell as mouse moves over it
    const targetCell = event.target as HTMLDivElement;
    if (targetCell.classList.length >= 2) {
        targetCell.classList.remove(targetCell.classList[1]);
    }

    targetCell.classList.add(maze.buildBlock.toLowerCase());

    // Update the maze array
    let [row, col] = coordinatesIndex(index);
    maze.array[row][col] = maze.buildBlock;
}



// Window onload event to initialize the maze
window.onload = function(): void {
    maze = new Maze(5, 5);
    maze.draw();
    bindHandlers();
};
