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

signed main()
{
    string s1 = "AGGTAB";
    string s2 = "GXTXAYB";
    // Common subsequence is "GTAB"
    assert(lcs(s1, s2) == 4);
    return 0;
}