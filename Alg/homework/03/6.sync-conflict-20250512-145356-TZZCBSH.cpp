#include <bits/stdc++.h>
using namespace std;
#define int long long

int solve(double dollar)
{
    int ans = 0;
    int dollar_int = dollar * 100;
    int coins[] = {25, 10, 5, 1};
    for (int i = 0; i < 4; i++)
    {
        ans += dollar_int / coins[i];
        dollar_int %= coins[i];
    }
    return ans;
}

signed main()
{
    cout << solve(3.33) << endl;
    return 0;
}