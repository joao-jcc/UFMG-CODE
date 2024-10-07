import { unHash, hash } from './algorithm.js';

export enum MazeCells {
    WALL = 'wall',
    EMPTY = 'empty',
    START = 'start',
    END = 'end',
    FRONTIER = 'frontier',
    EXPLORED = 'explored',
    NONE = 'none',
}

export class Maze {
    width: number;
    height: number;
    array: MazeCells[];

    start: number;
    end: number;

    buildBlock: MazeCells;
    buildDrawing: boolean

    constructor(width: number, height: number) {
        this.width = width;
        this.height = height;

        this.init();
    }


    resize(width: number, height: number) : void {
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


    buildArray(): void {
        for (let i=0; i < this.width * this.height; ++i) {
            this.array.push(Math.random() > 0.2 ? MazeCells.EMPTY : MazeCells.WALL);
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

        this.start = hash(xStart, yStart, this.width);
        this.end = hash(xEnd, yEnd, this.width);
        this.array[this.start] = MazeCells.START;
        this.array[this.end] = MazeCells.END;
    }

   
    draw(): void {
        let mazeDisplay = document.getElementById("maze-display");
        
        if (mazeDisplay) {
            // Limpa html em mazeDisplay
            mazeDisplay.innerHTML = '';
            mazeDisplay.style.gridTemplateColumns = `repeat(${this.width}, 1fr)`;
            mazeDisplay.style.gridTemplateRows = `repeat(${this.height}, 1fr)`;

            for (let i=0; i < this.width*this.height; ++i) {
                let div = document.createElement("div");

                if (this.array[i] === MazeCells.WALL) {
                    div.classList.add("mazeCell", "wall");
                } 
                else if (this.array[i] === MazeCells.EMPTY) {
                    div.classList.add("mazeCell", "empty");
                }
                else if (this.array[i] === MazeCells.START) {
                    div.classList.add("mazeCell", "start");
                }
                else if (this.array[i] === MazeCells.END) {
                    div.classList.add("mazeCell", "end");
                }

                mazeDisplay.appendChild(div);
            }
        }
    }

    // SETTERS e GETTERS
    setBlock(buildBlock: MazeCells) : void {
        this.buildBlock = buildBlock;
    }


    // Eventos e Binds
    bindHandlers(): void {
        // Seleciona todas as células (divs) do labirinto
        const mazeCells = document.querySelectorAll<HTMLDivElement>('.mazeCell');

        // Adiciona eventos para todas as células
        mazeCells.forEach((mazeCell, index) => {
            // Inicia desenho em mousedown
            mazeCell.addEventListener('mousedown', (event: MouseEvent) => this.mazeCellPressed(event, index));

            // Para de desenhar em mouseup
            mazeCell.addEventListener('mouseup', (event: MouseEvent) => this.mazeUpLeave(event));

            // Desenha enquanto o mouse se mouve desde que flag de desenho esteja ativa
            mazeCell.addEventListener('mousemove', (event: MouseEvent) => this.mazeCellOver(event, index));
        });

        // Para de desenhar de o mouse deixa o mazeDisplay
        const mazeDisplay = document.getElementById('maze-display');
        mazeDisplay.addEventListener('mouseleave', (event: MouseEvent) => this.mazeUpLeave(event));
    }

    mazeCellPressed(event: MouseEvent, index: number): void {
        if (this.buildBlock == MazeCells.NONE) {
            console.log("Build Block is NONE; Nothing to draw!");
            return;
        }
    
        this.buildDrawing = true;
        // Update the class of the clicked cell to represent a build block
        const targetCell = event.target as HTMLDivElement; 
        if (targetCell.classList.length >= 2) {
            targetCell.classList.remove(targetCell.classList[1]);
        }
        
        // update class html to fit new style
        targetCell.classList.add(this.buildBlock.toLowerCase()); 
    
        // Atualiza o labirinto
        this.array[index] = this.buildBlock;
    }
    
    
    mazeUpLeave(event: MouseEvent): void {
        this.buildDrawing = false;
    }
    
    
    // Function to handle the pressing of a maze cell
    mazeCellOver(event: MouseEvent, index: number): void {
        if (this.buildBlock == MazeCells.NONE) {
            return;
        }
    
        // Only continue drawing if buildDrawing is true
        if (!this.buildDrawing) {
            return;
        }
    
        // Update the class of the cell as mouse moves over it
        const targetCell = event.target as HTMLDivElement;
        if (targetCell.classList.length >= 2) {
            targetCell.classList.remove(targetCell.classList[1]);
        }
    


        targetCell.classList.add(this.buildBlock.toLowerCase());
    
        // Atualiza o labirinto: array
        this.array[index] = this.buildBlock;
    }
    

}
