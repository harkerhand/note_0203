#include <bits/stdc++.h>
using namespace std;
#define int long long

int solve(vector<int> d, vector<int> p)
{
    vector<pair<int, int>> co;
    int max_d = 0;
    for (int i = 0; i < d.size(); i++)
    {
        max_d = max(max_d, d[i]);
        co.push_back({d[i], p[i]});
    }
    sort(co.begin(), co.end(), [](pair<int, int> a, pair<int, int> b)
         { return a.second > b.second; });
    int ans = 0;
    int m = co.size();
    vector<bool> visited(max_d + 1, false);
    for (int i = 0; i < m; i++)
    {
        for (int j = co[i].first; j >= 1; j--)
        {
            if (!visited[j])
            {
                visited[j] = true;
                ans += co[i].second;
                break;
            }
        }
    }
    return ans;
}
signed main()
{
    vector<int> d = {3, 2, 1, 3};
    vector<int> p = {1, 2, 3, 4};
    cout << solve(d, p) << endl;
    return 0;
}