#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, c;
    cin >> n >> c;
    vector<int> weight(n), value(n);
    for (int i = 0; i < n; i++)
        cin >> weight[i] >> value[i];

    vector<int> dp(c + 1, LLONG_MIN);
    dp[0] = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = c; j >= weight[i]; j--)
        {
            if (dp[j - weight[i]] != LLONG_MIN)
                dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }

    if (dp[c] < 0)
        cout << 0 << endl;
    else
        cout << dp[c] << endl;
}

signed main()
{
    int m;
    cin >> m;
    while (m--)
        solve();
}
