#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    map<int, int, greater<int>> mp; // 长度为 n 的最小结尾，降序排列
    mp[1] = a[0];                   // 长度为 1 的最小结尾
    for (int i = 1; i < n; i++)
    {
        for (auto &j : mp)
        {
            if (a[i] >= j.second)
            {
                if (mp[j.first + 1] == 0)
                    mp[j.first + 1] = a[i];
                else
                    mp[j.first + 1] = min(mp[j.first + 1], a[i]);
            }

            if (j.first == 1)
                j.second = min(j.second, a[i]);
        }
    }
    int ans = 0;
    for (auto j : mp)
    {
        if (j.first > ans)
            ans = j.first;
    }
    cout << ans << endl;
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