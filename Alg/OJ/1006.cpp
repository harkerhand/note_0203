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
        for (int i = 0; i < n; i++)
            cin >> a[i];
        make_heap(a.begin(), a.end(), greater<int>());
        for (auto x : a)
            cout << x << " ";
        cout << endl;
    }
}