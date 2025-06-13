/* 拦截导弹
 * http://10.201.1.112/problem.php?id=1009
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long

// 获取最长非增子序列
int getLongest(vector<int> a)
{
    int n = a.size();
    map<int, int> dp; // dp[i] 表示以 i 结尾的最长非增子序列的长度
    dp[a[0]] = 1;     // 初始化第一个元素
    for (int i = 1; i < n; i++)
    {
        int ans = 0;
        for (auto it : dp)
        {
            if (it.first >= a[i]) // 如果当前元素小于等于 dp 中的元素
            {
                ans = max(ans, it.second); // 更新最长非增子序列长度
            }
        }
        dp[a[i]] = ans + 1; // 更新以 a[i] 结尾的最长非增子序列长度
    }
    // 找到最长非增子序列的长度
    int maxLength = 0;
    for (auto it : dp)
    {
        maxLength = max(maxLength, it.second);
    }

    return maxLength; // 返回最长非增子序列的长度
}

signed main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int t;
        cin >> t;
        vector<int> a(t);
        for (auto &x : a)
            cin >> x;
        auto ans = getLongest(a);
        cout << ans << endl;
    }
}