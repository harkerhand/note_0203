#include <bits/stdc++.h>
using namespace std;
#define int long long
struct Activity
{
    int start, finish, value;
};

int getMaxValue(vector<Activity> &acts)
{
    sort(acts.begin(), acts.end(), [](Activity &a, Activity &b)
         { return a.finish < b.finish; });
    int n = acts.size();
    vector<int> dp(n, 0);
    vector<int> pre(n, -1);
    for (int i = 0; i < n; i++)
    {
        int left = 0, right = i - 1;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (acts[mid].finish <= acts[i].start)
            {
                if (acts[mid + 1].finish <= acts[i].start)
                    left = mid + 1;
                else
                {
                    pre[i] = mid;
                    break;
                }
            }
            else
                right = mid - 1;
        }
    }
    dp[0] = acts[0].value;
    for (int i = 1; i < n; i++)
    {
        dp[i] = max(dp[i - 1], acts[i].value);
        if (pre[i] != -1)
            dp[i] = max(dp[i], dp[pre[i]] + acts[i].value);
    }
    return dp[n - 1];
}

signed main()
{

    vector<Activity> activities = {
        {1, 3, 5}, {2, 5, 6}, {4, 6, 5}, {6, 7, 4}, {5, 8, 11}, {7, 9, 2}};
    // choose _1 _4 => 17
    cout << getMaxValue(activities) << endl;
    return 0;
}