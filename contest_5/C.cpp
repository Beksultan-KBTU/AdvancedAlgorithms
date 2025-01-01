#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

class Graph {
public:
    Graph(int size) : size_(size) {
        graph_.resize(size);
        used_.assign(size, false);
        time_in_.assign(size, 0);
        fuckup_.assign(size, 0);
    }
    void AddEdge(int from, int to, int cost) {
        assert(0 <= from && from < size_);
        assert(0 <= to && to < size_);
        graph_[from].push_back({to, cost});
        graph_[to].push_back({from, cost});
    }
    int CalcMinBridgeCost() {
        min_bridge_cost_ = std::numeric_limits<int>::max();
        for (int vertex = 0; vertex < size_; ++vertex) {
            if (!used_[vertex]) {
                Dfs(vertex);
            }
        }
        return (min_bridge_cost_ == std::numeric_limits<int>::max()
                    ? -1
                    : min_bridge_cost_);
    }

private:
    struct Edge {
        int vertex;
        int cost;
    };
    int size_;
    int current_time_ = 0;
    int min_bridge_cost_;
    std::vector<std::vector<Edge>> graph_;
    std::vector<bool> used_;
    std::vector<int> time_in_;
    std::vector<int> fuckup_;

    void Dfs(int vertex, int parent_vertex = -1) {
        used_[vertex] = true;
        time_in_[vertex] = current_time_;
        fuckup_[vertex] = current_time_;
        ++current_time_;
        for (const Edge& edge : graph_[vertex]) {
            int to_vertex = edge.vertex;
            if (to_vertex == parent_vertex) {
                continue;
            }
            if (used_[to_vertex]) {
                fuckup_[vertex] =
                    std::min(fuckup_[vertex], time_in_[to_vertex]);
            } else {
                Dfs(to_vertex, vertex);
                fuckup_[vertex] = std::min(fuckup_[vertex], fuckup_[to_vertex]);
                if (fuckup_[to_vertex] > time_in_[vertex]) {
                    min_bridge_cost_ = std::min(min_bridge_cost_, edge.cost);
                }
            }
        }
    }
};

int main() {
    int graph_size;
    int edges_count;
    std::cin >> graph_size >> edges_count;
    Graph graph(graph_size);
    for (int edge_index = 0; edge_index < edges_count; ++edge_index) {
        int from;
        int to;
        int cost;
        std::cin >> from >> to >> cost;
        --from;
        --to;
        graph.AddEdge(from, to, cost);
    }

    std::cout << graph.CalcMinBridgeCost();
}