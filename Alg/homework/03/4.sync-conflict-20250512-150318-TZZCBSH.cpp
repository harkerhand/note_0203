#include <bits/stdc++.h>
using namespace std;
#define int long long

int solve(vector<bool> p)
{
    int ans = 0;
    int m = p.size();
    vector<bool> visited(m, false);
    for (int i = 0; i < m; i++)
    {
        if (visited[i])
            continue;
        for (int j = i + 1; j < m; j++)
        {
            if (visited[j])
                continue;
            if (p[i] != p[j])
            {
                visited[j] = true;
                ans += j - i;
                break;
            }
        }
    }
    return ans;
}

signed main()
{
    vector<bool> p = {1, 1, 0, 1, 0, 0, 0, 1};
    cout << solve(p) << endl;
    return 0;
}