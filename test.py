#!/usr/bin/env python3
import os
import subprocess

print("Testing compilation...")
result = subprocess.run(['g++', '-std=c++17', '-O2', 'main.cpp', '-o', 'maze_solver'], 
                       capture_output=True, text=True)

if result.returncode == 0:
    print("✓ Compilation successful!")

    # Test running the maze solver
    result2 = subprocess.run(['./maze_solver'], capture_output=True, text=True)
    print("Maze solver output:", result2.stdout)
    if result2.stderr:
        print("Maze solver errors:", result2.stderr)

    # Check if files were created
    if os.path.exists('maze.json') and os.path.exists('results.json'):
        print("✓ JSON files created successfully!")
    else:
        print("✗ JSON files not found")
else:
    print("✗ Compilation failed!")
    print("Error:", result.stderr)