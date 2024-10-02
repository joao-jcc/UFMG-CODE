export class Maze {

    constructor(width, height) {
        this.width = width;
        this.height = height;
        this.array = []
        this.buildArray();
    }


    reset(width, height) {
        // Update the width and height
        this.width = width;
        this.height = height;
        
        // Rebuild the maze array
        this.buildArray();

        // Optionally redraw the maze if needed
        this.draw();
    }


    buildArray() {
        let array = []
        for (let x=0; x < this.height; ++x) {
            
            let row = []
            for (let y=0; y < this.width; ++y) {
                row.push(Math.random() > 0.7 ? 1 : 0)
            }
    
            array.push(row)
        }
        
        this.array = array
    }




    draw() {   
        let mazeDisplay = document.getElementById("maze-display")
        // Clear the previous maze display
        mazeDisplay.innerHTML = '';
        
        mazeDisplay.style.gridTemplateColumns = `repeat(${this.width}, 1fr)`;
        mazeDisplay.style.gridTemplateRows = `repeat(${this.height}, 1fr)`;
    
        for (let x=0; x < this.height; ++x) {
    
            for (let y=0; y < this.width; ++y) {
                let div = document.createElement("div");
    
                if (this.array[x][y] === 1) {
                    div.classList.add("mazeCell", "wall")
                } else {
                    div.classList.add("mazeCell", "empty")
                }
    
                mazeDisplay.appendChild(div)
            }
    
        }
    }

}