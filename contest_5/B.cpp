#include <iostream>
#include <queue>
#include <string>
#include <vector>

struct Cell {
    int row;
    int column;
};

const std::vector<Cell> kDirections = {
    {-1, 0},  // U
    {0, 1},   // R
    {1, 0},   // D
    {0, -1}   // L
};

Cell operator+=(Cell lhs, const Cell& rhs) {
    lhs.row += rhs.row;
    lhs.column += rhs.column;
    return lhs;
}

struct State {
    Cell cell;
    int current_cost = 0;
    int current_dir_index = 0;

    void Forward() { cell += }
};

bool operator>(const State& lhs, const State& rhs) {
    return lhs.current_cost > rhs.current_cost;
}

int main() {
    // int row_count;
    // int column_count;
    // std::cin >> row_count >> column_count;

    // std::vector<std::string> grid(row_count);
    // for (auto& row : grid) {
    //     std::cin >> row;
    // }

    // Cell start;
    // Cell finish;
    // std::cin >> start.row >> start.column;
    // --start.row;
    // --start.column;
    // std::cin >> finish.row >> finish.column;
    // --finish.row;
    // --finish.column;

    std::priority_queue<State, std::vector<State>, std::greater<State>> states;
    states.push({{0, 0}, 0, 0});
    states.push({{1, 1}, 1, 1});

    std::cout << states.top().current_cost << std::endl;
}