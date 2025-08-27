// Calef Alesse
// Student ID: 2439923
// calesse@chapman.edu
// CPSC 350- 03
// PA02 Not So Super Mario

#ifndef WORLD_H
#define WORLD_H
#include "Level.h"
#include "FileProcessor.h"
#include "Mario.h"

class World{
   
    private:
        int L; // levels
        int N; // dimensions
        int V; // initial lives
        FileProcessor* fp;
        Level** world;
        // coordinates of boss
        int bossRow;
        int bossCol;

        // Mario object
        Mario* m;
        
 
    public:
        World(int* values, FileProcessor* fp, Mario* m);
        ~World();

        // write/prints to output to file
        void printWorld(FileProcessor* f);
        char getElementAtPosition(int row, int col);
        int currentLevelIdx; 
        void populateWorld();
        void clearCell(int i, int j);
        void setMarioLoc(int i, int j);
        void nextLevel();
        bool isLastLevel();

        int getCurrentLevelIdx() const {
            return currentLevelIdx;
        }
        
};


#endif