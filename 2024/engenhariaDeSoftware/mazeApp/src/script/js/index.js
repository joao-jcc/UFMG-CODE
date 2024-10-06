import { Maze, MazeCells } from './maze.js';
// maze: variável global que representa o labirinto
let maze;
// Bind Functions
function bindHandlers() {
    const resizeButton = document.getElementById("resize-btn");
    if (resizeButton) {
        resizeButton.addEventListener('click', clickOnResizeButton);
    }
    // Select all buttons with the class 'btn-build'
    const buildButtons = document.querySelectorAll('.btn-build');
    buildButtons.forEach(button => {
        button.addEventListener('mousedown', buildButtonClick);
    });
    document.addEventListener('contextmenu', rightClick);
}
// Event Handlers
function clickOnResizeButton() {
    const wInput = parseInt(document.getElementById("maze-width").value);
    const hInput = parseInt(document.getElementById("maze-height").value);
    // Validate inputs
    if (isNaN(wInput) || isNaN(hInput) || wInput <= 1 || hInput <= 1) {
        alert("Please enter valid dimensions width>=1 and height>=1.");
        return;
    }
    maze.resize(wInput, hInput);
    document.body.style.cursor = 'auto';
}
function buildButtonClick(event) {
    const buttonId = event.currentTarget.id;
    switch (buttonId) {
        case 'btn-wall':
            maze.setBlock(MazeCells.WALL);
            document.body.style.cursor = "url('../../img/wallCursor2.png'), auto";
            break;
        case 'btn-empty':
            maze.setBlock(MazeCells.EMPTY);
            document.body.style.cursor = "url('../../img/emptyCursor2.png'), auto";
            break;
        case 'btn-start':
            maze.setBlock(MazeCells.START);
            document.body.style.cursor = "url('../../img/startCursor2.png'), auto";
            break;
        case 'btn-end':
            maze.setBlock(MazeCells.END);
            document.body.style.cursor = "url('../../img/endCursor2.png'), auto";
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
// Window onload event to initialize the maze
window.onload = function () {
    maze = new Maze(40, 30);
    bindHandlers();
};
