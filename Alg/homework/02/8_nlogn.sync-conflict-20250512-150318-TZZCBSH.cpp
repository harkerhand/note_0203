#include <bits/stdc++.h>
using namespace std;
#define int long long

int maxSubArray(vector<int> &nums)
{
    // 分治
    int n = nums.size();
    if (n == 1)
        return nums[0];
    int mid = n / 2;
    vector<int> left(nums.begin(), nums.begin() + mid);
    vector<int> right(nums.begin() + mid, nums.end());
    int left_max = maxSubArray(left);
    int right_max = maxSubArray(right);
    // 跨越中点的最大子序列
    int left_sum = INT_MIN;
    int right_sum = INT_MIN;
    int sum = 0;
    for (int i = mid - 1; i >= 0; i--)
    {
        sum += nums[i];
        left_sum = max(left_sum, sum);
    }
    sum = 0;
    for (int i = mid; i < n; i++)
    {
        sum += nums[i];
        right_sum = max(right_sum, sum);
    }
    int cross_max = left_sum + right_sum;
    return max(max(left_max, right_max), cross_max);
}

signed main()
{
    vector<int> nums = {0, -2, 3, 5, -1, 2};
    cout << maxSubArray(nums) << endl;

    return 0;
}