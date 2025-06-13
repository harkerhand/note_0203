#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, c;
    cin >> c >> n;
    vector<int> weight(n), value(n);
    for (int i = 0; i < n; ++i)
        cin >> weight[i] >> value[i];
    vector<int> dp(c + 1, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = weight[i]; j <= c; j++)
        {
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }
    cout << dp[c] << endl;
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}