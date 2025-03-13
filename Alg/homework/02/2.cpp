#include <bits/stdc++.h>
using namespace std;
#define int long long

int minMaxSum(vector<int> &nums, int B)
{
    int N = nums.size();
    vector<int> dp(N + 1, 1e9 + 7);
    dp[0] = 0;
    dp[1] = nums[1];
    for (int i = 2; i <= N; i++)
    {
        int sum = 0, mx = 0;
        for (int j = i; j > 0; --j)
        {
            sum += nums[j - 1];
            mx = max(mx, nums[j - 1]);
            if (sum > B)
                break;
            dp[i] = min(dp[i], dp[j - 1] + mx);
        }
    }
    return dp[N];
}

signed main()
{
    vector<int> nums = {2, 2, 2, 8, 1, 8, 2, 1};
    int B = 17;
    cout << "min:" << minMaxSum(nums, B) << endl;
    return 0;
}