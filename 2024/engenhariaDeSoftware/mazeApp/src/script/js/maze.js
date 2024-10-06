import { unHash } from './algorithm.js';
export var MazeCells;
(function (MazeCells) {
    MazeCells["WALL"] = "wall";
    MazeCells["EMPTY"] = "empty";
    MazeCells["START"] = "start";
    MazeCells["END"] = "end";
    MazeCells["FRONTIER"] = "frontier";
    MazeCells["EXPLORED"] = "explored";
    MazeCells["NONE"] = "none";
})(MazeCells || (MazeCells = {}));
export class Maze {
    constructor(width, height) {
        this.width = width;
        this.height = height;
        this.init();
    }
    resize(width, height) {
        this.width = width;
        this.height = height;
        this.init();
    }
    init() {
        this.array = [];
        this.buildBlock = MazeCells.NONE;
        this.buildDrawing = false;
        this.buildArray();
        this.draw();
        this.bindHandlers();
    }
    buildArray() {
        let array = [];
        for (let x = 0; x < this.height; ++x) {
            let row = [];
            for (let y = 0; y < this.width; ++y) {
                row.push(Math.random() > 0.7 ? MazeCells.EMPTY : MazeCells.WALL);
            }
            array.push(row);
        }
        // Posição inicial e final do labirinto escolhida aleatoriamente
        let xStart = Math.floor(Math.random() * this.height);
        let yStart = Math.floor(Math.random() * this.width);
        let xEnd = xStart;
        let yEnd = yStart;
        // Posição inicial e final devem ser diferentes
        while (xEnd === xStart && yEnd === yStart) {
            xEnd = Math.floor(Math.random() * this.height);
            yEnd = Math.floor(Math.random() * this.width);
        }
        array[xStart][yStart] = MazeCells.START;
        array[xEnd][yEnd] = MazeCells.END;
        this.array = array;
        this.start = [xStart, yStart];
        this.end = [xEnd, yEnd];
    }
    draw() {
        let mazeDisplay = document.getElementById("maze-display");
        if (mazeDisplay) {
            // Limpa html em mazeDisplay
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
    // SETTERS e GETTERS
    setBlock(buildBlock) {
        this.buildBlock = buildBlock;
    }
    // Eventos e Binds
    bindHandlers() {
        // Seleciona todas as células (divs) do labirinto
        const mazeCells = document.querySelectorAll('.mazeCell');
        // Adiciona eventos para todas as células
        mazeCells.forEach((mazeCell, index) => {
            // Inicia desenho em mousedown
            mazeCell.addEventListener('mousedown', (event) => this.mazeCellPressed(event, index));
            // Para de desenhar em mouseup
            mazeCell.addEventListener('mouseup', (event) => this.mazeUpLeave(event));
            // Desenha enquanto o mouse se mouve desde que flag de desenho esteja ativa
            mazeCell.addEventListener('mousemove', (event) => this.mazeCellOver(event, index));
        });
        // Para de desenhar de o mouse deixa o mazeDisplay
        const mazeDisplay = document.getElementById('maze-display');
        mazeDisplay.addEventListener('mouseleave', (event) => this.mazeUpLeave(event));
    }
    mazeCellPressed(event, index) {
        if (this.buildBlock == MazeCells.NONE) {
            console.log("Build Block is NONE; Nothing to draw!");
            return;
        }
        this.buildDrawing = true;
        // Update the class of the clicked cell to represent a build block
        const targetCell = event.target;
        if (targetCell.classList.length >= 2) {
            targetCell.classList.remove(targetCell.classList[1]);
        }
        // update class html to fit new style
        targetCell.classList.add(this.buildBlock.toLowerCase());
        // Update the maze array to reflect the change
        let [row, col] = unHash(index, this.width);
        this.array[row][col] = this.buildBlock;
    }
    mazeUpLeave(event) {
        this.buildDrawing = false;
    }
    // Function to handle the pressing of a maze cell
    mazeCellOver(event, index) {
        if (this.buildBlock == MazeCells.NONE) {
            return;
        }
        // Only continue drawing if buildDrawing is true
        if (!this.buildDrawing) {
            return;
        }
        // Update the class of the cell as mouse moves over it
        const targetCell = event.target;
        if (targetCell.classList.length >= 2) {
            targetCell.classList.remove(targetCell.classList[1]);
        }
        targetCell.classList.add(this.buildBlock.toLowerCase());
        // Update the maze array
        let [row, col] = unHash(index, this.width);
        this.array[row][col] = this.buildBlock;
    }
}
