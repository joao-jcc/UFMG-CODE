import { Maze } from './maze.js';

let maze; // Changed from var to let for better scoping

// Aux
function bindHandlers() {
    let resizeButton = document.getElementById("resize-button");
    resizeButton.addEventListener('click', clickOnResizeButton);
}

// Event Handlers
function clickOnResizeButton() {
    const wInput = parseInt(document.getElementById("maze-width").value); // Use const
    const hInput = parseInt(document.getElementById("maze-height").value); // Use const

    // Check if inputs are valid
    if (isNaN(wInput) || isNaN(hInput) || wInput < 1 || hInput < 1) {
        alert("Please enter valid dimensions greater than 0.");
        return;
    }

    // Call reset method on maze instance
    maze.reset(wInput, hInput);
}

// Window onload event
window.onload = function() {
    maze = new Maze(60, 40);
    maze.draw();
    bindHandlers();
};
