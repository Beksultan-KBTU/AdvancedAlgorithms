#include <iostream>
#include <map>
#include <set>
#include <vector>

struct Rectangle {
    int left_x;
    int left_y;
    int right_x;
    int right_y;
    int color;
    int order;
};

struct Segment {
    int left;
    int right;
    int color;
    int order;
};

std::map<int, int> CountColorLengths(std::vector<Segment> segments) {
    std::map<int, int> color_summary_lengths;
    
}

int main() {
    int max_x;
    int max_y;
    std::cin >> max_x >> max_y;

    int size;
    std::cin >> size;

    std::vector<Rectangle> rectangles(size);
    int current_index = 1;
    for (auto& rect : rectangles) {
        std::cin >> rect.left_x >> rect.left_y;
        std::cin >> rect.right_x >> rect.right_y;

        std::cin >> rect.color;

        ++current_index;
        rect.order = current_index;
    }

    std::cout << "rect size: " << rectangles.size() << std::endl;

    std::cout << "rects: " << std::endl;
    for (const auto& rect : rectangles) {
        std::cout << "[" << rect.left_x << ", " << rect.right_x << "]" << " - "
                  << "[" << rect.left_y << ", " << rect.right_y << "]"
                  << std::endl;
    }
    std::cout << std::endl;

    std::set<int> unique_x = {0, max_x};
    for (const auto& rect : rectangles) {
        unique_x.insert(rect.left_x);
        unique_x.insert(rect.right_x);
    }

    std::cout << "unique_x size: " << unique_x.size() << std::endl;
    for (auto x : unique_x) {
        std::cout << "---" << x << std::endl;
    }
    std::cout << std::endl;

    std::vector<std::pair<int, std::vector<Segment>>> each_unique_segment;
    for (auto it = unique_x.begin();
         it != unique_x.end() && std::next(it) != unique_x.end(); ++it) {
        int current_x = *it;
        int next_x = *std::next(it);
        int len = next_x - current_x;
        std::vector<Segment> inner_segments = {Segment{0, max_y, 1, 1}};

        for (const auto& rect : rectangles) {
            if (rect.left_x <= current_x && next_x <= rect.right_x) {
                inner_segments.push_back(
                    {rect.left_y, rect.right_y, rect.color, rect.order});
            }
        }
        each_unique_segment.push_back({len, inner_segments});
    }

    for (const auto& [len, inner_segments] : each_unique_segment) {
        std::cout << "---len: " << len << std::endl;
        for (const Segment& segment : inner_segments) {
            std::cout << "[" << segment.left << ", " << segment.right << "] - ";
        }
        std::cout << std::endl;
    }
}