#include <bits/stdc++.h>
using namespace std;
#define int long long

int solve(vector<int> c, vector<int> y)
{
    int n = c.size();
    int ans = c[0] * y[0];
    for (int i = 1; i < n; i++)
    {
        c[i] = min(c[i], c[i - 1] + 1);
        ans += c[i] * y[i];
    }
    return ans;
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> c(n), y(n);
        for (int i = 0; i < n; i++)
            cin >> c[i];
        for (int i = 0; i < n; i++)
            cin >> y[i];
        cout << solve(c, y) << endl;
    }
    return 0;
}