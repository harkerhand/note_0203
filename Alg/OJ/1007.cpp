#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int M;
    cin >> M;
    while (M--)
    {
        int N, K;
        cin >> N >> K;
        string number;
        cin >> number;
        // dp[i][k] 表示前 i 位数字分成 k + 1 组的最大乘积
        vector<vector<int>> dp(N + 1, vector<int>(K + 1, 0));
        for (int i = 1; i <= N; i++)
        {
            dp[i][0] = stoll(number.substr(0, i)); // 前 i 位数字作为一组
        }
        // 枚举分组数 K
        for (int k = 1; k <= K; k++)
        {
            // 枚举前 i 位数字
            for (int i = k + 1; i <= N; i++)
            {
                // 枚举切分点 j
                for (int j = k; j < i; j++)
                {
                    dp[i][k] = max(dp[i][k], dp[j][k - 1] * stoll(number.substr(j, i - j)));
                }
            }
        }
        cout << dp[N][K] << endl; // 输出前 N 位数字分成 K + 1 组的最大乘积
    }
}