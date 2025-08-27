// Calef Alesse
// Student ID: 2439923
// calesse@chapman.edu
// CPSC 350- 03
// PA02 Not So Super Mario

#include "World.h"


World::World(int* values, FileProcessor* fp, Mario* m){ // constructor 
    L = values[0];
    N = values[1];
    V = values[2];
    currentLevelIdx = 0;

    // create world of arrays 
    world = new Level*[L];
        for (int i = 0; i < L; ++i) {
            if (i == L-1){
                world[i] = new Level(values, true);
                world[i] -> populateLevel();
            } else {
                world[i] = new Level(values, false);
                world[i] -> populateLevel();
            }
        }
}

World::~World() { // destructor 
    for (int i = 0; i < L; ++i){
        delete world[i];
    }
    delete[] world;
}

void World::printWorld(FileProcessor* f){
    fp = f;

        // Write the level header
        std::string levelHeader = "==========\n";
        fp->writeFile("output.txt", levelHeader); 

        // Level number
        std::string levelNum = "Level " + std::to_string(currentLevelIdx) + " world\n";
        fp->writeFile("output.txt", levelNum); 

        // Write the level grid
        world[currentLevelIdx]->printLevel(fp);

        // Write the level separator
        std::string levelFooter = "==========\n\n";
        fp->writeFile("output.txt", levelFooter);  
}

// for each level i in world, populate level
void World::populateWorld(){
    for (int i = 0; i < L; ++i) {
        world[i]->populateLevel(); 
    }
}

// return an objects position
char World::getElementAtPosition(int row, int col){
    return world[currentLevelIdx] -> getLocation(row, col);
}

// clear cell to empty 'x'
void World::clearCell(int row, int col){
    world[currentLevelIdx] -> setCell(row, col, 'x');
}

void World::setMarioLoc(int row, int col){ 
    int currentLevel = getCurrentLevelIdx();

    // Clear the old Mario position 
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (world[currentLevel]->getLocation(i, j) == 'H' && world[currentLevel]->getLocation(i, j) != 'b') {
                world[currentLevel]->setCell(i, j, 'x');  // Clear old position, but keep boss
            }
        }
    }

    // Set Mario new position
    world[currentLevel]->setCell(row, col, 'H');

}

// increase level index 
void World::nextLevel(){
    currentLevelIdx++;
}

// check if last level 
bool World::isLastLevel(){
    return world[getCurrentLevelIdx()]->lastLevel;
}
