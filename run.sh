#!/bin/bash

echo "=== Compiling C++ Code ==="
g++ -std=c++17 -O2 main.cpp -o maze_solver

if [ $? -eq 0 ]; then
    echo "✓ Compilation successful!"
    echo "=== Running Maze Solver ==="
    ./maze_solver
else
    echo "✗ Compilation failed!"
    exit 1
fi

echo "=== Starting Web Server ==="
python3 server.py