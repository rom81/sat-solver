# Features implemented:
- None; almost have a basic sat solver working. It works for some cases (e.g. f008-01-s.cnf and f008-01-u.cnf) but not others (e.g. f008-02-s.cnf) and we haven't finished debugging it to figure out why some becnhmarks don't work.

# Instructions to run:
- System requirements: built and tested on MacOS Monterey, compiled using g++ or clang++ in `compile.sh`
- To compile: `./compile.sh` 
- To run: `./sat-solver \[limit\] \[input cnf file\] \[output sat file\]`

# Contributions by Jimmy:
- Wrote readInput() and writeOutput()
- Debugging

# Contributions by Rachel:
- Wrote DPLL() and associated functions
- Debugging

# Documentation
This is a boolean satisfiability solver written for a graduate-level algorithms and modeling course. It takes input in conjunctive normative form (CNF) and provides outputs in a file specifying satisfiability and values which satisfy the input if it is satisfiable. 
