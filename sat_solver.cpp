#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
#include <vector>
#include <cmath>

using namespace std;

int limit;                      // recursive call limit
int num_variables;              // number of variables in clauses
int num_clauses;                // total number of clauses
string infile;                  // cnf file
string outfile;                 // sat file
vector<vector<int> > set_of_clauses;    // Set of clauses; global and immutable

bool DPLL(vector<int> variable_values);
void printValues(vector<int> variable_values);

// TODO: Read in values from cnf file. Populate set_of_clauses, num_variables, and num_clauses
vector<vector<int> > readInput(vector<vector<int> > set_of_clauses)
{
    string line; 
    ifstream input;
    input.open(infile);
    while(std::getline(input,line))
    {
        if(line.substr(0,1) == "c" || line.substr(0,1) == "C") {
            continue;
        } else if(line.substr(0,1) == "p" || line.substr(0,1) == "P") {
            num_variables = stoi(line.substr(6,1));
            cout << "num_variables: " << num_variables << endl;
            num_clauses = stoi(line.substr(8,1));
            cout << "num_clauses: " << num_clauses << endl;
        } else {
            int count = 0;
            stringstream ss(line);
            string num;
            vector<int> row;
            while(ss >> num) {
                cout << "num: " << num << endl;
                row.push_back(stoi(num));
            }
            cout << "\n" << endl;
            set_of_clauses.push_back(row);

            count++;
    }
    }
    input.close();

    return set_of_clauses;
}

// TODO: Write results to output file
void writeOutput(vector<int> variable_values, bool sat)
{
    ofstream output;
    output.open(outfile);
    output << "c This is the comments section" << endl;
    if(sat) {
        output << "s SATISFIABLE" << endl;
        output << "v ";
        for(int i = 0; i < variable_values.size(); i++) {
            output << to_string(variable_values.at(i)) << " ";
        }
    } else {
        output << "s UNSATISFIABLE" << endl;
    }
    output.close();
}

int main(int argc, char* argv[]) 
{
    // Read args (format: ./sat-solver [LIMIT] [INFILE.cnf] [OUTFILE.sat])
    limit   = atoi(argv[1]);
    infile  = argv[2];
    outfile = argv[3];
    
    // Read in cnf file and create set of clauses
    set_of_clauses = readInput(set_of_clauses);

    /* Stores variable values. Index 0 is empty; x1 maps to index 1, x2 to index 2, and so on */
    // vector<int> variable_values;    

    // // Initialize all variable values to -1 (no values assigned yet). 
    // for (int i = 0; i < num_variables + 1; i++) 
    //     variable_values.push_back(-1);

    // // Perform sat solving (DPLL algorithm)
    // bool sat;
    // sat = DPLL(variable_values);

    // // Write results to outfile
    // writeOutput(variable_values,sat);
}

vector<int> setVariable(int var, int val, vector<int> variable_values)
{
    variable_values.at(var) = val;
    return variable_values;
}

// Returns the mapping of a variable to an index in variable_values, e.g. x1 maps to 0,
// x2 maps to 1, and so on.
int varToIndex(int var)
{
    return abs(var);
}

// Evaluates a variable given an index (var) to be either true (1) or false (0) or unassigned (-1)
int evaluateVariable(int var, vector<int> variable_values)
{   
    int res;

    // Variable in unassigned
    if (variable_values.at(varToIndex(var)) < 0)
        res = -1;
    // If variable is assigned, evaluate it based on sign
    else    
        res = (var < 0) ? !variable_values.at(varToIndex(var)) : variable_values.at(varToIndex(var));

    return res;
}

// Check if clause is a unit clause. If so, return variable that causes it, otherwise return -1
pair<int, int> isUnitClause(vector<int> clause, vector<int> variable_values)
{
    int num_unassigned = clause.size(); // Assume all varables are unassigned at first
    int unassigned_id = -1;

    // Every variable but one must be assigned
    for (int var : clause)
    {
        if (evaluateVariable(var, variable_values) != -1)    // This variable is assigned
            num_unassigned--;
        else
            unassigned_id = var;            // Otherwise, record unassigned variable
    }

    int val_to_assign = -1;

    // More than one variable is unassigned
    if (num_unassigned != 1)
        unassigned_id = -1;

    // Otherwise, find the value to assign to this unassigned variable
    else // If complement, assign 0; otherwise assign 1
        val_to_assign = (unassigned_id < 0) ? 0 : 1;

    // Return unassigned_id if it's a unit clause, otherwise return -1
    return make_pair(unassigned_id, val_to_assign);
}

