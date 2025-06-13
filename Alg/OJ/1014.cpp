#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto &x : a)
            cin >> x;
        int ans = INT_MIN, now = a[0];
        for (int i = 1; i < n; i++)
        {
            if (now < 0)
            {
                ans = max(ans, now);
                now = a[i];
            }
            else
            {
                now += a[i];
                ans = max(ans, now);
            }
        }
        cout << ans << endl;
    }
}