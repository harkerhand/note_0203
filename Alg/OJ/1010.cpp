#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, x;
        cin >> n >> x;
        vector<int> a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];

        int l = 0, r = n - 1, mid, pre;
        while (l <= r)
        {
            pre = mid;
            mid = (l + r) / 2;
            if (a[mid] == x)
            {
                break;
            }
            if (a[mid] > x)
                r = mid - 1;
            else
                l = mid + 1;
        }
        cout << (a[mid] == x ? "success" : "not found") << ", father is " << (a[mid] == x ? a[pre] : a[mid]) << endl;
    }
}