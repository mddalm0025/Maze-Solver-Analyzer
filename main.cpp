
#include <iostream>
#include <fstream>
#include "maze.h"
#include "solvers.h"

using namespace std;

void run_maze_mode() {
    cout << "=== Maze Mode ===" << endl;
    cout << "Generating maze..." << endl;
    
    Maze maze(15, 15);
    
    cout << "Solving with algorithms..." << endl;
    auto results = MazeSolver::compare_algorithms(maze);
    
    ofstream maze_file("maze.json");
    if (maze_file.is_open()) {
        maze_file << maze.to_json();
        maze_file.close();
        cout << "✓ maze.json created successfully" << endl;
    }
    
    ofstream results_file("results.json");
    if (results_file.is_open()) {
        results_file << "[";
        for (size_t i = 0; i < results.size(); ++i) {
            results_file << results[i].to_json();
            if (i < results.size() - 1) results_file << ",";
        }
        results_file << "]";
        results_file.close();
        cout << "✓ results.json created successfully" << endl;
    }
    
    cout << "\n=== Maze Results ===" << endl;
    for (const auto& result : results) {
        cout << "\nAlgorithm: " << result.name << endl;
        cout << "Time: " << result.time_taken.count() << " μs" << endl;
        cout << "Nodes explored: " << result.nodes_explored << endl;
        cout << "Path length: " << result.path.size() << endl;
        cout << "Path found: " << (result.found_path ? "Yes" : "No") << endl;
    }
}

void run_graph_mode() {
    cout << "=== Graph Mode ===" << endl;
    
    int n, m;
    cout << "Enter number of nodes (n): ";
    cin >> n;
    cout << "Enter number of edges (m): ";
    cin >> m;
    
    if (n < 2) {
        cout << "Invalid input. Need at least 2 nodes." << endl;
        return;
    }
    
    if (m >= n) {
        cout << "Invalid input. Number of edges (m) must be less than number of nodes (n)." << endl;
        cout << "For n=" << n << ", maximum allowed edges is " << (n-1) << endl;
        return;
    }
    
    if (m < 1) {
        cout << "Invalid input. Need at least 1 edge." << endl;
        return;
    }
    
    cout << "Creating graph with " << n << " nodes..." << endl;
    Graph graph(n, m);
    
    cout << "\nNodes are numbered from 0 to " << (n-1) << endl;
    cout << "Enter " << m << " edges in format: from_node to_node weight" << endl;
    
    for (int i = 0; i < m; ++i) {
        int from, to, weight;
        cout << "Edge " << (i+1) << ": ";
        cin >> from >> to >> weight;
        
        if (from < 0 || from >= n || to < 0 || to >= n) {
            cout << "Invalid nodes. Nodes must be between 0 and " << (n-1) << ". Try again." << endl;
            i--; // retry this edge
            continue;
        }
        
        if (from == to) {
            cout << "Self-loops not allowed. Try again." << endl;
            i--; // retry this edge
            continue;
        }
        
        graph.add_edge(from, to, weight);
        cout << "Added edge: " << from << " -> " << to << " (weight: " << weight << ")" << endl;
    }
    
    int source, destination;
    cout << "\nEnter source node (0 to " << (n-1) << "): ";
    cin >> source;
    cout << "Enter destination node (0 to " << (n-1) << "): ";
    cin >> destination;
    
    if (source < 0 || source >= n || destination < 0 || destination >= n) {
        cout << "Invalid source or destination. Using default: 0 to " << (n-1) << endl;
        source = 0;
        destination = n-1;
    }
    
    if (source == destination) {
        cout << "Source and destination are the same. Using default: 0 to " << (n-1) << endl;
        source = 0;
        destination = n-1;
    }
    
    graph.set_start_end(source, destination);
    
    cout << "\nGraph created successfully!" << endl;
    cout << "Source: " << source << ", Destination: " << destination << endl;
    cout << "\nSolving with algorithms..." << endl;
    auto results = GraphSolver::compare_algorithms(graph);
    
    ofstream graph_file("graph.json");
    if (graph_file.is_open()) {
        graph_file << graph.to_json();
        graph_file.close();
        cout << "✓ graph.json created successfully" << endl;
    }
    
    ofstream results_file("results.json");
    if (results_file.is_open()) {
        results_file << "[";
        for (size_t i = 0; i < results.size(); ++i) {
            results_file << results[i].to_json();
            if (i < results.size() - 1) results_file << ",";
        }
        results_file << "]";
        results_file.close();
        cout << "✓ results.json created successfully" << endl;
    }
    
    cout << "\n=== Graph Results ===" << endl;
    cout << "Finding path from node " << source << " to node " << destination << endl;
    
    for (const auto& result : results) {
        cout << "\nAlgorithm: " << result.name << endl;
        cout << "Time: " << result.time_taken.count() << " μs" << endl;
        cout << "Nodes explored: " << result.nodes_explored << endl;
        cout << "Path length: " << result.node_path.size() << endl;
        cout << "Total cost: " << result.total_cost << endl;
        cout << "Path found: " << (result.found_path ? "Yes" : "No") << endl;
        if (result.found_path && !result.node_path.empty()) {
            cout << "Path: ";
            for (size_t i = 0; i < result.node_path.size(); ++i) {
                cout << result.node_path[i];
                if (i < result.node_path.size() - 1) cout << " -> ";
            }
            cout << endl;
        }
    }
}

int main() {
    cout << "=== Pathfinding Algorithm Analyzer ===" << endl;
    cout << "Choose mode:" << endl;
    cout << "1. Maze Mode (2D grid)" << endl;
    cout << "2. Graph Mode (custom nodes/edges with weights)" << endl;
    cout << "Enter choice (1 or 2): ";
    
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        run_maze_mode();
    } else if (choice == 2) {
        run_graph_mode();
    } else {
        cout << "Invalid choice. Running graph mode by default." << endl;
        run_graph_mode();
    }
    
    cout << "\nAnalysis complete!" << endl;
    return 0;
}
