#include <bits/stdc++.h>
using namespace std;
#define int long long

struct Edge
{
    int to, length;
};

int getMinPathDist(int n, vector<vector<Edge>> &graph, vector<int> &cost, int M, int s, int d)
{
    vector<vector<int>> dp(n, vector<int>(M + 1, INT_MAX));

    if (M >= cost[s])
        dp[s][M - cost[s]] = 0;

    for (int money = M; money >= 0; --money)
    {
        for (int u = 0; u < n; ++u)
        {
            if (dp[u][money] == INT_MAX)
                continue;
            for (const Edge &edge : graph[u])
            {
                int v = edge.to;
                int w = edge.length;
                if (money >= cost[v])
                {
                    int newMony = money - cost[v];
                    dp[v][newMony] = min(dp[v][newMony], dp[u][money] + w);
                }
            }
        }
    }

    int minDist = INT_MAX;
    for (int money = 0; money <= M; ++money)
    {
        minDist = min(minDist, dp[d][money]);
    }
    return minDist;
}

signed main()
{
    int n = 6, M = 100, s = 0, d = 4;
    vector<vector<Edge>> graph(n);
    vector<int> cost = {2, 3, 5, 1, 4, 90}; // 顶点过路费

    // 添加边
    graph[0].push_back({1, 4});
    graph[1].push_back({0, 4});
    graph[0].push_back({5, 2});
    graph[5].push_back({0, 2});
    graph[1].push_back({2, 2});
    graph[2].push_back({1, 2});
    graph[2].push_back({3, 3});
    graph[3].push_back({2, 3});
    graph[3].push_back({4, 2});
    graph[4].push_back({3, 2});
    graph[4].push_back({5, 2});
    graph[5].push_back({4, 2});

    int result = getMinPathDist(n, graph, cost, M, s, d);
    cout << result << endl;
    return 0;
}