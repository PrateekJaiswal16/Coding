#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
struct info {
    int full, open, close;
    info(int _full = 0, int _open = 0, int _close = 0) {
        full = _full;
        open = _open;
        close = _close;
    }
};

info seg[4 * N];

info merge(info left, info right) {
    info ans = info();
    int match = min(left.open, right.close);
    ans.full = left.full + right.full + match;
    ans.open = left.open + right.open - match;
    ans.close = left.close + right.close - match;
    return ans;
}

void build(int ind, int low, int high, string &s) {
    if (low == high) {
        seg[ind].open = s[low] == '(';
        seg[ind].close = s[low] == ')';
        seg[ind].full = 0;
        return;
    }
    int mid = (low + high) / 2;
    build(2 * ind + 1, low, mid, s);
    build(2 * ind + 2, mid + 1, high, s);
    seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
}

info query(int ind, int low, int high, int l, int r) {
    if (high < l || r < low) return info();
    if (low >= l && high <= r) return seg[ind];

    int mid = (low + high) / 2;
    info left = query(2 * ind + 1, low, mid, l, r);
    info right = query(2 * ind + 2, mid + 1, high, l, r);
    return merge(left, right);
}

void solve() {
    string s;
    cin >> s;
    int n = s.size();

    build(0, 0, n - 1, s);

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        info res = query(0, 0, n - 1, l, r);
        cout << res.full * 2 << endl;
    }
}

int main() {
    int t = 1;
    while (t--) {
        solve();
    }
}
