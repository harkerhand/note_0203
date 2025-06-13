#include <bits/stdc++.h>
using namespace std;
#define int long long

// 并查集
class DisjointSet
{
private:
    vector<int> parent;
    vector<int> rank;

public:
    DisjointSet(int n)
    {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY)
            return;

        if (rank[rootX] < rank[rootY])
        {
            parent[rootX] = rootY;
        }
        else
        {
            parent[rootY] = rootX;
            if (rank[rootX] == rank[rootY])
            {
                rank[rootX]++;
            }
        }
    }

    bool same(int x, int y)
    {
        return find(x) == find(y);
    }
};

void solve()
{
    int n, E;
    cin >> n >> E;
    map<pair<int, int>, int> edges;
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        if (u > v)
            swap(u, v);
        if (edges.find(make_pair(u, v)) == edges.end())
            edges[make_pair(u, v)] = w;
        else
            edges[make_pair(u, v)] = min(edges[make_pair(u, v)], w);
    }
    vector<pair<int, pair<int, int>>> edges_list;
    for (map<pair<int, int>, int>::iterator it = edges.begin(); it != edges.end(); ++it)
    {
        edges_list.push_back(make_pair(it->second, it->first));
    }

    sort(edges_list.begin(), edges_list.end());

    // Kruskal算法实现
    DisjointSet ds(n);
    int mst_weight = 0;
    int edges_count = 0;

    for (size_t i = 0; i < edges_list.size(); ++i)
    {
        int weight = edges_list[i].first;
        int u = edges_list[i].second.first;
        int v = edges_list[i].second.second;

        if (!ds.same(u, v))
        {
            ds.unite(u, v);
            mst_weight += weight;
            edges_count++;

            if (edges_count == n - 1)
            {
                break; // MST完成
            }
        }
    }

    // 检查图是否连通
    if (edges_count != n - 1)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << mst_weight << endl;
    }
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
}