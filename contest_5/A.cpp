#include <algorithm>
#include <cassert>
#include <ios>
#include <iostream>
#include <limits>
#include <vector>

class Graph {
public:
    Graph(int graph_size) : graph_size_(graph_size) {
        win_.resize(graph_size);
        proebal_.resize(graph_size);
        colors_.assign(graph_size + 5, -1);
        count_.assign(graph_size + 5, 0);
    }

    void AddEdge(int from, int to, int game_res) {
        assert(0 <= from && from < graph_size_);
        assert(0 <= to && to < graph_size_);
        if (game_res == 1) {
            proebal_[from].push_back(to);
            win_[to].push_back(from);
        } else if (game_res == 2) {
            win_[from].push_back(to);
            proebal_[to].push_back(from);
        }
    }

    int Solve() {
        std::vector<int> adam;

        used_.assign(graph_size_, false);
        for (int vertex = 0; vertex < graph_size_; ++vertex) {
            if (!used_[vertex]) {
                Dfs(vertex);
            }
        }

        used_.assign(graph_size_, false);
        int current_color = 1;
        std::reverse(top_sort_.begin(), top_sort_.end());
        for (int vertex : top_sort_) {
            if (!used_[vertex]) {
                CalcColors(vertex, current_color);
                ++current_color;
            }
        }

        used_.assign(graph_size_, false);
        for (int vertex : top_sort_) {
            if (!used_[vertex]) {
                adam.push_back(vertex);
                MakeComponentUsed(vertex);
            }
        }

        int otvet = std::numeric_limits<int>::max();
        for (int current_adam : adam) {
            otvet = std::min(otvet, count_[colors_[current_adam]]);
        }

        return graph_size_ - otvet + 1;
    }

private:
    int graph_size_;
    std::vector<std::vector<int>> win_;
    std::vector<std::vector<int>> proebal_;
    std::vector<bool> used_;
    std::vector<int> top_sort_;
    std::vector<int> colors_;
    std::vector<int> count_;

    void Dfs(int vertex) {
        used_[vertex] = true;
        for (int to : proebal_[vertex]) {
            if (!used_[to]) {
                Dfs(to);
            }
        }
        top_sort_.push_back(vertex);
    }

    void CalcColors(int vertex, int current_color) {
        used_[vertex] = true;
        colors_[vertex] = current_color;
        ++count_[current_color];

        for (int to : win_[vertex]) {
            if (!used_[to]) {
                CalcColors(to, current_color);
            }
        }
    }

    void MakeComponentUsed(int vertex) {
        used_[vertex] = true;
        for (int to : proebal_[vertex]) {
            if (!used_[to]) {
                MakeComponentUsed(to);
            }
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int graph_size;
    int edges_count;
    std::cin >> graph_size >> edges_count;

    Graph graph(graph_size);

    for (int edge_index = 0; edge_index < edges_count; ++edge_index) {
        int from;
        int to;
        int game_res;
        std::cin >> from >> to >> game_res;
        --from;
        --to;
        graph.AddEdge(from, to, game_res);
    }

    std::cout << graph.Solve();
}