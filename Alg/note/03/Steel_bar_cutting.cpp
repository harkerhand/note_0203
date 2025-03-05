#include <bits/stdc++.h>
using namespace std;
#define int long long

struct Steel
{
    // weight of steel
    int length;
    // value of steel
    int price;
};

// 自底向上的动态规划
// steels: 钢条的价格表
int cutSteel_v1(vector<Steel> &steels, int n)
{
    vector<int> dp(n + 1, 0);
    int m = steels.size();
    for (int i = 1; i <= n; i++)
    {
        auto &maxValue = dp[i];
        for (int j = 0; j < m; j++)
        {
            auto &weight = steels[j].length;
            auto &value = steels[j].price;
            if (i < weight)
                continue;
            maxValue = max(maxValue, value + dp[i - weight]);
        }
    }
    return dp[n];
}

// 递归备忘录
int cutSteel_v2(vector<Steel> &steels, int n, vector<int> &dp)
{
    if (n == 0)
        return 0;
    if (dp[n] != -1)
        return dp[n];
    int m = steels.size();
    auto &maxValue = dp[n];
    for (int i = 0; i < m; i++)
    {
        auto &weight = steels[i].length;
        auto &value = steels[i].price;
        if (n < weight)
            continue;
        maxValue = max(maxValue, value + cutSteel_v2(steels, n - weight, dp));
    }
    return dp[n];
}

signed main()
{
    vector<Steel> steels = {{1, 1}, {2, 5}, {3, 8}, {4, 9}, {5, 10}, {6, 17}, {7, 17}, {8, 20}};
    cout << cutSteel_v1(steels, 8) << endl;
    vector<int> dp(9, -1);
    cout << cutSteel_v2(steels, 8, dp) << endl;

    return 0;
}