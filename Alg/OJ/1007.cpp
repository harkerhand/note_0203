#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        int k;
        cin >> n >> k;
        string s;
        cin >> s;
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        for (int i = 1; i <= n; i++)
        {
            dp[i][0] = stoll(s.substr(0, i));
        }
        for (int K = 1; K <= k; K++)
        {
            for (int i = K + 1; i <= n; i++)
            {
                for (int j = K; j < i; j++)
                {
                    dp[i][K] = max(dp[i][K], dp[j][K - 1] * stoll(s.substr(j, i - j)));
                }
            }
        }
        cout << dp[n][k] << endl;
    }
}