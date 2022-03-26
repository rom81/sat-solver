#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 

using namespace std;

int main(int argc, char* argv[]) 
{
    int limit;
    std::string infile, outfile;

    // args format: ./mycprogram] LIMIT INFILE.cnf OUTFILE.sat
    if (argc == 4)
    {
        limit = atoi(argv[1]);
        infile = argv[2];
        outfile = argv[3];
    }

    // read in cnf file
    string line; 
    ifstream input;
    input.open(infile);
    while(std::getline(input,line))
    {
        
    }

    // Perform sat solving (DPLL algorithm)

    

    // Write results to outfile


}