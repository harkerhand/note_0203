#include <bits/stdc++.h>
using namespace std;

int maxExpressionValue(const vector<int> &nums, int K)
{
    int N = nums.size();
    vector<vector<vector<int>>> dp(N, vector<vector<int>>(N, vector<int>(K + 1, 0)));
    // 初始化dp[i][i][0]，即单个数的值
    for (int i = 0; i < N; ++i)
    {
        dp[i][i][0] = nums[i];
    }
    // 枚举区间长度 len = j - i
    for (int len = 1; len < N; ++len)
    {
        for (int i = 0; i + len < N; ++i)
        {
            int j = i + len;
            for (int k = 0; k <= K; ++k)
            {
                int maxVal = numeric_limits<int>::min();
                // 选一个 m 作为分割点
                for (int m = i; m < j; ++m)
                {
                    for (int k1 = 0; k1 <= k; ++k1)
                    {
                        if (k1 < k)
                        { // 乘号情况
                            maxVal = max(maxVal, dp[i][m][k1] * dp[m + 1][j][k - k1 - 1]);
                        }
                        // 加号情况
                        maxVal = max(maxVal, dp[i][m][k1] + dp[m + 1][j][k - k1]);
                    }
                }
                dp[i][j][k] = maxVal;
            }
        }
    }

    return dp[0][N - 1][K];
}
int main()
{
    vector<int> nums = {1, 2, 3, 4, 5};
    int K = 2;
    cout << "max:" << maxExpressionValue(nums, K) << endl;
    return 0;
}
