#include <bits/stdc++.h>
using namespace std;
#define int long long

int solve(vector<int> c, vector<int> y)
{
    int n = c.size();
    int cnt = 0;
    vector<int> need_product(y);
    for (int i = 0; i < n; i++)
    {
        int this_cnt = need_product[i] * c[i];
        for (int j = i + 1; j < n; j++)
        {
            if (c[i] + j - i < c[j])
            {
                this_cnt += need_product[j] * (c[i] + j - i);
                need_product[j] = 0;
            }
        }
        cnt += this_cnt;
    }
    return cnt;
}

signed main()
{
    vector<int> c = {2, 5, 3};
    vector<int> y = {2, 4, 5};
    cout << solve(c, y) << endl;
    return 0;
}