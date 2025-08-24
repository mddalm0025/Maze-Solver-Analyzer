
#pragma once
#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <random>

struct Edge {
    int to;
    int weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

struct Node {
    int id;
    std::vector<Edge> edges;
    int x, y; // for visualization
    Node(int i) : id(i), x(0), y(0) {}
};

struct Cell {
    int x, y;
    bool is_wall;
    bool visited;
    int parent_x, parent_y;
    int cost;
    int f, g, h;

    Cell();
};

class Graph {
private:
    int n, m; // number of nodes, number of edges
    std::vector<Node> nodes;
    int start_node, end_node;

public:
    Graph(int nodes_count, int edges_count);
    void add_edge(int from, int to, int weight);
    void generate_random_graph();
    void set_start_end(int start, int end);
    const std::vector<Node>& get_nodes() const;
    int get_start() const;
    int get_end() const;
    int get_node_count() const;
    std::string to_json() const;
};

class Maze {
private:
    int width, height;
    std::vector<std::vector<Cell>> grid;
    std::pair<int, int> start, end;

public:
    Maze(int w, int h);
    void generate_maze();
    bool is_valid(int x, int y) const;
    const std::vector<std::vector<Cell>>& get_grid() const;
    std::pair<int, int> get_start() const;
    std::pair<int, int> get_end() const;
    std::string to_json() const;
};
