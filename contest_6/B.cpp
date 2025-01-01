#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string encrypted_message;
    cin >> encrypted_message;

    int shift_count;
    cin >> shift_count;

    vector<array<int, 3>> shifts(shift_count);
    for (int idx = 0; idx < shift_count; idx++) {
        cin >> shifts[idx][0] >> shifts[idx][1] >> shifts[idx][2];
    }

    for (int idx = shift_count - 1; idx >= 0; idx--) {
        int left = shifts[idx][0];
        int right = shifts[idx][1];
        int shift = shifts[idx][2];
        int segment_length = right - left + 1;

        shift %= segment_length;

        string segment = encrypted_message.substr(left - 1, segment_length);
        string rotated_segment =
            segment.substr(shift) + segment.substr(0, shift);

        for (int pos = 0; pos < segment_length; pos++) {
            encrypted_message[left - 1 + pos] = rotated_segment[pos];
        }
    }

    cout << encrypted_message << "\n";
    return 0;
}
