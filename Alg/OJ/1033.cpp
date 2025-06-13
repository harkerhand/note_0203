#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXD = 50000 + 5;
int parent[MAXD];

// 并查集：查找当前时间点的父亲（即可用时间）
int find(int x)
{
    if (x != parent[x])
        parent[x] = find(parent[x]);
    return parent[x];
}

signed main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;

        vector<pair<int, int>> jobs(n); // (deadline, profit)
        for (int i = 0; i < n; ++i)
            cin >> jobs[i].first >> jobs[i].second;

        // 按 profit 从大到小排序
        sort(jobs.begin(), jobs.end(), [](auto &a, auto &b)
             { return a.second > b.second; });

        // 初始化并查集，每个时间点的父节点是自己
        for (int i = 0; i < MAXD; ++i)
            parent[i] = i;

        int total_profit = 0;

        for (auto &[d, p] : jobs)
        {
            int available_time = find(d); // 找到小于等于 d 的可用时间点
            if (available_time > 0)
            {
                total_profit += p;
                // 把这个时间点占用掉：它的父亲设为 available_time - 1
                parent[available_time] = available_time - 1;
            }
        }

        cout << total_profit << '\n';
    }

    return 0;
}
