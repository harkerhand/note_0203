#include <bits/stdc++.h>
using namespace std;
#define int long long

inline double dis(const pair<int, int> &a, const pair<int, int> &b)
{
    int dx = a.first - b.first;
    int dy = a.second - b.second;
    return dx * dx + dy * dy;
}

double divide(vector<pair<int, int>> &a, int l, int r)
{
    if (l >= r)
        return LONG_LONG_MAX;
    if (l + 1 == r)
        return dis(a[l], a[r]);
    int mid = (l + r) / 2;
    int mid_x = a[mid].first;
    double d1 = divide(a, l, mid);
    double d2 = divide(a, mid + 1, r);
    double mn = min(d1, d2);

    // 构造临界区
    vector<pair<int, int>> b;
    for (int i = l; i <= r; i++)
    {
        if (abs(a[i].first - mid_x) < mn)
        {
            b.push_back(a[i]);
        }
    }
    sort(b.begin(), b.end(), [](pair<int, int> &a, pair<int, int> &b)
         { return a.second >= b.second; });

    // 在临界区内寻找最小距离
    for (int i = 0; i < b.size(); i++)
    {
        for (int j = 1; j < 7 && i + j < b.size(); j++)
        {
            mn = min(mn, dis(b[i], b[i + j]));
        }
    }
    return mn;
}

void solve()
{
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i].first >> a[i].second;
    sort(a.begin(), a.end(), [](pair<int, int> &a, pair<int, int> &b)
         { return a.first == b.first ? a.second >= b.second : a.first >= b.first; });
    cout << fixed << setprecision(2) << sqrt(divide(a, 0, n - 1)) << endl;
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
}