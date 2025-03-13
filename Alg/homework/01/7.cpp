#include <bits/stdc++.h>
using namespace std;
#define int long long

int fullPackage(int n, int C, vector<int> w, vector<int> v)
{
    vector<int> dp(C + 1, -1e9 - 7);
    dp[0] = 0;
    for (int i = 0; i < n; i++)
    {
        for (int c = C; c >= w[i]; --c)
        {
            dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
        }
    }
    return dp[C] == -1e9 - 7 ? -1 : dp[C];
}

signed main()
{
    int n = 4, C = 10;
    vector<int> sizes = {2, 3, 5, 7};  // 物品大小
    vector<int> values = {3, 4, 6, 8}; // 物品价值

    int result = fullPackage(n, C, sizes, values);
    cout << result << endl;

    return 0;
}