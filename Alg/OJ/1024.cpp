#include <bits/stdc++.h>

using namespace std;

double optimal_bst(int N, const vector<double> &p, const vector<double> &q)
{
    vector<vector<double>> e(N + 2, vector<double>(N + 2, 0.0));
    vector<vector<double>> w(N + 2, vector<double>(N + 2, 0.0));

    for (int i = 1; i <= N + 1; ++i)
    {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    for (int len = 1; len <= N; ++len)
    {
        for (int i = 1; i <= N - len + 1; ++i)
        {
            int j = i + len - 1;
            e[i][j] = numeric_limits<double>::infinity();
            w[i][j] = w[i][j - 1] + p[j - 1] + q[j];
            for (int r = i; r <= j; ++r)
            {
                e[i][j] = min(e[i][j], e[i][r - 1] + e[r + 1][j] + w[i][j]);
            }
        }
    }

    return e[1][N];
}

int main()
{
    int M;
    cin >> M;
    cout << fixed << setprecision(6);

    while (M--)
    {
        int N;
        cin >> N;
        vector<int> keys(N);
        for (int &key : keys)
            cin >> key;

        vector<double> p(N), q(N + 1);
        double sum = 0;
        for (double &pi : p)
            cin >> pi;
        for (double &qi : q)
        {
            cin >> qi;
            sum += qi;
        }

        double result = optimal_bst(N, p, q);
        cout << result - sum << endl;
    }

    return 0;
}
