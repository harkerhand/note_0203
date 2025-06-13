#include <bits/stdc++.h>
using namespace std;
#define int long long

using Point = pair<int, int>;

vector<double> solve(vector<Point> points, double d)
{
    vector<pair<double, double>> blanks = vector<pair<double, double>>(points.size(), {0, 0});
    for (int i = 0; i < points.size(); i++)
    {
        int x = points[i].first;
        int y = points[i].second;
        blanks[i] = {x - sqrt(d * d - y * y), x + sqrt(d * d - y * y)};
    }
    sort(blanks.begin(), blanks.end(), [](const pair<double, double> &a, const pair<double, double> &b)
         { return a.second < b.second; });
    double last = -1e9;
    vector<double> ans;
    for (int i = 0; i < blanks.size(); i++)
    {
        if (blanks[i].first > last)
        {
            ans.push_back(blanks[i].second);
            last = blanks[i].second;
        }
    }
    return ans;
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, d;
        cin >> n >> d;
        vector<Point> points(n);
        for (int i = 0; i < n; i++)
        {
            cin >> points[i].first >> points[i].second;
        }
        vector<double> ans = solve(points, d);
        cout << ans.size() << endl;
    }
}