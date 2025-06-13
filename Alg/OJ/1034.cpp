#include <bits/stdc++.h>
using namespace std;
#define int long long

void dfs(int node, int parent, vector<vector<int>> &edges, vector<vector<int>> &dp)
{
    dp[node][0] = 0;
    dp[node][1] = 1;
    for (auto child : edges[node])
    {
        if (child != parent)
        {
            dfs(child, node, edges, dp);
            dp[node][1] += dp[child][0];
            dp[node][0] += max(dp[child][0], dp[child][1]);
        }
    }
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<vector<int>> edges(n + 1);
        for (int i = 0; i < n - 1; i++)
        {
            int u, v;
            cin >> u >> v;
            edges[u].push_back(v);
            edges[v].push_back(u);
        }
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));
        dfs(1, -1, edges, dp);
        cout << max(dp[1][0], dp[1][1]) << endl;
    }
}