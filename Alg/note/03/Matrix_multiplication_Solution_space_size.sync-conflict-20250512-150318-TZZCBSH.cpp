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
    auto dp = vector(n, vector(n, 0ll));
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
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + matrices[i].row * matrices[k].col * matrices[j].col);
            }
        }
    }
    return dp;
}

// 递归备忘录方法
void MatrixChainOrder_v2(vector<Matrix> &matrices, int i, int j, vector<vector<int>> &dp)
{
    // 递归终止条件
    if (i == j)
    {
        dp[i][j] = 0;
        return;
    }
    // 如果已经计算过，直接返回
    if (dp[i][j] != -1)
        return;
    dp[i][j] = LLONG_MAX;
    for (auto k = i; k < j; ++k)
    {
        // 递归计算左右两部分
        MatrixChainOrder_v2(matrices, i, k, dp);
        MatrixChainOrder_v2(matrices, k + 1, j, dp);
        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + matrices[i].row * matrices[k].col * matrices[j].col);
    }
}

signed main()
{
    vector<Matrix> matrices = {Matrix(10, 100), Matrix(100, 5), Matrix(5, 50)};
    auto dp = MatrixChainOrder_v1(matrices);
    cout << dp[0][matrices.size() - 1] << endl;
    vector<vector<int>> dp2(matrices.size(), vector<int>(matrices.size(), -1));
    MatrixChainOrder_v2(matrices, 0, matrices.size() - 1, dp2);
    cout << dp2[0][matrices.size() - 1] << endl;
    return 0;
}