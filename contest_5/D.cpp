#include <cassert>
#include <iostream>
#include <vector>

class Graph {
public:
    explicit Graph(int node_count) : node_count_(node_count) {
        adjacency_list_.resize(node_count_);
    }

    void AddEdge(int from, int to, int weight) {
        assert(0 <= from && from < node_count_);
        assert(0 <= to && to < node_count_);
        adjacency_list_[from].emplace_back(to, weight);
    }

    int FindShortestPath(int source, int destination, int modulus) const {
        std::vector<std::vector<int>> distance_buckets(modulus);
        std::vector<int> distances(node_count_, -1);

        distances[source] = 0;
        distance_buckets[0].push_back(source);
        int maximum_distance = 0;

        for (int current_distance = 0; current_distance <= maximum_distance;
             ++current_distance) {
            auto& current_bucket = distance_buckets[current_distance % modulus];
            while (!current_bucket.empty()) {
                int current_node = current_bucket.back();
                current_bucket.pop_back();
                if (distances[current_node] != current_distance) {
                    continue;
                }
                for (const auto& neighbor : adjacency_list_[current_node]) {
                    int neighbor_node = neighbor.destination;
                    int weight = neighbor.weight;
                    if (distances[neighbor_node] != -1 &&
                        distances[neighbor_node] <= current_distance + weight) {
                        continue;
                    }
                    distances[neighbor_node] = current_distance + weight;
                    distance_buckets[(current_distance + weight) % modulus]
                        .push_back(neighbor_node);
                    maximum_distance =
                        std::max(maximum_distance, current_distance + weight);
                }
            }
        }
        return distances[destination];
    }

private:
    struct Edge {
        int destination;
        int weight;
    };

    int node_count_;
    std::vector<std::vector<Edge>> adjacency_list_;

    void AddEdgeInternal(int from, int to, int weight) {
        adjacency_list_[from].push_back({to, weight});
    }
};

class Solution {
public:
    void InputGraph() {
        std::cin >> node_count_ >> edge_count_;
        graph_ = Graph(node_count_);
        for (int edge_index = 0; edge_index < edge_count_; ++edge_index) {
            int from;
            int to;
            int weight;
            std::cin >> from >> to >> weight;
            graph_.AddEdge(from - 1, to - 1, weight);
        }
    }

    void ProcessQueries() {
        int query_count;
        std::cin >> query_count;
        for (int query_index = 0; query_index < query_count; ++query_index) {
            int source;
            int destination;
            std::cin >> source >> destination;
            std::cout << graph_.FindShortestPath(source - 1, destination - 1,
                                                 kModulus)
                      << '\n';
        }
    }

private:
    int node_count_;
    int edge_count_;
    const int kModulus = 3;
    Graph graph_{0};
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Solution solution;
    solution.InputGraph();
    solution.ProcessQueries();

    return 0;
}
