import { Maze, MazeCells } from './maze.js';
// maze: variável global que representa o labirinto
let maze;
// Helper Functions
function coordinatesIndex(index) {
    const row = Math.floor(index / maze.width);
    const col = index % maze.width;
    return [row, col];
}
// Bind Functions
function bindHandlers() {
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
    mazeDisplay.addEventListener('mouseleave', (event) => mazeUpLeave(event));
    document.addEventListener('contextmenu', rightClick);
}
function bindMazeEvents() {
    // Select all elements with class 'mazeCells'
    const mazeCells = document.querySelectorAll('.mazeCell');
    // Add event listeners to all maze cells with index provided by forEach
    mazeCells.forEach((mazeCell, index) => {
        // Start drawing on mousedown
        mazeCell.addEventListener('mousedown', (event) => mazeCellPressed(event, index));
        // Stop drawing on mouseup
        mazeCell.addEventListener('mouseup', (event) => mazeUpLeave(event));
        // Draw as the mouse moves over a cell, if buildDrawing is true
        mazeCell.addEventListener('mousemove', (event) => mazeCellOver(event, index));
    });
}
// Event Handlers
function clickOnResizeButton() {
    const wInput = parseInt(document.getElementById("maze-width").value);
    const hInput = parseInt(document.getElementById("maze-height").value);
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
function clickOnResetButton() {
    maze.reset();
    bindMazeEvents();
    document.body.style.cursor = 'auto';
}
function buildButtonClick(event) {
    const buttonId = event.currentTarget.id;
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
    console.log("buildBlock set to " + maze.buildBlock);
}
function rightClick(event) {
    event.preventDefault();
    document.body.style.cursor = 'auto';
    console.log("RightClick: blockBuild set NONE");
    maze.setBlock(MazeCells.NONE);
    maze.buildDrawing = false;
}
function mazeCellPressed(event, index) {
    if (maze.buildBlock == MazeCells.NONE) {
        console.log("Build Block is NONE; Nothing to draw!");
        return;
    }
    maze.buildDrawing = true;
    // Update the class of the clicked cell to represent a build block
    const targetCell = event.target;
    if (targetCell.classList.length >= 2) {
        targetCell.classList.remove(targetCell.classList[1]);
    }
    // update class html to fit new style
    targetCell.classList.add(maze.buildBlock.toLowerCase());
    // Update the maze array to reflect the change
    let [row, col] = coordinatesIndex(index);
    maze.array[row][col] = maze.buildBlock;
}
function mazeUpLeave(event) {
    maze.buildDrawing = false;
}
// Function to handle the pressing of a maze cell
function mazeCellOver(event, index) {
    if (maze.buildBlock == MazeCells.NONE) {
        return;
    }
    // Only continue drawing if buildDrawing is true
    if (!maze.buildDrawing) {
        return;
    }
    // Update the class of the cell as mouse moves over it
    const targetCell = event.target;
    if (targetCell.classList.length >= 2) {
        targetCell.classList.remove(targetCell.classList[1]);
    }
    targetCell.classList.add(maze.buildBlock.toLowerCase());
    // Update the maze array
    let [row, col] = coordinatesIndex(index);
    maze.array[row][col] = maze.buildBlock;
}
// Window onload event to initialize the maze
window.onload = function () {
    maze = new Maze(5, 5);
    maze.draw();
    bindHandlers();
};
