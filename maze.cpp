
#include "maze.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#define _USE_MATH_DEFINES
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Cell::Cell() : x(0), y(0), is_wall(false), visited(false), 
               parent_x(-1), parent_y(-1), cost(1), f(0), g(0), h(0) {}

// Graph implementation
Graph::Graph(int nodes_count, int edges_count) : n(nodes_count), m(edges_count) {
    nodes.reserve(n);
    for (int i = 0; i < n; ++i) {
        nodes.emplace_back(i);
    }
    start_node = 0;
    end_node = n - 1;
    
    // Position nodes in a circular layout for visualization
    for (int i = 0; i < n; ++i) {
        double angle = 2.0 * M_PI * i / n;
        nodes[i].x = static_cast<int>(150 + 100 * cos(angle));
        nodes[i].y = static_cast<int>(150 + 100 * sin(angle));
    }
}

void Graph::add_edge(int from, int to, int weight) {
    if (from >= 0 && from < n && to >= 0 && to < n) {
        nodes[from].edges.emplace_back(to, weight);
    }
}

void Graph::generate_random_graph() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> node_dist(0, n - 1);
    std::uniform_int_distribution<> weight_dist(1, 20);
    
    // Ensure graph is connected by creating a path
    for (int i = 0; i < n - 1; ++i) {
        int weight = weight_dist(gen);
        add_edge(i, i + 1, weight);
        add_edge(i + 1, i, weight); // bidirectional
    }
    
    // Add random edges to reach the desired number
    int edges_added = 2 * (n - 1); // bidirectional edges
    while (edges_added < m) {
        int from = node_dist(gen);
        int to = node_dist(gen);
        if (from != to) {
            // Check if edge already exists
            bool exists = false;
            for (const auto& edge : nodes[from].edges) {
                if (edge.to == to) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                int weight = weight_dist(gen);
                add_edge(from, to, weight);
                edges_added++;
            }
        }
    }
}

void Graph::set_start_end(int start, int end) {
    if (start >= 0 && start < n) start_node = start;
    if (end >= 0 && end < n) end_node = end;
}

const std::vector<Node>& Graph::get_nodes() const { return nodes; }
int Graph::get_start() const { return start_node; }
int Graph::get_end() const { return end_node; }
int Graph::get_node_count() const { return n; }

std::string Graph::to_json() const {
    std::stringstream ss;
    ss << "{\"nodes\":" << n << ",\"edges\":" << m;
    ss << ",\"start\":" << start_node << ",\"end\":" << end_node;
    ss << ",\"nodePositions\":[";
    
    for (int i = 0; i < n; ++i) {
        ss << "{\"id\":" << i << ",\"x\":" << nodes[i].x << ",\"y\":" << nodes[i].y << "}";
        if (i < n - 1) ss << ",";
    }
    ss << "],\"edgeList\":[";
    
    bool first_edge = true;
    for (int i = 0; i < n; ++i) {
        for (const auto& edge : nodes[i].edges) {
            if (!first_edge) ss << ",";
            ss << "{\"from\":" << i << ",\"to\":" << edge.to << ",\"weight\":" << edge.weight << "}";
            first_edge = false;
        }
    }
    ss << "]}";
    return ss.str();
}

// Maze implementation (keeping existing functionality)
Maze::Maze(int w, int h) : width(w), height(h), grid(h, std::vector<Cell>(w)) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            grid[y][x].x = x;
            grid[y][x].y = y;
            grid[y][x].is_wall = true;
        }
    }
    start = {1, 1};
    end = {width-2, height-2};
    generate_maze();
}

void Maze::generate_maze() {
    for (int y = 1; y < height-1; y += 2) {
        for (int x = 1; x < width-1; x += 2) {
            grid[y][x].is_wall = false;
            if (x + 2 < width-1) grid[y][x+1].is_wall = false;
            if (y + 2 < height-1) grid[y+1][x].is_wall = false;
        }
    }
    grid[start.second][start.first].is_wall = false;
    grid[end.second][end.first].is_wall = false;
}

bool Maze::is_valid(int x, int y) const {
    return (x >= 0 && x < width && y >= 0 && y < height && !grid[y][x].is_wall);
}

const std::vector<std::vector<Cell>>& Maze::get_grid() const { return grid; }
std::pair<int, int> Maze::get_start() const { return start; }
std::pair<int, int> Maze::get_end() const { return end; }

std::string Maze::to_json() const {
    std::stringstream ss;
    ss << "{\"width\":" << width << ",\"height\":" << height;
    ss << ",\"start\":[" << start.first << "," << start.second << "]";
    ss << ",\"end\":[" << end.first << "," << end.second << "]";
    ss << ",\"grid\":[";

    for (int y = 0; y < height; ++y) {
        ss << "[";
        for (int x = 0; x < width; ++x) {
            ss << (grid[y][x].is_wall ? "1" : "0");
            if (x < width - 1) ss << ",";
        }
        ss << "]";
        if (y < height - 1) ss << ",";
    }
    ss << "]}";
    return ss.str();
}
