// Calef Alesse
// Student ID: 2439923
// calesse@chapman.edu
// CPSC 350- 03
// PA02 Not So Super Mario

#include <iostream>
#include <fstream>
#include <string>
#include "FileProcessor.h"


FileProcessor::FileProcessor(std::string inputFile, std::string outputFile){}; // constructor
FileProcessor::~FileProcessor(){}; // destructor 


int* FileProcessor::readFile(std::string inputFile){

    std::ifstream inFile(inputFile);
    std::string line;

    int maxNum = 8; // num of args per line
    int* values = new int[maxNum]; // array of initial values
    int count = 0; // number of elements read in
    

    if (inFile.is_open()){
        // read line by line
        while(std::getline(inFile, line) && count <= maxNum) {
            // convert string into an int and store in array
            values[count] = std::stoi(line); 
            count++;
        }

    } else {
        std::cout<< "Error opening input file." << std::endl;
    }

        inFile.close();
        // return array 
        return values;


}


void FileProcessor::writeFile(std::string outputFile, std::string entry) { // or 2D array int** arr[]
    std::ofstream outFile(outputFile, std::ofstream::app); // append mode

    if (outFile.is_open()){
        outFile << entry << std::endl;
        // entry will be defined based on the class that calls/uses it

    } else {
        std::cout<< "Error opening output file." << std::endl;
    }
    outFile.close();

}

void FileProcessor::resetFile(std::string outputFile){
    std::ofstream outFile(outputFile, std::ofstream::trunc);
    outFile.close(); 
}



