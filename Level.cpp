// Calef Alesse
// Student ID: 2439923
// calesse@chapman.edu
// CPSC 350- 03
// PA02 Not So Super Mario

#include "Level.h"

Level::Level(int* values, bool newlastLevel){ // constructor
    // read lines in from values array and assign to variables
    L = values[0];
    N = values[1];
    V = values[2];
    coinP = values[3];
    emptyP= values[4];
    goombaP= values[5];
    koopP= values[6];
    mushP= values[7];
    lastLevel = newlastLevel;

    // create grid 
    grid = new char*[N];
    for (int i =0; i < N; ++i){
        grid[i] = new char[N];
    }

};

Level::~Level(){ // destructor
    for (int i = 0; i < N; ++i){
        delete[] grid[i];
    }
    delete[] grid;
};

void Level::populateLevel(){
    // populate grid
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            int randNum = std::rand() % 100;

            if (randNum < coinP) {
                    grid[i][j] = 'c'; // coin
            } else if (randNum < (emptyP+coinP)) {
                    grid[i][j] = 'x'; // nothing
            } else if (randNum < (emptyP+coinP+goombaP)) {
                    grid[i][j] = 'g'; // goomba
            } else if (randNum < (emptyP+coinP+goombaP+koopP)) {
                    grid[i][j] = 'k'; // koopa
            } else {
                    grid[i][j] = 'm'; // mushroom
            }

        }
    }

        if (!lastLevel) { // place warp pipe as long as it is not the last level
            placeWP();
        }

        placeBoss();

}

char Level::getLocation(int i, int j){ // returns location coordinates
    return grid[i][j];

}

bool Level::isCellEmpty(int i, int j) { // checks to see if cell is "empty"
    return grid[i][j] == 'x';
}

void Level::setCell(int i, int j, char object) { // places an object in a cell
    grid[i][j] = object;
}

void Level::placeBoss() { // places boss on each level
    int i = rand() % N;
    int j = rand() % N;

    while (!isCellEmpty(i, j)) { // Keep finding an empty cell
        i = rand() % N;
        j = rand() % N;
    }

    setCell(i, j, 'b');

    int bossRow = i;
    int bossCol = j;

}


void Level::placeWP() { // Place a warp pipe in a random location
    int i = rand() % N;
    int j = rand() % N;

    while (!isCellEmpty(i, j) || (grid[i][j] == 'b')) { // Ensure it's empty and not on the boss
        i = rand() % N;
        j = rand() % N;
    }

    setCell(i, j, 'w'); // Place warp pipe
}

void Level::printLevel(FileProcessor* fp) {
    std::string levelContent; // To store the level's grid as a string
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            levelContent += grid[i][j];  // Add the grid character to the string
            levelContent += " ";         // Add space between characters
        }
        levelContent += "\n";  // New line after each row
    }

    // Write the grid to the output file
    fp->writeFile("output.txt", levelContent); 
}


