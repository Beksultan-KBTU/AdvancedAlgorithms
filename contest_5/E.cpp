#include <algorithm>
#include <bitset>
#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

class PuzzleSolver {
public:
    void ReadInput() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);

        std::cin >> row_count_ >> column_count_;
        grid_size_ = row_count_ * column_count_;

        board_.assign(row_count_, std::vector<int>(column_count_, 0));
        for (int row_index = 0; row_index < row_count_; ++row_index) {
            for (int column_index = 0; column_index < column_count_;
                 ++column_index) {
                char cell_value;
                std::cin >> cell_value;
                board_[row_index][column_index] = (cell_value == '1') ? 1 : 0;
            }
        }
    }

    void Solve() {
        InitializeDistanceAndVisited();
        int starting_mask = CreateStartingMask();
        ExecuteBreadthFirstSearch(starting_mask);
        std::vector<int> layout_pattern = GenerateLayoutPattern();
        int target_mask_one = 0;
        int target_mask_two = 0;
        CreateTargetMasks(layout_pattern, target_mask_one, target_mask_two);
        std::cout << ComputeResult(target_mask_one, target_mask_two) << "\n";
    }

private:
    int row_count_;
    int column_count_;
    int grid_size_;
    std::vector<std::vector<int>> board_;
    std::vector<int> distance_mask_;
    std::vector<bool> visited_states_;

    void InitializeDistanceAndVisited() {
        int max_states = (1 << grid_size_);
        distance_mask_.assign(max_states, -1);
        visited_states_.assign(max_states, false);
    }

    int CreateStartingMask() {
        int starting_mask = 0;
        for (int row_index = 0; row_index < row_count_; ++row_index) {
            for (int column_index = 0; column_index < column_count_;
                 ++column_index) {
                if (board_[row_index][column_index] == 1) {
                    starting_mask ^=
                        (1 << (row_index * column_count_ + column_index));
                }
            }
        }
        return starting_mask;
    }

    void ExecuteBreadthFirstSearch(int starting_mask) {
        std::queue<int> bfs_queue;
        bfs_queue.push(starting_mask);
        distance_mask_[starting_mask] = 0;
        visited_states_[starting_mask] = true;

        while (!bfs_queue.empty()) {
            int current_state = bfs_queue.front();
            bfs_queue.pop();
            std::vector<int> possible_transitions =
                GenerateTransitions(current_state);
            for (int next_state : possible_transitions) {
                if (!visited_states_[next_state]) {
                    distance_mask_[next_state] =
                        distance_mask_[current_state] + 1;
                    visited_states_[next_state] = true;
                    bfs_queue.push(next_state);
                }
            }
        }
    }

    std::vector<int> GenerateLayoutPattern() const {
        std::vector<int> layout_pattern;
        for (int row_index = 0; row_index < row_count_; ++row_index) {
            for (int column_index = 0; column_index < column_count_;
                 ++column_index) {
                if (row_index % 2 == 0) {
                    layout_pattern.push_back(column_index % 2);
                } else {
                    layout_pattern.push_back((column_index % 2) ^ 1);
                }
            }
        }
        return layout_pattern;
    }

    void CreateTargetMasks(const std::vector<int>& layout_pattern,
                           int& target_mask_one, int& target_mask_two) const {
        target_mask_one = 0;
        target_mask_two = 0;
        for (int index = 0; index < grid_size_; ++index) {
            if (layout_pattern[index] == 1) {
                target_mask_one += (1 << index);
            } else {
                target_mask_two += (1 << index);
            }
        }
    }

    int ComputeResult(int target_mask_one, int target_mask_two) {
        if (distance_mask_[target_mask_one] == -1 &&
            distance_mask_[target_mask_two] == -1) {
            return -1;
        }
        if (distance_mask_[target_mask_one] != -1 &&
            distance_mask_[target_mask_two] != -1) {
            return std::min(distance_mask_[target_mask_one],
                            distance_mask_[target_mask_two]);
        }
        return std::max(distance_mask_[target_mask_one],
                        distance_mask_[target_mask_two]);
    }

    std::vector<int> GenerateTransitions(int current_mask) {
        std::vector<int> transitions;
        for (int row_index = 0; row_index < row_count_ - 1; ++row_index) {
            for (int column_index = 0; column_index < column_count_;
                 ++column_index) {
                int bit_one = row_index * column_count_ + column_index;
                int bit_two = (row_index + 1) * column_count_ + column_index;
                int new_mask = current_mask ^ (1 << bit_one);
                new_mask ^= (1 << bit_two);
                if (!visited_states_[new_mask]) {
                    transitions.push_back(new_mask);
                }
            }
        }
        for (int column_index = 0; column_index < column_count_ - 1;
             ++column_index) {
            for (int row_index = 0; row_index < row_count_; ++row_index) {
                int bit_one = row_index * column_count_ + column_index;
                int bit_two = row_index * column_count_ + (column_index + 1);
                int new_mask = current_mask ^ (1 << bit_one);
                new_mask ^= (1 << bit_two);
                if (!visited_states_[new_mask]) {
                    transitions.push_back(new_mask);
                }
            }
        }
        return transitions;
    }
};

int main() {
    PuzzleSolver solver;
    solver.ReadInput();
    solver.Solve();
    return 0;
}
