#include <algorithm>
#include <cassert>
#include <cstddef>
#include <ios>
#include <iostream>
#include <sstream>
#include <vector>

class UnionFind {
public:
    UnionFind(int n) {
        parent_.resize(n);
        for (int i = 0; i < n; ++i) {
            parent_[i] = i;
        }
    }

    int FindSet(int index) {
        if (parent_[index] != index) {
            parent_[index] = FindSet(parent_[index]);
        }
        return parent_[index];
    }

    bool UnionSet(int index, int jindex) {
        index = FindSet(index);
        jindex = FindSet(jindex);
        if (index == jindex) {
            return false;  // Цикл или повторная операция
        }
        parent_[jindex] = index;
        return true;
    }

private:
    std::vector<int> parent_;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int size;
    int queries_count;
    std::cin >> size >> queries_count;

    UnionFind dsu(size);
    for (int i = 0; i < queries_count; ++i) {
        std::string line;
        std::getline(std::cin >> std::ws, line);
        std::istringstream stream(line);

        std::vector<int> query;
        int x;
        while (stream >> x) {
            query.push_back(x);
        }

        if (query.size() == 1) {
            int vertex = query[0] - 1;
            std::cout << dsu.FindSet(vertex) + 1 << '\n';
        } else if (query.size() == 2) {
            int parent = query[0] - 1;
            int child = query[1] - 1;

            if (dsu.FindSet(child) != child) {
                std::cout << 0 << '\n';
            } else if (dsu.UnionSet(parent, child)) {
                std::cout << 1 << '\n';
            } else {
                std::cout << 0 << '\n';
            }
        } else {
            assert(false);
        }
    }

    return 0;
}
