#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, E, s, t;
    cin >> n >> E >> s >> t;
    vector<vector<int>> edges(n + 1, vector<int>(n + 1, LLONG_MAX));
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges[u][v] = min(edges[u][v], w);
        edges[v][u] = min(edges[v][u], w);
    }
    vector<int> dist(n + 1, LLONG_MAX);
    dist[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s}); // beginning
    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u])
            continue;
        for (int v = 1; v <= n; v++)
        {
            if (edges[u][v] != LLONG_MAX)
            {
                if (dist[u] + edges[u][v] < dist[v])
                {
                    dist[v] = dist[u] + edges[u][v];
                    pq.push({dist[v], v});
                }
            }
        }
    }
    cout << (dist[t] == LLONG_MAX ? -1 : dist[t]) << "\n";
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
}