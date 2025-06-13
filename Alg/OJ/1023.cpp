#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;
const int MAXN = 505;
const int MAXM = 105;

struct Edge
{
    int to, w;
};

int T, n, E, s, t, M;
int B[MAXN]; // 国家过路费
vector<Edge> adj[MAXN];
int dist[MAXN][MAXM]; // dist[u][money]

void solve()
{
    cin >> n >> E >> s >> t >> M;
    for (int i = 1; i <= n; ++i)
        cin >> B[i];
    for (int i = 0; i < n + 5; ++i)
        adj[i].clear();
    for (int i = 0; i < E; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // 初始化
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= M; ++j)
            dist[i][j] = INF;

    // 小A出发国不需要付费
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
    dist[s][0] = 0;
    pq.push({0, s, 0}); // (路径长度, 国家编号, 当前已用费用)

    while (!pq.empty())
    {
        auto [d, u, cost] = pq.top();
        pq.pop();
        if (d > dist[u][cost])
            continue;

        for (auto &[v, w] : adj[u])
        {
            int toll = B[v]; // 进入v国需要付费
            int next_cost = cost + toll;
            if (next_cost <= M && dist[v][next_cost] > d + w)
            {
                dist[v][next_cost] = d + w;
                pq.push({dist[v][next_cost], v, next_cost});
            }
        }
    }

    int ans = INF;
    for (int i = 0; i <= M; ++i)
        ans = min(ans, dist[t][i]);

    cout << (ans == INF ? -1 : ans) << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> T;
    while (T--)
        solve();
    return 0;
}
