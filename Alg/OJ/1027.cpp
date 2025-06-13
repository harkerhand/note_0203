#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<tuple<int, int, int>> things(n);
    for (int i = 0; i < n; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        things[i] = {b, a, c}; // 按结束时间排序
    }

    sort(things.begin(), things.end()); // 按 end 排序
    map<int, int> dp;
    dp[0] = 0;

    for (auto [end, start, value] : things)
    {
        auto it = dp.upper_bound(start);
        --it;
        int current = it->second + value;

        // 只有当前更优时，才插入
        if (current > dp.rbegin()->second)
        {
            dp[end] = current;
        }
    }

    cout << dp.rbegin()->second << "\n";
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}
