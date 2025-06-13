#include <bits/stdc++.h>
using namespace std;
#define int long long

struct Matrix
{
    int row, col;
    Matrix(int r = 0, int c = 0) : row(r), col(c) {}
};

// 自底向上方法
vector<vector<int>> MatrixChainOrder_v1(vector<Matrix> &matrices)
{
    auto n = matrices.size();
    // dp[i][j] 表示从第i个矩阵到第j个矩阵的最小乘法次数
    vector<vector<int>> dp(n, vector<int>(n, 0ll));
    // x 表示矩阵链的长度
    for (auto x = 2; x <= n; ++x)
    {
        // i 表示矩阵链的起始位置
        for (auto i = 0; i + x - 1 < n; ++i)
        {
            // j 表示矩阵链的结束位置
            auto j = i + x - 1;
            dp[i][j] = LLONG_MAX;
            for (auto k = i; k < j; ++k)
            {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + matrices[i].row * matrices[k + 1].row * matrices[j].col);
            }
        }
    }
    return dp;
}

void solve()
{
    int n;
    cin >> n;
    vector<Matrix> matrices;
    for (int i = 0; i < n; ++i)
    {
        int a, b;
        cin >> a >> b;
        matrices.push_back(Matrix(a, b));
    }
    vector<vector<int>> dp = MatrixChainOrder_v1(matrices);
    cout << dp[0][matrices.size() - 1] << endl;
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}