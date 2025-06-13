#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int m;
    cin >> m;
    vector<int> days(m);
    for (int i = 0; i < m; i++)
    {
        cin >> days[i];
    }
    vector<int> costs(3);
    cin >> costs[0] >> costs[1] >> costs[2];
    vector<int> dp(366, 0);
    for (int i = 1; i < 366; i++)
    {
        if (binary_search(days.begin(), days.end(), i))
        {
            dp[i] = min({dp[i - 1] + costs[0], dp[max(0LL, i - 7)] + costs[1], dp[max(0LL, i - 30)] + costs[2]});
        }
        else
        {
            dp[i] = dp[i - 1];
        }
    }
    cout << dp[365] << endl;
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