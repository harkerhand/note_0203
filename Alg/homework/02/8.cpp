#include <bits/stdc++.h>
using namespace std;
#define int long long

int maxSubArray(vector<int> &nums)
{
    int n = nums.size();
    int max_sum = INT_MIN;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += nums[i];
        max_sum = max(max_sum, sum);
        if (sum < 0)
            sum = 0;
    }
    return max_sum;
}

signed main()
{
    vector<int> nums = {0, -2, 3, 5, -1, 2};
    cout << maxSubArray(nums) << endl;
    return 0;
}