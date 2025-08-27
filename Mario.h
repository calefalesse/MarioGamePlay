// Calef Alesse
// Student ID: 2439923
// calesse@chapman.edu
// CPSC 350- 03
// PA02 Not So Super Mario

#ifndef MARIO_H
#define MARIO_H
#include "FileProcessor.h"


class Mario{

private:
    int lives;
    int coins;
    int powerLvl;
    int enemyCount;
    // mario location
    int row, col;
    // determines if game is over
    bool isAlive;
    int L;
    int N;
    std::string moveDirection;


public:
    Mario(int* values, FileProcessor* fp); // constructor
    ~Mario(); // destructor

    void collectCoin();
    std::string move();
    void eatMushroom();
    bool combatGoomba(); // return true (win) or false (lose)
    bool combatKoopa(); 
    bool combatBoss();
    void warpPipe();
    void marioStats();
    void emptySpace();
    // void nextLevel();
    void setIsAlive(bool alive); // setter for isAlive

    
    FileProcessor* fp;


    // getter methods
    int getLives() const {
        return lives;
    }

    int getCoins() const {
        return coins;
    }

    int getPowerLvl() const {
        return powerLvl;
    }

    int getRow() const {
        return row;
    }

    int getColumn() const {
        return col;
    }

    bool getIsAlive() const {
        return isAlive;
    }

    std::string getMove() const {
        return moveDirection;
    }


};

#endif