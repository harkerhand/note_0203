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
        vector<int> white;
        vector<int> black;
        for (int i = 0; i < 2 * n; i++)
        {
            int x;
            cin >> x;
            if (x == 0)
                white.push_back(i);
            else
                black.push_back(i);
        }
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            ans += abs(white[i] - black[i]);
        }
        cout << ans << endl;
    }
}