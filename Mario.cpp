// Calef Alesse
// Student ID: 2439923
// calesse@chapman.edu
// CPSC 350- 03
// PA02 Not So Super Mario


#include "Mario.h"
#include "FileProcessor.h"
#include <cstdlib>
#include <string>


Mario::Mario(int* values, FileProcessor* fp){ // constructor
    coins = 0;
    powerLvl = 0;
    lives = values[2];  // Initialize with starting lives
    enemyCount = 0;
    moveDirection = "";
    isAlive = true;
    L = values[0];
    N = values[1];

    row = rand() % values[1]; // Random starting position for row
    col = rand() % values[1]; // Random starting position for column
}; 

Mario::~Mario(){}; // destructor


void Mario::collectCoin(){

    coins++;

    if(coins == 20){
        lives++;
        coins = 0;

        std::string message = "Mario collected 20 coins and gained a life. Current amount of coins: " +
        std::to_string(coins);
        fp -> writeFile("output.txt", message);
    }

    std::string message = "Mario collected a coin. Current amount of coins: " + std::to_string(coins);
    fp -> writeFile("output.txt", message);

}

std::string Mario::move(){

    // check enemy count to gain life back 
    if(enemyCount == 7){
        std::string message = "Mario's enemy kill count in this life = 7, Mario gains a life back";
        fp -> writeFile("output.txt", message);
        lives++;
        enemyCount = 0;
    }

    int direction = rand() % 4;
  
    switch(direction){

    case 0: // Move up
            row = (row - 1 + N) % N;  // Torus effect
            moveDirection = "UP";
            break;
    case 1: // Move down
            row = (row + 1) % N;
            moveDirection = "DOWN"; 
            break;
    case 2: // Move left
            col = (col - 1 + N) % N;
            moveDirection = "LEFT";
            break;
    case 3: // Move right
            col = (col + 1) % N;
            moveDirection = "RIGHT";
            break;
    }

    return moveDirection;
    
}

void Mario::eatMushroom(){

    if (powerLvl < 2){
        powerLvl++;
        std::string message = "Mario ate a Mushroom. Power level increased to " +
        std::to_string(powerLvl);
        fp -> writeFile("output.txt", message);
    } else {
        std::string message = "Mario ate a mushroom. Power level remains at max (PL2).";
        fp -> writeFile("output.txt", message);
    }

}

bool Mario::combatGoomba(){

        int randNum = rand() % 100;

        if (randNum < 80){ // win
            // enemy count increases
            enemyCount++;

            std::string message = "Mario fought a Goomba and won.";
            fp-> writeFile("output.txt", message);  
            return true;
        } else { // lose
            if (powerLvl > 0){ // dec PL
                powerLvl--;
                std::string message = "Mario fought a Goomba and lost. Power level decreased to: "
                + powerLvl;
                fp-> writeFile("output.txt", message);  
            } else { // if at PL0, lose life
                lives--;
                enemyCount = 0;
                std::string message = "Mario fought a Goomba and lost a life.";
                fp-> writeFile("output.txt", message);

                if (lives == 0){ // if at PL0 and 0 lives
                    std::string gameOver = "Game Over! Mario has 0 lives left.";
                    fp-> writeFile("output.txt", gameOver);
                    setIsAlive(false);
                    return false;
                }
            }
        }

    return false;
}

bool Mario::combatKoopa(){

        int randNum = rand() % 100;

        if (randNum < 65){ // win
            enemyCount++;
            std::string message = "Mario fought a Koopa and won.";
            fp-> writeFile("output.txt", message);  
            return true;
        } else { // lose
            if (powerLvl > 0){ // dec PL
                powerLvl--;
                std::string message = "Mario fought a Koopa and lost. Power level decreased to: "
                + powerLvl;
                fp-> writeFile("output.txt", message);  
            } else { // if at PL0, lose life
                lives--;
                enemyCount = 0;
                std::string message = "Mario fought a Koopa and lost a life.";
                fp-> writeFile("output.txt", message);

                if (lives == 0){ // if at PL0 and 0 lives
                    std::string gameOver = "Game Over! Mario has 0 lives left.";
                    fp-> writeFile("output.txt", gameOver);
                    setIsAlive(false);
                    return false;
                }
            }
        }

        return false;
        

}

bool Mario::combatBoss(){

int randNum = rand() % 100;
bool bossAlive = true;

while (bossAlive && lives > 0) { 
    randNum = rand() % 100;
    if (randNum < 50){ // win
        bossAlive = false;
        return true;

    } else { // lose 
        if (powerLvl > 1){ // decrease PL by 2
            powerLvl -= 2;
        } else{
            powerLvl = 0;
            lives--;
            enemyCount = 0;
            std::string message = "Mario fought the Boss and lost a life.";
            fp-> writeFile("output.txt", message);

            if (lives == 0){
                std::string gameOver = "Game Over! Mario has 0 lives left.";
                    fp-> writeFile("output.txt", gameOver);
                    setIsAlive(false);
                    return false;
            }
        }
    }
}
return false;


}


void Mario::warpPipe(){

        // new random location
        row = rand() % N;  // Random row in the new level
        col = rand() % N;  // Random column in the new level

        std::string message = "Mario landed on Warp Pipe and warped.";
        fp->writeFile("output.txt", message);
        
}

void Mario::emptySpace(){
    std::string message = "Mario landed on empty space. ";
    fp->writeFile("output.txt", message);
}

void Mario::marioStats(){
    // print all of these to file after every move/turn
 
    std::string message = "Current Stats:\n";
    message += "Power Level: " + std::to_string(powerLvl) + "\n"; // Mario's power level
    message += "Lives: " + std::to_string(lives) + "\n"; // Mario's remaining lives
    message += "Coins: " + std::to_string(coins) + "\n"; // Mario's coins
    message += "Enemies defeated in this life: " +std::to_string(enemyCount) + "\n"; // enemy count in current life

    fp->writeFile("output.txt", message);

}


void Mario::setIsAlive(bool alive) {
    isAlive = alive;  
}


