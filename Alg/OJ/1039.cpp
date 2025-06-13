#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> edges(n + 1);
    vector<int> indegree(n + 1, 0);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        indegree[v]++;
    }
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
            q.push(i);
    }
    vector<int> ans;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        ans.push_back(u);
        for (int v : edges[u])
        {
            indegree[v]--;
            if (indegree[v] == 0)
                q.push(v);
        }
    }
    if (ans.size() != n)
    {
        cout << 0 << endl;
        return;
    }
    for (int i = 0; i < n; i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
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