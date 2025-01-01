#include <cassert>
#include <iostream>
#include <vector>

struct Node {
    int sum;
    int index;
};

class SegmentTree {
private:
    int size_;
    std::vector<Node> tree_;

    static Node Merge(const Node& lhs, const Node& rhs) {
        return {lhs.sum + rhs.sum, -1};
    }

    void Update(int index, Node value, int vertex, int vertex_left,
                int vertex_right) {
        if (vertex_right - vertex_left == 1) {
            tree_[vertex] = value;
            return;
        }
        int vertex_mid = (vertex_left + vertex_right) / 2;
        if (index < vertex_mid) {
            Update(index, value, 2 * vertex + 1, vertex_left, vertex_mid);
        } else {
            Update(index, value, 2 * vertex + 2, vertex_mid, vertex_right);
        }
        tree_[vertex] = Merge(tree_[2 * vertex + 1], tree_[2 * vertex + 2]);
    }

    Node FindOrder(int pref_sum, int vertex, int vertex_left,
                   int vertex_right) {
        if (vertex_right - vertex_left == 1) {
            return tree_[vertex];
        }
        int vertex_mid = (vertex_left + vertex_right) / 2;
        if (tree_[2 * vertex + 1].sum >= pref_sum) {
            return FindOrder(pref_sum, 2 * vertex + 1, vertex_left, vertex_mid);
        }
        return FindOrder(pref_sum - tree_[2 * vertex + 1].sum, 2 * vertex + 2,
                         vertex_mid, vertex_right);
    }

    int GetSum(int left_index, int right_index, int vertex, int vertex_left,
               int vertex_right) {
        if (vertex_right <= left_index || right_index <= vertex_left) {
            return 0;
        }
        if (left_index <= vertex_left && vertex_right <= right_index) {
            return tree_[vertex].sum;
        }
        int vertex_mid = (vertex_left + vertex_right) / 2;
        int res_left = GetSum(left_index, right_index, 2 * vertex + 1,
                              vertex_left, vertex_mid);
        int res_right = GetSum(left_index, right_index, 2 * vertex + 2,
                               vertex_mid, vertex_right);

        return res_left + res_right;
    }

public:
    SegmentTree(int size) {
        size_ = 1;
        while (size_ < size) {
            size_ *= 2;
        }
        tree_.assign(2 * size_ - 1, {0, -1});
    }

    void Update(int index, Node value) { Update(index, value, 0, 0, size_); }

    Node FindOrder(int pref_sum) {
        assert(pref_sum <= tree_[0].sum);
        return FindOrder(pref_sum, 0, 0, size_);
    }

    int GetSum(int left_index, int right_index) {
        return GetSum(left_index, right_index + 1, 0, 0, size_);
    }
};

int main() {
    int size;
    std::cin >> size;

    int order;
    std::cin >> order;

    SegmentTree segtree(size);

    for (int index = 0; index < size; ++index) {
        segtree.Update(index, {1, index + 1});
    }

    int current_position = 0;

    for (int round = 0; round < size; ++round) {
        int remaining_size = size - round;
        int current_order = (current_position + order - 1) % remaining_size + 1;

        Node found_node = segtree.FindOrder(current_order);
        int found_index = found_node.index;

        std::cout << found_index << " ";

        segtree.Update(found_index - 1, {0, found_index});

        current_position = current_order - 1;
    }

    std::cout << std::endl;
    return 0;
}
