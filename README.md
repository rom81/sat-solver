# Features implemented:
- Two-literal watching?
- Branching heuristics?

# Instructions to run:
- System requirements: built and tested on MacOS Monterey, compiled using g++ or clang++
- To compile: `./compile.sh` 
- To run: `./sat-solver \[limit\] \[input cnf file\] \[output sat file\]`

# Contributions by Jimmy:
- Wrote readInput() and writeOutput()
- Implementing two-literal watching
- Debugging

# Contributions by Rachel:
- Wrote DPLL() and associated functions
- Implementing branching heuristics
- Debugging

# Documentation
This is a boolean satisfiability solver written for a graduate-level algorithms and modeling course. It takes input in conjunctive normative form (CNF) and provides outputs in a file. 