// Determine if set_of_clauses contains a unit cause due to literal L
// and return literal L (as an integer) and its required value V if so. 
// If there's no unit clause in set_of_clauses, return (-1, -1).
pair<int, int> containsUnitClaus(vector<int> variable_values)
{
    for (vector<int> clause : set_of_clauses)
    {
        pair<int, int> res = isUnitClause(clause, variable_values);
        if (res.first != -1)
            return res;  // Found a unit clause!
    }
    return pair<int, int>(-1,-1);
}

// Determine if clause evaluates to zero
bool checkIfClauseIsZero(vector<int> clause, vector<int> variable_values)
{
    for (int var : clause)
    {
        // If any variable evaluates to 1 or is unassigned, the entire clause is 1
        // (or unassigned), so return false        
        if ((evaluateVariable(var, variable_values) == -1) || 
            (evaluateVariable(var, variable_values) == 1))
            return false;
    }

    // If we've reached this point, no 1's or -1's have been found, so entire clause is 0
    return true;
}

// TODO: Heuristically choose an unassigned variable x and heuristically choose a value v
int selectVar(vector<int> variable_values)
{
    // For now, choose first variable in variable_values that's currently -1 (ignoring first index)
    for (int i = 1; i < variable_values.size(); i++)
    {
        if (variable_values.at(i) == -1)
            return i;
    }
    
    return -1;  // Should never reach this case -- it would mean there are no variables left to assign
}

// Determine if clause evaluates to one 
bool checkIfClauseIsOne(vector<int> clause, vector<int> variable_values)
{
    // cout << "checking if clause is one: " << endl;
    // If any variable has a value of 1, the entire clause is one    
    for (int var : clause)
    {
        if (evaluateVariable(var, variable_values) == 1)
            return true;
    }
        
    return false;
}

// Return true if every clause in set_of_clauses is simplified to 1
bool allOnes(vector<int> variable_values)
{
    for (vector<int> clause : set_of_clauses)
    {
        // Check individual clauses
        if (!checkIfClauseIsOne(clause, variable_values))
            return false;
    }
    return true;
}

// Return true if set_of_clauses contains any clause that evals to 0
bool containsZero( vector<int> variable_values)
{
    for (vector<int> clause : set_of_clauses)
    {
        // Check individual clauses
        if (checkIfClauseIsZero(clause, variable_values))
            return true;
    }
    return false;
}

// Print the current variable values
void printValues(vector<int> variable_values)
{
    for (int i = 1; i < variable_values.size(); i++)
    {
        cout << "\tx" << i << ": " << variable_values.at(i);

        if (variable_values.at(i) == -1)
            cout << " (unassigned)" << endl;
        else if (variable_values.at(i) == 0)
            cout << " (false)" << endl;
        else if (variable_values.at(i) == 1)
            cout << " (true)" << endl;
    }
}

// TODO: Return true if satisfied, false if not satisfied
bool DPLL(vector<int> variable_values)
{
    // Do BCP
    pair<int, int> L_V = containsUnitClaus(variable_values);
    // while (set_of_clausescontains a unit clause due to literal L)
    while (L_V.first > 0)
    {
        // Simplify set_of_clauses by setting variable for L to its required value
        // in all clauses in set_of_clauses
        variable_values = setVariable(L_V.first, L_V.second, variable_values);

        // Check for other unit clauses
        L_V = containsUnitClaus(variable_values);
    }

    if (allOnes(variable_values))
    {
        writeOutput(variable_values,true);

        return true; // return SAT; have simplified every clause to be 1
    }
    if (containsZero(variable_values))
    {
        return false; // return UNSAT; this is a conflict, this set of var assignment doesn't satisfy
    }

    // Otherwise, we need to recurse
    
    // TODO: Heuristically choose an unassigned variable x and heuristically choose a value v (in selectVar function)
    int x = selectVar(variable_values), v = 1; 
    
    variable_values = setVariable(x, v, variable_values);
    if (DPLL(variable_values)) // if( DPLL( set_of_clauses = simplified by setting x=v ) == SAT )
    {
        // cout << "tried x= " << x<< " and v= " << v << " and it worked" << endl;
        exit(1);
    }
    else  // else return( DPLL( set_of_clauses = simplified by setting x= ¬v ) )
    {
        // cout << "original choice didn't work. trying x" << x << " = " << 1-v << endl;
        variable_values = setVariable(x, 1-v, variable_values);

        return (DPLL(variable_values));    
    }
}