#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
#include <chrono>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    int weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

struct AlgorithmResult {
    string name;
    vector<int> node_path;
    int total_cost;
    bool found_path;
    int nodes_explored;
    std::chrono::microseconds time_taken;

    AlgorithmResult() : total_cost(0), found_path(false), nodes_explored(0) {}
};

class Graph {
private:
    vector<vector<Edge>> adj;
    int N;
public:
    Graph(int n) : N(n) { adj.resize(N); }
    void add_edge(int from, int to, int weight) {
        adj[from].emplace_back(to, weight);
    }
    const vector<Edge>& get_edges(int node) const { return adj[node]; }
    int get_node_count() const { return N; }
};

class GraphSolver {
public:
    static AlgorithmResult solve_bfs(const Graph& graph, int start, int end);
    static AlgorithmResult solve_dfs(const Graph& graph, int start, int end);
    static AlgorithmResult solve_dijkstra(const Graph& graph, int start, int end);
    // Implement other methods as needed
};

// BFS Implementation
AlgorithmResult GraphSolver::solve_bfs(const Graph& graph, int start, int end) {
    AlgorithmResult result;
    result.name = "BFS";
    const int n = graph.get_node_count();

    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    queue<int> q;

    auto start_time = chrono::high_resolution_clock::now();
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        if (current == end) {
            result.found_path = true;
            for (int v = end; v != -1; v = parent[v]) {
                result.node_path.push_back(v);
            }
            reverse(result.node_path.begin(), result.node_path.end());
            break;
        }

        for (const Edge& edge : graph.get_edges(current)) {
            if (!visited[edge.to]) {
                visited[edge.to] = true;
                parent[edge.to] = current;
                q.push(edge.to);
                result.nodes_explored++;
            }
        }
    }

    auto end_time = chrono::high_resolution_clock::now();
    result.time_taken = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    return result;
}

// DFS Implementation
AlgorithmResult GraphSolver::solve_dfs(const Graph& graph, int start, int end) {
    AlgorithmResult result;
    result.name = "DFS";
    const int n = graph.get_node_count();

    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    stack<int> s;

    auto start_time = chrono::high_resolution_clock::now();
    s.push(start);
    visited[start] = true;

    while (!s.empty()) {
        int current = s.top();
        s.pop();

        if (current == end) {
            result.found_path = true;
            for (int v = end; v != -1; v = parent[v]) {
                result.node_path.push_back(v);
            }
            reverse(result.node_path.begin(), result.node_path.end());
            break;
        }

        for (const Edge& edge : graph.get_edges(current)) {
            if (!visited[edge.to]) {
                visited[edge.to] = true;
                parent[edge.to] = current;
                s.push(edge.to);
                result.nodes_explored++;
            }
        }
    }

    auto end_time = chrono::high_resolution_clock::now();
    result.time_taken = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    return result;
}

// Dijkstra Implementation can be added similarly./run.sh