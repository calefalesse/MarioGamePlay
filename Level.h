// Calef Alesse
// Student ID: 2439923
// calesse@chapman.edu
// CPSC 350- 03
// PA02 Not So Super Mario

#ifndef LEVEL_H
#define LEVEL_H
#include "FileProcessor.h"

class Level{
    private:
        bool firstLevel;
        int currentLevel;
        int dimension;

        // all values from file
        int L;
        int N;
        int V;
        int coinP; 
        int emptyP;
        int goombaP;
        int koopP;
        int mushP;



    public:

        Level(int* values, bool lastLevel);
        ~Level();

        // 2D grid
        char** grid;

        bool lastLevel; // used to check for warp pipe

        // bool lastLevel; // used to check for warp pipe

        // populates each grid with character from file
        void populateLevel();
        // returns location
        char getLocation(int i, int j);
        // check if cell is 'x'
        bool isCellEmpty(int i, int j);
        // places warp pipe
        void placeWP();
        // places boss
        void placeBoss();
        // helps set warp pipe and boss
        void setCell(int i, int j, char object);
        // prints level based on population
        void printLevel(FileProcessor* fp);
    


     
    

};

#endif