#include <cstddef>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

struct Point {
    double x, y;
};

double Dist(const Point& lhs, const Point& rhs) {
    return (lhs.x - rhs.x) * (lhs.x - rhs.x) +
           (lhs.y - rhs.y) * (lhs.y - rhs.y);
}

void Dfs(int index, double radius, const std::vector<Point>& points,
         std::vector<bool>& used) {
    used[index] = true;
    for (size_t next_index = 0; next_index < used.size(); ++next_index) {
        if (!used[next_index] &&
            Dist(points[index], points[next_index]) <= radius * radius) {
            Dfs(next_index, radius, points, used);
        }
    }
}

bool Check(double radius, const std::vector<Point>& points,
           std::vector<bool>& used) {
    for (size_t index = 0; index < used.size(); ++index) {
        used[index] = false;
    }
    Dfs(0, radius, points, used);

    return std::accumulate(used.begin(), used.end(), 0) ==
           static_cast<int>(used.size());
}

int main() {
    int size;
    std::cin >> size;
    std::vector<Point> points(size);
    for (auto& point : points) {
        std::cin >> point.x >> point.y;
    }

    const double kEpsilon = 1e-5;
    const double kMax = 1e10;

    double left = 0;
    double right = kMax;
    double best_answer = 0;

    std::vector<bool> used(size, false);

    while (right - left > kEpsilon) {
        double mid = (left + right) / 2;
        if (Check(mid, points, used)) {
            best_answer = mid;
            right = mid;
        } else {
            left = mid;
        }
    }

    const int kOtak = 10;
    std::cout << std::fixed << std::setprecision(kOtak);
    std::cout << best_answer << std::endl;
}