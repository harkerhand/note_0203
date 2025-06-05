#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<double> solve(vector<int> p, vector<int> w, int M)
{
    int n = p.size();
    vector<pair<double, int>> profit = vector<pair<double, int>>(n, {0, 0});
    for (int i = 0; i < n; i++)
    {
        profit[i] = {(double)p[i] / w[i], i};
    }
    sort(profit.begin(), profit.end(), greater<pair<double, int>>());
    vector<double> ans(n, 0);
    while (M > 0 && profit.size() > 0)
    {
        int i = profit[0].second;
        if (w[i] <= M)
        {
            ans[i] = 1;
            M -= w[i];
        }
        else
        {
            ans[i] = (double)M / w[i];
            M = 0;
        }
        profit.erase(profit.begin());
    }
    return ans;
}

signed main()
{
    vector<int> p = {100, 120, 60};
    vector<int> w = {20, 30, 10};
    int M = 50;
    vector<double> ans = solve(p, w, M);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }

    return 0;
}