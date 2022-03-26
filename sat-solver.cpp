#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
#include <vector>

using namespace std;

void DPLL(vector<vector<int> > set_of_clauses);

int main(int argc, char* argv[]) 
{
    int limit;
    std::string infile, outfile;

    // args format: ./sat-solver [LIMIT] [INFILE.cnf] [OUTFILE.sat]
    limit = atoi(argv[1]);
    infile = argv[2];
    outfile = argv[3];
    
    // read in cnf file
    int num_variables = 2, num_set_of_clauses = 2;
    vector<vector<int> > set_of_clauses;

    string line; 
    ifstream input;
    input.open(infile);
    while(std::getline(input,line))
    {
        
    }

    // Perform sat solving (DPLL algorithm)
    DPLL(set_of_clauses);

    // Write results to outfile


}

int containsUnitClaus(vector<vector<int> > set_of_clauses)
{
    // TODO: Determine if set_of_clauses contains a unit cause due to literal L
    // and return literal L (as an integer) if so. If there's no unit set_of_clauses,
    // return 0.
    return 0;
}

bool allOnes(vector<vector<int> > set_of_clauses)
{
    // TODO: Return true if every clause in set_of_clauses is simplified to 1
    return false;
}

bool containsZero(vector<vector<int> > set_of_clauses)
{
    // TODO: Return true if set_of_clauses contains a clause that evals to 0
    return false;
}

// TODO: change return type to be appropriate for returning SAT/UNSAT
void DPLL(vector<vector<int> > set_of_clauses)
{
    // Do BCP
    int L = containsUnitClaus(set_of_clauses);
    while (L != 0)
    {
        // TODO: Simplify set_of_clauses by setting variable for L to its required value
        // in all set_of_clauses
        L = containsUnitClaus(set_of_clauses);
    }

    if (allOnes(set_of_clauses))
    {
        // return SAT; have simplified every clause to be 1
    }
    if (containsZero(set_of_clauses))
    {
        // return UNSAT; this is a conflict, this set of var assignment doesn't satisfy
    }

    // Otherwise, we need to recurse
    
    // TODO: Heuristically choose an unassigned variable x and 
    // heuristically choose a value v
    int x = 0, v = 1;

    // TODO: (taken from DPLL algortihm on slides)
    // if( DPLL( set_of_clauses = simplified by setting x=v ) == SAT )
    // return ( SAT )
    // else return( DPLL( set_of_clauses = simplified by setting x= ¬v ) )
    
}
