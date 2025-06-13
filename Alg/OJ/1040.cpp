#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int m, n, ta;
        cin >> m >> n >> ta;
        vector<vector<int>> a(m, vector<int>(n));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                cin >> a[i][j];
        int row = 0, col = n - 1;
        bool found = false;
        while (row < m && col >= 0)
        {
            int val = a[row][col];
            if (val == ta)
            {
                found = true;
                break;
            }
            else if (val > ta)
                col--;
            else
                row++;
        }
        cout << boolalpha << found << endl;
    }
}