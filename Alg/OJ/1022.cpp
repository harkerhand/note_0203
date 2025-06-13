#include <bits/stdc++.h>
using namespace std;
#define int long long

int lcs(string s1, string s2)
{
    int n = s1.size();
    int m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            }
        }
    }
    return dp[n][m];
}

void solve()
{
    string a, b;
    cin >> a >> b;
    cout << lcs(a, b) << endl;
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
}