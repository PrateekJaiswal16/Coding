#include "bits/stdc++.h"
#define int long long
#define uint unsigned long long
#define vi vector<int>
#define vvi vector<vi>
#define vb vector<bool>
#define vvb vector<vb>
#define fr(i, n) for (int i = 0; i < (n); i++)
#define rep(i, a, n) for (int i = (a); i <= (n); i++)
#define nl cout << "\n"
#define dbg(var) cout << #var << "=" << var << " "
#define all(v) v.begin(), v.end()
#define sz(v) (int)(v.size())
#define srt(v) sort(v.begin(), v.end())         // sort
#define mxe(v) *max_element(v.begin(), v.end()) // find max element in vector
#define mne(v) *min_element(v.begin(), v.end()) // find min element in vector
#define unq(v) v.resize(distance(v.begin(), unique(v.begin(), v.end())));
// make sure to sort before applying unique // else only consecutive duplicates would be removed
#define bin(x, y) bitset<y>(x)
using namespace std;
int MOD = 1e9 + 7; // Hardcoded, directly change from here for functions!

void modadd(int &a, int b) { a = ((a % MOD) + (b % MOD)) % MOD; }
void modsub(int &a, int b) { a = ((a % MOD) - (b % MOD) + MOD) % MOD; }
void modmul(int &a, int b) { a = ((a % MOD) * (b % MOD)) % MOD; }
// ================================== take ip/op like vector,pairs directly!==================================
template <typename typC, typename typD>
istream &operator>>(istream &cin, pair<typC, typD> &a) { return cin >> a.first >> a.second; }
template <typename typC>
istream &operator>>(istream &cin, vector<typC> &a)
{
    for (auto &x : a)
        cin >> x;
    return cin;
}
template <typename typC, typename typD>
ostream &operator<<(ostream &cout, const pair<typC, typD> &a) { return cout << a.first << ' ' << a.second; }
template <typename typC, typename typD>
ostream &operator<<(ostream &cout, const vector<pair<typC, typD>> &a)
{
    for (auto &x : a)
        cout << x << '\n';
    return cout;
}
template <typename typC>
ostream &operator<<(ostream &cout, const vector<typC> &a)
{
    int n = a.size();
    if (!n)
        return cout;
    cout << a[0];
    for (int i = 1; i < n; i++)
        cout << ' ' << a[i];
    return cout;
}
// ===================================END Of the input module ==========================================

class SGTree
{
    vector<int> seg;

public:
    SGTree(int n)
    {
        seg.resize(4 * n + 1);
    }

    void build(int ind, int low, int high, vector<int> &a)
    {
        if (low == high)
        {
            seg[ind] = a[low];
            return;
        }
        int mid = (low + high) >> 1;
        build(2 * ind + 1, low, mid, a);
        build(2 * ind + 2, mid + 1, high, a);
        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    int query(int ind, int low, int high, int L, int R)
    {

        if (high < L || R < low)
        {
            return INT_MAX;
        }
        if (L <= low && high <= R)
            return seg[ind];

        int mid = (low + high) >> 1;
        int left = query(2 * ind + 1, low, mid, L, R);
        int right = query(2 * ind + 2, mid + 1, high, L, R);
        return min(left, right);
    }

    void update(int ind, int low, int high, int i, int val)
    {
        if (low == high)
        {
            seg[ind] = val;
            return;
        }
        int mid = (low + high) >> 1;
        if (i <= mid)
            update(2 * ind + 1, low, mid, i, val);
        else
            update(2 * ind + 2, mid + 1, high, i, val);

        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
};

void solve()
{

    int n;
    cin >> n;
    vi a(n);
    cin >> a;

    SGTree sg1(n);
    sg1.build(0, 0, n - 1, a);

    int q;
    cin >> q;

    while (q--)
    {
        int type;
        cin >> type;

        if (type == 1)
        {
            int l, r;
            cin >> l >> r;
            cout << sg1.query(0, 0, n - 1, l, r) << endl;
        }
        else
        {
            int i, val;
            cin >> i >> val;
            sg1.update(0, 0, n - 1, i, val);
            a[i] = val;
        }
    }
}

int32_t main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T = 1;
    // cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}