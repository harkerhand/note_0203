#include <bits/stdc++.h>
using namespace std;
#define int long long
void solve()
{
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (auto &i : a)
        cin >> i;
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++)
    {
        int rest = x - a[i];
        if (binary_search(a.begin(), a.end(), rest))
        {
            cout << "yes" << endl;
            return;
        }
    }
    cout << "no" << endl;
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