Maze & Graph Solver Analyzer

A comprehensive pathfinding algorithm comparison tool that analyzes performance across different maze and graph structures. Features multiple algorithms with detailed metrics and a web-based visualization interface.
Features

Multiple Algorithms: BFS, DFS, Dijkstra, A*, Bellman-Ford, Floyd-Warshall, SPFA, Dinic's Algorithm
Performance Metrics: Execution time, nodes explored, path length, success rate
Output Formats: JSON data files for further analysis
Web Interface: Flask-based visualization dashboard
Flexible Input: Supports various maze sizes and graph structures

Prerequisites

C++17 compatible compiler
Python 3.x
Flask (pip install flask)
# Compile the solver
g++ -std=c++17 -O2 main.cpp maze.cpp solvers.cpp -o maze_solver

# Run the analysis
./maze_solver

# Start the web interface
python3 server.py

<img width="578" height="326" alt="image" src="https://github.com/user-attachments/assets/2e0ed0f3-e475-493e-be43-89234c548aca" />




