// Calef Alesse
// Student ID: 2439923
// calesse@chapman.edu
// CPSC 350- 03
// PA02 Not So Super Mario

#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <iostream>
#include <fstream>
#include <string>


class FileProcessor{
    private:
    // input and output files 
    std::string inFile;
    std::string outFile;
    
    public:

        FileProcessor(std::string inputFile, std::string outputFile); // constructor
        ~FileProcessor(); // destructor

        // read in strings from file
        int* readFile(std::string inputFile);
        // writes to file 
        void writeFile(std::string outputFile, std::string message);
        void resetFile(std::string outputFile);

        std::string getOutputFile() const {
            return outFile;
        }
};


#endif