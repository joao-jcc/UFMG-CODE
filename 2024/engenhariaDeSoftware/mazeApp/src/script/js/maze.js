export var MazeCells;
(function (MazeCells) {
    MazeCells["WALL"] = "wall";
    MazeCells["EMPTY"] = "empty";
    MazeCells["START"] = "start";
    MazeCells["END"] = "end";
    MazeCells["NONE"] = "none";
})(MazeCells || (MazeCells = {}));
export class Maze {
    constructor(width, height) {
        this.width = width;
        this.height = height;
        this.array = [];
        this.arrayBackup = [];
        this.buildArray(true);
        this.buildBlock = MazeCells.NONE;
        this.buildDrawing = false;
    }
    // maze retorna a configuração de backup
    reset() {
        this.width = this.arrayBackup.length;
        this.height = this.arrayBackup[0].length;
        this.array = JSON.parse(JSON.stringify(this.arrayBackup)); // deepcopy da arrayBackup
        this.buildBlock = MazeCells.NONE;
        this.buildDrawing = false;
        this.draw();
    }
    resize(width, height) {
        this.width = width;
        this.height = height;
        this.array = [];
        this.buildBlock = MazeCells.NONE;
        this.buildDrawing = false;
        this.buildArray(false);
        this.draw();
    }
    buildArray(backupFlag = false) {
        let array = [];
        for (let x = 0; x < this.height; ++x) {
            let row = [];
            for (let y = 0; y < this.width; ++y) {
                row.push(Math.random() > 0.7 ? MazeCells.EMPTY : MazeCells.WALL);
            }
            array.push(row);
        }
        // Randomly choose a start and end
        let xStart = Math.floor(Math.random() * this.height);
        let yStart = Math.floor(Math.random() * this.width);
        let xEnd = xStart;
        let yEnd = yStart;
        // Ensure the end point is different from the start point
        while (xEnd === xStart && yEnd === yStart) {
            xEnd = Math.floor(Math.random() * this.height);
            yEnd = Math.floor(Math.random() * this.width);
        }
        array[xStart][yStart] = MazeCells.START;
        array[xEnd][yEnd] = MazeCells.END;
        this.array = array;
        if (backupFlag) {
            this.arrayBackup = JSON.parse(JSON.stringify(array)); // deepcopy da array
        }
    }
    // cria array html
    draw() {
        let mazeDisplay = document.getElementById("maze-display");
        if (mazeDisplay) {
            // Clear the previous maze display
            mazeDisplay.innerHTML = '';
            mazeDisplay.style.gridTemplateColumns = `repeat(${this.width}, 1fr)`;
            mazeDisplay.style.gridTemplateRows = `repeat(${this.height}, 1fr)`;
            for (let x = 0; x < this.height; ++x) {
                for (let y = 0; y < this.width; ++y) {
                    let div = document.createElement("div");
                    if (this.array[x][y] === MazeCells.WALL) {
                        div.classList.add("mazeCell", "wall");
                    }
                    else if (this.array[x][y] === MazeCells.EMPTY) {
                        div.classList.add("mazeCell", "empty");
                    }
                    else if (this.array[x][y] === MazeCells.START) {
                        div.classList.add("mazeCell", "start");
                    }
                    else if (this.array[x][y] === MazeCells.END) {
                        div.classList.add("mazeCell", "end");
                    }
                    mazeDisplay.appendChild(div);
                }
            }
        }
    }
    // SETTERS AND GETTERS
    setBlock(buildBlock) {
        this.buildBlock = buildBlock;
    }
}
