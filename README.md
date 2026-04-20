## Rubik's Cube Kociemba Algorithm
 
  Hello! This is my project for solving 10K scrambled cubes in the input inside CubeSolver. The project combines the performance of parallel computing in C++ with a smart and relatively efficient algorithm.

<img width="1500" height="2000" alt="pozaCub" src="https://github.com/user-attachments/assets/4fc575da-ec1b-49c2-8ef9-fffda62e9052" />


# Documentation
The project includes documentation in Word format. To install/view it, click here: 

https://github.com/Stefan-cs-sudo/CubeSolverKociemba/raw/refs/heads/master/CubeSolver%20(1).docx

# Configuration and Execution
To view or modify the code, open the .sln file. Upon compilation (Build), it will generate a new executable in the Release folder.

# Technical Details & Optimizations
Although the settings are pre-configured in the project file, the program utilizes:

**OpenMP**: For parallelizing the cube solving process across all available CPU cores.

**Hardware Instructions**: Specific optimizations for AVX2, BMI1, BMI2, and LZCNT instruction sets.

**Compilation**: O3 optimizations and loop unrolling for minimum latency.

File Structure
-Source.cpp: The entry point and parallel processing logic.

-FaceCube.h / CubieCube.h: Mathematical representations of the cube states.

-Search.h: Implementation of the algorithm to find the optimal solution.

-Tables.h: Pruning tables (pre-calculation tables) to accelerate the search.

# Final Notes
The system was designed to be robust and easy to test. It represents a specific implementation of the Kociemba algorithm.
