#include <bits/stdc++.h>
using namespace std;

#define INF 1e9
#define MAXN 100

class MinCostMaxFlow
{
public:
    int n, source, sink;
    vector<vector<int>> adj, cost, cap;
    vector<int> dist, parent;

    MinCostMaxFlow(int n) : n(n)
    {
        adj.resize(n);
        cost.resize(n, vector<int>(n, 0));
        cap.resize(n, vector<int>(n, 0));
        dist.resize(n);
        parent.resize(n);
    }

    void addEdge(int u, int v, int c, int w)
    {
        adj[u].push_back(v);
        adj[v].push_back(u); // 添加反向边
        cap[u][v] += c;      // 正向边容量
        cap[v][u] += 0;      // 反向边初始容量为0
        cost[u][v] = w;      // 正向边费用
        cost[v][u] = -w;     // 反向边费用为负
    }

    bool spfa()
    {
        fill(dist.begin(), dist.end(), INF);
        vector<bool> in_queue(n, false);
        queue<int> q;

        dist[source] = 0;
        q.push(source);
        in_queue[source] = true;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            in_queue[u] = false;

            for (int v : adj[u])
            {
                if (cap[u][v] > 0 && dist[u] + cost[u][v] < dist[v])
                {
                    dist[v] = dist[u] + cost[u][v];
                    parent[v] = u;
                    if (!in_queue[v])
                    {
                        q.push(v);
                        in_queue[v] = true;
                    }
                }
            }
        }

        return dist[sink] < INF;
    }

    pair<int, int> minCostMaxFlow(int _source, int _sink)
    {
        source = _source;
        sink = _sink;

        int maxFlow = 0, minCost = 0;

        while (spfa())
        {
            int flow = INF;
            for (int v = sink; v != source; v = parent[v])
            {
                flow = min(flow, cap[parent[v]][v]);
            }
            maxFlow += flow;
            minCost += flow * dist[sink];

            for (int v = sink; v != source; v = parent[v])
            {
                cap[parent[v]][v] -= flow;
                cap[v][parent[v]] += flow; // 增加反向边容量
            }
        }

        return {maxFlow, minCost};
    }
};

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int n, m;
        cin >> n >> m;

        MinCostMaxFlow mcmf(n + m + 2);

        int source = n + m;
        int sink = n + m + 1;

        vector<vector<int>> cost(m, vector<int>(n));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                cin >> cost[i][j];

        for (int i = 0; i < n; i++)
        {
            int k;
            cin >> k;
            for (int j = 0; j < k; j++)
            {
                int woman;
                cin >> woman;
                woman--; // 转为0索引
                mcmf.addEdge(i, n + woman, 1, cost[woman][i]);
            }
            mcmf.addEdge(source, i, 1, 0);
        }

        for (int i = 0; i < m; i++)
        {
            mcmf.addEdge(n + i, sink, 1, 0);
        }

        pair<int, int> result = mcmf.minCostMaxFlow(source, sink);
        cout << result.first << " " << result.second << endl;
    }

    return 0;
}
