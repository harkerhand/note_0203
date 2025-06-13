#include <bits/stdc++.h>
using namespace std;
#define int long long

int n, m;                // n: 男嘉宾数, m: 女嘉宾数
vector<vector<int>> adj; // 邻接矩阵，记录每个男嘉宾喜欢哪些女嘉宾
vector<int> match;       // match[i]表示第i个女嘉宾的匹配男嘉宾
vector<bool> visited;    // 记录在DFS过程中，某个女嘉宾是否已被访问过

// 尝试为男嘉宾u找到一个匹配
bool dfs(int u)
{
    for (int v : adj[u])
    { // 遍历男嘉宾u喜欢的所有女嘉宾v
        if (!visited[v])
        { // 如果v没有被访问过
            visited[v] = true;
            if (match[v] == -1 || dfs(match[v]))
            {                 // 如果女嘉宾v没有匹配，或者当前匹配可以找到新的匹配
                match[v] = u; // v和u匹配
                return true;
            }
        }
    }
    return false;
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        adj.clear();
        adj.resize(n);
        match.clear();
        match.resize(m, -1);

        // 输入男嘉宾的偏好
        for (int i = 0; i < n; i++)
        {
            int k;
            cin >> k;
            adj[i].resize(k);
            for (int j = 0; j < k; j++)
            {
                int x;
                cin >> x;
                adj[i][j] = x - 1; // 女嘉宾编号转换为0-based
            }
        }

        int total_match = 0;
        // 对每个男嘉宾尝试进行匹配
        for (int i = 0; i < n; i++)
        {
            visited.clear();
            visited.resize(m, false);
            if (dfs(i))
            {
                total_match++;
            }
        }

        cout << total_match << endl;
    }
    return 0;
}
