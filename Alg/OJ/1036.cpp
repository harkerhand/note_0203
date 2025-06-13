#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n, m;
        string s, t;
        cin >> n >> m >> s >> t;

        int count = 0;
        int pos = 0; // 查找的起始位置

        while ((pos = s.find(t, pos)) != string::npos)
            count++, pos++;

        cout << count << endl;
    }
    return 0;
}
