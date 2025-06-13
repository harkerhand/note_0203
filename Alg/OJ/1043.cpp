#include <bits/stdc++.h>
using namespace std;
#define int long long

int superEggDrop(int K, int N)
{
    vector<vector<int>> dp(K + 1, vector<int>(N + 1, 0));
    int m = 0;
    while (dp[K][m] < N)
    {
        m++;
        for (int k = 1; k <= K; ++k)
        {
            //  dp[k][m - 1]: 鸡蛋没碎，还可以继续试。
            // dp[k - 1][m - 1]: 鸡蛋碎了，鸡蛋减1，楼层减到扔的楼层以下。
            // 加1是当前这层。
            dp[k][m] = dp[k][m - 1] + dp[k - 1][m - 1] + 1;
        }
    }
    return m;
}

signed main()
{
    int nums;
    cin >> nums;
    while (nums--)
    {
        int K, N;
        cin >> K >> N;
        cout << superEggDrop(K, N) << endl;
    }
    return 0;
}
