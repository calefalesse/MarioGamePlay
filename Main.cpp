// Calef Alesse
// Student ID: 2439923
// calesse@chapman.edu
// CPSC 350- 03
// PA02 Not So Super Mario


#include "Mario.h"
#include "World.h"
#include "FileProcessor.h"
#include <iostream>
#include <ctime>


namespace gamePlay{

static int gamePlay(std::string inputFile, std::string outputFile){

    // Create FileProcessor object to handle input/output
    FileProcessor* fp = new FileProcessor(inputFile, outputFile);
    fp->resetFile(outputFile);

    // Read values from input file 
    int* values = fp->readFile(inputFile);

    // Create mario object 
    Mario* m = new Mario(values, fp);


    // Create the game world with values and FileProcessor
    World* w = new World(values, fp, m);

    int totalMoves = 0;

    std::string initialWorld = "Initial World";
    fp->writeFile(outputFile, initialWorld);

    // print initial world 
    w->printWorld(fp);


    std::string mStartLocation = "Mario is starting in position: (" + std::to_string(m->getRow()) + "," + std::to_string(m->getColumn()) + ")\n";
    fp->writeFile(outputFile, mStartLocation);


    // loop gameplay while Mario is alive
    while(m->getIsAlive()){

        // Mario location
        int row = m->getRow();
        int col = m->getColumn();
        int level = w->getCurrentLevelIdx();

        // Print current stats before move
        std::string messageOne = "Level " + std::to_string(level) + "\n";
        messageOne += "Mario Position: (" + std::to_string(row) + ", " + std::to_string(col) + ")\n";
        messageOne += "Power Level: " + std::to_string(m->getPowerLvl()) + "\n";
        fp->writeFile(outputFile, messageOne);


        // interaction 
        char cell = w->getElementAtPosition(row, col);
        std::string action = "";
        bool actionTaken = false;

        switch (cell) {
            case 'c': // Coin
                m->collectCoin();
                w->clearCell(row, col);
                actionTaken = true;
                break;
            case 'm': // Mushroom
                m->eatMushroom();
                w->clearCell(row, col);
                actionTaken = true;
                break;
            case 'g': // Goomba
                if (m->combatGoomba()) {
                    w->clearCell(row, col);
                    actionTaken = true;
                }
                break;
            case 'k': // Koopa
                if (m->combatKoopa()) {
                    w->clearCell(row, col);
                    actionTaken = true;
                }
                break;
            case 'b': // Boss
                {
                    bool bossWin = m->combatBoss();
                    if (bossWin && w->isLastLevel()){ 
                        std::cout << "Game over, Mario wins" << std::endl;
                        std::string message = "Congrats! Mario fought the final Boss and won the game.";
                        fp-> writeFile(outputFile, message);
                        m->setIsAlive(false);
                        actionTaken = true;
                    } else if (bossWin){
                        std::cout << "Mario beat boss, next level" << std::endl;
                        std::string message = "Mario fought the boss and advanced to next level.";
                        fp-> writeFile(outputFile, message);
                        w->nextLevel();
                        w->clearCell(row, col);
                        actionTaken = true;
                    }
                }
                break;
            case 'w': // Warp Pipe
                m->warpPipe();
                w->nextLevel();
                actionTaken = true;
                break;
            case 'x': // Empty Space
                m->emptySpace();
                actionTaken = true;
                break;

        }

        m->move();
        totalMoves++;

        // After action taken
        if (actionTaken) {
            std::string message2 = "";
            message2 += "\nLives: " + std::to_string(m->getLives()) + "\n";
            message2 += "Coins: " + std::to_string(m->getCoins()) + "\n";
            message2 += "Next move: " + m->getMove() + "\n";  // Direction for next move
            fp->writeFile(outputFile, message2);

            // Set Mario's position as 'H'
            w->setMarioLoc(row, col); 

            // Print updated state after action
            w->printWorld(fp);
        }



    
    }

        std::string endGameMessage = "Total moves: " + std::to_string(totalMoves);
        fp -> writeFile(outputFile, endGameMessage);

        // clean up 
        delete[] values;
        delete m;
        delete w;
        delete fp;

        return 0;

    }

}


int main(int argc, char* argv[]){

    // set seed to time 
    srand(time(0));

    // take file names in as arguments
    std::string inputFile = argv[1];  
    std::string outputFile = argv[2];


    gamePlay::gamePlay(inputFile, outputFile);

    return 0;
}