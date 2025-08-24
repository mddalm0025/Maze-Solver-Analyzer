
#pragma once
#include "maze.h"
#include <vector>
#include <chrono>
#include <string>

struct AlgorithmResult {
    std::string name;
    std::chrono::microseconds time_taken;
    int nodes_explored;
    bool found_path;
    std::vector<std::pair<int, int>> path; // for maze
    std::vector<int> node_path; // for graph
    int total_cost;

    std::string to_json() const;
};

class MazeSolver {
public:
    static AlgorithmResult solve_bfs(const Maze& maze);
    static AlgorithmResult solve_astar(const Maze& maze);
    static AlgorithmResult solve_dfs(const Maze& maze);
    static AlgorithmResult solve_dijkstra(const Maze& maze);
    static AlgorithmResult solve_bellman_ford(const Maze& maze);
    static AlgorithmResult solve_floyd_warshall(const Maze& maze);
    static AlgorithmResult solve_spfa(const Maze& maze);
    static AlgorithmResult solve_dinic(const Maze& maze);
    static std::vector<AlgorithmResult> compare_algorithms(const Maze& maze);
};

class GraphSolver {
public:
    static AlgorithmResult solve_bfs(const Graph& graph);
    static AlgorithmResult solve_dfs(const Graph& graph);
    static AlgorithmResult solve_dijkstra(const Graph& graph);
    static AlgorithmResult solve_bellman_ford(const Graph& graph);
    static AlgorithmResult solve_floyd_warshall(const Graph& graph);
    static AlgorithmResult solve_spfa(const Graph& graph);
    static std::vector<AlgorithmResult> compare_algorithms(const Graph& graph);
};
