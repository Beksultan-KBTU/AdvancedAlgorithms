#include <bits/stdc++.h>
using namespace std;

struct Range3D {
    int x1, y1, z1, x2, y2, z2;
};

class Fenw3D {
public:
    Fenw3D(int size) : size_(size) {
        fenw_.assign((size_ + 1) * (size_ + 1) * (size_ + 1), 0);
    }

    void Update(int xx, int yy, int zz, int64_t value) {
        for (int cx = xx + 1; cx <= size_; cx += cx & -cx) {
            for (int cy = yy + 1; cy <= size_; cy += cy & -cy) {
                for (int cz = zz + 1; cz <= size_; cz += cz & -cz) {
                    int index = ((cx * (size_ + 1) + cy) * (size_ + 1) + cz);
                    fenw_[index] += value;
                }
            }
        }
    }

    int64_t Query(int xx, int yy, int zz) {
        int64_t result = 0;
        for (int cx = xx + 1; cx > 0; cx -= cx & -cx) {
            for (int cy = yy + 1; cy > 0; cy -= cy & -cy) {
                for (int cz = zz + 1; cz > 0; cz -= cz & -cz) {
                    int index = ((cx * (size_ + 1) + cy) * (size_ + 1) + cz);
                    result += fenw_[index];
                }
            }
        }
        return result;
    }

    int64_t GetSum(const Range3D& range) {
        int64_t total = Query(range.x2, range.y2, range.z2);
        int64_t subtract_x1 = Query(range.x1 - 1, range.y2, range.z2);
        int64_t subtract_y1 = Query(range.x2, range.y1 - 1, range.z2);
        int64_t subtract_z1 = Query(range.x2, range.y2, range.z1 - 1);
        int64_t add_xy1 = Query(range.x1 - 1, range.y1 - 1, range.z2);
        int64_t add_xz1 = Query(range.x1 - 1, range.y2, range.z1 - 1);
        int64_t add_yz1 = Query(range.x2, range.y1 - 1, range.z1 - 1);
        int64_t subtract_xyz1 = Query(range.x1 - 1, range.y1 - 1, range.z1 - 1);

        return total - subtract_x1 - subtract_y1 - subtract_z1 + add_xy1 +
               add_xz1 + add_yz1 - subtract_xyz1;
    }

private:
    int size_;
    vector<int64_t> fenw_;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int dimension;
    cin >> dimension;
    Fenw3D fenw(dimension);

    while (true) {
        int operation_type;
        cin >> operation_type;
        if (operation_type == 1) {
            int xx;
            int yy;
            int zz;
            int64_t value;
            cin >> xx >> yy >> zz >> value;
            fenw.Update(xx, yy, zz, value);
        } else if (operation_type == 2) {
            Range3D range;
            cin >> range.x1 >> range.y1 >> range.z1 >> range.x2 >> range.y2 >>
                range.z2;
            cout << fenw.GetSum(range) << "\n";
        } else {
            break;
        }
    }

    return 0;
}
