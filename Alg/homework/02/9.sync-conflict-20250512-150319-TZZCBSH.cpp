#include <bits/stdc++.h>
using namespace std;
#define int long long

int maxSubSequnceLen(vector<int> &arr)
{
    int n = arr.size();
    vector<int> dp(n, 1); // dp[i] 表示以 arr[i] 结尾的最长非降子序列长度

    // 填充 dp 数组
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[j] <= arr[i])
            {
                dp[i] = max(dp[i], dp[j] + 1); // 如果 arr[j] <= arr[i]，更新 dp[i]
            }
        }
    }

    // 返回 dp 数组中的最大值
    return *max_element(dp.begin(), dp.end());
}

signed main()
{
    vector<int> arr = {1, 2, -1, -9, 2, 7, -3, 4, 8, 6};
    cout << maxSubSequnceLen(arr) << endl;

    return 0;
}